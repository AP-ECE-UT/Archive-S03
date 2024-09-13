#include "professor.hpp"

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

#include "../../exceptions/exceptions.hpp"
#include "../shared_area/TAform.hpp"
#include "../shared_area/shared_area.hpp"
#include "../university_entities/major.hpp"
#include "../university_entities/presentation.hpp"
#include "member_consts.hpp"

using namespace member_consts;
using namespace communication_consts;

Professor::Professor(std::string id, std::string name, std::string password,
                     Major* teachingField, Position position)
    : Member(id, name, password) {
    teachingField_ = teachingField;
    position_ = position;
}

std::string Professor::getInformationStr() {
    return name_ + " " + teachingField_->getName() + " " +
           getPositionStr(position_) + " " + getPresentationsStr();
}

void Professor::addPresentation(Presentation* presentation) {
    presentations_.push_back(presentation);
}

std::string Professor::getPositionStr(Position position) {
    switch (position) {
    case ASSOCIATE:
        return teacher_position_str::ASSOCIATE;
    case ASSISTANT_PROFESSOR:
        return teacher_position_str::ASSISTANT_PROFESSOR;
    case INSTRUCTOR_PROFESSOR:
        return teacher_position_str::INSTRUCTOR_PROFESSOR;
    case PROFESSOR:
        return teacher_position_str::PROFESSOR;
    default:
        return teacher_position_str::UNKNOWN_POSITION;
    }
}

std::string Professor::getPresentationsStr() {
    std::string presentationsStr = "";
    for (size_t i = 0; i < presentations_.size(); i++) {
        presentationsStr += presentations_[i]->getCourseName();
        if (i != (presentations_.size() - 1))
            presentationsStr += ",";
    }
    return presentationsStr;
}

Professor::~Professor() {
    for (auto presentation : presentations_) {
        delete presentation;
    }
}

bool Professor::canPresent(Course* course, ClassTime classTime) {
    for (auto presentedCourse : presentations_) {
        if (presentedCourse->doesOverlapClassTime(classTime)) {
            return false;
        }
    }

    for (auto validMajor : course->getValidMajors()) {
        if (validMajor == teachingField_) {
            return true;
        }
    }

    return false;
}

void Professor::addStudentToTAForm(Member* student, unsigned int formId) {
    personalPage_->addStudentToTAForm(student, formId);
}

bool Professor::canRequestService(communication_consts::Services service) {
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
        return true;
    case Services::GET_NOTIFICATION:
        return true;
    case Services::ADD_PRESENTATION:
        return false;
    case Services::ADD_TO_MY_COURSES:
        return false;
    case Services::DELETE_FROM_MY_COURSES:
        return false;
    case Services::GET_MY_COURSES:
        return false;
    case Services::SEND_TA_FORM:
        return true;
    case Services::SET_PROFILE:
        return true;
    case Services::CLOSE_TA_FORM:
        return true;
    case Services::SEND_TA_REQUEST:
        return false;
    default:
        return false;
    }
}

void Professor::sendTAForm(unsigned int courseId, std::string message) {
    for (auto presentedCourse : presentations_) {
        if (presentedCourse->getId() == courseId) {
            personalPage_->addTAForm(presentedCourse, message, this);
            return;
        }
    }
    throw PermissionDeniedException(messages::CAN_NOT_FIND_COURSE_PRESENTATION);
}

void Professor::closeTAForm(unsigned int formId, std::vector<bool> results) {
    personalPage_->closeTAForm(formId, results);
}

std::vector<std::string>
Professor::collectStudentInfoForTAForm(unsigned int formId) {
    return personalPage_->collectStudentInfoForTAForm(formId);
}

void Professor::addAssistantsToPresentation(TAform* ta_form,
                                            std::vector<bool> results) {
    std::vector<Member*> requestedStudents = ta_form->getRequestedStudents();
    Presentation* presentation = ta_form->getCoursePresentation();
    for (int i = 0; i < (int)results.size(); i++)
        if (results[i])
            presentation->addTA(requestedStudents[i]);
}
