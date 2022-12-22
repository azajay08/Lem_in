# Lem_in - Hive (42)

## What is Lem-in?

## Usage

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
