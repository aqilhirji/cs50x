# imports the CS50 module 
import cs50

# main function, calls the 
def main(): 
	cc_raw = get_cc()
	if cc_raw == 0: 
		return 
	first_two_digs = first_two_cc(cc_raw)
	cc_type = check_type(first_two_digs)
	cc_check_pass = check_sum(cc_raw)
	if cc_check_pass == True: 
		print(cc_type)
	else: 
		print("INVALID")

# gets the credit card number, checks for length validity
def get_cc(): 
	print("Credit Card Number: ", end = "")
	cc = str(cs50.get_string())
	if len(cc) < 13 or len(cc) > 16 or len(cc) == 14: 
		print("INVALID")
		return 0
	return cc
# gets first two numbers of card
def first_two_cc(cc):
	cc_str = str(cc)
	first_two = str(cc_str[:2])
	return first_two

# Checks the CC Type based on first two digits
def check_type(first_two): 
	if (first_two == "34" or first_two == "37"): 
		return "AMEX" 
	elif (first_two == "51" or first_two == "52" or first_two == "53" or first_two == "54" or 
		first_two == "55"): 
		return "MASTERCARD"
	elif (first_two == "40" or first_two == "41" or first_two == "42" or first_two == "43" or
		first_two == "44" or first_two == "45" or first_two == "46" or first_two == "47" or
		first_two == "48" or first_two == "49"):
		return "VISA"
	else: 
		return "INVALID"

# Calculates the checksum and returnes True if Valid, False if Invalid
def check_sum(cc):
    nums = reversed(list(map(int, str(cc))))
    doubled = (ele * 2 if ind % 2 else ele for ind, ele in enumerate(nums))
    return not sum(sum(map(int, str(ele))) for ele in doubled) % 10

# Calls the main function
if __name__ == "__main__":
    main()