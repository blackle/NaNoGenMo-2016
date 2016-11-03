# Clod: A Game for Two Players.

## Materials

1. Two dice.
2. Thirty black stones.
3. Thirty white stones.
4. A Clod game board.

## The Clod Game Board

[an example Clod game board](board_diagram_mini.png)

A Clod board consists of a 6x6 grid, the rows and columns indexed on the top and sides by numbers. Spaces along the diagonal are marked with faces of a die, corresponding to the index of the row and column. This is to make interpreting the board easier.

## The Rules

The two players, black and white, take turns placing their stones on the empty spaces of the board. Black always goes first.

On their turn, a player rolls the two dice. The result of the dice roll decides which row and which column they can place their stone. The player decides which die is the "row" and which is the "column" index.

If any of the spaces the player can take are filled, they can go anywhere in the [Moore neighbourhood](https://en.wikipedia.org/wiki/Moore_neighborhood) of that space. If all of _those_ spaces are filled then the player can't go in that spot.

If the player cannot place a stone because all the available spaces are filled then they may roll the dice a second time. If they still have no spaces then they forfeit their turn.

The game is over when the whole board is filled.

### Example 1:

The black player rolls a 4 and a 2. This means they can place their stone in either of the two spots:

[row = 4 and column = 2, or row = 2 and column = 4](board_diagram_mini_ex1.png)

### Example 2:

The black player rolls a 3 and a 3. This means they can place their stone in only one spot, row = 3 and column = 3.

[row = 3 and column = 3](board_diagram_mini_ex2.png)

### Example 3:

The black player rolls a 3 and a 3, but the position 3,3 is already filled. This means they can place their stone in the nearest 8 spots around it:

[the next best spots around row = 3 and column = 3](board_diagram_mini_ex3.png)

### Example 4:

The black player rolls a 3 and a 3, but the positions 3,3; 3,2; and 3,4 is already filled. This means they can place their stone in the nearest 6 spots around it:

[the next best spots around row = 3 and column = 3](board_diagram_mini_ex4.png)

### Example 5:

The black player rolls a 3 and a 3, but that position and all the positions around it are filled. This means the player cannot place a stone.

[the next best spots around row = 3 and column = 3](board_diagram_mini_ex5.png)

## Scoring

The winner is the player who has the largest contiguous region of stones. A contiguous region is a group of stones that share edges. Stones connected by corners do not count.

### Example 6:

[the next best spots around row = 3 and column = 3](board_diagram_mini_ex6.png)

The largest region in the completed board above 

# RoyalClod: A Game for Two Players.

## Materials

1. Two dice.
2. Two hundred black stones.
3. Two hundred white stones.
4. A RoyalClod game board.

## The Clod Game Board

[an example Clod game board](board_diagram.png)

A RoyalClod game board consists of 6 Clod boards, arranged in a 3x2 grid. 