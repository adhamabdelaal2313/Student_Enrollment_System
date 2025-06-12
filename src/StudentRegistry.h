#pragma once

#include <unordered_map>
#include <memory>
#include <vector>
#include "Student.h"

// A small repository class that owns Student objects and provides
// basic CRUD operations. All ownership is handled through
// std::unique_ptr, ensuring there are no leaks and every Student
// instance has a single clear owner.
class StudentRegistry {
public:
    // Adds a student. Returns false if a student with the same id already exists.
    bool addStudent(std::unique_ptr<Student> student);

    // Removes student by id. Returns false if not found.
    bool removeStudent(std::int32_t id);

    // Finds a student by id. Returns nullptr if not found.
    Student* findStudent(std::int32_t id) const;

    // Returns a snapshot (const pointers) of all students.
    std::vector<const Student*> allStudents() const;

private:
    std::unordered_map<std::int32_t, std::unique_ptr<Student>> m_students;
}; 