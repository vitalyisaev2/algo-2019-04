from enum import Enum, IntFlag
from typing import List


class Color(Enum):
    UNSET = 0
    WHITE = 1
    BLACK = 2

    @staticmethod
    def from_str(src: str):
        if src.islower():
            return Color.BLACK
        elif src.isupper():
            return Color.WHITE
        else:
            raise ValueError("Unknown color code: {}".format(src))

    def colorize(self, char: str) -> str:
        if self == Color.BLACK:
            return char.lower()
        elif self == Color.WHITE:
            return char.upper()
        else:
            raise ValueError("Cannot serialize to string unmarked cell")


class Figure(Enum):
    EMPTY = 0
    PAWN = 1
    BISHOP = 2
    KNIGHT = 3
    ROOK = 4
    QUEEN = 5
    KING = 6

    @staticmethod
    def from_str(src: str):
        src = src.lower()
        if src == 'p':
            return Figure.PAWN
        elif src == 'b':
            return Figure.BISHOP
        elif src == 'n':
            return Figure.KNIGHT
        elif src == 'r':
            return Figure.ROOK
        elif src == 'q':
            return Figure.QUEEN
        elif src == 'k':
            return Figure.KING
        else:
            raise ValueError("Unknown figure code: {}".format(src))

    def __str__(self):
        if self == Figure.PAWN:
            return "p"
        elif self == Figure.BISHOP:
            return "b"
        elif self == Figure.KNIGHT:
            return "n"
        elif self == Figure.ROOK:
            return "r"
        elif self == Figure.QUEEN:
            return "q"
        elif self == Figure.KING:
            return "k"
        else:
            raise ValueError("Cannot serialize to string {}".format(self))


class Cell(object):
    color: Color
    figure: Figure

    def __init__(self, color: Color = Color.UNSET, figure: Figure = Figure.EMPTY):
        self.color = color
        self.figure = figure

    def __str__(self):
        return self.color.colorize(str(self.figure))


class Line:
    cells: List[Cell]

    def __init__(self, src: str):

        self.cells = []

        for c in src:
            if c.isdigit():
                empty = int(c)
                while empty > 0:
                    self.cells.append(Cell())
                    empty -= 1
            else:
                cell = Cell(color=Color.from_str(c), figure=Figure.from_str(c))
                self.cells.append(cell)

    def __str__(self):
        result = ""
        empty = 0
        for cell in self.cells:
            if cell.color == Color.UNSET:
                empty += 1
            else:
                if empty != 0:
                    result += str(empty)
                    empty = 0
                result += str(cell)
        if empty != 0:
            result += str(empty)
            empty = 0
        return result


class Position:
    lines: List[Line]

    def __init__(self, src: str):
        self.lines = []
        for part in src.split('/'):
            line = Line(part)
            self.lines.append(line)

    def __str__(self):
        return "/".join(str(line) for line in self.lines)


class CastlingDirection(IntFlag):
    NOWHERE = 0
    KINGSIDE = 1
    QUEENSIDE = 2

    @staticmethod
    def from_str(src: str):
        src = src.lower()
        if src == "k":
            return CastlingDirection.KINGSIDE
        elif src == "q":
            return CastlingDirection.QUEENSIDE
        else:
            raise ValueError("Unknown castling direction: {}".format(src))

    def __str__(self):
        result = ""
        if self == CastlingDirection.NOWHERE:
            pass
        if self & CastlingDirection.KINGSIDE == CastlingDirection.KINGSIDE:
            result += "k"
        if self & CastlingDirection.QUEENSIDE == CastlingDirection.QUEENSIDE:
            result += "q"
        return result


class Castling:
    white: CastlingDirection
    black: CastlingDirection

    def __init__(self, src: str):
        self.white = CastlingDirection.NOWHERE
        self.black = CastlingDirection.NOWHERE
        if src == "-":
            return

        for c in src:
            if c.isupper():
                self.white |= CastlingDirection.from_str(c)
            elif c.islower():
                self.black |= CastlingDirection.from_str(c)
            else:
                raise ValueError("Unknown castling value: {}".format(c))

    def __str__(self):
        white, black = str(self.white), str(self.black)
        if white == "" and black == "":
            return "-"
        else:
            return Color.WHITE.colorize(white) + Color.BLACK.colorize(black)


class Record:
    position: Position
    activeColor: Color
    pass
