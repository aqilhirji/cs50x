### CS50X 2017 ###
### Aqil Hirji ###
### PSET 7 ###
### Not to PEP 8 Style ###
### Custom Tweak - randomly pass or fail to add money to acct from index ###
### Skeleton File From CS50  Staff ###

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp
import time
import random

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    # return all rows of the user's stock, by symbol, avg share price, alphabetical order
    holding_details = db.execute("SELECT symbol, sum(purchase_price_per_share * number)*1.0/(sum(number))*1.0 as avg_purchase_price, sum(number) as num_shares_held FROM owned_shares WHERE user_id = :user_id GROUP BY symbol ORDER BY symbol ASC;", user_id=session["user_id"])
    cash_on_hand = usd((db.execute("SELECT cash FROM users WHERE id = :user_id;", user_id=session["user_id"] )[0])['cash'])
    # counter values for profit (loss)
    open_profit_loss = float(0)
    holding_total_value = float(0)
    # check to see if they hold stocks
    if holding_details != []:
        stocks = []

        #for each stock holding calculate value and cash paid and rolling profit/loss
        for holding in holding_details:
            if holding["num_shares_held"] == 0:
                holding_details.remove(holding)
            else:
                stock_price = lookup(holding['symbol'])
                holding["value"] = stock_price["price"]
                holding["holding_profit_loss"] = (holding["value"] - (holding["avg_purchase_price"]))*1.0*holding["num_shares_held"]
                open_profit_loss = open_profit_loss + (holding["value"] - holding["avg_purchase_price"])*1.0*holding["num_shares_held"]
                holding_total_value = holding_total_value + 1.0*(holding["value"] * holding["num_shares_held"])
                holding["value"] = usd(holding["value"])
                holding["avg_purchase_price"] = usd(float(holding["avg_purchase_price"]))
                holding["holding_profit_loss"] = usd(holding["holding_profit_loss"])
    # if no stocks held then pass
    else:
        pass
    #convert open profit and loss calculation to USD format for output
    open_profit_loss = usd(open_profit_loss)
    holding_total_value = usd(holding_total_value)

    return render_template("index.html", holdingDetails = holding_details, cashOnHand = cash_on_hand, openProfitLoss = open_profit_loss, holdingTotalValue = holding_total_value)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    if request.method == "POST":

        # check if submitted
        if not request.form.get("symbol"):
            return apology("Enter Symbol")

        # use lookup to return stock value
        stk = lookup((request.form.get("symbol")))
        numShares = (request.form.get("shares"))

        if not stk:
            return apology("Invalid symbol")

        # check from https://stackoverflow.com/questions/26198131/check-if-input-is-positive-integer
        while True:
            try:
                val = int(numShares)
                if val < 0:  # if not a positive int print message and ask for input again
                    return apology("Must enter positive integer for number of shares")
                    continue
                break
            except ValueError:
                return apology("Must enter positive integer for number of shares")

        # calculate cost of shares
        costShares = stk["price"] * int(numShares)
        moneyInAcct = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])

        # check for enough $$
        if float(moneyInAcct[0]['cash']) >= costShares:
            moneyAfterPurchase = float(moneyInAcct[0]['cash']) - costShares
            db.execute("INSERT INTO owned_shares (user_id, symbol, purchase_price_per_share, number) VALUES (:user_id, :symbol, :purchase_price_per_share, :number);", user_id=session["user_id"], symbol=stk["symbol"], purchase_price_per_share=stk["price"], number=int(numShares))
            db.execute("UPDATE users SET cash = :money_after WHERE id = :user_id;", money_after = moneyAfterPurchase, user_id=session["user_id"])
            return render_template("bought.html", numShares = int(numShares), stock = stk)

        else:
            return apology("Not enough $$$$$")

    elif request.method == "GET":
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
     # return all rows of the user's stock, by symbol, avg share price, alphabetical order
    transaction_history = db.execute("SELECT * FROM owned_shares WHERE user_id = :user_id ORDER BY purchase_created DESC;", user_id=session["user_id"])
    # counter values for profit (loss)
    # check to see if they hold stocks
    if transaction_history != []:
        stocks = []

        #for each stock calculate value and cash paid and rolling profit/loss
        for transaction in transaction_history:
            transaction["transaction_value"] = abs(transaction["number"])*1.0*transaction["purchase_price_per_share"]
            transaction["shares_transacted"] = int(abs(transaction["number"]))
            # record transaction type based on number of shares
            if transaction["number"] < 0:
                transaction["type"] = "BOUGHT"
            else:
                transaction["type"] = "SOLD"
            transaction["purchase_price_per_share"] = usd(transaction["purchase_price_per_share"])
            transaction["transaction_value"] = usd(transaction["transaction_value"])
    # if no stocks held then pass
    else:
        pass

    return render_template("history.html", transactionHistory = transaction_history)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        # check if submitted
        if not request.form.get("symbol"):
            return apology("Enter Symbol")

        # use lookup to return stock value
        stk = lookup((request.form.get("symbol")))

        if not stk:
            return apology("Invalid symbol")

        # render quote in template
        return render_template("quoted.html", stock = stk)

    elif request.method == "GET":
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure confirm password was submitted
        elif not request.form.get("confirm_password"):
            return apology("must provide password confirmation")

        # query database for username
        u_chk = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username not duplicate
        if len(u_chk) != 0:
            return apology("username already in use")

        # check passwords match
        if request.form.get("password") != request.form.get("confirm_password"):
            return apology("passwords must match")

        else:
        # insert user into database
            db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)", username=request.form["username"], hash=pwd_context.hash(request.form["password"]))

        # redirect user to home page
        return redirect(url_for("registered"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    if request.method == "POST":

        # check if submitted
        if not request.form.get("symbol"):
            return apology("Enter Symbol")

        # use lookup to return stock value from db
        stk = lookup((request.form.get("symbol")))
        num_shares_to_sell = (request.form.get("shares"))

        if not stk:
            return apology("Invalid symbol")

        # check positive int from https://stackoverflow.com/questions/26198131/check-if-input-is-positive-integer
        while True:
            try:
                val = int(num_shares_to_sell)
                if val < 0:  # if not a positive int print message and ask for input again
                    return apology("Must enter positive integer for number of shares")
                    continue
                break
            except ValueError:
                return apology("Must enter positive integer for number of shares")

        # check that they're selling more than 1 share
        num_shares_to_sell = int(num_shares_to_sell)
        if num_shares_to_sell <= 0:
            return apology("Have to at least sell 1 share...")

        # check the number of shares that the user has
        num_shares_owned = db.execute("SELECT sum(number) as owned_shares FROM owned_shares WHERE user_id = :user_id AND symbol = :symbol  ;", user_id = session["user_id"], symbol = stk["symbol"])
        num_shares_owned = int(num_shares_owned[0]["owned_shares"])

        #check if the number the user wants is more or less than owned
        if not ((num_shares_owned >= num_shares_to_sell) and int(num_shares_owned) > 0):
            return apology("Not enough shares, you can't scam us!")

        # calculate sale value of shares
        sale_value_shares = stk["price"] * int(num_shares_to_sell)
        moneyInAcct = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"])
        num_shares_subtracted = -num_shares_to_sell

        moneyAfterSale = float(moneyInAcct[0]['cash']) + (num_shares_to_sell * stk["price"])*1.0
        db.execute("INSERT INTO owned_shares (user_id, symbol, purchase_price_per_share, number) VALUES (:user_id, :symbol, :purchase_price_per_share, :number);", user_id=session["user_id"], symbol=stk["symbol"], purchase_price_per_share=stk["price"], number=int(num_shares_subtracted))
        db.execute("UPDATE users SET cash = :money_after WHERE id = :user_id;", money_after = moneyAfterSale, user_id=session["user_id"])
        return render_template("sold.html", numShares = int(num_shares_to_sell), stock = stk)


    elif request.method == "GET":
        return render_template("sell.html")

@app.route("/registered", methods=["GET", "POST"])
def registered():
    return success()

@app.route("/cashinjection", methods=["GET", "POST"])
def cashinjection():
    """Randomly Decide Yes or No For Cash Injection"""
    #get how much cash user wants from form check if b/w 1 and 50000
    additional_cash = int(request.form.get("cash"))
    if additional_cash > 50000 or additional_cash < 0:
        return apology("Must ask for $1 to $50000")
    else:
        pass

    # Randomly generate true or false to see if the user gets the money
    if bool(random.getrandbits(1)) == True:
        current_cash = (float((db.execute("SELECT cash FROM users WHERE id = :user_id;", user_id=session["user_id"] )[0])['cash']))
        cash_infusion = current_cash + (additional_cash)
        db.execute("UPDATE users SET cash = :cash_infusion WHERE id = :user_id;", cash_infusion = cash_infusion, user_id = session["user_id"])
        #return render_template("cashinfusion.html", additionalCash = usd(additional_cash), cashInfusion = usd(cash_infusion))
    # Return apology if unlucky
    #else:
        #return apology("Better luck next time")
