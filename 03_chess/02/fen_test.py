import unittest
from fen import Line, Position, Castling, Record, Board


class TestLine(unittest.TestCase):

    def test_parsing_and_serialization(self):
        cases = [
            "rnbqkbnr", "pppppppp", "8", "PPPPPPPP", "RNBQKBNR", "4P3", "3p4", "PPPP1PPP", "ppp1pppp",
        ]
        for case in cases:
            self.assertEqual(str(Line(row=0, src=case)), case)


class TestPosition(unittest.TestCase):

    def test_parsing_and_serialization(self):
        cases = [
            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR",
        ]
        for case in cases:
            self.assertEqual(str(Position(case)), case)


class TestCastling(unittest.TestCase):

    def test_parsing_and_serialization(self):
        cases = [
            "KQkq",
            "-"
        ]
        for case in cases:
            self.assertEqual(str(Castling(case)), case)


class TestRecord(unittest.TestCase):

    def test_parsing_and_serialization(self):
        cases = [
            (
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KkQq - 0 1",
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"
            )
        ]
        for case in cases:
            self.assertEqual(str(Record(case[0])), case[1])

    def test_change_active_color_and_fullmove_counter(self):
        cases = [
            (
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                "e2e2",
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1",
            ),
            (
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq - 0 1",
                "e7e7",
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 2"
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(str(r), case[2])

    def test_change_halfmove(self):
        cases = [
            (
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                "b1f3",
                "rnbqkbnr/pppppppp/8/8/8/5N2/PPPPPPPP/R1BQKBNR b KQkq - 1 1"
            ),
            (
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                "e2e4",
                "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq - 0 1",
            ),
            (
                "rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3",
                "e5g4",
                "rnbqkb1r/pppppppp/8/8/6N1/8/PPPPPPPP/RNBQKB1R b KQkq - 4 3",
            ),
            (
                "rnbqkb1r/pppppppp/8/4N3/6n1/8/PPPPPPPP/RNBQKB1R w KQkq - 4 3",
                "b1f3",
                "rnbqkb1r/pppppppp/8/4N3/6n1/5N2/PPPPPPPP/R1BQKB1R b KQkq - 5 3",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(str(r), case[2])


class TestBoard(unittest.TestCase):

    def test_parsing_and_serialization(self):
        cases = [
            (
                "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1",
                """  +-----------------+
8 | r n b q k b n r |
7 | p p p p p p p p |
6 | . . . . . . . . |
5 | . . . . . . . . |
4 | . . . . . . . . |
3 | . . . . . . . . |
2 | P P P P P P P P |
1 | R N B Q K B N R |
  +-----------------+
    a b c d e f g h  """
            )
        ]
        for case in cases:
            p = Record(case[0]).position
            self.assertEqual(str(Board(p)), case[1])


if __name__ == "__main__":
    unittest.main()
