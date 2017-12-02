import unittest

import russianbank as rb


class TestMove(unittest.TestCase):
    def test_errors(self):
        field = rb.Field(1)
        self.assertEqual(field.moveCard(12, 12, 0), 1,
                         msg='Allows move to same position')
        self.assertEqual(field.moveCard(-1, 12, 0), 2,
                         msg='Allows positions out of range')
        self.assertEqual(field.moveCard(20, 12, 0), 2,
                         msg='Allows positions out of range')
        self.assertEqual(field.moveCard(12, -1, 0), 2,
                         msg='Allows positions out of range')
        self.assertEqual(field.moveCard(12, 20, 0), 2,
                         msg='Allows positions out of range')
        self.assertEqual(field.moveCard(5, 12, 0), 3,
                         msg='Allows banks as initial position')
        self.assertEqual(field.moveCard(12, 1, 0), 3,
                         msg="Allows move to player's decks")
        initial_card = 12
        field.popCard(initial_card, 0)
        field.popCard(initial_card + 1, 0)
        self.assertEqual(field.moveCard(initial_card, initial_card+1, 0), 4,
                            msg='Allows empty initial card')
        field.pushCard(initial_card, 0, rb.Card(5, 0, True))
        field.pushCard(initial_card + 1, 0, rb.Card(6, 0, True))
        self.assertEqual(field.moveCard(initial_card, initial_card + 1, 0), 5,
                         msg='Allows illegal move')


    def test_playable_to_bank(self):
        field = rb.Field(1)

        initial_card = rb.Card(1, 0, False)
        final_card = rb.Card()
        self.assertTrue(field.playableToBank(initial_card, final_card),
                        msg='Disallows valid move')

        initial_card = rb.Card(2, 0, True)
        final_card = rb.Card(1, 0, False)
        self.assertTrue(field.playableToBank(initial_card, final_card),
                        msg='Disallows valid move')

        initial_card = rb.Card(2, 0, False)
        final_card = rb.Card()
        self.assertFalse(field.playableToBank(initial_card, final_card),
                         msg='Allows invalid move')

        initial_card = rb.Card(3, 0, False)
        final_card = rb.Card(1, 0, True)
        self.assertFalse(field.playableToBank(initial_card, final_card),
                         msg='Allows invalid move')

        initial_card = rb.Card(2, 1, False)
        final_card = rb.Card(3, 1, True)
        self.assertFalse(field.playableToBank(initial_card, final_card),
                         msg='Allows invalid move')

        initial_card = rb.Card(5, 2, True)
        final_card = rb.Card(4, 1, True)
        self.assertFalse(field.playableToBank(initial_card, final_card),
                         msg='Allows invalid move')


    def test_playable_to_player(self):
        field = rb.Field(1)

        initial_card = rb.Card(6, 1, False)
        final_card = rb.Card(5, 1, True)
        self.assertTrue(field.playableToPlayer(initial_card, final_card),
                        msg='Disallows valid move')

        initial_card = rb.Card(5, 1, False)
        final_card = rb.Card(6, 1, True)
        self.assertTrue(field.playableToPlayer(initial_card, final_card),
                        msg='Disallows valid move')

        initial_card = rb.Card(4, 3, False)
        final_card = rb.Card()
        self.assertFalse(field.playableToPlayer(initial_card, final_card),
                         msg='Allows invalid move')

        initial_card = rb.Card(5, 1, False)
        final_card = rb.Card(6, 2, True)
        self.assertFalse(field.playableToPlayer(initial_card, final_card),
                         msg='Allows invalid move')

        initial_card = rb.Card(4, 3, False)
        final_card = rb.Card(6, 3, False)
        self.assertFalse(field.playableToPlayer(initial_card, final_card),
                         msg='Allows invalid move')


    def test_playable_to_tableau(self):
        field = rb.Field(1)

        initial_card = rb.Card(13, 2, True)
        final_card = rb.Card()
        self.assertTrue(field.playableToTableau(initial_card, final_card),
                        msg='Disallows valid move')

        suit_pairs = [[0, 1], [0, 3], [1, 2]]
        for pair in suit_pairs:
            initial_card = rb.Card(10, pair[0], True)
            final_card = rb.Card(11, pair[1], False)
            self.assertTrue(field.playableToTableau(initial_card, final_card),
                            msg='Disallows valid move')

        suit_pairs = [[0, 0], [0, 2], [1, 1], [1, 3], [2, 2], [3, 3]]
        for pair in suit_pairs:
            initial_card = rb.Card(10, pair[0], True)
            final_card = rb.Card(11, pair[1], False)
            self.assertFalse(field.playableToTableau(initial_card, final_card),
                             msg='Allows invalid move')

        initial_card = rb.Card(5, 0, False)
        final_card = rb.Card(8, 1, False)
        self.assertFalse(field.playableToTableau(initial_card, final_card),
                         msg='Allows invalid move')


    def test_to_stock(self):
        field = rb.Field(1)
        initial_card = 12
        final_card = 2
        field.pushCard(final_card, 0, rb.Card(5, 0, True))
        field.pushCard(initial_card, 0, rb.Card(6, 0, False))
        field.pushCard(initial_card + 1, 0, rb.Card(5, 0, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 0,
                         msg='Cannot move to stock')
        self.assertEqual(field.moveCard(initial_card + 1, final_card, 0), 0,
                         msg='Cannot move to stock')


    def test_to_waste(self):
        field = rb.Field(1)
        initial_card = 12
        final_card = 3
        field.pushCard(final_card, 0, rb.Card(5, 0, True))

        field.pushCard(initial_card, 0, rb.Card(6, 0, False))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 0,
                         msg='Cannot move to waste')

        field.pushCard(initial_card, 0, rb.Card(5, 0, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 0,
                         msg='Cannot move to waste')

        field.pushCard(initial_card, 0, rb.Card(1, 0, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to waste')

        field.pushCard(initial_card, 0, rb.Card(4, 1, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to waste')


    def test_to_bank(self):
        field = rb.Field(1)
        initial_card = 12
        final_card = 7

        field.pushCard(initial_card, 0, rb.Card(1, 0, False))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 0,
                         msg='Cannot move to bank')

        field.pushCard(initial_card, 0, rb.Card(2, 0, False))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 0,
                         msg='Cannot move to bank')

        field.pushCard(initial_card, 0, rb.Card(5, 0, False))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to bank')

        field.pushCard(initial_card, 0, rb.Card(3, 1, False))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to bank')

        field.pushCard(initial_card, 0, rb.Card(2, 0, False))
        self.assertEqual(field.moveCard(initial_card, final_card - 1, 0), 5,
                         msg='Allows illegal move to bank')

        final_card = 11

        field.pushCard(initial_card, 0, rb.Card(5, 0, False))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to bank')

        field.pushCard(initial_card, 0, rb.Card(3, 1, False))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to bank')

        field.pushCard(initial_card, 0, rb.Card(2, 0, False))
        self.assertEqual(field.moveCard(initial_card, final_card - 1, 0), 5,
                         msg='Allows illegal move to bank')


    def test_to_tableau(self):
        field = rb.Field(1)
        initial_card = 12
        final_card = 13

        cards = [[12, 1], [11, 2], [10, 3], [9, 0]]
        field.pushCard(final_card, 0, rb.Card(13, 0, True))
        for i in range(len(cards)):
            field.pushCard(initial_card, 0, rb.Card(cards[i][0], cards[i][1],
                                                    False))
            self.assertEqual(field.moveCard(initial_card, final_card, 0), 0,
                             msg='Cannot move to tableau')

        initial_card = 12
        final_card = 14
        field.popCard(final_card, 0)
        field.pushCard(initial_card, 0, rb.Card(2, 0, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 0,
                         msg='Cannot move to tableau')

        initial_card = 14
        final_card = 15
        card_suits = [[0, [0, 2]], [1, [1, 3]]]
        for i in range(2):
            field.pushCard(final_card, 0, rb.Card(13, card_suits[i][0], True))
            for j in range(len(card_suits[i][1])):
                field.pushCard(initial_card, 0, rb.Card(12, card_suits[i][1][j],
                                                        False))
                self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                                 msg='Allows illegal move to tableau')

        initial_card = 16
        final_card = 17
        field.pushCard(final_card, 0, rb.Card(7, 1, False))
        field.pushCard(initial_card, 0, rb.Card(5, 0, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to tableau')
        field.pushCard(initial_card, 0, rb.Card(7, 0, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to tableau')
        field.pushCard(initial_card, 0, rb.Card(8, 0, True))
        self.assertEqual(field.moveCard(initial_card, final_card, 0), 5,
                         msg='Allows illegal move to tableau')


if __name__ == '__main__':
    unittest.main()
