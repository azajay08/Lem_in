# Lem_in - Hive (42) :ant: :ant: :ant:

Lem_in is the second to last project in the algorithm branch at Hive(42). It is a paired group project. The aim of the project is to come up with an algorithm that will give us the fewest possible turns at sending ants through a map made up of one or multiple path options. As with all Hive projects, they come with restraints and limitations. We have to abide by the rules of `Norminette`. Here are some of the rules we must follow:

```
* The mandatory part must be written in C
* 25 lines maximum per function
* 5 functions maximum per file
* 80 columns wide maximum
* 5 variables per function maximum
* For loops are forbidden
* Declaration and an initialisation cannot be on the same line
* A function can take 4 named parameters maximum
* Printf is forbidden - But we can use our own version made in a previous project (ft_printf)
* Functions allowed:
  * write
  * malloc
  * free
  * exit
  * read
  * sterror
  * perror
```
For the bonus of the project, we made a visualizer. The visualizer doesn't have to follow the same `Norminette` rules as the mandatory part, and can be done in a language of our choosing, so we decided to do it in Python using Pygame.


## What is Lem_in?


![ezgif com-gif-maker](https://user-images.githubusercontent.com/86073849/209192867-549939b7-319c-4147-a758-f6669efab447.gif)

Do you remember the game Lemmings? Well that is what I instantly thought of when seeing this project for the first time. If you don't remember the game, it was a game made in the early 90s where you have an amount of little lemmings that follow each other along a path filled with obstacles, and you have to make sure that they get to the end of the path. Well this project shares some aspects of the game. We are given a file(map) that must be parsed. Instead of the little Lemmings from the game, we are using ants. These maps contain the following information:
```
* Number of ants
* Room names and coordinates
* Links - which rooms are connected to eachother.
* #Comments - comments can contain any bits of information just for the user, but do not effect the output
* ##Commands - `##Start` and `##End`, symbalising the starting room(source) and the ending room (sink)
```
This is an example of valid map:

<img width="273" alt="Screen Shot 2022-12-22 at 5 49 32 PM" src="https://user-images.githubusercontent.com/86073849/209171802-d16163a5-4a18-45bb-964c-b59ae300ce7d.png">

Like the game Lemmings, we must find a path to the `end(sink)`. But for us, we must do it in as few turns as possible, which might require the `ants` to take different paths so that they all get to the `sink` quicker. `Ants` can only move one at a time and fill a `room` one at a time. There can be no collisions meaning there can be no ants in the same room at one time, with the exception of the `source` room and the `sink` room. A turn is considered as a movement from every `ant` in play, and that makes a movement. The turn will be displayed on one line, and a new turn is shown on a new line. Therefore, we try to get our ants to the `sink` in as few lines as possible. The output would have the map given to it printed on the `STDOUT` along with the moves like so:

<img width="290" alt="Screen Shot 2022-12-22 at 6 07 44 PM" src="https://user-images.githubusercontent.com/86073849/209177557-30e6d65c-89fe-46fd-8bdb-9fdefc25f66a.png">

As you can see at the bottom of the image above, they are the moves and turns. Let's take the first turn for example `L1-1 L2-3`. The `L` represents that it is an ant. The number next the the `L` is the ant number, therefore `L1` is ant number 1, in our case the `Ant Queen`. Then the `-` separates the ant and the room it is moving to. `1` is the name of the room that the ant has moved to(in this example). So on here we can see that the first ant has moved to `room 1` and ant 2 has moved to `room 3`. An ant will stop making moves once it has reached the `sink`, in our case the room called `end`.

<details>
<summary><h4><strong>Usage</strong></h4></summary>
<p>
You can clone the repo with ..
        
```
git clone https://github.com/azajay08/Lem_in.git
```
        
Once the repository has been cloned, you can move into the root of the repository.
```
make
```` 
This will then create the executable `lem-in` in the root of the repository

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
</p>
</details>

<details>
<summary><h4><strong>Method</strong></h4></summary>
<p>
  

There was a lot of research to be done before we could even start coding. First we studied [Ford-Fulkerson algorithm](https://en.wikipedia.org/wiki/Ford%E2%80%93Fulkerson_algorithm), and then [Edmonds-Karp algorithm](https://en.wikipedia.org/wiki/Edmonds%E2%80%93Karp_algorithm), which is *"an implementation of the Ford–Fulkerson method"*. By understanding these algorithms we had set the base on how we solve the problems.  
  
We start solving the paths with [BFS(Breadth-First Search)](https://en.wikipedia.org/wiki/Breadth-first_search), which is a tool for finding the shortest path.  
Our solver finds the shortest paths one by one while updating the map between the searches. This way some better paths can be left undetected.
However, by finding [Vertex Disjoint Paths](https://matthewdaws.github.io/blog/2015-06-08-Paths.html), we found the solution to this dilemma.
  
As we can see in the gif below, the BFS finds the shortest path first, which blocks other paths from being found. 
By using the Vertex Disjoint Paths -method, we can find more paths by following few rules:
- if we encounter a vertex(room) that is already used by a path:
   - Must follow the path backwards
   - When followed, can hop off to a vertex when found one  
   
If a path is found from source(start) to sink(end) with these rules, we delete the edge(s)(links) that have been followed.  
Then BFS will find more paths.
  
&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;&emsp;![lemin_solver gif](https://user-images.githubusercontent.com/90178358/209240702-1e378c68-8ce3-465e-b7fb-0c89292aa777.gif)
  
  
We use some calculations to know when we have found the number of paths we will use with the amount of ants we have.  
With the number of ants, paths, and edges in each path, we calculate how many ants we send through each path.
  
  
</p>      
</details>

<details>
<summary><h4><strong>Visualiser</strong></h4></summary>
<p>
For the visualiser, we decided to use Pygame. Being relatively new to python at the the time, Pygame was a good option that was familiar, as I had done a visualiser for the previous project with it. To be able to use the visualiser, you would need to have python3 and pygame installed. If you have python3, installed, depending on your system, you can easily install pygame for example with ...
 
```
pip3 install pygame
```

It is in a 2D format, so it would require the coordinates of the rooms to be spread out for it to be visualised properly. So maps with just ascending coordinates, may not be the best visual representation. If you have some nice maps with nice coordinates to test, you can use it like this ...

```
./lem-in < [map] | python3 visualizer/lem_in_vis.py
```
                

https://user-images.githubusercontent.com/86073849/205643151-ca0e3334-fcfb-4ab2-bc26-01aeb49a574e.mov

</p>      
</details>
