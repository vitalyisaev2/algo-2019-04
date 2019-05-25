from enum import Enum
from typing import List

class Color(Enum):
    UNSET = 0
    WHITE = 1
    BLACK = 2

    @staticmethod
    def from_str(input: str):
        if input.islower():
            return Color.WHITE
        elif input.isupper():
            return Color.BLACK
        else:
            raise "Unknown color code: {}".format(input)


class Figure(Enum):
    EMPTY = 0
    PAWN = 1
    BISHOP = 2
    KNIGHT = 3
    ROOK = 4
    QUEEN = 5
    KING = 6

    @staticmethod
    def from_str(input: str):
        input = input.lower()
        if input == 'p':
            return Figure.PAWN
        elif input == 'b':
            return Figure.BISHOP
        elif input == 'n':
            return Figure.KNIGHT
        elif input == 'r':
            return Figure.ROOK
        elif input == 'q':
            return Figure.QUEEN
        elif input == 'k':
            return Figure.KING
        else:
            raise "Unknown figure code: {}".format(input)

    def to_string(self) -> str:
        if input == Figure.PAWN:
            return "p"
        elif input == Figure.BISHOP:
            return "b"
        elif input == Figure.KNIGHT:
            return "n"
        elif input  == Figure.ROOK:
            return "r"
        elif input == Figure.QUEEN:
            return "q"
        elif input == Figure.KING:
            return "k"
        else:
            raise "Cannot serialize to string {}".format(self)


class Cell(Enum):
    color: Color
    figure: Figure

    def __init__(self, color: Color = color.UNSET, figure: Figure = figure.EMPTY):
        self.color = color
        self.figure = figure

    def __str__(self):
        letter = self.figure.to_string()
        if self.color == Color.WHITE:
            letter = letter.upper()
        return letter


class Line:
    cells: List[Cell]

    def __init__(self, input: str):
        pass

class Board:
    pass


class Record:
    pass
