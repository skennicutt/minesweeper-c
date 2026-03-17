cmake_minimum_required(VERSION 3.21)
project(minesweeper-c)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

# Create your game executable target as usual
add_executable(minesweeper-c WIN32 main.cpp)

# Link to the actual SDL3 library.
target_link_libraries(minesweeper-c PRIVATE SDL3::SDL3)

# Enable all compiler warnings
target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:-Wall -Wextra -Wpedantic -Werror>
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

# Install the game executable
install(TARGETS minesweeper-c
        RUNTIME DESTINATION .
)

# Install SDL3 runtime DLLs alongside the executable (Windows only)
install(FILES $<TARGET_RUNTIME_DLLS:minesweeper-c>
        DESTINATION .
        CONFIGURATIONS Release
)
