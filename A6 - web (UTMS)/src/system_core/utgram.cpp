#include "utgram.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "../data_loader/data_loader.hpp"
#include "../exceptions/exceptions.hpp"
#include "../general/io_utils.hpp"
#include "member/member.hpp"
#include "member/ut_member.hpp"
#include "token/token.hpp"
#include "university_entities/course.hpp"
#include "university_entities/presentation.hpp"
#include "utgram_consts.hpp"

using namespace utgram_consts;
using namespace std;

Utgram::Utgram(DataLoader loader) {
    majors_ = loader.loadMajors();
    courses_ = loader.loadCourses(majors_);
    members_ = loader.loadAllMembers(majors_);
    members_.push_back(setupUtMember());
}

UtMember* Utgram::setupUtMember() {
    UtMember* utMember = new UtMember();
    for (Member* member : members_) {
        utMember->connectTo(member);
    }
    return utMember;
}

Token Utgram::login(std::string id, std::string password) {
    Token token(id, password, true);
    authentication(token);
    return token;
}

Member* Utgram::authentication(Token token) {
    if (!token.isValid()) {
        throw PermissionDeniedException(err_messages::INVALID_TOKEN);
    }

    Member* targetMember = Member::findById(members_, token.getId());
    if (targetMember->isPassword(token.getPass())) {
        return targetMember;
    }
    else {
        throw PermissionDeniedException(err_messages::WRONG_PASSWORD);
    }
}

Utgram::~Utgram() {
    for (auto member : members_) {
        delete member;
    }
    for (auto major : majors_) {
        delete major;
    }
    for (auto course : courses_) {
        delete course;
    }
}

vector<Presentation*>
Utgram::getCourses(vector<unsigned int> presentationIds) {
    if (presentationIds.empty()) {
        if (presentations_.size() == 0) {
            throw EmptyException();
        }
        else {
            return presentations_;
        }
    }
    vector<Presentation*> res;
    for (auto presentationId : presentationIds) {
        auto presentation = Presentation::findById(presentations_, presentationId);
        res.push_back(presentation);
    }

    sort(res.begin(), res.end(), [](Presentation* a, Presentation* b) {
        return a->getCourseId() < b->getCourseId();
    });

    return res;
}

void Utgram::logout(Token& token) { token.disable(); }

void Utgram::addPost(Token token, string title, string message) {
    auto currentUser = authentication(token);
    currentUser->addPost(title, message, currentUser);
    auto notif = new Notification(currentUser, Notification::NEW_POST);
    currentUser->notifyYourConnections(notif);
}

void Utgram::addPost(Token token, string title, string message, string image) {
    auto currentUser = authentication(token);
    currentUser->addPost(title, message, currentUser, image);
    auto notif = new Notification(currentUser, Notification::NEW_POST);
    currentUser->notifyYourConnections(notif);
}

void Utgram::deletePost(Token token, unsigned int postId) {
    auto currentUser = authentication(token);
    currentUser->deletePost(postId, currentUser);
}

std::vector<std::string> Utgram::getPersonalPage(string id) {
    auto user = Member::findById(members_, id);
    return user->getContentSummary(user);
}

string Utgram::getPost(string id, vector<unsigned int> postIds) {
    auto user = Member::findById(members_, id);
    return user->getPostDetail(postIds[0], user);
}

void Utgram::connect(Token token, std::string id) {
    auto currentUser = authentication(token);
    auto destUser = Member::findById(members_, id);

    if (currentUser->isAlreadyConnected(destUser)) {
        throw BadRequestException();
    }

    currentUser->connectTo(destUser);
    destUser->connectTo(currentUser);
}

vector<Notification> Utgram::getNotification(Token token) {
    auto currentUser = authentication(token);
    return currentUser->getNotifications();
}

void Utgram::addPresentation(Token token, unsigned int courseId,
                             std::string professorId, int cap, std::string time,
                             std::string examDate, int classNum) {
    auto currentUser = (UtMember*)authentication(token);
    auto course = Course::findById(courses_, courseId);
    auto foundMember = Member::findById(members_, professorId);
    auto professor = dynamic_cast<Professor*>(foundMember);
    if (professor == nullptr) {
        throw PermissionDeniedException();
    }
    auto classTime = new ClassTime(time);
    auto data = new ExamDate(examDate);

    auto new_presentation = currentUser->createPresentation(
        course, professor, cap, classTime, data, classNum);
    presentations_.push_back(new_presentation);
    auto notif = new Notification(professor, Notification::NEW_PRESENTATION);
    currentUser->notifyYourConnections(notif);
}

void Utgram::addToMyCourses(Token token, unsigned int presentationId) {
    auto currentUser = (Student*)authentication(token);
    auto presentation = Presentation::findById(presentations_, presentationId);
    if (!presentation->checkRequirements(currentUser)) {
        throw PermissionDeniedException();
    }

    currentUser->addCourse(presentation);
    presentation->addStudent(currentUser);
    auto notif = new Notification(currentUser, Notification::GET_COURSE);
    currentUser->notifyYourConnections(notif);
}

void Utgram::deleteFromMyCourses(Token token, unsigned int presentationId) {
    auto currentUser = (Student*)authentication(token);
    auto presentation =
        Presentation::findById(currentUser->getCourses(), presentationId);
    currentUser->removeCourse(presentation);
    auto notif = new Notification(currentUser, Notification::DELETE_COURSE);
    currentUser->notifyYourConnections(notif);
}

std::vector<Presentation*> Utgram::getMyCourses(Token token) {
    auto currentUser = (Student*)authentication(token);
    return currentUser->getCourses();
}

void Utgram::sendTAForm(Token token, unsigned int courseId,
                        std::string messages) {
    auto currentUser = (Professor*)authentication(token);
    Presentation::findById(this->presentations_, courseId);
    currentUser->sendTAForm(courseId, messages);
    auto notif = new Notification(currentUser, Notification::NEW_FORM);
    currentUser->notifyYourConnections(notif);
}

void Utgram::setProfile(Token token, std::string photoAddress) {
    auto currentUser = authentication(token);
    currentUser->setProfile(photoAddress);
}

void Utgram::sendTARequest(Token token, std::string professorId,
                           unsigned int formId) {
    auto currentUser = authentication(token);
    auto foundMember = Member::findById(members_, professorId);
    auto professor = dynamic_cast<Professor*>(foundMember);
    Post* form = professor->getPostById(formId);
    if (!form->isTAform()) {
        throw NotFoundException();
    }
    professor->addStudentToTAForm(currentUser, formId);
}

Member* Utgram::findMemberById(string id) {
    return Member::findById(members_, id);
}

void Utgram::closeTAForm(Token token, unsigned int formId,
                         vector<bool> results) {
    auto currentUser = (Professor*)authentication(token);
    Post* form = currentUser->getPostById(formId);
    if (!form->isTAform()) {
        throw NotFoundException();
    }
    currentUser->closeTAForm(formId, results);
}

std::vector<std::string>
Utgram::collectStudentInfoForTAForm(Token token, unsigned int formId) {
    auto currentUser = (Professor*)authentication(token);
    return currentUser->collectStudentInfoForTAForm(formId);
}

void Utgram::addCoursePost(Token token, unsigned int presentationId,
                           string title, string message, string image) {
    Member* currentUser = authentication(token);
    Presentation* targetPresentation =
        Presentation::findById(this->presentations_, presentationId);
    targetPresentation->addPost(title, message, currentUser, image);
    auto notif = new Notification(targetPresentation, Notification::NEW_COURSE_POST, currentUser);
    targetPresentation->notifyMembers(notif);
}

void Utgram::addCoursePost(Token token, unsigned int presentationId,
                           string title, string message) {
    Member* currentUser = authentication(token);
    Presentation* targetPresentation =
        Presentation::findById(this->presentations_, presentationId);
    targetPresentation->addPost(title, message, currentUser);
    auto notif = new Notification(targetPresentation, Notification::NEW_COURSE_POST, currentUser);
    targetPresentation->notifyMembers(notif);
}

std::vector<std::string> Utgram::getCourseChanel(Token token,
                                                 unsigned int presentationId) {
    Member* currentUser = authentication(token);
    Presentation* targetPresentation =
        Presentation::findById(this->presentations_, presentationId);
    return targetPresentation->getContentSummary(currentUser);
}

vector<string> Utgram::getCoursePost(Token token, unsigned int presentationId,
                                     unsigned int postId) {
    Member* currentUser = authentication(token);
    Presentation* targetPresentation =
        Presentation::findById(this->presentations_, presentationId);

    vector<string> response;
    // response.push_back(targetPresentation->detailedStr());
    response.push_back(targetPresentation->getPostDetail(postId, currentUser));
    return response;
}
