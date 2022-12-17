# FdF

This wire frame viewer for Linux is a project from my core curriculum at 42 Vienna. It shows .fdf-Files as a wireframe model in isometric projection.
FdF stands for fil de fer which means wireframe in French.
The mandatory part just displays the wireframe model.
The bonus part allows the user to move the model with the keyboard.
It was coded according to the school norm which prohibits i.e. for-loops.

## Video Demonstration
Click the image to watch a short video on YouTube:
[![Video demonstrating some test_maps with the fdf wire frame model viewer](https://img.youtube.com/vi/Ov3ljgXXIAQ/maxresdefault.jpg)](https://www.youtube.com/watch?v=Ov3ljgXXIAQ)

## Installation
1. Clone the repository
2. Install Dependencies
```
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```
3. Build Mandatory Part (Wireframe Viewer)
```
make
```
4. Build Bonus Part (Wireframe Viewer Controllable By user)
```
make bonus
```

## Usage
Mandatory Part:
```./fdf test_maps/<test_map_file>```

Bonus Part:
```./fdf_bonus test_maps/<test_map_file>```
