import unittest

import russianbank as rb


class TestDeal(unittest.TestCase):
    def setUp(self):
        self.field = rb.Field(1)


    def test_banks(self):
        for i in range(4):
            for j in range(2):
                self.assertTrue(self.field.get_banks(i, j).is_empty(),
                                msg='Banks not empty')


    def test_tableau(self):
        for i in range(8):
            stack = self.field.get_tableau(i)
            self.assertEqual(len(stack), 1,
                             msg='Tableau has more than one card')
            self.assertFalse(stack[0].is_empty(), msg='Empty card in tableau')


    def test_hiden_stocks(self):
        for i in range(2):
            stack = self.field.get_hidden_stocks(i)
            self.assertEqual(len(stack), 12,
                             msg='Wrong number of cards in stock')
            for card in stack:
                self.assertFalse(card.is_empty(), msg='Empty card in stock')


    def test_exposed_stocks(self):
        for i in range(2):
            stack = self.field.get_exposed_stocks(i)
            self.assertEqual(len(stack), 0, msg='Stock has exposed card')


    def test_hands(self):
        for i in range(2):
            stack = self.field.get_hands(i)
            self.assertEqual(len(stack), 36,
                             msg='Wrong number of cards in hand')
            for card in stack:
                self.assertFalse(card.is_empty(), msg='Empty card in hand')


    def test_wastes(self):
        for i in range(2):
            stack = self.field.get_wastes(i)
            self.assertEqual(len(stack), 0, msg='Waste pile not empty')


    def test_shuffle(self):
        self.assertNotEqual(self.field, rb.Field(3),
                            msg='Shuffling not working')



if __name__ == '__main__':
    unittest.main()
