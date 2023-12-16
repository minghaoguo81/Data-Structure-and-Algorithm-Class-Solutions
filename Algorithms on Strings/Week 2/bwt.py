# python3
import sys

def bwt(input):
    result = ''
    bwt_strings = []
    bwt_strings.append(input)

    for index in range(1, len(input)):
        temp_text = input[index:] + input[:index]
        bwt_strings.append(temp_text)

    bwt_strings.sort()

    for string in bwt_strings:
        result += string[-1]

    return result

if __name__ == '__main__':
    input = sys.stdin.readline().strip()
    print(bwt(input))