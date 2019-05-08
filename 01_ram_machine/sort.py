#!/usr/bin/env python
import sys

def main():
    n = int(sys.argv[1])
    array = []
    r = 0
    while r < n:
        array.append(sys.argv[r+2])
        r += 1

    i = 0
    k = 0
    while i < n:
        k = i
        while k < n:
            if array[i] > array[k]:
                array[i], array[k] = array[k], array[i]
            k += 1
        i += 1

    print(array)


if __name__ == "__main__":
    main()
