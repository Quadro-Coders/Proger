import random
import time

def main():
    print("\n============================\n"
          "This program generates <n> random words with generator's seed <seed>\n"
          "from <min length> to <max length>, from <min ascii> to <max ascii>\n"
          "and writes it into <filename>;\n"
          "if generator's seed equals to 0, then seed is current time\n"
          "============================\n")

    try:
        # Фикс: строка теперь в одной линии или корректно продолжена через \
        n, min_length, max_length, min_ascii, max_ascii, seed = \
            map(int, input("Input:\n<n> <min length> <max length> <min ascii> <max ascii> <seed>\n").split())
    except ValueError:
        print("Ошибка: введите 6 целых чисел через пробел.")
        return

    if max_length < min_length or max_ascii < min_ascii:
        print("<max length> должно быть >= <min length>\n"
              "<max ascii> должно быть >= <min ascii>\n")
        exit(1)

    if (max_length < 1 or min_length < 1 or n < 1 or
        min_ascii < 32 or max_ascii < 32 or min_ascii > 126 or max_ascii > 126):
        print("all numbers should be greater than 0;\n"
              "<max ascii> and <min ascii> should be less than 127 and greater than 31;\n")
        exit(1)

    if seed == 0:
        random.seed(time.time())
    else:
        random.seed(seed)

    if n > 5000000:
        print("n > 5000000, exit\n")
        exit(1)
    elif n >= 1000000:
        res = input(f"n={n}, press <Y> to continue\n")
        if res != "Y":
            exit(1)

    filename = input("Input <filename>:\n")
    with open(filename, 'w', encoding='utf-8') as f:
        for _ in range(n):
            word_len = random.randint(min_length, max_length)
            word = ''
            for _ in range(word_len):
                word += chr(random.randint(min_ascii, max_ascii))
            f.write(word + '\n')
    print("Done\n")

if __name__ == "__main__":
    main()
