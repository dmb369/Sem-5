# Name: Dev M. Bandhiya
# Roll No.: SE22UCSE078
# Section: CSE1

import re

# List of C keywords
keywords = [
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void",
    "volatile", "while", "_Bool", "_Complex", "_Imaginary"
]

# List of punctuation characters
punctuation = [
    "!", "#", "$", "%", "&", "'", "(", ")", "*", "+", ",", "-", 
    ".", "/", ":", ";", "?", "[", "\\", "]", "^", "_", "`", 
    "{", "|", "}", "~"
]

# List of C operators
operators = [
    "+", "-", "*", "/", "%", "==", "!=", ">", "<", ">=", "<=",
    "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "=", "+=",
    "-=", "*=", "/=", "%=", "<<=", ">>=", "&=", "^=", "|=", "++",
    "--", "?:"
]

# Regular expression patterns for identifiers and constants
identifier_pattern = r'^[a-zA-Z_][a-zA-Z0-9_]*$'
constant_pattern = r'\b0[xX][0-9a-fA-F]+\b|(\b\d+(\.\d*)?([eE][+-]?\d+)?\b)|\'([^\\\'\n\r\t\b\f\v]|\\[nrt\'\"\\])\'|\"([^\\\"\n\r\t\b\f\v]|\\.)*\"'


user_input = input("Enter a string to classify: ").strip()

# Keywords
if user_input in keywords:
    print(f"'{user_input}' is a Keyword in C.")

# Punctuation character
elif user_input in punctuation:
    print(f"'{user_input}' is a Punctuation in C.")

# Operator
elif user_input in operators:
    print(f"'{user_input}' is an Operator in C.")

# Identifier
elif re.match(identifier_pattern, user_input) and user_input not in keywords:
    print(f"'{user_input}' is an Identifier in C.")

# Constant
elif re.match(constant_pattern, user_input):
    print(f"'{user_input}' is a Constant in C.")

# Not a Token
else:
    print(f"'{user_input}' does not match any known C language tokens.")
