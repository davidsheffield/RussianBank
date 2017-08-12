import random
import russianbank as rb
import sys


def exitGame():
    print("\n" * 55)
    sys.stdout.write('\x1b7\x1b[0;0f')
    sys.stdout.flush()
    sys.exit()


def checkGameDone(field):
    total = []
    for player_ in range(2):
        total.append(len(field.getExposedStocks(player_)) \
                     + len(field.getHiddenStocks(player_)) \
                     + len(field.getHands(player_)) \
                     + len(field.getWastes(player_)))
    if total[0] == 0:
        printMoveError("Player 0 wins with {0} points!".format(30 + total[1]))
        input()
        exitGame()
    elif total[1] == 0:
        printMoveError("Player 1 wins with {0} points!".format(30 + total[0]))
        input()
        exitGame()


def printMoveError(text):
    sys.stdout.write("\x1b7\x1b[16;0f{0}".format(text))
    sys.stdout.flush()


def display(field, player):
    sys.stdout.write("\x1b7\x1b[4;0f                                        ")
    sys.stdout.write('\x1b7\x1b[5;0f{0}'.format(
        rb.getDisplayString(field, player)))
    sys.stdout.write("\x1b7\x1b[13;0f                                        ")
    sys.stdout.flush()


def getMove(field, player, is_shown):
    sys.stdout.write("\x1b7\x1b[15;0f")
    sys.stdout.flush()
    response = input("Player {0}: ".format(player))
    sys.stdout.write("\x1b7\x1b[15;0f                                        \n                                        ")
    sys.stdout.flush()
    split = response.split(" ")
    if response == "0":
        if is_shown:
            printMoveError("Must move hand card.")
            return False, player, True
        error = field.exposeStockCard(player)
        if error == 0:
            return True, player, False
        else:
            return False, player, False
    elif response == "1":
        if len(field.getHands(player)) == 0:
            printMoveError("Big Josh")
            field.bigJosh(player)
        display(field, player)
        return False, player, True
    elif response == "end":
        if not is_shown:
            printMoveError("Turn over hand card frist.")
            return False, player, False
        field.discard(player)
        if player == 0:
            player = 1
        else:
            player = 0
        return True, player, False
    elif response == "q" or response == "quit" or response == "exit":
        exitGame()
    elif response == "show":
        for player_ in range(2):
            cards = ""
            for card in field.getExposedStocks(player_):
                cards += " {0}".format(rb.core.display.cardFront(card))
            sys.stdout.write("\x1b7\x1b[{0};0fOn player {1}'s stock:{2}".format(
                13 - 9*player_, player_, cards))
            sys.stdout.flush()
        return False, player, is_shown
    elif len(split) != 2:
        printMoveError("Invalid move")
        return False, player, is_shown
    else:
        if split[0].isdigit() and split[1].isdigit():
            if is_shown and split[0] != "1":
                printMoveError("Must move hand card.")
                return False, player, True
            error = field.moveCard(int(split[0]), int(split[1]), player)
            if error == 0:
                return True, player, False
            else:
                printMoveError("Invalid move")
                return False, player, is_shown
        else:
            printMoveError("Invalid move")
            return False, player, is_shown


def main():
    field = rb.RussianBankField(random.randint(1, 1000000))

    # First player
    player = 0
    if random.random() < 0.5:
        player = 1

    single_player = False
    while True:
        value = input("How many players? (1 or 2) ")
        if value == "1":
            single_player = True
            break
        elif value == "2":
            break
        else:
            print("Invalid input")

    print("\n" * 55)

    robot = rb.RussianBankPlayer(field)
    is_shown = False
    while True:
        checkGameDone(field)

        display(field, 2)

        if not single_player or player == 0:
            while True:
                value, player, is_shown = getMove(field, player, is_shown)
                if value:
                    robot.startTurn()
                    break
        else:
            robot.setField(field)
            value = robot.move()
            field = robot.getField()
            status = 2
            if robot.isHandInHand():
                status = 1
            display(field, status)
            sys.stdout.write("\x1b7\x1b[15;0f")
            sys.stdout.flush()
            input("Player 1's move: {0}".format(value))
            sys.stdout.write("\x1b7\x1b[15;0f                                        ")
            sys.stdout.flush()
            if robot.end():
                player = 0


if __name__ == '__main__':
    main()
