#include "Course.h"

Course::Course(std::int32_t id,
               std::string name,
               std::uint8_t credits,
               std::string instructor,
               std::vector<std::int32_t> prerequisites)
    : m_id(id),
      m_name(std::move(name)),
      m_credits(credits),
      m_instructor(std::move(instructor)),
      m_prerequisites(std::move(prerequisites)) {} 