# Cub3D

## Overview
Cub3D is a 3D game project developed as part of the 42 Network curriculum at the 1337 school. This project involves creating a basic 3D game using the raycasting technique, similar to the mechanics found in the classic game Wolfenstein 3D.

[![Cub3D Demo Video](https://github.com/Serghini04/Cub3D/blob/master/Screen%20Shot%202024-10-12%20at%203.29.53%20PM.png)](https://youtu.be/AYjC75kCCzk?si=zbxT8YhsR1jSKB4s)
Click the image above to watch the demo video!

## Project Structure
- `Bonus/`: Additional features beyond the core requirements
- `Mandatory/`: Core project files and implementations
- `maps/`: Map files for the game
- `mlx/`: MiniLibX graphics library files
- `textures/`: Texture files for game graphics
- `Makefile`: Build automation script

## Features
- Raycasting engine for 3D rendering.
- Texture mapping for immersive graphics.
- Player movement and rotation.
- Map parsing and rendering.
- Weapon display and animation.
- Mouse movement for camera control.
- Interactive doors (open/close functionality).
- Minimap for enhanced navigation.

## Collaboration
This project was developed collaboratively :
- Map parsing : [Hicham Driouch](https://github.com/paybat) 
- 3D rendering, animations, and additional features: [Mehdi Serghini](https://github.com/Serghini04)


## Building and Running
To build the project, use the provided Makefile:

```
make bonus
```

To run the game:

```
./cub3D [map_file]
```

Replace `[map_file]` with the path to a valid map file from the `maps/` directory.

## Controls
- `A` : Move left
- `W` : Move forward
- `S` : Move backward
- `D` : Move right
- `<` : Rotate camera left
- `>` : Rotate camera right
- `R` : Reload weapon
- `O` : Open door
- `C` : Close door
- `M` : Activate/Deactivate mouse control
- Mouse movement: Control camera

## Additional Resources
For a detailed explanation of the raycasting technique used in this project, check out our [Notion](https://innate-newsboy-cc3.notion.site/Ray-Casting-35bf6d83ea574d6e96bcc5b9104b3680) page on Ray Casting.

## License
This project is part of the 42 Network curriculum and is subject to their academic policies.

## Contributing
While this project is primarily an academic exercise, we welcome feedback and suggestions. Please open an issue if you encounter any bugs or have ideas for improvements.

## Acknowledgments
- 42 Network and 1337 School for the project subject and resources
- The creators of Wolfenstein 3D for inspiration
- [Hicham Driouch](https://github.com/paybat) for their work on map parsing
