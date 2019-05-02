#!/usr/bin/env python
import sys

def main():
    dividend = int(sys.argv[1])
    dividor = int(sys.argv[2])
    quotient = 0
    remainder = 0

    while True:
        if dividend == 0:
            break
        if dividend < dividor:
            remainder = dividend
            break
        dividend -= dividor
        quotient+= 1

    print(quotient, remainder)

if __name__ == "__main__":
    main()
