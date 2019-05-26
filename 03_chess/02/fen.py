from enum import Enum, IntFlag
from typing import List


class Color(Enum):
    UNSET = 0
    WHITE = 1
    BLACK = 2

    @staticmethod
    def from_str(src: str):
        if src == "b":
            return Color.BLACK
        if src == "w":
            return Color.WHITE
        raise ValueError("Cannot build color from value {}".format(src))

    @staticmethod
    def from_case(src: str):
        if src.islower():
            return Color.BLACK
        if src.isupper():
            return Color.WHITE
        raise ValueError("Unknown color code: {}".format(src))

    def colorize(self, char: chr) -> str:
        if self == Color.BLACK:
            return char.lower()
        if self == Color.WHITE:
            return char.upper()
        return char

    def __str__(self):
        if self == Color.BLACK:
            return "b"
        if self == Color.WHITE:
            return "w"
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
        if src == 'b':
            return Figure.BISHOP
        if src == 'n':
            return Figure.KNIGHT
        if src == 'r':
            return Figure.ROOK
        if src == 'q':
            return Figure.QUEEN
        if src == 'k':
            return Figure.KING
        raise ValueError("Unknown figure code: {}".format(src))

    def __str__(self):
        if self == Figure.EMPTY:
            return "."
        if self == Figure.PAWN:
            return "p"
        if self == Figure.BISHOP:
            return "b"
        if self == Figure.KNIGHT:
            return "n"
        if self == Figure.ROOK:
            return "r"
        if self == Figure.QUEEN:
            return "q"
        if self == Figure.KING:
            return "k"
        raise ValueError("Cannot serialize Figure value to string")


class Coordinates:
    row: int
    column: chr

    def __init__(self, row: int, column: chr):
        self.row = row
        self.column = column

    @staticmethod
    def from_int_pair(row: int, column: int):
        return Coordinates(row, chr(ord('a') + column))

    def __str__(self):
        return str(self.row) + str(self.column)


class Cell:
    color: Color
    figure: Figure

    def __init__(self, coordinates: Coordinates, color: Color = Color.UNSET, figure: Figure = Figure.EMPTY):
        self.color = color
        self.figure = figure
        self.coordinates = coordinates

    def __str__(self):
        return self.color.colorize(str(self.figure))


class Line:
    cells: List[Cell]
    row: int

    def __init__(self, row: int, src: str):

        self.row = row
        self.cells = []

        for c in src:
            if c.isdigit():
                empty = int(c)
                while empty > 0:
                    coordinates = Coordinates.from_int_pair(
                        self.row, len(self.cells))
                    cell = Cell(coordinates)
                    self.cells.append(cell)
                    empty -= 1
            else:
                coordinates = Coordinates.from_int_pair(
                    self.row, len(self.cells))
                cell = Cell(
                    coordinates=coordinates,
                    color=Color.from_case(c),
                    figure=Figure.from_str(c),
                )
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
            line = Line(row=8-len(self.lines), src=part)
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
        if src == "q":
            return CastlingDirection.QUEENSIDE
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
        return Color.WHITE.colorize(white) + Color.BLACK.colorize(black)


class EnPassant:
    coordinates: Coordinates

    def __init__(self, src: str):
        if src == "-":
            self.coordinates = None
        elif len(src) == 2:
            column, row = src[0], int(src[1])
            self.coordinates = Coordinates(row, column)
        else:
            raise ValueError("Unknown EnPassant value: {}".format(src))

    def __str__(self):
        if self.coordinates is None:
            return "-"
        return str(self.coordinates)


class Record:
    position: Position
    active_color: Color
    castling: Castling
    en_passant: EnPassant
    halfmoves: int
    fullmoves: int

    def __init__(self, src: str):
        split = src.split(" ")
        if len(split) != 6:
            raise ValueError(
                "Unexpected format for FEN record: {}".format(src))

        self.position = Position(split[0])
        self.active_color = Color.from_str(split[1])
        self.castling = Castling(split[2])
        self.en_passant = EnPassant(split[3])
        self.halfmoves = int(split[4])
        self.fullmoves = int(split[5])

    def __str__(self):
        fields = (self.position, self.active_color, self.castling,
                  self.en_passant, self.halfmoves, self.fullmoves)
        return " ".join(str(item) for item in fields)


class Board:
    position: Position

    def __init__(self, src: Position):
        self.position = src

    def _header(self) -> str:
        return "  " + "+" + "-"*17 + "+"

    def _footer(self) -> str:
        return "    " + " ".join(('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h')) + "  "

    def _line(self, line: Line) -> str:
        return str(line.row) + " | " + " ".join((str(cell) for cell in line.cells)) + " |"

    def __str__(self):
        result = []
        result.append(self._header())
        for line in self.position.lines:
            result.append(self._line(line))
        result.append(self._header())
        result.append(self._footer())
        return "\n".join(result)
