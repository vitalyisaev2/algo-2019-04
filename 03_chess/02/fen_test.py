import unittest
from fen import Line, Position, Castling


class TestLine(unittest.TestCase):

    def test_parsing_and_serialization(self):
        cases = [
            "rnbqkbnr", "pppppppp", "8", "PPPPPPPP", "RNBQKBNR", "4P3", "3p4", "PPPP1PPP", "ppp1pppp",
        ]
        for case in cases:
            self.assertEqual(str(Line(case)), case)


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


if __name__ == "__main__":
    unittest.main()
