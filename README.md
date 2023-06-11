# Cub3d

This is a brief description of the project.

![alt text](Cub3d.png)

## Table of Contents

- [Concepts](#concepts)
- [Installation](#installation)
- [Usage](#usage)


## Concepts

### Raycasting

Imagine that We are standing in the middle of a 3D world, with a line shooting straight out from our eyes. 
This line travels through the world, until it collides with our specified objects. 
By measuring the distance the beam traveled till it hit the wall. We can determine how far away the object is from us.
Now, here's where it gets really interesting. Using some fancy math, We can use the direction that the beam is pointing in, along with the distance to the object it hit, to create a 3D image of the world on our 2D screen. It's almost like magic - We can see the depth and texture of objects in the world, even though they're really just 2D images on my screen.
It's kind of like being a detective, piecing together clues to figure out what's really going on in the world around me. And the best part is, We can do all of this in real-time, as We move through the world and the raycasted beam travels forward until it collides with the wall in front of us.


# Flowchar 


1. Get player's current position and viewing angle
2. Loop through each vertical column on the screen
3. Determine the angle of the current ray based on the player's viewing angle and the current column
4. Shoot a ray out in the direction of the current angle
5. Repeat the following steps until the ray hits a wall:
6. Calculate the distance to the nearest vertical grid line
7. Calculate the distance to the nearest horizontal grid line
8. Choose the smaller distance
9. Calculate the height of the wall based on the distance and the player's viewing angle
10. Draw a vertical line on the screen at the current column with the calculated height
11. Repeat steps 2-10 for each column on the screen
12. END


## Installation

1. Clone the repository.
2. Install required dependencies:
    ```
    $ make
    ```
3. Run the program:
    ```
    $ ./cub3d assets/maps/*.cub
    ```

## Usage

Explain how to use the program with examples.
