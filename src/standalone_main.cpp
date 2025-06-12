#include <iostream>
#include <string>
#include <memory>
#include <iomanip>
#include <sstream>
#include "StudentRegistry.h"
#include "CourseRegistry.h"
#include "EnrollmentManager.h"
#include "WaitlistManager.h"

// Simple console-based GUI using text menus
class ConsoleApp {
public:
    ConsoleApp() {
        // Initialize business logic
        m_students = std::make_unique<StudentRegistry>();
        m_courses = std::make_unique<CourseRegistry>();
        m_enrollmentManager = std::make_unique<EnrollmentManager>(*m_students, *m_courses);
        m_waitlistManager = std::make_unique<WaitlistManager>();
        
        // Add sample data
        initializeSampleData();
    }
    
    void run() {
        std::cout << "=== Student Enrollment System ===\n";
        std::cout << "Professional C++ Application\n\n";
        
        while (true) {
            showMainMenu();
            int choice = getChoice();
            
            switch (choice) {
                case 1: studentManagement(); break;
                case 2: courseManagement(); break;
                case 3: enrollmentManagement(); break;
                case 4: viewReports(); break;
                case 5: viewWaitlists(); break;
                case 6: runDemo(); break;
                case 0: 
                    std::cout << "\nThank you for using the Student Enrollment System!\n";
                    return;
                default:
                    std::cout << "\nInvalid choice. Please try again.\n";
            }
            
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore();
            std::cin.get();
        }
    }

private:
    std::unique_ptr<StudentRegistry> m_students;
    std::unique_ptr<CourseRegistry> m_courses;
    std::unique_ptr<EnrollmentManager> m_enrollmentManager;
    std::unique_ptr<WaitlistManager> m_waitlistManager;
    
    void initializeSampleData() {
        // Add sample students
        m_students->addStudent(std::make_unique<Student>(1, "Alice Johnson", "alice@university.edu", "555-0101", "123 Main St"));
        m_students->addStudent(std::make_unique<Student>(2, "Bob Smith", "bob@university.edu", "555-0102", "456 Oak Ave"));
        m_students->addStudent(std::make_unique<Student>(3, "Charlie Brown", "charlie@university.edu", "555-0103", "789 Pine Rd"));
        
        // Add sample courses with prerequisites
        m_courses->addCourse(std::make_unique<Course>(101, "Introduction to Programming", 3, "Dr. Smith"));
        m_courses->addCourse(std::make_unique<Course>(201, "Data Structures", 4, "Dr. Johnson", std::vector<std::int32_t>{101}));
        m_courses->addCourse(std::make_unique<Course>(301, "Algorithms", 4, "Dr. Wilson", std::vector<std::int32_t>{101, 201}));
        m_courses->addCourse(std::make_unique<Course>(102, "Mathematics", 3, "Prof. Euler"));
        m_courses->addCourse(std::make_unique<Course>(202, "Physics", 4, "Prof. Feynman", std::vector<std::int32_t>{102}));
    }
    
    void showMainMenu() {
        std::cout << "\n" << std::string(50, '=') << "\n";
        std::cout << "           MAIN MENU\n";
        std::cout << std::string(50, '=') << "\n";
        std::cout << "1. Student Management\n";
        std::cout << "2. Course Management\n";
        std::cout << "3. Enrollment Management\n";
        std::cout << "4. View Reports\n";
        std::cout << "5. View Waitlists\n";
        std::cout << "6. Run Demo\n";
        std::cout << "0. Exit\n";
        std::cout << std::string(50, '=') << "\n";
        std::cout << "Enter your choice: ";
    }
    
    int getChoice() {
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return -1;
        }
        std::cin.ignore(); // Clear the newline
        return choice;
    }
    
    void studentManagement() {
        while (true) {
            std::cout << "\n--- Student Management ---\n";
            std::cout << "1. View All Students\n";
            std::cout << "2. Add Student\n";
            std::cout << "3. Remove Student\n";
            std::cout << "4. Find Student\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Choice: ";
            
            int choice = getChoice();
            switch (choice) {
                case 1: viewAllStudents(); break;
                case 2: addStudent(); break;
                case 3: removeStudent(); break;
                case 4: findStudent(); break;
                case 0: return;
                default: std::cout << "Invalid choice.\n";
            }
        }
    }
    
    void courseManagement() {
        while (true) {
            std::cout << "\n--- Course Management ---\n";
            std::cout << "1. View All Courses\n";
            std::cout << "2. Add Course\n";
            std::cout << "3. Remove Course\n";
            std::cout << "4. Find Course\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Choice: ";
            
            int choice = getChoice();
            switch (choice) {
                case 1: viewAllCourses(); break;
                case 2: addCourse(); break;
                case 3: removeCourse(); break;
                case 4: findCourse(); break;
                case 0: return;
                default: std::cout << "Invalid choice.\n";
            }
        }
    }
    
    void enrollmentManagement() {
        while (true) {
            std::cout << "\n--- Enrollment Management ---\n";
            std::cout << "1. View All Enrollments\n";
            std::cout << "2. Enroll Student\n";
            std::cout << "3. Drop Student\n";
            std::cout << "4. Check Prerequisites\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Choice: ";
            
            int choice = getChoice();
            switch (choice) {
                case 1: viewAllEnrollments(); break;
                case 2: enrollStudent(); break;
                case 3: dropStudent(); break;
                case 4: checkPrerequisites(); break;
                case 0: return;
                default: std::cout << "Invalid choice.\n";
            }
        }
    }
    
    void viewAllStudents() {
        std::cout << "\n--- All Students ---\n";
        std::cout << std::string(80, '-') << "\n";
        std::cout << "ID    Name                Email                     Phone        \n";
        std::cout << std::string(80, '-') << "\n";
        
        for (const Student* student : m_students->allStudents()) {
            std::cout << std::left 
                      << std::setw(6) << student->id()
                      << std::setw(20) << student->name()
                      << std::setw(26) << student->email()
                      << student->phone() << "\n";
        }
    }
    
    void addStudent() {
        std::cout << "\n--- Add New Student ---\n";
        int id;
        std::string name, email, phone, address;
        
        std::cout << "Student ID: ";
        std::cin >> id;
        std::cin.ignore();
        
        std::cout << "Name: ";
        std::getline(std::cin, name);
        
        std::cout << "Email: ";
        std::getline(std::cin, email);
        
        std::cout << "Phone: ";
        std::getline(std::cin, phone);
        
        std::cout << "Address: ";
        std::getline(std::cin, address);
        
        auto student = std::make_unique<Student>(id, name, email, phone, address);
        if (m_students->addStudent(std::move(student))) {
            std::cout << "Student added successfully!\n";
        } else {
            std::cout << "Failed to add student (ID may already exist).\n";
        }
    }
    
    void removeStudent() {
        std::cout << "\n--- Remove Student ---\n";
        int id;
        std::cout << "Enter Student ID to remove: ";
        std::cin >> id;
        
        if (m_students->removeStudent(id)) {
            std::cout << "Student removed successfully!\n";
        } else {
            std::cout << "Student not found.\n";
        }
    }
    
    void findStudent() {
        std::cout << "\n--- Find Student ---\n";
        int id;
        std::cout << "Enter Student ID: ";
        std::cin >> id;
        
        const Student* student = m_students->findStudent(id);
        if (student) {
            std::cout << "\nStudent Found:\n";
            std::cout << "ID: " << student->id() << "\n";
            std::cout << "Name: " << student->name() << "\n";
            std::cout << "Email: " << student->email() << "\n";
            std::cout << "Phone: " << student->phone() << "\n";
            std::cout << "Address: " << student->address() << "\n";
        } else {
            std::cout << "Student not found.\n";
        }
    }
    
    void viewAllCourses() {
        std::cout << "\n--- All Courses ---\n";
        std::cout << std::string(80, '-') << "\n";
        std::cout << "ID    Name                     Credits  Instructor\n";
        std::cout << std::string(80, '-') << "\n";
        
        for (const Course* course : m_courses->allCourses()) {
            std::cout << std::left 
                      << std::setw(6) << course->id()
                      << std::setw(25) << course->name()
                      << std::setw(9) << static_cast<int>(course->credits())
                      << course->instructor() << "\n";
            
            if (!course->prerequisites().empty()) {
                std::cout << "      Prerequisites: ";
                for (size_t i = 0; i < course->prerequisites().size(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << course->prerequisites()[i];
                }
                std::cout << "\n";
            }
        }
    }
    
    void addCourse() {
        std::cout << "\n--- Add New Course ---\n";
        int id, credits;
        std::string name, instructor, prereqStr;
        
        std::cout << "Course ID: ";
        std::cin >> id;
        std::cin.ignore();
        
        std::cout << "Name: ";
        std::getline(std::cin, name);
        
        std::cout << "Credits: ";
        std::cin >> credits;
        std::cin.ignore();
        
        std::cout << "Instructor: ";
        std::getline(std::cin, instructor);
        
        std::cout << "Prerequisites (comma-separated IDs, or press Enter for none): ";
        std::getline(std::cin, prereqStr);
        
        // Parse prerequisites
        std::vector<std::int32_t> prerequisites;
        if (!prereqStr.empty()) {
            std::stringstream ss(prereqStr);
            std::string item;
            while (std::getline(ss, item, ',')) {
                try {
                    int prereq = std::stoi(item);
                    prerequisites.push_back(prereq);
                } catch (...) {
                    // Ignore invalid numbers
                }
            }
        }
        
        auto course = std::make_unique<Course>(id, name, static_cast<std::uint8_t>(credits), instructor, prerequisites);
        if (m_courses->addCourse(std::move(course))) {
            std::cout << "Course added successfully!\n";
        } else {
            std::cout << "Failed to add course (ID may already exist).\n";
        }
    }
    
    void removeCourse() {
        std::cout << "\n--- Remove Course ---\n";
        int id;
        std::cout << "Enter Course ID to remove: ";
        std::cin >> id;
        
        if (m_courses->removeCourse(id)) {
            std::cout << "Course removed successfully!\n";
        } else {
            std::cout << "Course not found.\n";
        }
    }
    
    void findCourse() {
        std::cout << "\n--- Find Course ---\n";
        int id;
        std::cout << "Enter Course ID: ";
        std::cin >> id;
        
        const Course* course = m_courses->findCourse(id);
        if (course) {
            std::cout << "\nCourse Found:\n";
            std::cout << "ID: " << course->id() << "\n";
            std::cout << "Name: " << course->name() << "\n";
            std::cout << "Credits: " << static_cast<int>(course->credits()) << "\n";
            std::cout << "Instructor: " << course->instructor() << "\n";
            
            if (!course->prerequisites().empty()) {
                std::cout << "Prerequisites: ";
                for (size_t i = 0; i < course->prerequisites().size(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << course->prerequisites()[i];
                }
                std::cout << "\n";
            }
        } else {
            std::cout << "Course not found.\n";
        }
    }
    
    void viewAllEnrollments() {
        std::cout << "\n--- All Enrollments ---\n";
        std::cout << std::string(80, '-') << "\n";
        std::cout << "Student                  Course                   Status\n";
        std::cout << std::string(80, '-') << "\n";
        
        for (const Enrollment* enrollment : m_enrollmentManager->getAllEnrollments()) {
            const Student* student = m_students->findStudent(enrollment->studentId());
            const Course* course = m_courses->findCourse(enrollment->courseId());
            
            if (student && course) {
                std::cout << std::left 
                          << std::setw(25) << student->name()
                          << std::setw(25) << course->name()
                          << (enrollment->isActive() ? "Active" : "Inactive") << "\n";
            }
        }
    }
    
    void enrollStudent() {
        std::cout << "\n--- Enroll Student ---\n";
        int studentId, courseId;
        
        std::cout << "Student ID: ";
        std::cin >> studentId;
        
        std::cout << "Course ID: ";
        std::cin >> courseId;
        
        auto result = m_enrollmentManager->enrollStudent(studentId, courseId);
        
        switch (result) {
            case EnrollmentManager::EnrollmentResult::Success:
                std::cout << "Enrollment successful!\n";
                break;
            case EnrollmentManager::EnrollmentResult::StudentNotFound:
                std::cout << "Error: Student not found!\n";
                break;
            case EnrollmentManager::EnrollmentResult::CourseNotFound:
                std::cout << "Error: Course not found!\n";
                break;
            case EnrollmentManager::EnrollmentResult::PrerequisitesNotMet:
                std::cout << "Error: Prerequisites not met!\n";
                {
                    auto missing = m_enrollmentManager->getMissingPrerequisites(studentId, courseId);
                    std::cout << "Missing prerequisites: ";
                    for (size_t i = 0; i < missing.size(); ++i) {
                        if (i > 0) std::cout << ", ";
                        std::cout << missing[i];
                    }
                    std::cout << "\n";
                }
                break;
            case EnrollmentManager::EnrollmentResult::AlreadyEnrolled:
                std::cout << "Error: Student already enrolled in this course!\n";
                break;
            case EnrollmentManager::EnrollmentResult::CourseFull:
                std::cout << "Error: Course is full!\n";
                break;
        }
    }
    
    void dropStudent() {
        std::cout << "\n--- Drop Student ---\n";
        int studentId, courseId;
        
        std::cout << "Student ID: ";
        std::cin >> studentId;
        
        std::cout << "Course ID: ";
        std::cin >> courseId;
        
        if (m_enrollmentManager->dropStudent(studentId, courseId)) {
            std::cout << "Student dropped successfully!\n";
        } else {
            std::cout << "Error: Enrollment not found or already inactive.\n";
        }
    }
    
    void checkPrerequisites() {
        std::cout << "\n--- Check Prerequisites ---\n";
        int studentId, courseId;
        
        std::cout << "Student ID: ";
        std::cin >> studentId;
        
        std::cout << "Course ID: ";
        std::cin >> courseId;
        
        if (m_enrollmentManager->hasPrerequisites(studentId, courseId)) {
            std::cout << "Student meets all prerequisites for this course.\n";
        } else {
            std::cout << "Student does not meet prerequisites.\n";
            auto missing = m_enrollmentManager->getMissingPrerequisites(studentId, courseId);
            std::cout << "Missing prerequisites: ";
            for (size_t i = 0; i < missing.size(); ++i) {
                if (i > 0) std::cout << ", ";
                std::cout << missing[i];
            }
            std::cout << "\n";
        }
    }
    
    void viewReports() {
        std::cout << "\n--- System Reports ---\n";
        std::cout << std::string(50, '=') << "\n";
        
        std::cout << "Total Students: " << m_students->allStudents().size() << "\n";
        std::cout << "Total Courses: " << m_courses->allCourses().size() << "\n";
        std::cout << "Total Enrollments: " << m_enrollmentManager->getAllEnrollments().size() << "\n\n";
        
        std::cout << "Course Enrollment Details:\n";
        std::cout << std::string(50, '-') << "\n";
        
        for (const Course* course : m_courses->allCourses()) {
            auto enrollments = m_enrollmentManager->getCourseEnrollments(course->id());
            std::cout << course->name() << ": " << enrollments.size() << " students\n";
        }
    }
    
    void viewWaitlists() {
        std::cout << "\n--- Course Waitlists ---\n";
        std::cout << std::string(50, '=') << "\n";
        
        bool hasWaitlists = false;
        for (const Course* course : m_courses->allCourses()) {
            auto waitlistSize = m_waitlistManager->getWaitlistSize(course->id());
            if (waitlistSize > 0) {
                hasWaitlists = true;
                std::cout << course->name() << ": " << waitlistSize << " students waiting\n";
                
                auto waitlist = m_waitlistManager->getWaitlist(course->id());
                for (size_t i = 0; i < waitlist.size(); ++i) {
                    const Student* student = m_students->findStudent(waitlist[i]);
                    if (student) {
                        std::cout << "  " << (i + 1) << ". " << student->name() << "\n";
                    }
                }
                std::cout << "\n";
            }
        }
        
        if (!hasWaitlists) {
            std::cout << "No students are currently on any waitlists.\n";
        }
    }
    
    void runDemo() {
        std::cout << "\n=== Running System Demo ===\n";
        
        // Demo the enrollment system
        std::cout << "\n1. Enrolling Alice in Introduction to Programming...\n";
        auto result = m_enrollmentManager->enrollStudent(1, 101);
        std::cout << "Result: " << (result == EnrollmentManager::EnrollmentResult::Success ? "Success" : "Failed") << "\n";
        
        std::cout << "\n2. Trying to enroll Bob in Data Structures (requires Intro Programming)...\n";
        result = m_enrollmentManager->enrollStudent(2, 201);
        if (result == EnrollmentManager::EnrollmentResult::PrerequisitesNotMet) {
            std::cout << "Result: Prerequisites not met\n";
            auto missing = m_enrollmentManager->getMissingPrerequisites(2, 201);
            std::cout << "Missing prerequisites for Bob: ";
            for (auto prereq : missing) {
                std::cout << prereq << " ";
            }
            std::cout << "\n";
        }
        
        std::cout << "\n3. Enrolling Bob in Introduction to Programming first...\n";
        result = m_enrollmentManager->enrollStudent(2, 101);
        std::cout << "Result: " << (result == EnrollmentManager::EnrollmentResult::Success ? "Success" : "Failed") << "\n";
        
        std::cout << "\n4. Now enrolling Bob in Data Structures...\n";
        result = m_enrollmentManager->enrollStudent(2, 201);
        std::cout << "Result: " << (result == EnrollmentManager::EnrollmentResult::Success ? "Success" : "Failed") << "\n";
        
        std::cout << "\n5. Current enrollments:\n";
        for (const auto* e : m_enrollmentManager->getAllEnrollments()) {
            const Student* student = m_students->findStudent(e->studentId());
            const Course* course = m_courses->findCourse(e->courseId());
            if (student && course && e->isActive()) {
                std::cout << "  " << student->name() << " enrolled in " << course->name() << "\n";
            }
        }
        
        std::cout << "\n6. Testing waitlist - adding Charlie to Introduction to Programming waitlist...\n";
        m_waitlistManager->addToWaitlist(101, 3);
        std::cout << "Charlie's position in waitlist: " << m_waitlistManager->getWaitlistPosition(101, 3) << "\n";
        
        std::cout << "\nDemo complete!\n";
    }
};

int main() {
    try {
        ConsoleApp app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
} 