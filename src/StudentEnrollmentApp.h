#pragma once

#include <memory>
#include <string>
#include <vector>
#include "StudentRegistry.h"
#include "CourseRegistry.h"
#include "EnrollmentManager.h"
#include "WaitlistManager.h"

// Main application class that manages the GUI and coordinates all subsystems
class StudentEnrollmentApp {
public:
    StudentEnrollmentApp();
    ~StudentEnrollmentApp();

    // Main application lifecycle
    bool initialize();
    void run();
    void shutdown();

private:
    // GUI rendering methods
    void renderMainMenuBar();
    void renderStudentManagement();
    void renderCourseManagement();
    void renderEnrollmentManagement();
    void renderReportsView();
    void renderWaitlistView();

    // Helper methods for GUI forms
    void renderAddStudentForm();
    void renderAddCourseForm();
    void renderEnrollStudentForm();

    // Application state
    bool m_showStudentWindow = true;
    bool m_showCourseWindow = true;
    bool m_showEnrollmentWindow = true;
    bool m_showReportsWindow = false;
    bool m_showWaitlistWindow = false;

    // Form state
    struct StudentForm {
        char name[256] = "";
        char email[256] = "";
        char phone[64] = "";
        char address[512] = "";
        int id = 0;
    } m_studentForm;

    struct CourseForm {
        char name[256] = "";
        char instructor[256] = "";
        int id = 0;
        int credits = 3;
        std::vector<int> prerequisites;
        char prerequisiteInput[256] = "";
    } m_courseForm;

    struct EnrollmentForm {
        int studentId = 0;
        int courseId = 0;
    } m_enrollmentForm;

    // Core business logic
    std::unique_ptr<StudentRegistry> m_students;
    std::unique_ptr<CourseRegistry> m_courses;
    std::unique_ptr<EnrollmentManager> m_enrollmentManager;
    std::unique_ptr<WaitlistManager> m_waitlistManager;

    // GUI state
    struct GLFWwindow* m_window = nullptr;
    bool m_shouldClose = false;
}; 