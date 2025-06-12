#include "Student.h"

Student::Student(std::int32_t id,
                 std::string name,
                 std::string email,
                 std::string phone,
                 std::string address,
                 std::string password)
    : m_id(id),
      m_name(std::move(name)),
      m_email(std::move(email)),
      m_phone(std::move(phone)),
      m_address(std::move(address)),
      m_password(std::move(password)) {} 