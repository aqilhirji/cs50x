# Import the cs50 python module
import cs50


# Main function to generate output
def main(): 
	print("What's the pyramid height?")
	i = get_mario_int()
	for j in range (i):
		print_pyramid(j, i)


# Function to print each pyramid line
def print_pyramid(m, n):
    print(" " * (n - m - 1), end = "")
    print("#" * (m + 1), end = "")
    print("  ", end = "")
    print("#" * (m + 1))

# Function to get the integer within Mario spec
def get_mario_int(): 
	while True: 
		n = cs50.get_int()
		if (n > 0 and n <= 23):
			break
		print("Pyramid height must be a positive integer less than 24")
		print("What's the pyramid height?")
	return n

# Calls the main function
if __name__ == "__main__":
    main()