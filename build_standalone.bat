@echo off
echo Building Student Enrollment System (Standalone Interactive)...
echo.

REM Clean previous build
if exist build_standalone rmdir /s /q build_standalone

REM Configure and build
cmake -S . -B build_standalone -G Ninja
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

cmake --build build_standalone
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful! Starting interactive application...
echo.
.\build_standalone\src\student_standalone.exe

echo.
echo Press any key to exit...
pause >nul 