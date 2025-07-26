# 2D Physics Engine (Windows API + OpenGL)
Physics engine built using Windows API and OpenGL, created before my 2D platformer engine with level editor.

## Overview
A focused physics simulation project exploring Windows API for window management and OpenGL for rendering. This engine implements proper fixed timestep physics simulation with interpolation.

## Features
- **Windows API Integration**: Custom window class using Win32 API
- **OpenGL Rendering**: Shader-based rendering with OpenGL 4.6
- **Physics Simulation**:
  - Velocity-based movement with gravity
  - Collision response with walls (restitution/bouncing)
  - Air resistance simulation
  - Ground friction when in contact
  - Fixed timestep with interpolation (Glenn Fiedler's method)
  
## Technical Implementation
- **Fixed Timestep Loop**: Deterministic physics at 100 Hz (dt = 0.01)
- **State Interpolation**: Smooth rendering between physics steps
- **Custom Math**: Vec2 class for 2D vector operations
- **Modern OpenGL**: Shader-based rendering pipeline
- **High-precision Timing**: QueryPerformanceCounter for accurate frame timing

## Architecture
- `BaseWindow`: Template-based Win32 window wrapper
- `SimpleRenderer`: VAO/VBO-based rendering with GLSL shaders
- `InputManager`: Mouse input handling (framework for interaction)
- `PhysicsState`: Interpolatable physics state

## Key Learning
This project solidified my understanding of:
- Game loop architecture with fixed timestep
- Separating physics updates from rendering
- Low-level Windows API programming
- Modern OpenGL practices

## Evolution
After this project, I moved to SDL for my next engine (2D platformer with editor) for cross-platform support, but the physics and architecture knowledge from this project carried forward.
