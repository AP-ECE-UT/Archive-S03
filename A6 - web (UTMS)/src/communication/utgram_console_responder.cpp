#include "utgram_console_responder.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "../general/io_utils.hpp"
#include "../system_core/utgram.hpp"
#include "communication_consts.hpp"
#include "request.hpp"
#include "utgram_base_responder.hpp"

using namespace communication_consts;
using namespace std;

UtgramConsoleResponder::UtgramConsoleResponder(Utgram* utgram)
    : UtgramBaseResponder(utgram){};

void UtgramConsoleResponder::checkPermission(
    bool doesRequireLogin, Token token,
    communication_consts::Services service) {
    if (doesRequireLogin) {
        if (!token.isValid()) {
            throw PermissionDeniedException();
        }
        auto currentUser = utgram_->findMemberById(token.getId());
        if (!currentUser->canRequestService(service)) {
            throw PermissionDeniedException();
        }
    }
}

void UtgramConsoleResponder::requireNotLoggedIn() {
    if (token_.isValid()) {
        throw PermissionDeniedException();
    }
}

void UtgramConsoleResponder::ok() { cout << "OK" << endl; }

void UtgramConsoleResponder::empty() {
    cout << EmptyException::exceptionMessage() << endl;
}

void UtgramConsoleResponder::notFound() {
    cout << NotFoundException::exceptionMessage() << endl;
}

void UtgramConsoleResponder::badRequest() {
    cout << BadRequestException::exceptionMessage() << endl;
}

void UtgramConsoleResponder::permissionDenied() {
    cout << PermissionDeniedException::exceptionMessage() << endl;
}

void UtgramConsoleResponder::login(Arguments args) {
    requireNotLoggedIn();
    checkPermission(false, token_, communication_consts::Services::LOGIN);

    if (!validateArgumentExistance(args, vector<string>{"id", "password"}))
        throw BadRequestException();
    token_ = utgram_->login(args["id"], args["password"]);
    ok();
}

void UtgramConsoleResponder::logout() {
    checkPermission(true, token_, communication_consts::Services::LOGOUT);
    if (token_.isValid()) {
        token_.disable();
        ok();
    }
    else {
        throw PermissionDeniedException();
    }
}

void UtgramConsoleResponder::getCourses(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::GET_COURSES);

    if (args.find(arguments::ID) == args.end()) {
        getAllCourses();
    }
    else {
        getCourseById(args[arguments::ID]);
    }
}

void UtgramConsoleResponder::addPost(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::ADD_POST);

    if (!validateArgumentExistance(args, vector<string>{"title", "message"}))
        throw BadRequestException();

    if (validateArgumentExistance(args, vector<string>{"image"})) {
        utgram_->addPost(token_, args["title"], args["message"], args["image"]);
    }
    else {
        utgram_->addPost(token_, args["title"], args["message"]);
    }
    ok();
}

void UtgramConsoleResponder::deletePost(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::DELETE_POST);

    if (!validateArgumentExistance(args, vector<string>{"id"}))
        throw BadRequestException();
    utgram_->deletePost(token_, stoul(args["id"]));
    ok();
}

void UtgramConsoleResponder::getPersonalPage(Arguments args) {
    checkPermission(true, token_,
                    communication_consts::Services::GET_PERSONAL_PAGE);

    if (!validateArgumentExistance(args, vector<string>{"id"}))
        throw BadRequestException();
    std::vector<std::string> response = utgram_->getPersonalPage(args["id"]);
    cout << vectorToStr(response);
}

void UtgramConsoleResponder::getPost(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::GET_POST);

    if (!validateArgumentExistance(args, vector<string>{"id", "post_id"}))
        throw BadRequestException();
    auto stringIds = io_utils::splitString(args["post_id"], IDS_DELIM);
    auto unsignedIds = io_utils::convertToUnsigned(stringIds);
    string postDetail = utgram_->getPost(args["id"], unsignedIds);
    cout << postDetail << endl;
}

void UtgramConsoleResponder::connect(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::CONNECT);

    if (!validateArgumentExistance(args, vector<string>{"id"}))
        throw BadRequestException();
    utgram_->connect(token_, args["id"]);
    ok();
}

void UtgramConsoleResponder::getNotification() {
    checkPermission(true, token_,
                    communication_consts::Services::GET_NOTIFICATION);

    vector<Notification> notifs = utgram_->getNotification(token_);
    if (notifs.empty())
        throw EmptyException();
    for_each(notifs.begin(), notifs.end(),
             [](Notification n) { cout << n.getDetail() << endl; });
}

void UtgramConsoleResponder::addPresentation(Arguments args) {
    checkPermission(true, token_,
                    communication_consts::Services::ADD_PRESENTATION);

    if (!validateArgumentExistance(
            args, vector<string>{"course_id", "professor_id", "capacity", "time",
                                 "exam_date", "class_number"}))
        throw BadRequestException();

    if (!io_utils::isNumber(args["course_id"]))
        throw BadRequestException();
    if (!io_utils::isNumber(args["capacity"]))
        throw BadRequestException();
    if (!io_utils::isNumber(args["class_number"]))
        throw BadRequestException();

    utgram_->addPresentation(token_, stoul(args["course_id"]),
                             args["professor_id"], stoi(args["capacity"]),
                             args["time"], args["exam_date"],
                             stoi(args["class_number"]));
    ok();
}

void UtgramConsoleResponder::addToMyCourses(Arguments args) {
    checkPermission(true, token_,
                    communication_consts::Services::ADD_TO_MY_COURSES);

    if (!validateArgumentExistance(args, vector<string>{"id"}))
        throw BadRequestException();
    if (!io_utils::isNumber(args["id"]))
        throw BadRequestException();
    utgram_->addToMyCourses(token_, stoi(args["id"]));
    ok();
}

void UtgramConsoleResponder::deleteFromMyCourses(Arguments args) {
    checkPermission(true, token_,
                    communication_consts::Services::DELETE_FROM_MY_COURSES);

    if (!validateArgumentExistance(args, vector<string>{"id"}))
        throw BadRequestException();
    if (!io_utils::isNumber(args["id"]))
        throw BadRequestException();
    utgram_->deleteFromMyCourses(token_, stoul(args["id"]));
    ok();
}

void UtgramConsoleResponder::getMyCourses() {
    checkPermission(true, token_, communication_consts::Services::GET_MY_COURSES);

    vector<Presentation*> courses = utgram_->getMyCourses(token_);
    if (courses.empty())
        throw EmptyException();
    for_each(courses.begin(), courses.end(),
             [](Presentation* p) { cout << p->detailedStr() << endl; });
}

string UtgramConsoleResponder::vectorToStr(vector<string> vec) {
    stringstream str;
    for (string s : vec)
        str << s << '\n';
    return str.str();
}

void UtgramConsoleResponder::getAllCourses() {
    vector<Presentation*> courses = utgram_->getCourses(vector<unsigned int>());
    if (courses.empty()) {
        throw EmptyException();
    }

    for_each(courses.begin(), courses.end(),
             [](Presentation* p) { cout << p->summaryStr() << endl; });
}

void UtgramConsoleResponder::sendTAForm(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::SEND_TA_FORM);

    if (!validateArgumentExistance(args, vector<string>{"course_id", "message"}))
        throw BadRequestException();
    utgram_->sendTAForm(token_, stoul(args["course_id"]), args["message"]);
    ok();
}

void UtgramConsoleResponder::setProfile(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::SET_PROFILE);
    if (!validateArgumentExistance(args, vector<string>{"photo"}))
        throw BadRequestException();
    utgram_->setProfile(token_, args["photo"]);
    ok();
}

void UtgramConsoleResponder::sendTARequest(Arguments args) {
    checkPermission(true, token_,
                    communication_consts::Services::SEND_TA_REQUEST);
    if (!validateArgumentExistance(args,
                                   vector<string>{"professor_id", "form_id"}))
        throw BadRequestException();
    utgram_->sendTARequest(token_, args["professor_id"], stoul(args["form_id"]));
    ok();
}

void UtgramConsoleResponder::getCourseById(std::string idStr) {
    auto stringIds = io_utils::splitString(idStr, IDS_DELIM);
    auto unsignedIds = io_utils::convertToUnsigned(stringIds);
    vector<Presentation*> courses = utgram_->getCourses(unsignedIds);
    for_each(courses.begin(), courses.end(),
             [](Presentation* p) { cout << p->detailedStr() << endl; });
}

void UtgramConsoleResponder::closeTAForm(Arguments args) {
    checkPermission(true, token_, communication_consts::Services::CLOSE_TA_FORM);
    if (!validateArgumentExistance(args, vector<string>{"id"}))
        throw BadRequestException();
    auto currentUser = (Professor*)utgram_->authentication(token_);
    Post* form = currentUser->getPostById(stoul(args["id"]));
    if (!form->isTAform()) {
        throw NotFoundException();
    }
    vector<string> studentInfos =
        utgram_->collectStudentInfoForTAForm(token_, stoul(args["id"]));
    vector<bool> results;
    cout << "We have received " << studentInfos.size()
         << " requests for the teaching assistant position\n";
    for (std::string info : studentInfos) {
        while (true) {
            string respond;
            cout << info << ": ";
            cin >> respond;
            if (respond == "accept") {
                results.push_back(true);
                break;
            }
            else if (respond == "reject") {
                results.push_back(false);
                break;
            }
        }
    }
    utgram_->closeTAForm(token_, stoul(args["id"]), results);
}

void UtgramConsoleResponder::addCoursePost(Arguments args) {
    if (!validateArgumentExistance(args,
                                   vector<string>{"id", "title", "message"}))
        throw BadRequestException();

    if (validateArgumentExistance(args, vector<string>{"image"})) {
        utgram_->addCoursePost(token_, stoul(args["id"]), args["title"],
                               args["message"], args["image"]);
    }
    else {
        utgram_->addCoursePost(token_, stoul(args["id"]), args["title"],
                               args["message"]);
    }
    ok();
}

void UtgramConsoleResponder::getCourseChannel(Arguments args) {
    if (!validateArgumentExistance(args, vector<string>{"id"}))
        throw BadRequestException();

    vector<string> response = utgram_->getCourseChanel(token_, stoul(args["id"]));
    cout << vectorToStr(response);
}

void UtgramConsoleResponder::getCoursePost(Arguments args) {
    if (!validateArgumentExistance(args, vector<string>{"id", "post_id"}))
        throw BadRequestException();

    vector<string> response =
        utgram_->getCoursePost(token_, stoul(args["id"]), stoul(args["post_id"]));
    cout << vectorToStr(response);
}
