from flask import Flask, redirect, render_template, request, url_for

import sys
import os
import helpers
import math
from analyzer import Analyzer

app = Flask(__name__)

@app.route("/")
def index():
	return render_template("index.html")

@app.route("/search")
def search():

	# validate screen_name
	screen_name = request.args.get("screen_name", "")
	if not screen_name:
		return redirect(url_for("index"))

	# get screen_name's tweets
	tweets = helpers.get_user_timeline(screen_name, 100)

	positives = os.path.join(sys.path[0], "positive-words.txt")
	negatives = os.path.join(sys.path[0], "negative-words.txt")
	
	tweet_analyzer = Analyzer(positives, negatives)
	
	if tweets == "": 
		print('User is private, user has no tweets, or username is incorrect')
		return 0
	
	# initialize positive, negative, and neutral as 0 value
	positive, negative, neutral = 0.0, 0.0, 0.0
	
	# reassign percentages
	for tweet in tweets: 
		score = tweet_analyzer.analyze(tweet)
		if score > 0: 
			positive += 1
		elif score < 0:
			negative += 1
		else: 
			neutral += 1
			
		total_tweets = positive + negative + neutral
		# account for cases where less than 100 tweets
		positive = (positive)/(total_tweets)*100.0
		negative = (negative)/(total_tweets)*100.0
		neutral = (neutral)/(total_tweets)*100.0

	# generate chart
	chart = helpers.chart(positive, negative, neutral)

	# render results
	return render_template("search.html", chart=chart, screen_name=screen_name)
	