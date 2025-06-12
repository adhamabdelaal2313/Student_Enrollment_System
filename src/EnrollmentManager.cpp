#include "EnrollmentManager.h"
#include <algorithm>

EnrollmentManager::EnrollmentManager(const StudentRegistry& students, const CourseRegistry& courses)
    : m_students(students), m_courses(courses) {}

EnrollmentManager::EnrollmentResult EnrollmentManager::enrollStudent(std::int32_t studentId, std::int32_t courseId) {
    // Validate student exists
    if (!m_students.findStudent(studentId)) {
        return EnrollmentResult::StudentNotFound;
    }
    
    // Validate course exists
    const Course* course = m_courses.findCourse(courseId);
    if (!course) {
        return EnrollmentResult::CourseNotFound;
    }
    
    // Check if already enrolled
    if (isAlreadyEnrolled(studentId, courseId)) {
        return EnrollmentResult::AlreadyEnrolled;
    }
    
    // Check prerequisites
    if (!hasPrerequisites(studentId, courseId)) {
        return EnrollmentResult::PrerequisitesNotMet;
    }
    
    // Create enrollment
    m_enrollments.push_back(std::make_unique<Enrollment>(studentId, courseId));
    return EnrollmentResult::Success;
}

bool EnrollmentManager::dropStudent(std::int32_t studentId, std::int32_t courseId) {
    auto it = std::find_if(m_enrollments.begin(), m_enrollments.end(),
        [studentId, courseId](const std::unique_ptr<Enrollment>& enrollment) {
            return enrollment->studentId() == studentId && 
                   enrollment->courseId() == courseId && 
                   enrollment->isActive();
        });
    
    if (it != m_enrollments.end()) {
        (*it)->setStatus(Enrollment::Status::Dropped);
        return true;
    }
    return false;
}

std::vector<const Enrollment*> EnrollmentManager::getStudentEnrollments(std::int32_t studentId) const {
    std::vector<const Enrollment*> result;
    for (const auto& enrollment : m_enrollments) {
        if (enrollment->studentId() == studentId && enrollment->isActive()) {
            result.push_back(enrollment.get());
        }
    }
    return result;
}

std::vector<const Enrollment*> EnrollmentManager::getCourseEnrollments(std::int32_t courseId) const {
    std::vector<const Enrollment*> result;
    for (const auto& enrollment : m_enrollments) {
        if (enrollment->courseId() == courseId && enrollment->isActive()) {
            result.push_back(enrollment.get());
        }
    }
    return result;
}

std::vector<const Enrollment*> EnrollmentManager::getAllEnrollments() const {
    std::vector<const Enrollment*> result;
    result.reserve(m_enrollments.size());
    for (const auto& enrollment : m_enrollments) {
        result.push_back(enrollment.get());
    }
    return result;
}

bool EnrollmentManager::hasPrerequisites(std::int32_t studentId, std::int32_t courseId) const {
    const Course* course = m_courses.findCourse(courseId);
    if (!course || course->prerequisites().empty()) {
        return true; // No prerequisites required
    }
    
    auto completedCourses = getCompletedCourses(studentId);
    
    // Check if all prerequisites are satisfied
    for (std::int32_t prereqId : course->prerequisites()) {
        if (completedCourses.find(prereqId) == completedCourses.end()) {
            return false;
        }
    }
    return true;
}

std::vector<std::int32_t> EnrollmentManager::getMissingPrerequisites(std::int32_t studentId, std::int32_t courseId) const {
    std::vector<std::int32_t> missing;
    const Course* course = m_courses.findCourse(courseId);
    if (!course) {
        return missing;
    }
    
    auto completedCourses = getCompletedCourses(studentId);
    
    for (std::int32_t prereqId : course->prerequisites()) {
        if (completedCourses.find(prereqId) == completedCourses.end()) {
            missing.push_back(prereqId);
        }
    }
    return missing;
}

bool EnrollmentManager::isAlreadyEnrolled(std::int32_t studentId, std::int32_t courseId) const {
    return std::any_of(m_enrollments.begin(), m_enrollments.end(),
        [studentId, courseId](const std::unique_ptr<Enrollment>& enrollment) {
            return enrollment->studentId() == studentId && 
                   enrollment->courseId() == courseId && 
                   enrollment->isActive();
        });
}

std::unordered_set<std::int32_t> EnrollmentManager::getCompletedCourses(std::int32_t studentId) const {
    std::unordered_set<std::int32_t> completed;
    for (const auto& enrollment : m_enrollments) {
        if (enrollment->studentId() == studentId && enrollment->isCompleted()) {
            completed.insert(enrollment->courseId());
        }
    }
    return completed;
} 