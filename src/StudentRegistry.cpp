#include "StudentRegistry.h"

bool StudentRegistry::addStudent(std::unique_ptr<Student> student) {
    if (!student) { return false; }
    const auto id = student->id();
    auto [it, inserted] = m_students.emplace(id, std::move(student));
    return inserted;
}

bool StudentRegistry::removeStudent(std::int32_t id) {
    return m_students.erase(id) > 0;
}

Student* StudentRegistry::findStudent(std::int32_t id) const {
    auto it = m_students.find(id);
    return it == m_students.end() ? nullptr : it->second.get();
}

std::vector<const Student*> StudentRegistry::allStudents() const {
    std::vector<const Student*> result;
    result.reserve(m_students.size());
    for (const auto& [id, ptr] : m_students) {
        result.push_back(ptr.get());
    }
    return result;
} 