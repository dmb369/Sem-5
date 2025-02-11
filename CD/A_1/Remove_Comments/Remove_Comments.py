# Name: Dev M. Bandhiya
# Roll No.: SE22UCSE078
# Section: CSE1

import re

def remove_comments(input_file, output_file):
    # Reading the contents of the input file
    with open(input_file, 'r') as file:
        program_code = file.read()

    # Pattern to identify comments for single-line and multi-line
    comment_pattern = r'//.*?$|/\*.*?\*/'

    # Removing the comments
    code_without_comments = re.sub(comment_pattern, '', program_code, flags=re.DOTALL | re.MULTILINE)

    # Writing the cleaned code to the output file
    with open(output_file, 'w') as file:
        file.write(code_without_comments)

input_file = input("Enter the name of the input C program file: ")
output_file = input("Enter the name of the output file: ")

remove_comments(input_file, output_file)
print(f"Comments have been removed and saved to {output_file}.")
   