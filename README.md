# 3D Renderer

A 3D rendering engine built from scratch in C++ using modern OpenGL.

The goal of this project is to learn how a real-time renderer works internally, beginning with OpenGL fundamentals and progressively building higher-level rendering systems and abstractions.

## Current Stack

- C++20
- OpenGL 3.3 Core
- GLFW
- GLAD
- CMake
- Ninja
- MinGW / GCC
- JetBrains Rider

## Project Status

### Phase 1 — OpenGL Foundation ✅

- [x] Create CMake project structure
- [x] Add GLFW
- [x] Add GLAD
- [x] Create an application window
- [x] Create an OpenGL 3.3 Core context
- [x] Initialize GLAD
- [x] Add the main application loop
- [x] Clear the framebuffer
- [x] Handle framebuffer resizing with `glViewport`

### Phase 2 — First Geometry ✅

- [x] Define triangle vertex data
- [x] Create a Vertex Buffer Object (VBO)
- [x] Create a Vertex Array Object (VAO)
- [x] Configure vertex attributes
- [x] Create a vertex shader
- [x] Create a fragment shader
- [x] Load shaders from external `.glsl` files
- [x] Compile shaders
- [x] Link a shader program
- [x] Render the first triangle with `glDrawArrays`
- [x] Add shader files to the CMake build environment

## Phase 3 — Renderer Resource Abstractions ✅

The goal of this phase was to move raw OpenGL resource ownership out of `main.cpp` and into reusable C++ classes.

### Shader ✅

- [x] Create `Shader.h` and `Shader.cpp`
- [x] Load shader files
- [x] Compile vertex and fragment shaders
- [x] Link the OpenGL program
- [x] Store the OpenGL program ID
- [x] Implement `Shader::use()`
- [x] Delete the OpenGL program automatically in the destructor
- [x] Remove the original shader helper functions from `main.cpp`

### VertexBuffer ✅

- [x] Create `VertexBuffer.h` and `VertexBuffer.cpp`
- [x] Generate and own a VBO
- [x] Upload vertex data with `glBufferData`
- [x] Implement bind / unbind
- [x] Delete the VBO automatically in the destructor
- [x] Remove raw VBO ownership from application code

### VertexArray ✅

- [x] Create `VertexArray.h` and `VertexArray.cpp`
- [x] Generate and own a VAO
- [x] Implement bind / unbind
- [x] Delete the VAO automatically in the destructor
- [x] Remove raw VAO ownership from application code

## Phase 4 — Application Structure ✅

The goal of this phase was to separate application coordination from platform and rendering implementation details.

### Application ✅

- [x] Create `Application.h` and `Application.cpp`
- [x] Move application execution out of `main.cpp`
- [x] Add `Application::run()`
- [x] Reduce `main.cpp` to application creation and execution

Target entry point achieved:

```cpp
#include "core/Application.h"

int main()
{
    Application application;
    return application.run();
}
```

### Window ✅

- [x] Create `Window.h` and `Window.cpp`
- [x] Move GLFW initialization into `Window`
- [x] Move OpenGL context creation into `Window`
- [x] Move GLAD initialization into `Window`
- [x] Move framebuffer resize handling into `Window`
- [x] Add `Window::isValid()`
- [x] Add `Window::shouldClose()`
- [x] Add buffer swapping
- [x] Add event polling
- [x] Destroy the GLFW window and terminate GLFW automatically

### Renderer ✅

- [x] Create `Renderer.h` and `Renderer.cpp`
- [x] Move framebuffer clearing into `Renderer`
- [x] Move `glDrawArrays` into `Renderer`
- [x] Keep raw draw commands out of `Application.cpp`

### VertexBufferLayout ✅

- [x] Create `VertexBufferLayout.h` and `VertexBufferLayout.cpp`
- [x] Introduce `VertexBufferElement`
- [x] Store vertex attribute descriptions
- [x] Calculate vertex stride automatically
- [x] Add float attributes with `pushFloat()`
- [x] Add `VertexArray::addBuffer()`
- [x] Move `glVertexAttribPointer` out of `Application.cpp`
- [x] Move `glEnableVertexAttribArray` out of `Application.cpp`
- [x] Remove direct GLAD usage from `Application.cpp`

Current separation:

```text
main.cpp
   ↓
Application
   ├── Window
   ├── Renderer
   ├── Shader
   ├── VertexBuffer
   ├── VertexArray
   └── VertexBufferLayout
```

`Application` now coordinates the system without directly calling GLFW or raw OpenGL functions.

## Phase 5 — Geometry / Mesh Abstraction ✅

The goal of this phase was to remove geometry ownership and buffer setup from `Application.cpp` and introduce reusable CPU-side and GPU-side geometry abstractions.

### Mesh ✅

- [x] Create `Mesh.h`
- [x] Create `Mesh.cpp`
- [x] Let `Mesh` own its `VertexBuffer`
- [x] Let `Mesh` own its `VertexArray`
- [x] Let `Mesh` configure its `VertexBufferLayout`
- [x] Store the vertex count in `Mesh`
- [x] Allow `Renderer` to draw a `Mesh` directly
- [x] Keep OpenGL resource lifetime automatic
- [x] Render the same triangle through the new abstraction

### MeshData and Primitives ✅

- [x] Create `MeshData`
- [x] Store CPU-side vertex data in `MeshData`
- [x] Create `Primitives`
- [x] Move triangle coordinates out of `Application.cpp`
- [x] Add `Primitives::triangle()`
- [x] Construct `Mesh` from `MeshData`
- [x] Remove raw geometry details from `Application.cpp`

Current geometry flow:

```text
Primitives
    ↓
MeshData
    ↓
Mesh
├── VertexBuffer
├── VertexArray
├── VertexBufferLayout
└── vertex count
    ↓
Renderer
```

`Application` now only needs to know which mesh it wants to create and when it should be rendered.

## Phase 6 — Vertex Data 🚧

Current phase.

Learn how richer information can be passed through the graphics pipeline.

- [ ] Add vertex colors
- [ ] Add multiple vertex attributes
- [ ] Deepen understanding of stride and offsets
- [ ] Pass color data from the vertex shader to the fragment shader
- [ ] Observe shader interpolation across a triangle
- [ ] Create an Index Buffer / Element Buffer Object (EBO)
- [ ] Create an `IndexBuffer` abstraction
- [ ] Render a rectangle using indexed drawing

Target pipeline:

```text
CPU vertex data
      ↓
Mesh
      ↓
VBO + VAO + Layout
      ↓
Vertex Shader
      ↓
Rasterizer
      ↓
Fragment Shader
      ↓
Framebuffer
```

## Phase 7 — Transformations

Move from static geometry toward a real 3D renderer.

- [ ] Add GLM
- [ ] Learn vectors and matrices
- [ ] Translation
- [ ] Rotation
- [ ] Scaling
- [ ] Model matrix
- [ ] View matrix
- [ ] Projection matrix
- [ ] Perspective projection
- [ ] Send matrices to shaders using uniforms

Target pipeline:

```text
Local Space
    ↓
Model Matrix
    ↓
World Space
    ↓
View Matrix
    ↓
View Space
    ↓
Projection Matrix
    ↓
Clip Space
```

## Phase 8 — Textures

- [ ] Load image files
- [ ] Create OpenGL textures
- [ ] Configure texture parameters
- [ ] Add UV coordinates to vertices
- [ ] Pass UV coordinates through shaders
- [ ] Use texture samplers
- [ ] Render textured geometry
- [ ] Support multiple textures

## Phase 9 — Camera

- [ ] Create a `Camera` class
- [ ] Camera position
- [ ] Camera direction
- [ ] View matrix
- [ ] Keyboard movement
- [ ] Mouse movement
- [ ] FPS-style camera controls
- [ ] Field-of-view control

At this stage the renderer should allow free movement through a 3D scene.

## Phase 10 — 3D Geometry

- [ ] Enable depth testing
- [ ] Understand the depth buffer
- [ ] Render a cube
- [ ] Render multiple meshes
- [ ] Expand the `Mesh` abstraction for reusable 3D geometry
- [ ] Separate object transforms from mesh data

## Phase 11 — Lighting

- [ ] Surface normals
- [ ] Normal attributes
- [ ] Ambient lighting
- [ ] Diffuse lighting
- [ ] Specular lighting
- [ ] Phong / Blinn-Phong lighting
- [ ] Directional lights
- [ ] Point lights
- [ ] Spotlights
- [ ] Multiple lights

## Phase 12 — Model Loading

- [ ] Investigate Assimp or another model-loading library
- [ ] Load external 3D models
- [ ] Load meshes
- [ ] Load model textures
- [ ] Support multiple meshes per model
- [ ] Create a `Model` abstraction

Potential formats:

- OBJ
- FBX
- glTF

## Phase 13 — Framebuffers and Post-Processing

- [ ] Create custom framebuffers
- [ ] Render the scene into a texture
- [ ] Screen-space quad
- [ ] Grayscale effect
- [ ] Color inversion
- [ ] Basic post-processing effects

## Phase 14 — Advanced Rendering

Possible later additions:

- [ ] Shadow mapping
- [ ] Skyboxes / cubemaps
- [ ] Environment mapping
- [ ] Instanced rendering
- [ ] HDR
- [ ] Bloom
- [ ] Gamma correction
- [ ] Normal mapping
- [ ] PBR
- [ ] Deferred rendering
- [ ] Frustum culling

These features are intentionally left until the renderer fundamentals and architecture are stable.

## Planned Renderer Architecture

The project will gradually evolve toward:

```text
3D-Renderer/
│
├── assets/
│   ├── models/
│   └── textures/
│
├── shaders/
│   ├── vertex.glsl
│   └── fragment.glsl
│
├── src/
│   ├── main.cpp
│   │
│   ├── core/
│   │   ├── Application.h
│   │   ├── Application.cpp
│   │   ├── Window.h
│   │   └── Window.cpp
│   │
│   └── renderer/
│       ├── Renderer.h
│       ├── Renderer.cpp
│       ├── Shader.h
│       ├── Shader.cpp
│       ├── VertexBuffer.h
│       ├── VertexBuffer.cpp
│       ├── VertexArray.h
│       ├── VertexArray.cpp
│       ├── VertexBufferLayout.h
│       ├── VertexBufferLayout.cpp
│       ├── Mesh.h
│       ├── Mesh.cpp
│       ├── MeshData.h
│       ├── Primitives.h
│       ├── Primitives.cpp
│       ├── IndexBuffer.h
│       ├── IndexBuffer.cpp
│       ├── Texture.h
│       ├── Texture.cpp
│       ├── Camera.h
│       └── Camera.cpp
│
├── tests/
├── CMakeLists.txt
└── README.md
```

This is a target architecture and will continue to evolve as new renderer concepts are learned.

## Architectural Responsibilities

```text
main.cpp
   └── starts the application

Application
   ├── coordinates program lifetime
   └── runs the application loop

Window
   ├── owns the GLFW window
   ├── owns the OpenGL context lifetime
   └── handles platform/window events

Renderer
   ├── clears render targets
   └── issues draw commands

Shader
   └── owns an OpenGL shader program

VertexBuffer
   └── owns an OpenGL VBO

VertexBufferLayout
   └── describes vertex memory layout

VertexArray
   └── owns a VAO and connects buffers to layouts

MeshData
   └── stores CPU-side geometry data

Primitives
   └── creates predefined geometry data

Mesh
   └── owns reusable GPU geometry and its rendering resources
```

The aim is not merely to move code into different files. Each class should have a clear responsibility and ownership model.

## OpenGL Resource Lifetime

OpenGL resources must be destroyed while the OpenGL context still exists.

```text
Create Window / OpenGL context
            ↓
Create renderer resources
            ↓
Run application
            ↓
Destroy renderer resources
            ↓
Destroy Window / OpenGL context
```

The C++ classes use destructors to make this cleanup automatic.

## Development Philosophy

The renderer is being built incrementally.

Each feature should follow this process:

```text
Understand the concept
        ↓
Implement the smallest working version
        ↓
Build and test
        ↓
Understand the OpenGL calls involved
        ↓
Refactor when appropriate
        ↓
Commit
        ↓
Create Pull Request
        ↓
Merge into main
```

The objective is not only to make the renderer work, but to understand why each part works.

## Git Workflow

Development is done using feature branches.

For the current phase:

```bash
git switch main
git pull origin main
git switch -c feature/vertex-data
```

After completing and testing the feature:

```bash
git status
git add .
git commit -m "Add vertex color attributes"
git push -u origin feature/vertex-data
```

Then create a Pull Request and merge it into `main`.

After merging:

```bash
git switch main
git pull origin main
```

## Current Next Step

The next task is:

> Extend the vertex format with color data and learn how multiple vertex attributes are passed through the rendering pipeline.

The immediate implementation sequence will be:

```text
Add color values to vertex data
        ↓
Add a second layout attribute
        ↓
Understand stride and attribute offsets
        ↓
Update the vertex shader
        ↓
Pass color to the fragment shader
        ↓
Observe interpolation across the triangle
```

This begins Phase 6 — Vertex Data.

---

This project is primarily a learning project focused on understanding graphics programming, modern OpenGL, C++ architecture, and the internal structure of a real-time renderer.
