# AStar-3D-Pathfinding
A* pathfinding algorithm extended for 3D space

## Note on extra files
The cpp file can be used on it's own but I made this project in Visual Studio so I included those files too.

## Use
First the 3D map needs to be hardcoded. Entering it every time as input would be a colossal pain. Here, the coordinated are as Y X Z and are always positive. Think of it as rows(Y) of columns(X) which have depth(Z). The 3D space is divided into cubes as units. In the Map array provided at the beginning of the code file, 0 means that cube in space is blocked and 1 means it's free to be moved to. This way the entire space can mapped without a need for use of a specific unit. Each cube's size can be considered as needed without changing the code but simply the interpretation of the output.

Then, by running the program multiple paths can be found by inputting as many Start Points and End Points as needed.

## Future
I may polish and compile this project to be used as a library in C++ or other languages.
