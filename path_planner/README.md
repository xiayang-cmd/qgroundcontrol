# Path Planner

This folder contains a minimal C++ reimplementation of the area/grid and corridor/strip planning algorithms from QGroundControl. The code provides:

- `AreaGridPlanner` – generates parallel transects covering a polygon.
- `CorridorStripPlanner` – generates offset transects along a polyline.
- Simple unit tests writing the resulting transects to text files in the `output/` directory.
- `python/plot_transects.py` – script that plots the generated transects with matplotlib.

## Building

```bash
mkdir build && cd build
cmake ..
make
```

## Running tests

```bash
./test_planner
```

This will generate `output/area_transects.txt` and `output/corridor_transects.txt`.

## Plotting results

After running the tests, execute:

```bash
python ../python/plot_transects.py ../output
```

which will create `area.png` and `corridor.png` images with the transects.
