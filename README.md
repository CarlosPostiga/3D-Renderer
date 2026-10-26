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

## Phase 3 — Renderer Structure 🚧

Current phase.

The goal of this phase is to move OpenGL implementation details out of `main.cpp` and start building reusable renderer components.

### Shader Class

- [x] Create `Shader.h`
- [x] Create `Shader.cpp`
- [x] Move shader file loading into `Shader`
- [x] Move shader compilation into `Shader`
- [ ] Make the `Shader` constructor load both shader files
- [ ] Compile the vertex shader
- [ ] Compile the fragment shader
- [ ] Link them into an OpenGL program
- [ ] Store the OpenGL program ID
- [ ] Implement `Shader::use()`
- [ ] Implement shader cleanup in the destructor
- [ ] Remove the old shader helper functions from `main.cpp`

Expected usage:

```cpp
Shader shader(
    "shaders/vertex.glsl",
    "shaders/fragment.glsl"
);

shader.use();
```

### Buffer Abstractions

After the Shader class is complete:

- [ ] Create a `VertexBuffer` class
- [ ] Create a `VertexArray` class
- [ ] Move VBO logic out of `main.cpp`
- [ ] Move VAO logic out of `main.cpp`
- [ ] Handle OpenGL resource cleanup automatically

## Phase 4 — Vertex Data

Learn how more information can be passed through the graphics pipeline.

- [ ] Add vertex colors
- [ ] Add multiple vertex attributes
- [ ] Understand vertex stride and offsets
- [ ] Pass color data from the vertex shader to the fragment shader
- [ ] Observe shader interpolation across a triangle
- [ ] Create an Index Buffer / Element Buffer Object (EBO)
- [ ] Render a rectangle using indexed drawing

Target concepts:

```text
CPU vertex data
      ↓
VBO
      ↓
VAO
      ↓
Vertex Shader
      ↓
Rasterizer
      ↓
Fragment Shader
      ↓
Framebuffer
```

## Phase 5 — Transformations

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

## Phase 6 — Textures

- [ ] Load image files
- [ ] Create OpenGL textures
- [ ] Configure texture parameters
- [ ] Add UV coordinates to vertices
- [ ] Pass UV coordinates through shaders
- [ ] Use texture samplers
- [ ] Render textured geometry
- [ ] Support multiple textures

## Phase 7 — Camera

- [ ] Create a Camera class
- [ ] Camera position
- [ ] Camera direction
- [ ] View matrix
- [ ] Keyboard movement
- [ ] Mouse movement
- [ ] FPS-style camera controls
- [ ] Field-of-view control

At this stage the renderer should allow free movement through a 3D scene.

## Phase 8 — 3D Geometry

- [ ] Enable depth testing
- [ ] Understand the depth buffer
- [ ] Render a cube
- [ ] Render multiple objects
- [ ] Create reusable mesh data
- [ ] Introduce a `Mesh` class
- [ ] Separate object data from rendering logic

## Phase 9 — Lighting

Start implementing a basic lighting model.

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

## Phase 10 — Model Loading

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

## Phase 11 — Framebuffers and Post-Processing

- [ ] Create custom framebuffers
- [ ] Render the scene into a texture
- [ ] Screen-space quad
- [ ] Grayscale effect
- [ ] Color inversion
- [ ] Basic post-processing effects

## Phase 12 — Advanced Rendering

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

The project will gradually evolve toward a structure similar to:

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
│   └── renderer/
│       ├── Shader.h
│       ├── Shader.cpp
│       ├── VertexBuffer.h
│       ├── VertexBuffer.cpp
│       ├── VertexArray.h
│       ├── VertexArray.cpp
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

This structure is a target rather than something that needs to be created all at once.

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

Example:

```bash
git switch main
git pull origin main
git switch -c feature/shader-class
```

After completing and testing the feature:

```bash
git status
git add .
git commit -m "Implement Shader class"
git push -u origin feature/shader-class
```

Then create a Pull Request:

```text
feature/shader-class
        ↓
       main
```

After merging:

```bash
git switch main
git pull origin main
```

Then start the next feature from the updated `main`.

## Current Next Step

The current task is:

> Complete the `Shader` class constructor.

The constructor will perform:

```text
Shader(vertexPath, fragmentPath)
            ↓
     Read shader files
            ↓
   Compile vertex shader
            ↓
  Compile fragment shader
            ↓
      Create program
            ↓
      Attach shaders
            ↓
       Link program
            ↓
      Store programID
            ↓
 Delete temporary shader objects
```

Once this works, `main.cpp` will use the new `Shader` class instead of handling shader compilation directly.

---

This project is primarily a learning project focused on understanding graphics programming, modern OpenGL, C++ architecture, and the internal structure of a real-time renderer.
