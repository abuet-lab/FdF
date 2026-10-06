*This project has been created as part of the 42 curriculum by abuet.*

# FdF — Wireframe 3D renderer

![Language](https://img.shields.io/badge/language-C-blue)
![School](https://img.shields.io/badge/school-42-black)
![Graphics](https://img.shields.io/badge/graphics-MiniLibX-lightgrey)

A C program that reads a height map and renders it as a **3D wireframe landscape** using an isometric projection. Each point of the map has an altitude (Z) and an optional color, and the program connects the points with line segments to draw the relief. The view can be zoomed, moved and rotated in real time.

> Project from the [42 school](https://42.fr/) curriculum ("FdF" stands for *fil de fer*, French for "wireframe"). Written in C with the MiniLibX graphics library, following the 42 coding standard (the *Norm*).

---

<!-- Add a screenshot of your program here, for example:
![FdF preview](docs/preview.png)
-->

## Features

- Isometric projection with an adjustable angle
- Zoom and translation of the map
- Rotation (tilt) of the view
- Per-point colors defined in the map file
- Automatic scaling to the size of the map
- Clean exit: all memory is freed and MiniLibX resources are destroyed
- Works on both macOS and Linux

## Map format

Each line of a `.fdf` file is a row of points. Each value is an integer altitude, optionally followed by a hexadecimal color separated by a comma:

```text
0 0 0 0
0,0xFF0000 5,0x00FF00 0
0 0 0 0
```

The position of a value in the file gives its `x` and `y` coordinates, and the value itself gives its altitude `z`.

## How it works

1. **Parsing**: the file is read line by line and stored in a linked list, then converted into a grid of points with their altitude and color. The map is validated (consistent line lengths, valid values).
2. **Scaling**: the altitude range and the map size are computed so the model fits inside the window.
3. **Projection**: each 3D point `(x, y, z)` is rotated and projected onto the 2D screen with an **isometric projection**.
4. **Drawing**: neighboring points are connected using the **DDA line algorithm**, which steps along the dominant axis to avoid gaps in the lines. Pixels are written into an image buffer that is then displayed.
5. **Events**: keyboard hooks update the zoom, position and rotation, and the image is redrawn.

## Project structure

```text
.
├── main.c            # Entry point
├── parse.c           # Reads and validates the .fdf map
├── free_parse.c      # Frees memory used during parsing
├── linked_list.c/.h  # Linked list used to store map lines while reading
├── min_max.c         # Computes altitude range and scaling
├── utils_draw.c      # Projection and line drawing (DDA)
├── manage_window.c   # Window creation, key and close events
├── utils.c           # Helper functions
├── fdf.h             # Main header
├── struct.h          # Data structures (points, map, window…)
├── keys.h            # Keyboard codes
├── libft/            # My own C library
├── minilibx-linux/   # MiniLibX for Linux
├── minilibx_macos/   # MiniLibX for macOS
└── test_maps/        # Sample maps
```

## Build

### Prerequisites

On Linux, MiniLibX needs the X11 development libraries:

```bash
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### Compile

`minilibx-linux` is a Git submodule, so clone with `--recurse-submodules`:

```bash
git clone --recurse-submodules https://github.com/abuet-lab/FdF.git
cd FdF
make
```

| Rule          | Description |
|---------------|-------------|
| `make`        | Compiles libft, MiniLibX and the `fdf` executable |
| `make clean`  | Removes object files |
| `make fclean` | Removes object files and the executable |
| `make re`     | Rebuilds everything from scratch |

## Usage

```bash
./fdf <path_to_map.fdf>

./fdf test_maps/42.fdf
./fdf test_maps/elem.fdf
```

### Controls

| Key           | Action |
|---------------|--------|
| `↑` / `↓`     | Zoom in / out |
| `←` / `→`     | Move horizontally |
| `W` / `S`     | Rotate (tilt) the view |
| `ESC`         | Quit cleanly |
| Close button  | Close the window |

## What I learned

- Basics of **computer graphics**: rotating and projecting 3D coordinates onto a 2D screen
- Drawing lines pixel by pixel with the **DDA algorithm**
- Using a low-level graphics library (**MiniLibX**) and an image buffer
- **Event-driven programming**: keyboard and window events with hooks
- Parsing and validating input files robustly
- Managing memory across a larger C project split into several modules

## Resources

- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [DDA line algorithm — Wikipedia](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Isometric projection — Wikipedia](https://en.wikipedia.org/wiki/Isometric_projection)
- [MiniLibX for Linux](https://github.com/42Paris/minilibx-linux)

### Use of AI

AI was used as a development aid for the following points:

- **Debugging**: finding bugs such as a duplicated struct definition, wrong MiniLibX callback signatures, and an integer division that resulted in `size_square = 0`
- **DDA algorithm**: explanation and correction of the algorithm so that it iterates over the dominant axis and avoids gaps in the lines
- **Isometric projection**: rotation and translation formulas
