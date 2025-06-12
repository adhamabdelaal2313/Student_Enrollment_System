#pragma once

#include <queue>
#include <unordered_map>
#include <cstdint>
#include <vector>

// Manages waitlists for courses that are full
class WaitlistManager {
public:
    // Add student to course waitlist
    bool addToWaitlist(std::int32_t courseId, std::int32_t studentId);
    
    // Remove and return next student from waitlist
    std::int32_t getNextFromWaitlist(std::int32_t courseId);
    
    // Check if student is on waitlist
    bool isOnWaitlist(std::int32_t courseId, std::int32_t studentId) const;
    
    // Remove student from waitlist (if they enroll elsewhere, etc.)
    bool removeFromWaitlist(std::int32_t courseId, std::int32_t studentId);
    
    // Get all students on a course's waitlist
    std::vector<std::int32_t> getWaitlist(std::int32_t courseId) const;
    
    // Get waitlist position (1-based, 0 if not on waitlist)
    std::size_t getWaitlistPosition(std::int32_t courseId, std::int32_t studentId) const;
    
    // Check if waitlist is empty
    bool isWaitlistEmpty(std::int32_t courseId) const;
    
    // Get waitlist size
    std::size_t getWaitlistSize(std::int32_t courseId) const;

private:
    // Map from courseId to queue of studentIds
    std::unordered_map<std::int32_t, std::queue<std::int32_t>> m_waitlists;
}; 