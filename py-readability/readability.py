from cs50 import get_string

def main():
    text = get_string("Text: ")
    index = coleman_liau(text)
    print_grade(index)

def coleman_liau(text):
    letters = sum(1 for c in text if c.isalpha())
    words = len(text.split())
    sentences = sum(1 for c in text if c in [".", "!", "?"])

    # Compute the Coleman-Liau index
    L = (letters / words) * 100
    S = (sentences / words) * 100
    return 0.0588 * L - 0.296 * S - 15.8

def print_grade(index):
    grade = round(index)
    if grade < 1:
        print("Before Grade 1")
    elif grade > 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")

main()
