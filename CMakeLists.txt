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

# Set RPATH so the executable finds SDL3 in the same directory at runtime
set_target_properties(minesweeper-c PROPERTIES
        INSTALL_RPATH "$<IF:$<PLATFORM_ID:Darwin>,@executable_path,\$ORIGIN>"
)

# Install the game executable and SDL3 shared library
install(TARGETS minesweeper-c SDL3-shared
        RUNTIME DESTINATION .
        LIBRARY DESTINATION .
)
