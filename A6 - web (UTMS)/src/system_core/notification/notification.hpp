#ifndef NOTIFICATION_HPP_INCLUDE
#define NOTIFICATION_HPP_INCLUDE

#include <string>

namespace notification_consts {
// clang-format off

namespace typestr {
constexpr char NEW_POST[]         = "New Post";
constexpr char NEW_PRESENTATION[] = "New Course Offering";
constexpr char GET_COURSE[]       = "Get Course";
constexpr char DELETE_COURSE[]    = "Delete Course";
constexpr char UNKNOWN_TYPE[]     = "UNKNOWN TYPE";
constexpr char TA_REQUEST_ACCEPTED[]     = "Your request to be a teaching assistant has been accepted.";
constexpr char TA_REQUEST_REJECTED[]     = "Your request to be a teaching assistant has been rejected.";
constexpr char NEW_COUESE_POST[]         = "New Course Post";
constexpr char NEW_FORM[]         = "New Form";
} // namespace typestr

// clang-format on
} // namespace notification_consts

class Member;
class Presentation;

class Notification {
public:
    enum Type {
        NEW_POST,
        NEW_PRESENTATION,
        GET_COURSE,
        DELETE_COURSE,
        TA_REQUEST_ACCEPTED,
        TA_REQUEST_REJECTED,
        NEW_COURSE_POST,
        NEW_FORM
    };

    Notification(Member* member, Type type);
    Notification(Presentation* presentation, Type type);
    Notification(Presentation* presentation, Type type, Member* publisher);
    std::string getDetail();
    Member* getPublisher();
    void sent();
    void read();

private:
    static std::string typeToStr(Type type);

    bool isPresentationNotif_;
    Presentation* presentation_;
    Member* member_;
    Type type_;
    int unreadNumber_;
};

#endif // NOTIFICATION_HPP_INCLUDE
