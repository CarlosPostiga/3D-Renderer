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

## Phase 5 — Geometry / Mesh Abstraction 🚧

Current phase.

The next goal is to remove geometry ownership and buffer setup from `Application.cpp`.

Right now the application still knows:

- The triangle's raw vertex values
- How many vertices the triangle contains
- That a VAO, VBO, and vertex layout must be created for the geometry

Those responsibilities should move into a reusable geometry abstraction.

### Mesh

- [ ] Create `Mesh.h`
- [ ] Create `Mesh.cpp`
- [ ] Move triangle vertex data out of `Application.cpp`
- [ ] Let `Mesh` own its `VertexBuffer`
- [ ] Let `Mesh` own its `VertexArray`
- [ ] Let `Mesh` own or configure its `VertexBufferLayout`
- [ ] Store the vertex count in `Mesh`
- [ ] Expose the information needed by `Renderer`
- [ ] Keep OpenGL resource lifetime automatic
- [ ] Render the same triangle through the new abstraction

Target direction:

```text
Application
    ↓
Mesh
├── vertex data
├── VertexBuffer
├── VertexArray
├── VertexBufferLayout
└── vertex count
    ↓
Renderer
```

The first version will remain intentionally simple. The goal is to learn ownership and geometry structure before making `Mesh` generic enough for complex models.

## Phase 6 — Vertex Data

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

Mesh
   └── next: owns reusable geometry and its rendering resources
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

For the next phase:

```bash
git switch main
git pull origin main
git switch -c feature/mesh-abstraction
```

After completing and testing the feature:

```bash
git status
git add .
git commit -m "Introduce Mesh abstraction"
git push -u origin feature/mesh-abstraction
```

Then create a Pull Request and merge it into `main`.

After merging:

```bash
git switch main
git pull origin main
```

## Current Next Step

The next task is:

> Create the first `Mesh` abstraction and move triangle geometry ownership out of `Application.cpp`.

The first version should preserve the current output exactly:

```text
same window
same shaders
same triangle
same color
```

Only the architecture changes.

The immediate implementation sequence will be:

```text
Create Mesh.h / Mesh.cpp
        ↓
Give Mesh vertex data
        ↓
Create its VertexBuffer
        ↓
Create its VertexArray
        ↓
Create/configure its VertexBufferLayout
        ↓
Store vertex count
        ↓
Use Mesh from Application
        ↓
Render the same triangle
```

---

This project is primarily a learning project focused on understanding graphics programming, modern OpenGL, C++ architecture, and the internal structure of a real-time renderer.
