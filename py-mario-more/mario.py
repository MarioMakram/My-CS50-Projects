def main():
    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                break
        except ValueError:
            pass  

    for i in range(1, height + 1):
        print_spaces(height - i)
        print_hashes(i)
        print("  ", end="")
        print_hashes(i)
        print()

def print_hashes(n):
    for _ in range(n):
        print("#", end="")

def print_spaces(n):
    for _ in range(n):
        print(" ", end="")

main()