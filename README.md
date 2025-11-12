# miniRT

A basic ray tracer implementation in C.

## Description

miniRT is a simple ray tracer that renders 3D scenes. This project is part of the 42 curriculum.

## Features

- Basic ray tracing engine
- Multiple geometric objects support
- Light and shadow rendering
- Scene configuration via .rt files

## Dependencies

- MinilibX (included in `libs/minilibx-linux/`)
- libft (included in `libs/libft/`)
- X11 libraries

## Installation

```bash
make
```

## Usage

```bash
./miniRT [scene_file.rt]
```

## Project Structure

```
miniRT/
├── include/        # Header files
├── src/           # Source files
├── libs/          # External libraries
│   ├── libft/     # Custom C library
│   └── minilibx-linux/  # Graphics library
└── Makefile
```

## Author

rfleritt

## License

This project is part of the 42 School curriculum.
