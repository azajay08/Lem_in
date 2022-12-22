# Lem_in - Hive (42)

## What is Lem-in?
Do you remember the game Lemmings? Well that is what I instantly thought of when seeing this project for the first time. If you don't remember the game. It was a game made in the early 90s where you have an amount of little lemmings that follow eachother along a path filled with obstacles, and you have to make sure that they get to the end of the path. Well this project shares some aspects of the game. We are given a file(map) that must be parsed. These maps contain the information:
* Number of ants
* Room names and coordinates
* Links - which rooms are connected to eachother.
* #Comments - comments can contain any bits of information just for the user, but do not effect the output
* ##Commands - like comments but these effect to output. They will be `##Start` and `##End`, symbalising the starting room(source) and the ending room (sink)


## Usage
You can clone the repo with ..
```
git clone https://github.com/azajay08/Lem_in.git
```
Once the repository has been cloned, you can move into the root of the repository and `make`. This will then create the executable `lem-in` in the root of the repository

```
Usage: ./lem-in -[flag] < [map]

Flags:
        -h      help - shows usage and flag options
        -p      paths - prints path route(s)
        -q      quiet mode - does not print map
        -t      turns - prints the number of turns

Visualizer usage: ./lem-in < [map] | python3 visualizer/lem_in_vis.py
```
For multiple modes, group flags together, for example `./lem-in -qtp < [map]`

## Method





## Visualizer
For the visualizer, we decided to use Pygame. Being reletively new to python at the the time, Pygame was a good option that was familiar, as I had done a visualizer for the previous project with it. To be able to use the visualizer, you would need to have python3 and pygame installed. If you have python3, installed, depending on your system, you can easily install pygame for example with `pip3 install pygame`.

It is in a 2D format, so it would require the coordinates of the rooms to be spread out for it to be visualized properly. So maps with with just ascending coordiantes, may not be the best visual representation. If you have some nice maps with nice coordinates to test, you can use it like this ...

`./lem-in < [map] | python3 visualizer/lem_in_vis.py`

https://user-images.githubusercontent.com/86073849/205643151-ca0e3334-fcfb-4ab2-bc26-01aeb49a574e.mov
