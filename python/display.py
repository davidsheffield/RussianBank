import sys
from termcolor import colored
sys.path.append('build/lib.macosx-10.7-x86_64-3.6/')
import russianbank as rb


def cardBack(card):
    if card.getDeck():
        return colored("WW", "magenta")
    else:
        return colored("XX", "blue")


def cardFront(card):
    if card.getSuit() % 2 == 0:
        return colored(card.getCard(), "red")
    else:
        return card.getCard()


def getPlayerString(field, player, hand_in_hand):
    stock_card = "  "
    exposed_stock = field.getExposedStocks(player)
    hidden_stock = field.getHiddenStocks(player)
    if len(exposed_stock) > 0:
        stock_card = cardFront(exposed_stock[-1])
    elif len(hidden_stock) > 0:
        stock_card = cardBack(hidden_stock[-1])

    waste_card = "  "
    waste = field.getWastes(player)
    if len(waste) > 0:
        waste_card = cardFront(waste[-1])

    hand_card = "  "
    hand = field.getHands(player)
    if len(hand) > 0:
        if hand_in_hand:
            hand_card = cardFront(hand[-1])
        else:
            hand_card = cardBack(hand[-1])

    if player == 0:
        # sys.stdout.write('\r')
        # sys.stdout.flush()
        left_card = stock_card
        right_card = hand_card
    else:
        left_card = hand_card
        right_card = stock_card
    return "                                  {2}    {1}     {0}".format(
        left_card, waste_card, right_card)


def bankCard(card):
    if card.getRank() < 13:
        return cardFront(card)
    else:
        return cardBack(card)


def getTableauString(field):
    tableau_string = ""
    for i in range(4):
        cards = ""

        stack = field.getTableau(i+4)
        for j in range(12 - len(stack)):
            cards += "   "
        for card in reversed(stack):
            cards += " {0}".format(cardFront(card))

        cards += "   {0} {1}  ".format(bankCard(field.getBanks(i, 0)),
                                        bankCard(field.getBanks(i, 1)))

        stack = field.getTableau(i)
        for card in stack:
            cards += " {0}".format(cardFront(card))
        for j in range(12 - len(stack)):
            cards += "   "

        tableau_string += cards + "\n"
    return tableau_string


def getDisplayString(field, state):
    display_string = getPlayerString(field, 1, state == 1)
    display_string += "\n\n"
    display_string += getTableauString(field)
    display_string += "\n"
    display_string += getPlayerString(field, 0, state == 0)
    return display_string


def display(field, state):
    # state: 0 = Player 0's top hand card is displayed
    #        1 = Player 1's top hand card is displayed
    #        2 = No hand cards are displayed
    print(getDisplayString(field, state))


def main():
    field = rb.RussianBankField(0)
    display(field)


if __name__ == '__main__':
    main()
