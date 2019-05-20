#!/usr/bin/python3

import sys

def genMask(centerID):
    center = 1 << centerID
    disposition = (center >> 17) | (center >> 15) | (center >> 10) | (center >> 6) | \
                  (center << 6) | (center << 10) | (center << 15) | (center << 17)
    mask = 2 ** 64 - 1
    return disposition & mask

if __name__ == "__main__":
    value = int(sys.argv[1])
    print(genMask(value))
