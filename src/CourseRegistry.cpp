#include "CourseRegistry.h"

bool CourseRegistry::addCourse(std::unique_ptr<Course> course) {
    if (!course) return false;
    const auto id = course->id();
    auto [it, inserted] = m_courses.emplace(id, std::move(course));
    return inserted;
}

bool CourseRegistry::removeCourse(std::int32_t id) {
    return m_courses.erase(id) > 0;
}

Course* CourseRegistry::findCourse(std::int32_t id) const {
    auto it = m_courses.find(id);
    return it == m_courses.end() ? nullptr : it->second.get();
}

std::vector<const Course*> CourseRegistry::allCourses() const {
    std::vector<const Course*> result;
    result.reserve(m_courses.size());
    for (const auto& [id, ptr] : m_courses) {
        result.push_back(ptr.get());
    }
    return result;
} 