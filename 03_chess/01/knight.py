#!/usr/bin/python3

import sys

border = 2 ** 64 - 1
noA = 0xfefefefefefefefe
noAB = 0xfcfcfcfcfcfcfcfc
noH = 0x7f7f7f7f7f7f7f7f
noGH = 0x3f3f3f3f3f3f3f3f

def buildKnightMask(centerID):
    """
    >>> buildKnightMask(0)
    132096L
    >>> buildKnightMask(30)
    175990581010432L
    >>> buildKnightMask(63)
    9077567998918656L
    """
    center = 1 << centerID
    disposition = (center >> 17) | (center >> 15) | (center >> 10) | (center >> 6) | \
                  (center << 6) | (center << 10) | (center << 15) | (center << 17)
    residual = centerID % 8
    if residual == 0:
        disposition &= noGH
    elif residual == 1:
        disposition &= noH
    elif residual == 6:
        disposition &= noA
    elif residual == 7:
        disposition &= noAB

    return disposition & border

def getNumberOfMoves(mask):
    """
    >>> getNumberOfMoves(22667534005174272)
    8
    >>> getNumberOfMoves(132096)
    2
    """
    count = 0
    while mask != 0:
        mask &= (mask - 1)
        count += 1
    return count

if __name__ == "__main__":
    centerID = int(sys.argv[1])
    mask = buildKnightMask(centerID)
    moves = getNumberOfMoves(mask)
    print(moves)
    print(mask)
