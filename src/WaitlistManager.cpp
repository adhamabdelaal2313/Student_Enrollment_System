#include "WaitlistManager.h"
#include <algorithm>

bool WaitlistManager::addToWaitlist(std::int32_t courseId, std::int32_t studentId) {
    // Check if student is already on this waitlist
    if (isOnWaitlist(courseId, studentId)) {
        return false;
    }
    
    m_waitlists[courseId].push(studentId);
    return true;
}

std::int32_t WaitlistManager::getNextFromWaitlist(std::int32_t courseId) {
    auto it = m_waitlists.find(courseId);
    if (it == m_waitlists.end() || it->second.empty()) {
        return -1; // No students on waitlist
    }
    
    std::int32_t studentId = it->second.front();
    it->second.pop();
    
    // Clean up empty waitlists
    if (it->second.empty()) {
        m_waitlists.erase(it);
    }
    
    return studentId;
}

bool WaitlistManager::isOnWaitlist(std::int32_t courseId, std::int32_t studentId) const {
    auto it = m_waitlists.find(courseId);
    if (it == m_waitlists.end()) {
        return false;
    }
    
    // Need to check if studentId is in the queue
    // Since std::queue doesn't provide iteration, we'll use a temporary copy
    std::queue<std::int32_t> temp = it->second;
    while (!temp.empty()) {
        if (temp.front() == studentId) {
            return true;
        }
        temp.pop();
    }
    return false;
}

bool WaitlistManager::removeFromWaitlist(std::int32_t courseId, std::int32_t studentId) {
    auto it = m_waitlists.find(courseId);
    if (it == m_waitlists.end()) {
        return false;
    }
    
    // Rebuild queue without the target student
    std::queue<std::int32_t> newQueue;
    bool found = false;
    
    while (!it->second.empty()) {
        std::int32_t current = it->second.front();
        it->second.pop();
        
        if (current == studentId && !found) {
            found = true; // Skip this student (remove them)
        } else {
            newQueue.push(current);
        }
    }
    
    if (newQueue.empty()) {
        m_waitlists.erase(it);
    } else {
        it->second = std::move(newQueue);
    }
    
    return found;
}

std::vector<std::int32_t> WaitlistManager::getWaitlist(std::int32_t courseId) const {
    std::vector<std::int32_t> result;
    auto it = m_waitlists.find(courseId);
    if (it == m_waitlists.end()) {
        return result;
    }
    
    std::queue<std::int32_t> temp = it->second;
    while (!temp.empty()) {
        result.push_back(temp.front());
        temp.pop();
    }
    return result;
}

std::size_t WaitlistManager::getWaitlistPosition(std::int32_t courseId, std::int32_t studentId) const {
    auto it = m_waitlists.find(courseId);
    if (it == m_waitlists.end()) {
        return 0;
    }
    
    std::queue<std::int32_t> temp = it->second;
    std::size_t position = 1;
    
    while (!temp.empty()) {
        if (temp.front() == studentId) {
            return position;
        }
        temp.pop();
        ++position;
    }
    return 0; // Not found
}

bool WaitlistManager::isWaitlistEmpty(std::int32_t courseId) const {
    auto it = m_waitlists.find(courseId);
    return it == m_waitlists.end() || it->second.empty();
}

std::size_t WaitlistManager::getWaitlistSize(std::int32_t courseId) const {
    auto it = m_waitlists.find(courseId);
    return it == m_waitlists.end() ? 0 : it->second.size();
} 