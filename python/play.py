import random
import sys
sys.path.append('build/lib.macosx-10.7-x86_64-3.6/')
import russianbank as rb
sys.path.append('python/')
from display import *


def exampleGame():

    field.moveCard(19, 15, 0)
    field.exposeStockCard(0)
    field.moveCard(0, 19, 0)
    field.exposeStockCard(0)
    field.discard(0)


    display(field, 2)


def checkGameDone(field):
    total = []
    for player_ in range(2):
        total.append(len(field.getExposedStocks(player_)) \
                     + len(field.getHiddenStocks(player_)) \
                     + len(field.getHands(player_)) \
                     + len(field.getWastes(player_)))
    if total[0] == 0:
        print("Player 0 wins with {0} points!".format(30 + total[1]))
        sys.exit()
    elif total[1] == 0:
        print("Player 1 wins with {0} points!".format(30 + total[0]))
        sys.exit()


def getMove(field, player, is_shown):
    # Need to require hand moves after 1
    response = input("Player {0} move: ".format(player))
    split = response.split(" ")
    if response == "0":
        if is_shown:
            print("Must move hand card.")
            return False, player, True
        error = field.exposeStockCard(player)
        if error == 0:
            return True, player, False
        else:
            return False, player, False
    elif response == "1":
        if len(field.getHands(player)) == 0:
            print("Big Josh")
            field.bigJosh(player)
        display(field, player)
        return False, player, True
    elif response == "end":
        if not is_shown:
            print("Turn over hand card frist.")
            return False, player, False
        field.discard(player)
        if player == 0:
            player = 1
        else:
            player = 0
        return True, player, False
    elif response == "q" or response == "quit" or response == "exit":
        sys.exit()
    elif response == "show":
        for player_ in [1, 0]:
            print("On player {0}'s stock: {1}".format(
                player_, field.getExposedStocks(player_)))
        return False, player, is_shown
    elif len(split) != 2:
        print("Invalid move")
        return False, player, is_shown
    else:
        if split[0].isdigit() and split[1].isdigit():
            if is_shown and split[0] != "1":
                print("Must move hand card.")
                return False, player, True
            error = field.moveCard(int(split[0]), int(split[1]), player)
            if error == 0:
                return True, player, False
            else:
                print("Invalid move")
                return False, player, is_shown
        else:
            print("Invalid move")
            return False, player, is_shown


def main():
    field = rb.RussianBankField(random.randint(1, 1000000))

    # First player
    player = 0
    if random.random() < 0.5:
        player = 1

    is_shown = False
    while True:
        checkGameDone(field)

        display(field, 2)

        while True:
            value, player, is_shown = getMove(field, player, is_shown)
            if value:
                break


if __name__ == '__main__':
    main()
