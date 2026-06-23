# minesweeper-c

A Minesweeper clone written in C++ using SDL3.

## Requirements

- CMake 3.21+
- A C++ compiler (GCC, Clang, or MSVC)
- Git (for submodules)

SDL3 and SDL3_image are vendored as submodules and built from source — no system SDL installation required.

## Building

Clone the repository with submodules:

```bash
git clone --recurse-submodules <repo-url>
cd minesweeper-c
```

Or clone the repo first and initialize the submodules after.
```
git submodule update --init --recursive
```
```
```

Then build:

```bash
./local-build.sh
```

Or manually:

```bash
cmake -S . -B build
cmake --build build
```

The binary is placed in `build/`.

## Running

From the `build/` directory:

```bash
./minesweeper-c
```

The game expects the `images/` directory to be present relative to the working directory. When building with `cmake --install`, assets are copied automatically.

## Controls

| Key | Action |
|-----|--------|
| Escape | Quit |

## Project Structure

```
minesweeper-c/
├── main.cpp        # Entry point, game loop, window/renderer setup
├── main.h          # Global constants and includes
├── border.cpp/h    # Border rendering component
├── utils.h         # Sprite sheet loading, utility functions
├── images/         # Game assets (sprite sheets, icon)
├── vendored/       # SDL3 and SDL3_image source (git submodules)
├── CMakeLists.txt  # Build configuration
├── steam/          # Steam deployment config
└── gog/            # GOG deployment config
```

## License

MIT — see [LICENSE](LICENSE).
