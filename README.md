# Ultimate Despair Tournament

This project aims to provide a battleground for AI applied to a simple game.

## Basics of the game

Each player controls a pixel on an initially empty 2D board. This pixel is moving forward at constant speed, leaving a trail behind it. The player can control the movement of the pixel by making it turn left or right. Also note that exiting the board from one side makes the pixel appear on the other side.

A player dies when his/her pixel collides into an existing trail. The last player standing wins the game.

## Creating a game

To start a match between two players, call the `fightPlayer` function and pass the initialization functions for each of the two players.

This function takes a `Game` object as argument and returns a function that will be called each time the game is updated.

This update function should have a prototype of the form:

```C
char getTheta (const Game game);
```

It takes a `Game` object as argument and returns one of the three possible values:
* 0 if the player doesn't want to alter its direction
* 1 if the player wants to turn left
* -1 if the player wants to turn right

## To be done

Up to now the remaining core functionnalities that should be implemented are:
* enables multiple (>2) players to play together
* create an interface for a human player
