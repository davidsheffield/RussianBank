import sys
sys.path.append('build/lib.macosx-10.7-x86_64-3.6/')
import russianbank as rb
sys.path.append('python/')
from display import *


def testDeal():
    field = rb.RussianBankField(1)

    good_deal = True
    for i in range(4):
        for j in range(2):
            if not field.getBanks(i, j).isEmpty():
                good_deal = False
                print("After deal, bank {0},{1} has card {2}.".format(
                    i, j, field.getBanks(i, j).getCard()))
    for i in range(8):
        stack = field.getTableau(i)
        if len(stack) != 1:
            good_deal = False
            print("After deal, pile {0} in the tableau has {1} cards.".format(
                i, len(stack)))
        elif stack[0].isEmpty():
            good_deal = False
            print("After deal, pile {0} in the tableau has an empty card.".format(i))
    for i in range(2):
        stack = field.getHiddenStocks(i)
        if len(stack) != 12:
            good_deal = False
            print("After deal, player {0}'s stock has {1} cards.".format(
                i, len(stack)))
        for card in stack:
            if card.isEmpty():
                good_deal = False
                print("After deal, player {0}'s stock has an empty card.".format(i))
    for i in range(2):
        stack = field.getExposedStocks(i)
        if len(stack) != 0:
            good_deal = False
            print("After deal, player {0}'s stock has {1} exposed cards.".format(
                i, len(stack)))
    for i in range(2):
        stack = field.getHands(i)
        if len(stack) != 36:
            good_deal = False
            print("After deal, player {0}'s hand has {1} cards.".format(
                i, len(stack)))
        for card in stack:
            if card.isEmpty():
                good_deal = False
                print("After deal, player {0}'s hand has an empty card.".format(i))
    for i in range(2):
        stack = field.getWastes(i)
        if len(stack) != 0:
            good_deal = False
            print("After deal, player {0}'s waste pile has {1} cards.".format(
                i, len(stack)))

    if field == rb.RussianBankField(3):
        good_deal = False
        print("Shuffling is not working.")

    if good_deal:
        print("RussianBankField passes deal check.")
        display(field, 2)


def testMove():
    field = rb.RussianBankField(3)
    good_move = True
    if field.moveCard(14, 18, 0) != 0:
        good_move = False
        print("Not able to move cards in tableau.")
    if good_move:
        print("RussianBankField passes move check.")


def main():
    testDeal()
    testMove()


if __name__ == '__main__':
    main()
