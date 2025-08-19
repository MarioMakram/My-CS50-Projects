from cs50 import get_float

def main():
    change = float(get_float("Change: "))
    while change < 0:
        change = float(get_float("Change: "))
    quarters = quarters_charges(change)
    change = round(change - quarters * .25, 2)
    dimes = dimes_charges(change)
    change = round(change - dimes * .10, 2)
    nickels = nickels_charges(change)
    change = round(change - nickels * .05, 2)
    pennies = pennies_charges(change)
    change = round(change - pennies * .01, 2)
    print(quarters + dimes + nickels + pennies)

def quarters_charges(change):
    q = 0
    while change >= .25:
        change -= .25
        q += 1
    return q
def dimes_charges(change):
    d = 0
    while change >= .10:
        change -= .10
        d += 1
    return d
def nickels_charges(change):
    n = 0
    while change >= .05:
        change -= .05
        n += 1
    return n
def pennies_charges(change):
    p = 0
    while change >= .01:
        change -= .01
        p += 1
    return p

main()
