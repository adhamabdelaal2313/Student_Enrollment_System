#include <iostream>
#include <memory>
#include "StudentRegistry.h"
#include "CourseRegistry.h"
#include "EnrollmentManager.h"
#include "WaitlistManager.h"

int main() {
    // Create registries
    StudentRegistry students;
    CourseRegistry courses;
    
    // Add students
    students.addStudent(std::make_unique<Student>(1, "Alice", "alice@example.com"));
    students.addStudent(std::make_unique<Student>(2, "Bob", "bob@example.com"));
    students.addStudent(std::make_unique<Student>(3, "Charlie", "charlie@example.com"));

    // Add courses with prerequisites
    courses.addCourse(std::make_unique<Course>(101, "Math 101", 3, "Prof. Euler"));
    courses.addCourse(std::make_unique<Course>(201, "Math 201", 3, "Prof. Gauss", std::vector<std::int32_t>{101}));
    courses.addCourse(std::make_unique<Course>(301, "Advanced Math", 4, "Prof. Newton", std::vector<std::int32_t>{101, 201}));

    std::cout << "=== Student Enrollment System Demo ===\n\n";

    // Create enrollment manager
    EnrollmentManager enrollment(students, courses);
    WaitlistManager waitlist;

    // Test enrollments
    std::cout << "1. Enrolling Alice in Math 101...\n";
    auto result = enrollment.enrollStudent(1, 101);
    std::cout << "Result: " << (result == EnrollmentManager::EnrollmentResult::Success ? "Success" : "Failed") << "\n\n";

    std::cout << "2. Trying to enroll Bob in Math 201 (requires Math 101)...\n";
    result = enrollment.enrollStudent(2, 201);
    std::cout << "Result: " << (result == EnrollmentManager::EnrollmentResult::PrerequisitesNotMet ? "Prerequisites not met" : "Unexpected") << "\n";
    
    auto missing = enrollment.getMissingPrerequisites(2, 201);
    std::cout << "Missing prerequisites for Bob: ";
    for (auto prereq : missing) {
        std::cout << prereq << " ";
    }
    std::cout << "\n\n";

    std::cout << "3. Enrolling Bob in Math 101 first...\n";
    result = enrollment.enrollStudent(2, 101);
    std::cout << "Result: " << (result == EnrollmentManager::EnrollmentResult::Success ? "Success" : "Failed") << "\n\n";

    std::cout << "4. Current enrollments:\n";
    for (const auto* e : enrollment.getAllEnrollments()) {
        const Student* student = students.findStudent(e->studentId());
        const Course* course = courses.findCourse(e->courseId());
        std::cout << "  " << student->name() << " enrolled in " << course->name() << "\n";
    }
    std::cout << "\n";

    std::cout << "5. Testing waitlist - adding Charlie to Math 101 waitlist...\n";
    waitlist.addToWaitlist(101, 3);
    std::cout << "Charlie's position in Math 101 waitlist: " << waitlist.getWaitlistPosition(101, 3) << "\n\n";

    std::cout << "6. Dropping Alice from Math 101...\n";
    enrollment.dropStudent(1, 101);
    std::cout << "Next student from waitlist: " << waitlist.getNextFromWaitlist(101) << " (Charlie)\n\n";

    std::cout << "=== Demo Complete ===\n";
    return 0;
} 