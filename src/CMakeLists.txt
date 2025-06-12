add_library(student_core
    Student.cpp
    StudentRegistry.cpp
    Course.cpp
    CourseRegistry.cpp
    Enrollment.cpp
    EnrollmentManager.cpp
    WaitlistManager.cpp
)

target_include_directories(student_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Console application (existing)
add_executable(student_app main.cpp)
target_link_libraries(student_app PRIVATE student_core)

# Standalone application with interactive menu (NEW - works without dependencies)
add_executable(student_standalone standalone_main.cpp)
target_link_libraries(student_standalone PRIVATE student_core)

# GUI application (only if dependencies are available)
if(BUILD_GUI)
    add_executable(student_gui 
        gui_main.cpp
        StudentEnrollmentApp.cpp
    )

    target_link_libraries(student_gui PRIVATE 
        student_core
        imgui::imgui
        glfw
        glad::glad
    )
    
    message(STATUS "Building GUI application: student_gui")
else()
    message(STATUS "Skipping GUI application (missing dependencies)")
endif() 