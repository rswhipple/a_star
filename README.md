# Welcome to My Mouse
A* Search Algorithm
***

## Task
Find the shortest path between entering and leaving a labyrinth while avoiding obstacles.
A maze is given to you in a file to be passed as an argument to the program.
The first line of the labyrinth contains the information to read the map:
* The number of labyrinth lines then the number of columns (LINExCOL);
* The "full" character
* The "empty" character
* The character "path"
* The character "entered labyrinth"
* The character "exit labyrinth".

The maze is composed of "empty" characters, "full" characters, characters "entering the labyrinth" and characters "exiting the labyrinth".
The purpose of the program is to replace "empty" characters with "path" characters to represent the shortest way to cross the labyrinth.
Movements can only be horizontally or vertically, not diagonally.
In the case where several solutions exist, one will choose to represent the shortest one. 
In case of equality, it will be the one whose exit where the solution is the most up then the leftmost. 

## Description
To parse the maze file, my_mouse uses a custom readline function to read and tokenize the first line of the maze.
These tokens are translated into a struct called legend_t.
The rest of the file is read, and all data including the first line is stored in a string array.

To find the path, I implement the A* algorithm. 
A* combines the benefits of Dijkstra's algorithm, which guarantees the shortest path, AND greedy best-first search, 
which uses heuristics to prioritize nodes likely to lead to the goal.
As you traverse the maze from the starting node to the ending node, A* creates nodes and organizes them into 2 lists, open and closed.
At each step, the node with the "lowest total cost" is moved from the open to closed list.

This implementation of the A* algorithm uses a cell node struct that hold both heuristic information and a graph data structure.
To improve performance I implement a binary heap for the open list, and a node array for the closed list.


## Installation
All header files are in the "include" folder, c files are in the "src" folder.
To compile the program:
$>make my_mouse

## Usage
$>./my_mouse "name_of_correctly_formatted_maze_file.map"

HINT: You will find 3 correctly formatted map examples in the assets folder, "assets/01.map" etc.


### The Core Team

Rebecca Whipple Silverstein

<span><i>Made at <a href='https://qwasar.io'>Qwasar SV -- Software Engineering School</a></i></span>