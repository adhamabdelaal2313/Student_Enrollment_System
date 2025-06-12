@echo off
echo Building Student Enrollment System (Console)...
echo.

REM Clean previous build
if exist build rmdir /s /q build

REM Configure and build
cmake -S . -B build -G Ninja
if %errorlevel% neq 0 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

cmake --build build
if %errorlevel% neq 0 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful! Running demo...
echo.
.\build\src\student_app.exe

echo.
echo Press any key to exit...
pause >nul 