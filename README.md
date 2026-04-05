*This project has been created as part of the 42 curriculum by rfleritt(Ricardo Fleritt), nroson-m(Nicolas Rosón).*

## Description

miniRT is a basic ray tracer written in C using the MiniLibX library.
It renders 3D scenes defined in .rt files, supporting spheres, planes and
cylinders with ambient and diffuse lighting, hard shadows, and a full Phong
model.

## Instructions

**Dependencies (Linux):**
```bash
sudo apt install libglfw3-dev cmake
```

**Compile:**
```bash
make
```

**Run:**
```bash
./miniRT scene/example.rt
```

**Controls:**
- `ESC` — close the window

## Resources

- [Scratchapixel — Ray Tracing from scratch](https://www.scratchapixel.com)
- [Ray Tracing in One Weekend — Peter Shirley](https://raytracing.github.io)
- [MLX42 documentation](https://github.com/codam-coding-college/MLX42)

**AI usage:** Claude was used to help plan the development roadmap, 
understand mathematical concepts (ray-sphere intersection, Phong lighting model),
and review edge cases in the parser. All code was written and understood by the authors.