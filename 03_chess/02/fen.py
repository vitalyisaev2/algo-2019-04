#!/usr/bin/python3

from enum import Enum, IntFlag
from typing import List, Dict
import re


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
    column: int
    pattern = re.compile("[abcdefgh]{1}[1-8]{1}")

    def __init__(self, row: int, column: int):
        self.row = row
        if not type(column) == int:
            raise ValueError("column must be int, not '{}'".format(column))
        self.column = column

    @staticmethod
    def from_str(src: str):
        if not Coordinates.pattern.match(src):
            raise ValueError("Invalid Coordinates format: '{}'".format(src))
        column = ord(src[0]) - ord('a')
        return Coordinates(row=int(src[1]), column=column)

    def __eq__(self, other):
        return self.row == other.row and self.column == other.column

    def __str__(self):
        column = chr(ord('a') + self.column)
        return column+str(self.row)


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
                    coordinates = Coordinates(self.row, len(self.cells))
                    cell = Cell(coordinates)
                    self.cells.append(cell)
                    empty -= 1
            else:
                coordinates = Coordinates(self.row, len(self.cells))
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


class Move:
    before: Coordinates
    after: Coordinates
    substitution: Figure
    color: Color

    pattern = re.compile("([abcdefgh]{1}[1-8]{1}){2}[rnbqRNBQ]?")

    def __init__(self, before: Coordinates, after: Coordinates, substitution: Figure = None, color: Color = None):
        self.before = before
        self.after = after
        self.substitution = substitution
        self.color = color

    @staticmethod
    def from_str(src: str):

        if not Move.pattern.match(src):
            raise ValueError("Unknown Move format: {}".format(src))

        before = Coordinates.from_str(src[:2])
        after = Coordinates.from_str(src[2:])
        substitution = None
        color = None

        # ход описывает замену пешки на последней строчке
        if len(src) == 5:
            substitution = Figure.from_str(src[-1])
            color = Color.from_case(src[-1])

        return Move(before, after, substitution, color)

    @property
    def dummy(self) -> bool:
        return self.before == self.after


class Position:
    lines: List[Line]

    def __init__(self, src: str):
        self.lines = []
        for part in src.split('/'):
            line = Line(row=8-len(self.lines), src=part)
            self.lines.append(line)

    def __str__(self):
        return "/".join(str(line) for line in self.lines)

    def move_figure(self, move: Move):
        """
        Передвигает имеющуюся фигуру с одного места на другое. На старом месте возникает пустая клетка.
        """
        if not move.dummy:
            if move.substitution is None:
                # фигура перемещается из старой позиции в новую
                self.lines[8 - move.after.row].cells[move.after.column] = \
                    self.lines[8 - move.before.row].cells[move.before.column]
            else:
                # случай с превращением: в новой позиции пешка заменяется на желаемую фигуру
                self.lines[8 - move.after.row].cells[move.after.column] = Cell(
                    coordinates=move.after, color=move.color, figure=move.substitution)

            # на старом месте появляется пустая клетка
            self.empty_cell(move.before)

    def empty_cell(self, coordinates: Coordinates):
        """
        Опустошает указанную клетку
        """
        cell = Cell(coordinates=coordinates, figure=Figure.EMPTY)
        self.lines[8 - coordinates.row].cells[coordinates.column] = cell

    def get_cell(self, coordinates: Coordinates) -> Cell:
        return self.lines[8 - coordinates.row].cells[coordinates.column]


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
    directions: Dict[Color, CastlingDirection]

    def __init__(self, src: str):
        self.directions = {
            Color.BLACK: CastlingDirection.NOWHERE,
            Color.WHITE: CastlingDirection.NOWHERE,
        }
        if src == "-":
            return

        for c in src:
            if c.isupper():
                self.directions[Color.WHITE] |= CastlingDirection.from_str(c)
            elif c.islower():
                self.directions[Color.BLACK] |= CastlingDirection.from_str(c)
            else:
                raise ValueError("Unknown castling value: {}".format(c))

    def __str__(self):
        white = str(self.directions[Color.WHITE])
        black = str(self.directions[Color.BLACK])
        if white == "" and black == "":
            return "-"
        return Color.WHITE.colorize(white) + Color.BLACK.colorize(black)


class EnPassant:
    coordinates: Coordinates

    def __init__(self, src: str):
        if src == "-":
            self.coordinates = None
        elif len(src) == 2:
            self.coordinates = Coordinates.from_str(src)
        else:
            raise ValueError("Unknown EnPassant value: {}".format(src))

    def update(self, move: Move, position: Position):

        # белая пешка ходит на два хода
        if white_pawn_first_long_move(move, position):
            self.coordinates = Coordinates(row=3, column=move.before.column)
            return

        # черная пешка ходит на два хода
        if black_pawn_first_long_move(move, position):
            self.coordinates = Coordinates(row=6, column=move.before.column)
            return

        self.coordinates = None

    def __str__(self):
        if self.coordinates is None:
            return "-"
        return str(self.coordinates)


# функции, проверяющие различные специальные условия

def white_pawn_first_long_move(move: Move, position: Position) -> bool:
    figure = position.get_cell(move.before)
    return all((move.before.row == 2, figure.figure == Figure.PAWN,
                figure.color == Color.WHITE, move.after.row == 4))


def black_pawn_first_long_move(move: Move, position: Position) -> bool:
    figure = position.get_cell(move.before)
    return all((move.before.row == 7, figure.figure == Figure.PAWN,
                figure.color == Color.BLACK, move.after.row == 5))


def white_pawn_attack(move: Move, position: Position) -> bool:
    return all(
        (
            move.before.row < 8,
            move.after.row == move.before.row + 1,
            (move.after.column == move.before.column - 1) or
            (move.after.column == move.before.column + 1)
        )
    )


def black_pawn_attack(move: Move, position: Position) -> bool:
    return all(
        (
            move.before.row > 1,
            move.after.row == move.before.row - 1,
            (move.after.column == move.before.column - 1) or
            (move.after.column == move.before.column + 1)
        )
    )


def check_castling(move: Move, position: Position) -> (Move, CastlingDirection, Color):
    supp_move = None
    direction = None
    color = position.get_cell(move.before).color

    # короткая
    if all(
        (
            move.before.row == move.after.row,
            move.before.row in (1, 8),
            move.before.column == 4,
            move.after.column == 6,
            position.get_cell(move.before).figure == Figure.KING
        )
    ):
        supp_move = Move(
            before=Coordinates(row=move.before.row, column=7),
            after=Coordinates(row=move.before.row, column=5),
        )
        direction = CastlingDirection.KINGSIDE

    # длинная
    elif all(
        (
            move.before.row == move.after.row,
            move.before.row in (1, 8),
            move.before.column == 4,
            move.after.column == 2,
            position.get_cell(move.before).figure == Figure.KING
        )
    ):
        supp_move = Move(
            before=Coordinates(row=move.before.row, column=0),
            after=Coordinates(row=move.before.row, column=3),
        )
        direction = CastlingDirection.QUEENSIDE

    return (supp_move, direction, color)


def white_pawn_takes_black_en_passant(move: Move, position: Position, en_passant: EnPassant) -> Coordinates:
    if all((white_pawn_attack(move, position),
            en_passant.coordinates is not None and en_passant.coordinates == move.after)
           ):
        return Coordinates(row=en_passant.coordinates.row-1, column=en_passant.coordinates.column)
    return None


def black_pawn_takes_white_en_passant(move: Move, position: Position, en_passant: EnPassant) -> Coordinates:
    if all((black_pawn_attack(move, position),
            en_passant.coordinates is not None and en_passant.coordinates == move.after)
           ):
        return Coordinates(row=en_passant.coordinates.row+1, column=en_passant.coordinates.column)
    return None


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

    def make_move(self, m: str):
        move = Move.from_str(m)

        # изменение очерёдности и номера хода
        if self.active_color == Color.WHITE:
            self.active_color = Color.BLACK
        else:
            self.active_color = Color.WHITE
            self.fullmoves += 1

        # увеличение счётчика полуходов без ходов пешкой и взятий
        src_cell = self.position.get_cell(move.before)
        dst_cell = self.position.get_cell(move.after)
        if src_cell.figure != Figure.PAWN and dst_cell.figure == Figure.EMPTY:
            self.halfmoves += 1

        # проверяем, не взяла ли одна пешка другую на проходе
        victim = white_pawn_takes_black_en_passant(
            move, self.position, self.en_passant)
        if victim is None:
            victim = black_pawn_takes_white_en_passant(
                move, self.position, self.en_passant)

        # проверяем, не выполняется ли рокировка
        castiling_move, castling_direction, castling_color = check_castling(
            move, self.position)

        if victim is not None:
            # изменить состояние фигур на доске
            self.position.move_figure(move)
            # сделать пустым поле пешки
            self.position.empty_cell(victim)
            # битое поле очищается
            self.en_passant.coordinates = None
        elif castiling_move is not None:
            self.position.move_figure(move)
            self.position.move_figure(castiling_move)
            self.castling.directions[castling_color] &= ~castling_direction
        else:
            # фиксация битого поля
            self.en_passant.update(move, self.position)
            # изменить состояние фигур на доске
            self.position.move_figure(move)

        # ревизия возможностей для рокировки
        self.__review_castling(Color.BLACK)
        self.__review_castling(Color.WHITE)

    def __review_castling(self, target_color: Color):
        if target_color == Color.WHITE:
            enemy_color = Color.BLACK
            home_row_id = 7
        else:
            enemy_color = Color.WHITE
            home_row_id = 0

        # если король или ладья стоят не на своём месте, отключаем соответственные варианты рокировки
        if self.position.lines[home_row_id].cells[4].figure != Figure.KING:
            self.castling.directions[target_color] &= CastlingDirection.NOWHERE
            return

        if self.position.lines[home_row_id].cells[0].figure != Figure.ROOK:
            self.castling.directions[target_color] &= ~CastlingDirection.QUEENSIDE

        if self.position.lines[home_row_id].cells[7].figure != Figure.ROOK:
            self.castling.directions[target_color] &= ~CastlingDirection.KINGSIDE

        # вычисляем позиции ячеек с фигурами чужого цвета
        enemies_on_last_line = set(i for (i, cell) in enumerate(
            self.position.lines[home_row_id].cells) if cell.color == enemy_color)

        # фигуры чужого цвета поместились слева от короля
        if set((0, 1, 2, 3)).intersection(enemies_on_last_line):
            self.castling.directions[target_color] &= ~CastlingDirection.QUEENSIDE

        # фигуры чужого цвета поместились справа от короля
        if set((5, 6, 7)).intersection(enemies_on_last_line):
            self.castling.directions[target_color] &= ~CastlingDirection.KINGSIDE


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


if __name__ == "__main__":
    record = Record(input())
    print(Board(record.position))
    record.make_move(input())
    print(Board(record.position))
