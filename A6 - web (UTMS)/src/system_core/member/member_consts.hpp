#ifndef MEMBER_CONSTS_HPP_INCLUDE
#define MEMBER_CONSTS_HPP_INCLUDE

#include <map>
#include <string_view>

#include "professor.hpp"

namespace member_consts {
// clang-format off

namespace messages {
constexpr char CAN_NOT_FIND_COURSE_PRESENTATION[] = "Can not find course presentation";
constexpr char CAN_NOT_FIND_MEMBER[] = "Can not find member";
} // namespace messages

const std::map<std::string, Professor::Position> teacher_position_map
{
    {"associate", Professor::Position::ASSOCIATE},
    {"assistant professor", Professor::Position::ASSISTANT_PROFESSOR},
    {"instructor professor", Professor::Position::INSTRUCTOR_PROFESSOR},
    {"professor", Professor::Position::PROFESSOR}
};

namespace teacher_position_str {
constexpr char ASSOCIATE[]            = "Associate";
constexpr char ASSISTANT_PROFESSOR[]  = "Assistant Professor";
constexpr char INSTRUCTOR_PROFESSOR[] = "Instructor Professor";
constexpr char PROFESSOR[]            = "Professor";
constexpr char UNKNOWN_POSITION[]     = "Unknown Position";
} // namespace teacher_position_str

namespace ut_member {
constexpr std::string_view ID = "0";
constexpr char PASSWORD[] = "UT_account";
} // namespace ut_member

// clang-format on
} // namespace member_consts

#endif // MEMBER_CONSTS_HPP_INCLUDE
