# Snake training AI

This is an algorithm used to train a neural network to play Snake.

I made a video about it, if you want more info about this project: https://www.youtube.com/watch?v=CQCFxJSwGzI

## Dependencies

* freeGlut (http://freeglut.sourceforge.net/)

The next two files and their headers are already included in the project:
* network.cpp (https://github.com/gregora/Cpp-neural-network)
* simple2D.cpp (https://github.com/gregora/Simple2D-OpenGL-wrapper)

## Run and compile

Everything necessary to compile and run is already in run.sh and render.sh files.

run.sh and render.sh already compile and run everything on Linux. If you want to run this on Windows, you will probably have to compile it on your own.

## What do ./run.sh and ./render.sh do?

### run.sh
Runs the learning algorithm and saves the neural network to a saved.AI file.

### render.sh
Renders what neural network does (How neural network actually plays the game)
