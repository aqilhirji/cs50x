# Import cs50 module
import cs50 
# Import sys module
import sys 
# Import crypt module
import crypt

# Main Function with salt pre-defined, calls guess_and_check() to guess and check
def main():
	if len(sys.argv) != 2:
		print("Usage: crack.py hashed_password")
		return 1

	salt = '50'
	hashed_string = sys.argv[1]
	# Empty Symbol array 
	symbol_sub = [0] * 52
	password_guess = ""
	# Upper Case Sym Offset
	upper_case_val = 65
	# Lower Case Sym Offset
	lower_case_val = 97
	# creates an array of all characters a-zA-Z
	for i in range(52): 
		symbol_sub[i] = chr(lower_case_val + i)
		if i > 25: 
			symbol_sub[i] = chr(upper_case_val + i - 26)
	# Checks 1 Char 
	for j in range(52): 
		password_g_1 = symbol_sub[j]
		guess_and_check(password_g_1, salt, hashed_string)
		
		# Checks 2 Char
		for k in range(52): 
			add_1 = symbol_sub[k]
			password_g_2 = password_g_1 + add_1
			guess_and_check(password_g_2, salt, hashed_string)
			
			# Checks 3 Char
			for l in range(52): 
				add_2 = symbol_sub[l]
				password_g_3 = password_g_2 + add_2
				guess_and_check(password_g_3, salt, hashed_string)
				
				# Checks 4 Char 
				for m in range(52): 
					add_3 = symbol_sub[m]
					password_g_4 = password_g_3 + add_3
					guess_and_check(password_g_4, salt, hashed_string)
	# Prints not solvable with the program if if fails to find a solution
	print("Not Solvable With This Program")
	return 0
	
# Guess and check function, takes guess, salt, and expected output as arguments
def guess_and_check(password_guess, salt, hashed_string):
	# Crypt function from crypt module hashes the guess
	hashed_guess = crypt.crypt(password_guess, salt)
	if hashed_string == hashed_guess: 
		print(password_guess)
		sys.exit()

# Code to call the main function from the command line when file loaded 
if __name__ == "__main__":
	main()