#include "Enrollment.h"

Enrollment::Enrollment(std::int32_t studentId, 
                       std::int32_t courseId,
                       Status status)
    : m_studentId(studentId),
      m_courseId(courseId),
      m_status(status),
      m_enrollmentDate(std::chrono::system_clock::now()) {} 