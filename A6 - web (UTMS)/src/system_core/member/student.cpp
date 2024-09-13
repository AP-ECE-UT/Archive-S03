#include "student.hpp"

#include <string>
#include <vector>

#include "../university_entities/major.hpp"
#include "../university_entities/presentation.hpp"
#include "member_consts.hpp"

using namespace communication_consts;
using namespace member_consts;

Student::Student(std::string id, std::string name, std::string password,
                 Major* studingField, int semester)
    : Member(id, name, password) {
    studingField_ = studingField;
    semester_ = semester;
}

std::string Student::getInformationStr() {
    return name_ + " " + studingField_->getName() + " " +
           std::to_string(semester_) + " " + getCoursesStr();
}

std::string Student::getInformationForTaForm() {
    return id_ + " " + name_ + " " + std::to_string(semester_);
}

void Student::addCourse(Presentation* course) { courses_.push_back(course); }

void Student::removeCourse(Presentation* course) {
    std::vector<Presentation*> newPresentations;
    for (auto c : courses_) {
        if (c != course) {
            newPresentations.push_back(c);
        }
    }
    courses_ = newPresentations;
}

std::string Student::getCoursesStr() {
    std::string presentationsStr = "";
    for (size_t i = 0; i < courses_.size(); i++) {
        presentationsStr += courses_[i]->getCourseName();
        if (i != (courses_.size() - 1))
            presentationsStr += ",";
    }
    return presentationsStr;
}

std::vector<Presentation*> Student::getCourses() { return courses_; }

int Student::getSemester() { return semester_; }

Major* Student::getMajor() { return studingField_; }

bool Student::canRequestService(communication_consts::Services service) {
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
        return true;
    case Services::DELETE_FROM_MY_COURSES:
        return true;
    case Services::GET_MY_COURSES:
        return true;
    case Services::SET_PROFILE:
        return true;
    case Services::SEND_TA_REQUEST:
        return true;
    case Services::SEND_TA_FORM:
        return false;
    case Services::CLOSE_TA_FORM:
        return false;
    default: return false;
    }
}
