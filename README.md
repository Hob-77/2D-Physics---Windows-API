# 2D Physics Engine (Windows API + OpenGL)
Early physics engine prototype built while learning Windows API and OpenGL fundamentals.

## Overview
This project represents my first attempt at building a physics engine from scratch. While learning the Windows API for window management and OpenGL for rendering, I implemented basic physics simulation with proper fixed timestep integration.

## Features Implemented
- **Windows API Integration**: Custom window class using Win32 API
- **OpenGL Rendering**: Basic shader-based rendering system
- **Physics Simulation**:
  - Velocity and position integration
  - Gravity simulation
  - Wall bouncing with restitution
  - Air resistance
  - Ground friction
  - Fixed timestep with interpolation (Glenn Fiedler's method)
  
## Technical Highlights
- Custom Vec2 math class
- Input management system
- Shader-based renderer with orthographic projection
- Proper game loop with accumulator-based fixed timestep
- State interpolation for smooth rendering

## Architecture
- `BaseWindow`: Template-based Win32 window wrapper
- `SimpleRenderer`: OpenGL 4.6 shader-based rendering
- `InputManager`: Mouse and keyboard input handling
- `PhysicsState`: Position/velocity state with interpolation

## What I Learned
This project taught me:
- Low-level Windows API programming
- OpenGL initialization and rendering pipeline
- Importance of fixed timestep for deterministic physics
- Frame interpolation for smooth visual results

## Note
While this implementation worked, I later moved to SDL for cross-platform support and built a more comprehensive physics engine with collision detection, as seen in my 2D Physics Engine project.
