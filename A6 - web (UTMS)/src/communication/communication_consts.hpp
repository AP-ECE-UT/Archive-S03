#ifndef COMMUNICATION_CONSTS_HPP_INCLUDE
#define COMMUNICATION_CONSTS_HPP_INCLUDE

namespace communication_consts {
// clang-format off

namespace commands {
constexpr char LOGIN[]         = "login";
constexpr char LOGOUT[]        = "logout";
constexpr char COURSES[]       = "courses";
constexpr char POST[]          = "post";
constexpr char PERSONAL_PAGE[] = "personal_page";
constexpr char CONNECT[]       = "connect";
constexpr char NOTIFICATION[]  = "notification";
constexpr char PRESENTATION[]  = "course_offer";
constexpr char MY_COURSES[]    = "my_courses";
constexpr char TA_FORM[]       = "ta_form";
constexpr char SET_PROFILE[]   = "profile_photo";
constexpr char SEND_TA_REQUEST[]   = "ta_request";
constexpr char CLOSE_TA_FORM[]   = "close_ta_form";
constexpr char COURSE_POST[]   = "course_post";
constexpr char COURSE_CHANNEL[]   = "course_channel";
} // namespace commands

namespace arguments {
constexpr char ID[]           = "id";
constexpr char PASSWORD[]     = "password";
constexpr char TITLE[]        = "title";
constexpr char MESSAGE[]      = "message";
constexpr char POST_ID[]      = "post_id";
constexpr char COURSE_ID[]    = "course_id";
constexpr char PROFESSOR_ID[] = "professor_id";
constexpr char CAPACITY[]     = "capacity";
constexpr char TIME[]         = "time";
constexpr char EXAM_DATE[]    = "exam_date";
constexpr char CLASS_NUMBER[] = "class_number";
} // namespace arguments

namespace err_messages {
constexpr char NO_MATCHING_ACTION_TYPE[]      = "No matching action type";
constexpr char NO_MATCHING_COMMAND[]          = "No matching command";
constexpr char CAN_NOT_CONVERTED_TO_REQUEST[] = "Can not converted to request"; 
} // namespace err_messages

// clang-format on

enum Services {
    LOGIN,
    LOGOUT,
    GET_COURSES,
    ADD_POST,
    DELETE_POST,
    GET_PERSONAL_PAGE,
    GET_POST,
    CONNECT,
    GET_NOTIFICATION,
    ADD_PRESENTATION,
    ADD_TO_MY_COURSES,
    DELETE_FROM_MY_COURSES,
    GET_MY_COURSES,
    SEND_TA_FORM,
    SET_PROFILE,
    SEND_TA_REQUEST,
    CLOSE_TA_FORM
};

} // namespace communication_consts

#endif // COMMUNICATION_CONSTS_HPP_INCLUDE
