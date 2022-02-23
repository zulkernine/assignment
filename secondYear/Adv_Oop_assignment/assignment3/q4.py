import re

def isValid(s):
    pattern = re.compile("(0/91)?[7-9][0-9]{9}")
    return pattern.match(s)

str = input("Phone number: ")

print("Valid number" if isValid(str) else "Invalid number")
