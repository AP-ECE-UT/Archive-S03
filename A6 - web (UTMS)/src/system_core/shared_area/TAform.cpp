#include "TAform.hpp"

#include <iostream>

#include "../../exceptions/exceptions.hpp"
#include "../member/student.hpp"
#include "../notification/notification.hpp"
#include "../university_entities/presentation.hpp"
#include "shared_area_consts.hpp"

using namespace shared_area_consts;

TAform::TAform(unsigned int id, std::string message, Member* publisher,
               Presentation* coursePresentation)
    : Post(id, message, publisher) {
    status_ = ACTIVE;
    coursePresentation_ = coursePresentation;
}

std::string TAform::getSummary() {
    return std::to_string(id_) + " TA form for " +
           coursePresentation_->getCourseName() + " course";
}

std::string TAform::getDetail() {
    return getSummary() + "\n" + coursePresentation_->detailedStr() + "\n" +
           message_;
}

void TAform::addStudentToTAForm(Member* student) {
    Student* tempStudent = dynamic_cast<Student*>(student);
    checkRequestedStudent(tempStudent);
    requestedStudents_.push_back(student);
}

void TAform::checkRequestedStudent(Student* student) {
    if (!coursePresentation_->canGetThisPresentation(student))
        throw PermissionDeniedException();
}

std::vector<std::string> TAform::studentInfos() {
    std::vector<std::string> res;
    for (auto member : requestedStudents_) {
        auto student = dynamic_cast<Student*>(member);
        res.push_back(student->getInformationForTaForm());
    }
    return res;
}

void TAform::sendRequestResults(std::vector<bool> resutls) {
    for (int i = 0; i < (int)requestedStudents_.size(); i++) {
        Notification* notification;
        if (resutls[i])
            notification = new Notification(coursePresentation_,
                                            Notification::TA_REQUEST_ACCEPTED);
        else
            notification = new Notification(coursePresentation_,
                                            Notification::TA_REQUEST_REJECTED);
        notification->sent();
        requestedStudents_[i]->getNotified(notification);
    }
}

std::vector<Member*> TAform::getRequestedStudents() {
    return this->requestedStudents_;
}
Presentation* TAform::getCoursePresentation() {
    return this->coursePresentation_;
}

bool TAform::isTAform() {
    return true;
}