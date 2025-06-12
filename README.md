# Student Enrollment System

A modern C++ application for managing student enrollments, courses, and waitlists.

## Features
- Register students and courses
- Manage enrollments and waitlists
- Console and GUI modes
- Modular, maintainable codebase

## Build Instructions

### Prerequisites
- CMake (3.15+)
- C++17 compatible compiler
- [vcpkg](https://github.com/microsoft/vcpkg) for dependency management

### Build (Console)
```sh
./build_console.bat
```

### Build (Standalone)
```sh
./build_standalone.bat
```

### Build (GUI)
```sh
# With vcpkg
cmake -S . -B build_gui -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build build_gui
./build_gui/src/student_gui.exe
```

## Project Structure
- `src/` - Source code
- `build/`, `build_standalone/`, `build_gui/` - Build artifacts (ignored in git)
- `vcpkg/` - Dependency manager

## Usage
- Standalone: Menu-driven interface for student, course, enrollment, and waitlist management
- Console: Demonstrates core features
- GUI: Graphical interface for all management features

## Code Quality
- Memory safety: smart pointers, RAII
- Const correctness
- Exception safety
- Modern C++ best practices

## Contributing
Pull requests are welcome. For major changes, please open an issue first.

## License

This project is licensed under the MIT License. See the LICENSE.txt file for details.

**This code is provided for public use. You are free to use, modify, and distribute it under the terms of the MIT License.**

