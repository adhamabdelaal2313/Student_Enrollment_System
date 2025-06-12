#pragma once

#include <string>
#include <cstdint>
#include <vector>

class Course final {
public:
    Course(std::int32_t id,
           std::string name,
           std::uint8_t credits,
           std::string instructor,
           std::vector<std::int32_t> prerequisites = {});

    // Immutable getters
    std::int32_t id() const noexcept { return m_id; }
    const std::string &name() const noexcept { return m_name; }
    std::uint8_t credits() const noexcept { return m_credits; }
    const std::string &instructor() const noexcept { return m_instructor; }
    const std::vector<std::int32_t> &prerequisites() const noexcept { return m_prerequisites; }

    // Mutators
    void setName(std::string name) { m_name = std::move(name); }
    void setCredits(std::uint8_t credits) { m_credits = credits; }
    void setInstructor(std::string instructor) { m_instructor = std::move(instructor); }
    void setPrerequisites(std::vector<std::int32_t> pre) { m_prerequisites = std::move(pre); }

private:
    std::int32_t m_id;
    std::string m_name;
    std::uint8_t m_credits;
    std::string m_instructor;
    std::vector<std::int32_t> m_prerequisites;
}; 