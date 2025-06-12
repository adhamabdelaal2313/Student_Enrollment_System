#pragma once

#include <vector>
#include <memory>
#include <unordered_set>
#include <functional>
#include "Enrollment.h"
#include "StudentRegistry.h"
#include "CourseRegistry.h"

// Manages all enrollment operations including prerequisite validation
class EnrollmentManager {
public:
    enum class EnrollmentResult {
        Success,
        StudentNotFound,
        CourseNotFound,
        PrerequisitesNotMet,
        AlreadyEnrolled,
        CourseFull
    };

    EnrollmentManager(const StudentRegistry& students, const CourseRegistry& courses);

    // Core enrollment operations
    EnrollmentResult enrollStudent(std::int32_t studentId, std::int32_t courseId);
    bool dropStudent(std::int32_t studentId, std::int32_t courseId);
    
    // Query operations
    std::vector<const Enrollment*> getStudentEnrollments(std::int32_t studentId) const;
    std::vector<const Enrollment*> getCourseEnrollments(std::int32_t courseId) const;
    std::vector<const Enrollment*> getAllEnrollments() const;
    
    // Prerequisite validation
    bool hasPrerequisites(std::int32_t studentId, std::int32_t courseId) const;
    std::vector<std::int32_t> getMissingPrerequisites(std::int32_t studentId, std::int32_t courseId) const;

private:
    const StudentRegistry& m_students;
    const CourseRegistry& m_courses;
    std::vector<std::unique_ptr<Enrollment>> m_enrollments;
    
    // Helper methods
    bool isAlreadyEnrolled(std::int32_t studentId, std::int32_t courseId) const;
    std::unordered_set<std::int32_t> getCompletedCourses(std::int32_t studentId) const;
}; 