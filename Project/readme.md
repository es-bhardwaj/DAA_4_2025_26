## Maze Solver - Dijkstra Visualizer

A pathfinding tool demonstrating **Dijkstra's Algorithm** through a C++ reference and an interactive web interface.

## Project Structure
* `maze-solver.cpp`: Standalone C++ implementation for reference.
* `/web-implementation`: Web-based GUI built with HTML, CSS, and JavaScript.

## Algorithm Logic
* **Dijkstra’s Algorithm**: Treats the grid as a weighted graph to find the absolute shortest path.
* **Min-Heap (Priority Queue)**: Optimizes the search by always exploring the node with the lowest cumulative cost first. 
* **Backtracking**: The final path is reconstructed by traversing "parent" pointers from the destination back to the source.

## Usage
1.  Open `index.html` in a browser.
2.  Set grid size and click **Generate**.
3.  Choose a mode to draw walls, place the **Start (S)**, **End (E)**.
4.  Click **Solve Path** to visualize the Dijkstra traversal.

## Complexity Analysis
Based on the implementation in maze-solver.cpp and the visualizer:
* **Time Complexity**: O((V + E) / log V) <br>
V is the number of vertices (cells in the grid). <br>
E is the number of edges (possible moves to neighbors). <br>
The log V factor comes from the Min-Heap (Priority Queue) operations used to extract the minimum distance node.
* **Space Complexity**: O(V) <br>
We store a 2D distance array and a parent map, both proportional to the number of cells in the grid.
