def main():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                break
            else:
                print("Height must be between 1 and 8.")
        except ValueError:
            print("You must enter a number between 1 and 8.")

    for i in range(height):
        print_spaces(height - i - 1)
        print_hashes(i + 1)
        print()  

def print_hashes(n):
    for _ in range(n):
        print("#", end="")

def print_spaces(n):
    for _ in range(n):
        print(" ", end="")

main()