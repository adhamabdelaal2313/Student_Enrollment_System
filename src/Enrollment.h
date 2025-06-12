#pragma once

#include <cstdint>
#include <chrono>

// Represents a single enrollment record - a student enrolled in a course
class Enrollment final {
public:
    enum class Status {
        Active,
        Completed,
        Dropped,
        Withdrawn
    };

    Enrollment(std::int32_t studentId, 
               std::int32_t courseId,
               Status status = Status::Active);

    // Immutable getters
    std::int32_t studentId() const noexcept { return m_studentId; }
    std::int32_t courseId() const noexcept { return m_courseId; }
    Status status() const noexcept { return m_status; }
    const std::chrono::system_clock::time_point& enrollmentDate() const noexcept { return m_enrollmentDate; }

    // Status management
    void setStatus(Status status) { m_status = status; }
    
    // Convenience methods
    bool isActive() const noexcept { return m_status == Status::Active; }
    bool isCompleted() const noexcept { return m_status == Status::Completed; }

private:
    std::int32_t m_studentId;
    std::int32_t m_courseId;
    Status m_status;
    std::chrono::system_clock::time_point m_enrollmentDate;
}; 