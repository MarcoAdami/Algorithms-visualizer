# Sorting Algorithm Visualizer

A C++ program that provides a visual representation of various sorting algorithms in action. Watch how different sorting algorithms reorganize arrays in real-time, represented as rectangles of varying heights.

## Features

### Implemented Sorting Algorithms
- Bubble Sort (key 1)
- Merge Sort  (key 2)
- Shaker Sort (key 3)
- Quick Sort (key 4)
- Radix Sort (key 5)
- Shell Sort (key 6)

### Visualization Controls
- **S key**: Shuffle blocks 
- **Up/Down Arrow Keys**: Control animation speed
- **Left/Right Arrow Keys**: Adjust number of blocks (up to 100,000)
- Real-time visualization of block swaps
- Dedicated frames for blocks and algorithm description
- Multi-threaded algorithm execution for smooth visualization

### Performance Optimizations
- Utilizes vertex and vertexBuffer for efficient rendering
- Supports up to 1,000,000 blocks
- Thread separation for algorithm execution and visualization

## Technical Implementation

### Core Components
- Custom class architecture for maintainable code
- Multi-threaded design separating visualization and sorting logic
- Optimized rendering using vertex buffers
- Modular algorithm implementation system

## Project Status

### Completed Features

#### Logic
- [x] Class-based architecture implementation
- [x] Multi-threaded algorithm execution
- [x] Six sorting algorithms implemented
- [x] Dynamic speed control
- [x] Scalable block count (up to 100,000)

#### Performance
- [x] Vertex buffer optimization
- [x] High-performance rendering system

#### Visualization
- [x] Block frame implementation
- [x] Description frame
- [x] Active swap visualization

### Upcoming Features

#### Logic
- [ ] Window resizing functionality
- [ ] Graph algorithm support (BFS, DFS)

#### Performance
- [ ] Further CPU optimization

#### Visualization
- [ ] Algorithm specifications panel
- [ ] Statistical analysis features:
  - Algorithm comparison metrics
  - Performance graphs
  - Block size impact analysis
