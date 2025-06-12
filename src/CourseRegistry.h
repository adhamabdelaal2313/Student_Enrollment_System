#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "Course.h"

class CourseRegistry {
public:
    bool addCourse(std::unique_ptr<Course> course);
    bool removeCourse(std::int32_t id);

    Course* findCourse(std::int32_t id) const;
    std::vector<const Course*> allCourses() const;

private:
    std::unordered_map<std::int32_t, std::unique_ptr<Course>> m_courses;
}; 