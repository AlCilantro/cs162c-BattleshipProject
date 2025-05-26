# cs162c-BattleshipProject
Personal Project for cs162c.  
Create a simple turn-based Battleship game. Player and CPU place ships on a grid and take turns guessing the location of enemy ships.

## Requirements
2D array grid for each player  
Ships of different sizes are placed on a two-dimensional array.  
For the CPU, it is decided by a random number generator.  
Turn system: player guesses a spot (like B5), checks for hit/miss.  
Possible probability check or something along those lines for the CPU to make a move.  
Track hits and misses  
The game ends when one player’s ships are all sunk or the CPU has no ships left.  
The CPU opponent could be random guessing for locations on an array for the beginning or as a response move, should they go second.  
Visualization of the boards for the player and the CPU, along with hits and misses.  
The CPU’s board should be empty and only show hits.  
CPU attacks in either randomly or in some sort of strategic manner
Coin Flip for who goes first in the game.  
Horizontal and Vertical boat placement  
Possible way for keeping track of boats sunk on each side  

## Not Supported
Strategic placement of boats from the CPU.  
Scoreboard of the game.  
A very large number of ships or a large size of map.  
Diagonal placement.  
Multiple Rounds.  
Any special features besides the basic game.

## Success Criteria
Players can place ships without overlapping.  
The turn system works.  
Hits/misses are shown clearly.  
The game ends correctly and declares a winner.  
The CPU places ships randomly.  
CPU attacks in general.  
Coin Flip appears random.  
The CPU’s board remains empty until a ship is hit or a miss is registered.  
The CPU does not attack the player’s boats instantly.  
The CPU does not continue to attack ships that are already sunk.  