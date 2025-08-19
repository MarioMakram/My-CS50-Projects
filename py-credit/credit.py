from cs50 import get_int
import re


def luhn_check(number):
    reversed_number = number[::-1]
    total = 0

    for i in range(len(reversed_number)):
        digit = int(reversed_number[i])
        if i % 2 == 1: # Even Numbers
            digit *= 2
            if digit > 9:
                digit -= 9
        total += digit

    return total % 10 == 0

def cardCheck(number):
    length = len(number)

    if luhn_check(number):
        if length == 15 and re.match("^3[47]", number):
            print("AMEX")
        elif length == 16 and re.match("^5[1-5]", number):
            print("MasterCard")
        elif length in [13, 16] and re.match("^4", number):
            print("Visa")
        else:
            print("INVALID")
    else:
        print("INVALID")


cardnumber = str(get_int("Number: "))
# number = input("Number: ")
cardCheck(cardnumber)