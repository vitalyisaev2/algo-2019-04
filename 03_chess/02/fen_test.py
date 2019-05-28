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


class TestRecordMoveCounters(unittest.TestCase):

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
                "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1",
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
            self.assertEqual(
                str(r), case[2], msg="before='{}' move='{}' after='{}'".format(*case))


class TestRecordMovings(unittest.TestCase):

    def test_move_without_capturing(self):
        cases = [
            (
                "k7/r7/b7/q7/N7/B7/R7/K7 w - - 15 48",
                "a2h2",
                "k7/r7/b7/q7/N7/B7/7R/K7 b - - 16 48",
            ),
            (
                "k7/r7/b7/q7/N7/B7/7R/K7 b - - 16 48",
                "a5e1",
                "k7/r7/b7/8/N7/B7/7R/K3q3 w - - 17 49",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(str(r), case[2])

    def test_move_with_capturing(self):
        cases = [
            (
                "rnbqkbnr/ppp1pppp/8/3p4/4P3/8/PPPP1PPP/RNBQKBNR w KQkq - 0 2",
                "e4d5",
                "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2",
            ),
            (
                "rnbqkbnr/ppp1pppp/8/3P4/8/8/PPPP1PPP/RNBQKBNR b KQkq - 0 2",
                "d8d5",
                "rnb1kbnr/ppp1pppp/8/3q4/8/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(str(r), case[2])

    def test_pawn_promotion(self):
        cases = [
            (
                "rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5",
                "b2a1q",
                "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/qNBQKBNR w Kkq - 0 6",
            ),
            (
                "rnbqkbnr/pppp1ppp/4P3/8/8/8/Pp3PPP/RNBQKBNR b KQkq - 0 5",
                "b2a1b",
                "rnbqkbnr/pppp1ppp/4P3/8/8/8/P4PPP/bNBQKBNR w Kkq - 0 6",
            ),
            (
                "rnbq1bnr/pppPkppp/8/8/8/8/P4PPP/qNBQKBNR w K - 0 6",
                "d7c8R",
                "rnRq1bnr/ppp1kppp/8/8/8/8/P4PPP/qNBQKBNR b K - 0 6",
            ),
            (
                "rnbq1bnr/pppPkppp/8/8/8/8/P4PPP/qNBQKBNR w Kkq - 0 6",
                "d7c8N",
                "rnNq1bnr/ppp1kppp/8/8/8/8/P4PPP/qNBQKBNR b K - 0 6",
            ),
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(str(r), case[2])

    def test_en_passant_determine(self):
        cases = [
            (
                "rnbqkbnr/ppp1pppp/8/4P3/3p4/8/PPPP1PPP/RNBQKBNR w KQkq - 0 3",
                "c2c4",
                "rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3",
            ),
            (
                "rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3",
                "f7f5",
                "rnbqkbnr/ppp1p1pp/8/4Pp2/2Pp4/8/PP1P1PPP/RNBQKBNR w KQkq f6 0 4",
            ),
            (
                "rnbqkbnr/ppp1pppp/8/8/3p4/N6N/PPPPPPPP/R1BQKB1R w KQkq - 0 3",
                "b2b4",
                "rnbqkbnr/ppp1pppp/8/8/1P1p4/N6N/P1PPPPPP/R1BQKB1R b KQkq b3 0 3",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(
                str(r), case[2], msg="before='{}' move='{}' after='{}'".format(*case))

    def test_en_passant_capture(self):
        cases = [
            (
                "rnbqkbnr/ppp1pppp/8/4P3/2Pp4/8/PP1P1PPP/RNBQKBNR b KQkq c3 0 3",
                "d4c3",
                "rnbqkbnr/ppp1pppp/8/4P3/8/2p5/PP1P1PPP/RNBQKBNR w KQkq - 0 4",
            ),
            (
                "r1bqkbnr/ppp1p1pp/2n5/4PpP1/8/2p5/PP1P1P1P/RNBQKBNR w KQkq f6 0 6",
                "g5f6",
                "r1bqkbnr/ppp1p1pp/2n2P2/4P3/8/2p5/PP1P1P1P/RNBQKBNR b KQkq - 0 6",
            ),
            (
                "r1bqkbnr/ppp1p1pp/2n5/4PpP1/8/2p5/PP1P1P1P/RNBQKBNR w KQkq f6 0 6",
                "e5f6",
                "r1bqkbnr/ppp1p1pp/2n2P2/6P1/8/2p5/PP1P1P1P/RNBQKBNR b KQkq - 0 6",
            ),
            (
                "r2qkbnr/pppbp2p/2n2p2/4PpP1/8/2p2N2/PP1P1P1P/RNBQK2R w KQkq - 0 9",
                "e5f6",
                "r2qkbnr/pppbp2p/2n2P2/5pP1/8/2p2N2/PP1P1P1P/RNBQK2R b KQkq - 0 9",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(
                str(r), case[2], msg="before='{}' move='{}' after='{}'".format(*case))

    def test_no_castling_after_king_move(self):
        cases = [
            (
                "r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
                "e8d8",
                "r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
            ),
            (
                "r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
                "e1d1",
                "r2k3r/pppppppp/8/N7/8/8/PPPPPPPP/R2K3R b - - 2 17",
            ),
            (
                "r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R3K2R w KQkq - 4 16",
                "e1d1",
                "r3k2r/pppppppp/8/n7/2N5/8/PPPPPPPP/R2K3R b kq - 5 16",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(
                str(r), case[2], msg="before='{}' move='{}' after='{}'".format(*case))

    def test_no_castling_after_rook_move(self):
        cases = [
            (
                "r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
                "a8b8",
                "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQk - 1 17",
            ),
            (
                "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQk - 1 17",
                "h1g1",
                "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 b Qk - 2 17",
            ),
            (
                "1r2k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 b Qk - 2 17",
                "h8g8",
                "1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 w Q - 3 18",
            ),
            (
                "1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/R3K1R1 w Q - 3 18",
                "a1c1",
                "1r2k1r1/pppppppp/8/N7/8/8/PPPPPPPP/2R1K1R1 b - - 4 18",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(
                str(r), case[2], msg="before='{}' move='{}' after='{}'".format(*case))

    def test_kingside_castling(self):
        cases = [
            (
                "r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
                "e8g8",
                "r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
            ),
            (
                "r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
                "e1g1",
                "r4rk1/pppppppp/8/N7/8/8/PPPPPPPP/R4RK1 b - - 2 17",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(
                str(r), case[2], msg="before='{}' move='{}' after='{}'".format(*case))

    def test_queenside_castling(self):
        cases = [
            (
                "r3k2r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R b KQkq - 0 16",
                "e8c8",
                "2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
            ),
            (
                "2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/R3K2R w KQ - 1 17",
                "e1c1",
                "2kr3r/pppppppp/8/N7/8/8/PPPPPPPP/2KR3R b - - 2 17",
            )
        ]
        for case in cases:
            r = Record(case[0])
            r.make_move(case[1])
            self.assertEqual(
                str(r), case[2], msg="before='{}' move='{}' after='{}'".format(*case))


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
