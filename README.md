# Cub3D

Cub3D is a simple 3D game engine project inspired by Wolfenstein 3D, developed as part of the 42 school curriculum. It uses raycasting to render a 3D environment from a 2D map.

## Features

## What is Raycasting?
Raycasting is a rendering technique used to simulate a 3D environment from a 2D map. In Cub3D, raycasting works by casting rays from the player's viewpoint into the map grid to detect walls and objects. For each vertical stripe on the screen, a ray is sent out at a specific angle:

- The ray moves forward until it hits a wall in the map.
- The distance to the wall is calculated, and the height of the wall slice is determined based on this distance (closer walls appear taller).
- The correct texture is selected and mapped onto the wall slice.
- This process is repeated for every column of pixels, creating a pseudo-3D effect.

Raycasting is efficient and was famously used in early 3D games like Wolfenstein 3D. It allows for fast rendering and simple collision detection, making it ideal for projects like Cub3D.

## Project Structure
```
.
├── mandatory/
│   ├── src/
│   │   ├── parsing/       # Map and config file parsing
│   │   ├── raycasting/    # Core rendering engine
│   │   ├── events/        # Input handling
│   │   └── utils/         # Helper functions
│   └── includes/          # Header files
├── bonus/
│   ├── src/
│   │   ├── parsing/       # Enhanced map parsing
│   │   ├── raycasting/    # Advanced rendering
│   │   ├── minimap/       # Minimap implementation
│   │   ├── events/        # Mouse and keyboard handling
│   │   └── utils/         # Helper functions
│   └── includes/          # Header files
├── textures/              # Wall texture files (.xpm)
├── sp/                    # Sprite texture files (.xpm)
├── maps/                  # Map configuration files
├── Makefile              # Build instructions
└── README.md             # Project documentation
```

### Key Directories
- **mandatory/**: Contains the core game logic, parsing, raycasting, and utility functions.
- **bonus/**: Adds extra features like minimap, mouse controls, and advanced sprite handling.
- **textures/**: Wall textures in XPM format.
- **sp/**: Sprite textures in XPM format.

## How to Build
1. Clone the repository.
2. Run `make` in the project root to build the mandatory part.
3. Run `make bonus` to build the bonus part (if available).

## How to Run
- After building, run the executable:
  - `./cub3D map.cub` (mandatory)
  - `./cub3D_bonus map.cub` (bonus)

## Map File Format
The map file (`.cub`) contains:
- Texture paths for each wall direction
- RGB values for floor and ceiling
- 2D map layout (1 = wall, 0 = empty, N/S/E/W = player start)

Example:
```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 225,30,0
111111
100001
1020N1
111111
```

## Controls
- **W/A/S/D**: Move forward/left/back/right
- **Arrow keys**: Rotate view
- **ESC**: Exit
- **Mouse**: Look around (bonus)

## Dependencies
- MinilibX (graphics library)
- XPM image files for textures

## Authors
- [khsellami](https://github.com/khsellami)
- [kahmada](https://github.com/kahmada)

## License
This project is for educational purposes at 42 school.
