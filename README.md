# 🕹️ Cub3D

> A 3D FPS game created in C, powered by a custom raycasting engine inspired by the classic Wolfenstein 3D.

## 📖 Description

**Cub3D** is a graphics programming project from the **42 School** curriculum.

The primary goal of this project is to build a minimal 3D game engine using **raycasting**. Written entirely in **C**, the program reads a simple 2D map from a file and renders a navigable, first-person 3D perspective. This project serves as a hands-on introduction to mathematics in computer graphics, window management, and algorithmic optimization.

### ✨ Technical Overview & Core Features

* **Raycasting Engine**: Calculates the distance between the player and walls to project a pseudo-3D environment from a 2D grid in real-time.
* **Texture Mapping**: Dynamically applies distinct textures to North, South, East, and West facing walls, alongside customizable floor and ceiling colors.
* **Fluid Mechanics**: Smooth camera and player movements (forward, backward, strafing, and rotation).
* **Robust Parsing**: Strictly validates `.cub` configuration files to ensure the map is perfectly closed, characters are valid, and texture paths are correct.
* **MiniLibX Stack**: Built using *MiniLibX* (a basic graphics library provided by 42) to manually handle window creation, pixel drawing, and keyboard/mouse events.

### 🌟 Bonus Features

* **Wall Collisions**: Precise collision detection ensuring the player glides smoothly against surfaces without clipping through walls.
* **Minimap System**: A dynamic, on-screen 2D minimap that tracks the player's exact position and line of sight in real-time.


## 🚀 Instructions

### Prerequisites

To compile and run this project, you will need `make`, a C compiler (`gcc` or `clang`), and an environment compatible with **MiniLibX** (macOS, or Linux with X11 dependencies). The MiniLibX library is already included and configured within the project.

### Compilation

Open your terminal, navigate to the project folder, and compile the source code using `make`:

```bash
# Compile the project
make
```

### Execution

Once compiled, you can launch the game by passing a valid `.cub` map configuration file as an argument:

```bash
# Run the game with a sample map
./cub3d maps/map.cub
```
