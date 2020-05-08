# OpenGl Basic Overview

OpenGl provides a multi-stage graphics pipeline partially programmable in the *GLSL* shading language.

Modern graphics programming utilizes a pipeline, a series of steps, in order to convert a 3D scene to a 2D image.

At it's simplest, the pipeline works by having an application send graphics data into the **vertex shader**, from which processing proceeds through the graphics pipeline until pixels emerge for display to a monitor.

At minimum, it's usually required to provide a *vertex* and *fragment* shader for the pipeline.

## Primitives

OpenGL is only capable of ultimately drawing a few basic shapes, such as *points*, *lines*, and *triangles*. They are referred to as **primitives**.
