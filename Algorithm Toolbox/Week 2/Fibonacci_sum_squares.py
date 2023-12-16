# Uses python3

import sys

def fibonacci_huge_mod(n, m):
    if n <= 1:
        return n

    remainders = [0, 1]

    period = 0

    for i in range(2, 6*m + 2):
        remainders.append((remainders[i - 1] + remainders[i - 2]) % m)
        period += 1
        if remainders[i - 1] == 0 and remainders[i] == 1:
            break

    return remainders[n % period]


def fibonacci_sum_squares_last_digit(n):
    fn1_ld = fibonacci_huge_mod(n, 10)
    fn2_ld = fibonacci_huge_mod(n-1, 10)

    sum_Squares_ld = fn1_ld * (fn1_ld + fn2_ld) % 10
    return sum_Squares_ld


if __name__ == '__main__':
    n = int(sys.stdin.read())
    print(fibonacci_sum_squares_last_digit(n))