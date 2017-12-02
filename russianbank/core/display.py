import russianbank as rb
import sys
from termcolor import colored


def card_back(card):
    if card.get_deck():
        return colored("WW", "magenta")
    else:
        return colored("XX", "blue")


def card_front(card):
    if card.get_suit() % 2 == 0:
        return colored(card.get_card(), "red")
    else:
        return card.get_card()


def get_player_string(field, player, hand_in_hand):
    stock_card = "  "
    exposed_stock = field.get_exposed_stocks(player)
    hidden_stock = field.get_hidden_stocks(player)
    if len(exposed_stock) > 0:
        stock_card = card_front(exposed_stock[-1])
    elif len(hidden_stock) > 0:
        stock_card = card_back(hidden_stock[-1])

    waste_card = "  "
    waste = field.get_wastes(player)
    if len(waste) > 0:
        waste_card = card_front(waste[-1])

    hand_card = "  "
    hand = field.get_hands(player)
    if len(hand) > 0:
        if hand_in_hand:
            hand_card = card_front(hand[-1])
        else:
            hand_card = card_back(hand[-1])

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


def bank_card(card):
    if card.get_rank() < 13:
        return card_front(card)
    else:
        return card_back(card)


def get_tableau_string(field):
    tableau_string = ""
    for i in range(4):
        cards = ""

        stack = field.get_tableau(i+4)
        for j in range(12 - len(stack)):
            cards += "   "
        for card in reversed(stack):
            cards += " {0}".format(card_front(card))

        cards += "   {0} {1}  ".format(bank_card(field.get_banks(i, 0)),
                                        bank_card(field.get_banks(i, 1)))

        stack = field.get_tableau(i)
        for card in stack:
            cards += " {0}".format(card_front(card))
        for j in range(12 - len(stack)):
            cards += "   "

        tableau_string += cards + "\n"
    return tableau_string


def get_display_string(field, state):
    display_string = get_player_string(field, 1, state == 1)
    display_string += "\n\n"
    display_string += get_tableau_string(field)
    display_string += "\n"
    display_string += get_player_string(field, 0, state == 0)
    return display_string


def display(field, state):
    # state: 0 = Player 0's top hand card is displayed
    #        1 = Player 1's top hand card is displayed
    #        2 = No hand cards are displayed
    print(get_display_string(field, state))


def main():
    field = rb.Field(0)
    display(field, 2)


if __name__ == '__main__':
    main()
