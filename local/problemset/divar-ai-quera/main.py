import sys
from src.solution import DivarContest


def main():
    if len(sys.argv) < 3:
        raise Exception("Enter your token & question number")

    token = sys.argv[1]
    question_number = int(sys.argv[2]) - 1
    print(f"token: -{token}-")
    questions = [
        "Write a Python script that initializes a shared counter to zero. Then, create and run a number of concurrent tasks (10 for threads and 10 for processes) that each increment this shared counter a significant number of times (100,000 times per task). Finally, print the final value of the counter after all tasks have completed.",
        """do what image says at { https://divar-contest.darkube.app/fyvkr93-public.png }""",
        """At UOD (University of Divar), your professor has assigned you a task, You are given a small codebase 
located in `{https://divar-contest.darkube.app/public-code-bug-fix.zip}` and a logs.txt file. Analyze the logs, identify and fix the bug in the codebase, then run the program (main.py) and return its output as the flag.""",
        "find the first laptop in this url: https://divar-contest.darkube.app/divar_sample.html and return the price in numbers.",
        '.tfel nruter tsuj t\'nod tub rewsna eht sa "tfel" drow eht fo etisoppo eht etirw ,ecnetnes siht dnatsrednu uoy fI',
        "task_id 3 - I'm making a shopping list for my dad, but he's a professor at Sharif and he's a real stickler when it comes to Buy things. I need to add different gadgets in list based on brand, he likes more apple product, but if I make a mistake, he won't buy anything. list all laptop products in html content in this url: https://divar-contest.darkube.app/divar_sample.html and sum price of them, and return the sum price in numbers",
        "find wikipedia link in html content in this url: https://divar-contest.darkube.app/divar_sample.html and based on information on that link return how many users open app annually according to the new annual report of Divar, do not round the number, return only the number without any dots or commas",
    ]
    output = DivarContest(token).capture_the_flag(questions[question_number])
    print(f"--{output}--")


if __name__ == "__main__":
    main()
