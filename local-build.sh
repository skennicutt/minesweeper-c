#!/usr/bin/env bash

set -euo pipefail

repo_dir="$(cd "$(dirname "$0")" && pwd)"
build_dir="$repo_dir/build"

# SDL's CMake files use file(GLOB ...). CMake treats square brackets in paths
# as glob syntax, so configure through a bracket-free symlink for local builds.
link_hash="$(printf '%s' "$repo_dir" | shasum | awk '{print substr($1, 1, 12)}')"
link_dir="${TMPDIR:-/tmp}/minesweeper-c-src-$link_hash"

rm -f "$link_dir"
ln -s "$repo_dir" "$link_dir"

if [ -f "$build_dir/CMakeCache.txt" ] && ! grep -q "^CMAKE_HOME_DIRECTORY:INTERNAL=$link_dir$" "$build_dir/CMakeCache.txt"; then
    rm -rf "$build_dir"
fi

cmake -S "$link_dir" -B "$build_dir"
cmake --build "$build_dir"
