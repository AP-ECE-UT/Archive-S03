#ifndef UTGRAM_CONSOLE_RESPONDER_HPP_INCLUDE
#define UTGRAM_CONSOLE_RESPONDER_HPP_INCLUDE

#include <string>

#include "../exceptions/bad_request_exception.hpp"
#include "../exceptions/empty_exception.hpp"
#include "../exceptions/not_found_exception.hpp"
#include "../exceptions/permission_denied_exception.hpp"
#include "../system_core/utgram.hpp"
#include "communication_consts.hpp"
#include "request.hpp"
#include "utgram_base_responder.hpp"

class UtgramConsoleResponder : public UtgramBaseResponder {
public:
    UtgramConsoleResponder(Utgram* utgram);
    virtual void ok();
    virtual void empty();
    virtual void notFound();
    virtual void badRequest();
    virtual void permissionDenied();
    virtual void login(Arguments args);
    virtual void logout();
    virtual void getCourses(Arguments args);
    virtual void addPost(Arguments args);
    virtual void deletePost(Arguments args);
    virtual void getPersonalPage(Arguments args);
    virtual void getPost(Arguments args);
    virtual void connect(Arguments args);
    virtual void getNotification();
    virtual void addPresentation(Arguments args);
    virtual void addToMyCourses(Arguments args);
    virtual void deleteFromMyCourses(Arguments args);
    virtual void getMyCourses();
    virtual void sendTAForm(Arguments args);
    virtual void setProfile(Arguments args);
    virtual void sendTARequest(Arguments args);
    virtual void closeTAForm(Arguments args);
    virtual void addCoursePost(Arguments args);
    virtual void getCourseChannel(Arguments args);
    virtual void getCoursePost(Arguments args);
    std::string vectorToStr(std::vector<std::string> vec);

private:
    void checkPermission(bool doesRequireLogin, Token token,
                         communication_consts::Services service);
    void requireNotLoggedIn();
    void getAllCourses();
    void getCourseById(std::string idStr);
};

#endif // UTGRAM_CONSOLE_RESPONDER_HPP_INCLUDE
