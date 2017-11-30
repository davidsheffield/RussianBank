Russian Bank
============

.. image:: https://travis-ci.org/davidsheffield/RussianBank.svg?branch=travis
    :target: https://travis-ci.org/davidsheffield/RussianBank

Code to play Russian Bank.

Positions
---------

0: Player stock

1: Player hand

2: Opponent stock

3: Opponent waste

4-11: Banks

12-19: Tableau

+--+--+--+--+
|  | 2| 3|  |
+--+--+--+--+
|16| 4| 8|12|
+--+--+--+--+
|17| 5| 9|13|
+--+--+--+--+
|18| 6|10|14|
+--+--+--+--+
|19| 7|11|15|
+--+--+--+--+
|  | 1| 0|  |
+--+--+--+--+

Move errors
-----------

0: Card moved, no error.

1: Attempt to move card to original location.

2: Locations out of range.

3: Cannot move opponent's cards or bank cards, cannot move to players piles.

4: Cannot move a card that is not there.

5: Not a legal move.
