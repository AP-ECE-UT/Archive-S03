#include "notification.hpp"

#include <string>

#include "../member/member.hpp"
#include "../university_entities/presentation.hpp"

using namespace notification_consts;

Notification::Notification(Member* member, Type type) {
    member_ = member;
    type_ = type;
    unreadNumber_ = 0;
    isPresentationNotif_ = false;
}

Notification::Notification(Presentation* presentation, Type type) {
    presentation_ = presentation;
    type_ = type;
    unreadNumber_ = 0;
    isPresentationNotif_ = true;
}

Notification::Notification(Presentation* presentation, Type type, Member* publisher) : Notification::Notification(presentation, type) {
    member_ = publisher;
}

std::string Notification::getDetail() {
    if (!isPresentationNotif_) {
        std::string memberId = member_->getId();
        std::string memberName = member_->getName();
        std::string typeStr = typeToStr(type_);
        return memberId + " " + memberName + ": " + typeStr;
    }
    else {
        unsigned int presentationId = presentation_->getId();
        std::string courseName = presentation_->getCourseName();
        return std::to_string(presentationId) + " " + courseName + ": " +
               typeToStr(type_);
    }
}

void Notification::sent() { unreadNumber_++; }

void Notification::read() {
    unreadNumber_--;
    if (unreadNumber_ <= 0) {
        delete this;
    }
}

std::string Notification::typeToStr(Type type) {
    switch (type) {
    case NEW_POST:
        return typestr::NEW_POST;
    case NEW_PRESENTATION:
        return typestr::NEW_PRESENTATION;
    case GET_COURSE:
        return typestr::GET_COURSE;
    case DELETE_COURSE:
        return typestr::DELETE_COURSE;
    case TA_REQUEST_ACCEPTED:
        return typestr::TA_REQUEST_ACCEPTED;
    case TA_REQUEST_REJECTED:
        return typestr::TA_REQUEST_REJECTED;
    case NEW_COURSE_POST:
        return typestr::NEW_COUESE_POST;
    case NEW_FORM:
        return typestr::NEW_FORM;
    default:
        return typestr::UNKNOWN_TYPE;
    }
}

Member* Notification::getPublisher() {
    return member_;
}
