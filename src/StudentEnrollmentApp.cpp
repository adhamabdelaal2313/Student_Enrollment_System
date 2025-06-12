#include "StudentEnrollmentApp.h"
#include <iostream>
#include <sstream>
#include <algorithm>

// ImGui includes
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// OpenGL includes
#include <glad/glad.h>
#include <GLFW/glfw3.h>

StudentEnrollmentApp::StudentEnrollmentApp() {
    // Initialize business logic components
    m_students = std::make_unique<StudentRegistry>();
    m_courses = std::make_unique<CourseRegistry>();
    m_enrollmentManager = std::make_unique<EnrollmentManager>(*m_students, *m_courses);
    m_waitlistManager = std::make_unique<WaitlistManager>();

    // Add some sample data
    m_students->addStudent(std::make_unique<Student>(1, "Alice Johnson", "alice@university.edu"));
    m_students->addStudent(std::make_unique<Student>(2, "Bob Smith", "bob@university.edu"));
    m_students->addStudent(std::make_unique<Student>(3, "Charlie Brown", "charlie@university.edu"));

    m_courses->addCourse(std::make_unique<Course>(101, "Introduction to Programming", 3, "Dr. Smith"));
    m_courses->addCourse(std::make_unique<Course>(201, "Data Structures", 4, "Dr. Johnson", std::vector<std::int32_t>{101}));
    m_courses->addCourse(std::make_unique<Course>(301, "Algorithms", 4, "Dr. Wilson", std::vector<std::int32_t>{101, 201}));
}

StudentEnrollmentApp::~StudentEnrollmentApp() {
    shutdown();
}

bool StudentEnrollmentApp::initialize() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        return false;
    }

    // GL 3.3 + GLSL 330
    const char* glsl_version = "#version 330";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    m_window = glfwCreateWindow(1280, 720, "Student Enrollment System", nullptr, nullptr);
    if (!m_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context\n";
        return false;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    return true;
}

void StudentEnrollmentApp::run() {
    while (!glfwWindowShouldClose(m_window) && !m_shouldClose) {
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Enable docking
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        // Render GUI components
        renderMainMenuBar();
        
        if (m_showStudentWindow) renderStudentManagement();
        if (m_showCourseWindow) renderCourseManagement();
        if (m_showEnrollmentWindow) renderEnrollmentManagement();
        if (m_showReportsWindow) renderReportsView();
        if (m_showWaitlistWindow) renderWaitlistView();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

void StudentEnrollmentApp::shutdown() {
    if (m_window) {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        glfwDestroyWindow(m_window);
        glfwTerminate();
        m_window = nullptr;
    }
}

void StudentEnrollmentApp::renderMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("Windows")) {
            ImGui::MenuItem("Students", nullptr, &m_showStudentWindow);
            ImGui::MenuItem("Courses", nullptr, &m_showCourseWindow);
            ImGui::MenuItem("Enrollment", nullptr, &m_showEnrollmentWindow);
            ImGui::MenuItem("Reports", nullptr, &m_showReportsWindow);
            ImGui::MenuItem("Waitlists", nullptr, &m_showWaitlistWindow);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            if (ImGui::MenuItem("About")) {
                // Could show about dialog
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void StudentEnrollmentApp::renderStudentManagement() {
    if (ImGui::Begin("Student Management", &m_showStudentWindow)) {
        // Add student form
        renderAddStudentForm();
        
        ImGui::Separator();
        ImGui::Text("Current Students:");
        
        // Students table
        if (ImGui::BeginTable("StudentsTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Email");
            ImGui::TableSetupColumn("Actions");
            ImGui::TableHeadersRow();

            for (const Student* student : m_students->allStudents()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", student->id());
                ImGui::TableNextColumn();
                ImGui::Text("%s", student->name().c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%s", student->email().c_str());
                ImGui::TableNextColumn();
                
                ImGui::PushID(student->id());
                if (ImGui::Button("Remove")) {
                    m_students->removeStudent(student->id());
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void StudentEnrollmentApp::renderAddStudentForm() {
    ImGui::Text("Add New Student:");
    ImGui::InputInt("Student ID", &m_studentForm.id);
    ImGui::InputText("Name", m_studentForm.name, sizeof(m_studentForm.name));
    ImGui::InputText("Email", m_studentForm.email, sizeof(m_studentForm.email));
    ImGui::InputText("Phone", m_studentForm.phone, sizeof(m_studentForm.phone));
    ImGui::InputText("Address", m_studentForm.address, sizeof(m_studentForm.address));
    
    if (ImGui::Button("Add Student")) {
        if (m_studentForm.id > 0 && strlen(m_studentForm.name) > 0) {
            auto student = std::make_unique<Student>(
                m_studentForm.id,
                std::string(m_studentForm.name),
                std::string(m_studentForm.email),
                std::string(m_studentForm.phone),
                std::string(m_studentForm.address)
            );
            
            if (m_students->addStudent(std::move(student))) {
                // Clear form on success
                m_studentForm = StudentForm{};
            }
        }
    }
}

void StudentEnrollmentApp::renderCourseManagement() {
    if (ImGui::Begin("Course Management", &m_showCourseWindow)) {
        renderAddCourseForm();
        
        ImGui::Separator();
        ImGui::Text("Current Courses:");
        
        if (ImGui::BeginTable("CoursesTable", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("ID");
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Credits");
            ImGui::TableSetupColumn("Instructor");
            ImGui::TableSetupColumn("Actions");
            ImGui::TableHeadersRow();

            for (const Course* course : m_courses->allCourses()) {
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("%d", course->id());
                ImGui::TableNextColumn();
                ImGui::Text("%s", course->name().c_str());
                ImGui::TableNextColumn();
                ImGui::Text("%d", static_cast<int>(course->credits()));
                ImGui::TableNextColumn();
                ImGui::Text("%s", course->instructor().c_str());
                ImGui::TableNextColumn();
                
                ImGui::PushID(course->id());
                if (ImGui::Button("Remove")) {
                    m_courses->removeCourse(course->id());
                }
                ImGui::PopID();
            }
            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void StudentEnrollmentApp::renderAddCourseForm() {
    ImGui::Text("Add New Course:");
    ImGui::InputInt("Course ID", &m_courseForm.id);
    ImGui::InputText("Name", m_courseForm.name, sizeof(m_courseForm.name));
    ImGui::InputInt("Credits", &m_courseForm.credits);
    ImGui::InputText("Instructor", m_courseForm.instructor, sizeof(m_courseForm.instructor));
    ImGui::InputText("Prerequisites (comma-separated IDs)", m_courseForm.prerequisiteInput, sizeof(m_courseForm.prerequisiteInput));
    
    if (ImGui::Button("Add Course")) {
        if (m_courseForm.id > 0 && strlen(m_courseForm.name) > 0) {
            // Parse prerequisites
            std::vector<std::int32_t> prerequisites;
            std::stringstream ss(m_courseForm.prerequisiteInput);
            std::string item;
            while (std::getline(ss, item, ',')) {
                try {
                    int prereq = std::stoi(item);
                    if (prereq > 0) prerequisites.push_back(prereq);
                } catch (...) {
                    // Ignore invalid numbers
                }
            }
            
            auto course = std::make_unique<Course>(
                m_courseForm.id,
                std::string(m_courseForm.name),
                static_cast<std::uint8_t>(std::max(1, std::min(10, m_courseForm.credits))),
                std::string(m_courseForm.instructor),
                prerequisites
            );
            
            if (m_courses->addCourse(std::move(course))) {
                m_courseForm = CourseForm{};
            }
        }
    }
}

void StudentEnrollmentApp::renderEnrollmentManagement() {
    if (ImGui::Begin("Enrollment Management", &m_showEnrollmentWindow)) {
        renderEnrollStudentForm();
        
        ImGui::Separator();
        ImGui::Text("Current Enrollments:");
        
        if (ImGui::BeginTable("EnrollmentsTable", 4, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Student");
            ImGui::TableSetupColumn("Course");
            ImGui::TableSetupColumn("Status");
            ImGui::TableSetupColumn("Actions");
            ImGui::TableHeadersRow();

            for (const Enrollment* enrollment : m_enrollmentManager->getAllEnrollments()) {
                const Student* student = m_students->findStudent(enrollment->studentId());
                const Course* course = m_courses->findCourse(enrollment->courseId());
                
                if (student && course) {
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", student->name().c_str());
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", course->name().c_str());
                    ImGui::TableNextColumn();
                    ImGui::Text("%s", enrollment->isActive() ? "Active" : "Inactive");
                    ImGui::TableNextColumn();
                    
                    ImGui::PushID(enrollment->studentId() * 1000 + enrollment->courseId());
                    if (ImGui::Button("Drop") && enrollment->isActive()) {
                        m_enrollmentManager->dropStudent(enrollment->studentId(), enrollment->courseId());
                    }
                    ImGui::PopID();
                }
            }
            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void StudentEnrollmentApp::renderEnrollStudentForm() {
    ImGui::Text("Enroll Student in Course:");
    ImGui::InputInt("Student ID", &m_enrollmentForm.studentId);
    ImGui::InputInt("Course ID", &m_enrollmentForm.courseId);
    
    if (ImGui::Button("Enroll")) {
        auto result = m_enrollmentManager->enrollStudent(m_enrollmentForm.studentId, m_enrollmentForm.courseId);
        
        // Show result message
        const char* message = "Unknown error";
        switch (result) {
            case EnrollmentManager::EnrollmentResult::Success:
                message = "Enrollment successful!";
                m_enrollmentForm = EnrollmentForm{};
                break;
            case EnrollmentManager::EnrollmentResult::StudentNotFound:
                message = "Student not found!";
                break;
            case EnrollmentManager::EnrollmentResult::CourseNotFound:
                message = "Course not found!";
                break;
            case EnrollmentManager::EnrollmentResult::PrerequisitesNotMet:
                message = "Prerequisites not met!";
                break;
            case EnrollmentManager::EnrollmentResult::AlreadyEnrolled:
                message = "Student already enrolled!";
                break;
            case EnrollmentManager::EnrollmentResult::CourseFull:
                message = "Course is full!";
                break;
        }
        
        // Display message (in a real app, you'd want a proper notification system)
        ImGui::SameLine();
        if (result == EnrollmentManager::EnrollmentResult::Success) {
            ImGui::TextColored(ImVec4(0, 1, 0, 1), "%s", message);
        } else {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "%s", message);
        }
    }
}

void StudentEnrollmentApp::renderReportsView() {
    if (ImGui::Begin("Reports", &m_showReportsWindow)) {
        ImGui::Text("Enrollment Statistics:");
        
        ImGui::Text("Total Students: %zu", m_students->allStudents().size());
        ImGui::Text("Total Courses: %zu", m_courses->allCourses().size());
        ImGui::Text("Total Enrollments: %zu", m_enrollmentManager->getAllEnrollments().size());
        
        ImGui::Separator();
        ImGui::Text("Course Enrollment Details:");
        
        for (const Course* course : m_courses->allCourses()) {
            auto enrollments = m_enrollmentManager->getCourseEnrollments(course->id());
            ImGui::Text("%s: %zu students enrolled", course->name().c_str(), enrollments.size());
        }
    }
    ImGui::End();
}

void StudentEnrollmentApp::renderWaitlistView() {
    if (ImGui::Begin("Waitlists", &m_showWaitlistWindow)) {
        ImGui::Text("Course Waitlists:");
        
        for (const Course* course : m_courses->allCourses()) {
            auto waitlistSize = m_waitlistManager->getWaitlistSize(course->id());
            if (waitlistSize > 0) {
                ImGui::Text("%s: %zu students waiting", course->name().c_str(), waitlistSize);
                
                auto waitlist = m_waitlistManager->getWaitlist(course->id());
                for (size_t i = 0; i < waitlist.size(); ++i) {
                    const Student* student = m_students->findStudent(waitlist[i]);
                    if (student) {
                        ImGui::Text("  %zu. %s", i + 1, student->name().c_str());
                    }
                }
            }
        }
    }
    ImGui::End();
}
