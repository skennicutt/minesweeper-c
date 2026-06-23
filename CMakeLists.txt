cmake_minimum_required(VERSION 3.21)
project(minesweeper-c)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# Disable SDL features that require unavailable system packages on Fedora 44
set(SDL_X11_XSCRNSAVER OFF CACHE BOOL "" FORCE)
set(SDL_VULKAN OFF CACHE BOOL "" FORCE)

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Use vendored libpng/zlib to avoid requiring system static libs (e.g. libpng-static)
set(SDLIMAGE_VENDORED ON CACHE BOOL "" FORCE)

# Disable image formats not needed by this project (also avoids build tool / system lib conflicts)
set(SDLIMAGE_AVIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_TIF OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_WEBP OFF CACHE BOOL "" FORCE)
set(SDLIMAGE_JXL OFF CACHE BOOL "" FORCE)

# This assumes the SDL_image source is available in vendored/SDL_image
add_subdirectory(vendored/SDL_image EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(minesweeper-c WIN32 main.cpp)

# Link to the actual SDL3 and SDL3_image libraries.
target_link_libraries(minesweeper-c PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

# Enable all compiler warnings
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall -Wextra -Wpedantic -Werror>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# Set RPATH so the executable finds SDL3 in the same directory at runtime
set_target_properties(minesweeper-c PROPERTIES
        INSTALL_RPATH "$<IF:$<PLATFORM_ID:Darwin>,@executable_path,\$ORIGIN>"
)

# Install the game executable, SDL3, and SDL3_image shared libraries
install(TARGETS minesweeper-c SDL3-shared SDL3_image-shared
        RUNTIME DESTINATION .
        LIBRARY DESTINATION .
)

# Install game assets
install(DIRECTORY images/ DESTINATION images)
