#include "ut_member.hpp"

#include <string>

#include "../../exceptions/permission_denied_exception.hpp"
#include "../university_entities/presentation.hpp"
#include "member.hpp"
#include "member_consts.hpp"
#include "professor.hpp"

using namespace member_consts;
using namespace communication_consts;

UtMember::UtMember()
    : Member(std::string(ut_member::ID), ut_member::PASSWORD,
             ut_member::PASSWORD) {}

std::string UtMember::getInformationStr() { return name_; }

Presentation* UtMember::createPresentation(Course* course, Professor* professor,
                                           int cap, ClassTime* classTime,
                                           ExamDate* date, int classNum) {
    if (!professor->canPresent(course, *classTime)) {
        throw PermissionDeniedException();
    }

    auto presentation =
        new Presentation(course, professor, cap, classTime, date, classNum);

    professor->addPresentation(presentation);
    return presentation;
}

bool UtMember::canRequestService(communication_consts::Services service) {
    switch (service) {
    case Services::LOGIN:
        return false;
    case Services::LOGOUT:
        return true;
    case Services::GET_COURSES:
        return true;
    case Services::ADD_POST:
        return true;
    case Services::DELETE_POST:
        return true;
    case Services::GET_PERSONAL_PAGE:
        return true;
    case Services::GET_POST:
        return true;
    case Services::CONNECT:
        return false;
    case Services::GET_NOTIFICATION:
        return false;
    case Services::ADD_PRESENTATION:
        return true;
    case Services::ADD_TO_MY_COURSES:
        return false;
    case Services::DELETE_FROM_MY_COURSES:
        return false;
    case Services::GET_MY_COURSES:
        return false;
    case Services::SET_PROFILE:
        return true;
    case Services::SEND_TA_FORM:
        return false;
    case Services::SEND_TA_REQUEST:
        return false;
    case Services::CLOSE_TA_FORM:
        return false;
    default:
        return false;
    }
}
