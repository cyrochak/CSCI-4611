# CSCI4611_Project_03
## Information
* Name: Tiannan Zhou
* Student ID: 5232494
* Email: zhou0745@umn.edu

## Config
Please replace the value of `dataDir` in `config.hpp` file with the full path of your data folder to make sure that the program can find the earthquake and map resources.

## Compile
This program is based on Linux and you just need to use GNU Makefile to compile the whole project.
```
make
```
The recommended environment for compiling this project is CSELAB Ubuntu Linux 16.04.

## Run
You can find a executive program which is named `EarthquakeVisualization` in the folder the source code located in. You also can simply run command `./EarthquakeVisualization` in terminal to start this session.

## Description
1. This project is based on OpenGL and GLM libiary.
2. I used different colors to represent different magnitudes of earthquakes. Earthquakes with magnitude which is smaller than 7.0 would be represented by red, which means this is a serious earthquake. Earthquakes with magnitude which is not less than 7.0 would be marked by purple, which means this is a very senior earthquake. The initial size of every earthquake is determined by the magnitude of this earthquake. The magnitude is bigger, the initial size of marker will be bigger. This can help readers to know which earthquake's situation is heavier. The size would be shrunk to none while time flies.
3. I added a another feature that pressing `M` can switch the view between meshes, geo-map and height-map for the Earth. You can press `M` multiply to switch the view from one to another one.
