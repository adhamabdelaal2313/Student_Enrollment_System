#pragma once

#include <string>
#include <cstdint>

// A lightweight value-object representing a student in the enrollment system.
// This class is fully RAII and does not allocate any dynamic memory on its own —
// all std::string members manage their memory automatically.
class Student final {
public:
    Student(std::int32_t id,
            std::string name,
            std::string email = {},
            std::string phone = {},
            std::string address = {},
            std::string password = {});

    // ---------- Immutable getters ----------
    std::int32_t id() const noexcept { return m_id; }
    const std::string &name() const noexcept { return m_name; }
    const std::string &email() const noexcept { return m_email; }
    const std::string &phone() const noexcept { return m_phone; }
    const std::string &address() const noexcept { return m_address; }

    // ---------- Mutators ----------
    void setName(std::string name) { m_name = std::move(name); }
    void setEmail(std::string email) { m_email = std::move(email); }
    void setPhone(std::string phone) { m_phone = std::move(phone); }
    void setAddress(std::string address) { m_address = std::move(address); }

private:
    std::int32_t m_id;
    std::string m_name;
    std::string m_email;
    std::string m_phone;
    std::string m_address;
    std::string m_password; // stored as plain-text for now — replace with secure hash in production
}; 