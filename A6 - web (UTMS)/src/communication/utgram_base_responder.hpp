#ifndef UTGRAM_BASE_RESPONDER_HPP_INCLUDE
#define UTGRAM_BASE_RESPONDER_HPP_INCLUDE

#include "../system_core/token/token.hpp"
#include "../system_core/utgram.hpp"
#include "base_responder.hpp"
#include "request.hpp"

constexpr char IDS_DELIM = ',';

class UtgramBaseResponder : public BaseResponder {
public:
    UtgramBaseResponder(Utgram* utgram) { utgram_ = utgram; };
    virtual void ok() = 0;
    virtual void empty() = 0;
    virtual void notFound() = 0;
    virtual void badRequest() = 0;
    virtual void permissionDenied() = 0;
    virtual void login(Arguments args) = 0;
    virtual void logout() = 0;
    virtual void getCourses(Arguments args) = 0;
    virtual void addPost(Arguments args) = 0;
    virtual void deletePost(Arguments args) = 0;
    virtual void getPersonalPage(Arguments args) = 0;
    virtual void getPost(Arguments args) = 0;
    virtual void connect(Arguments args) = 0;
    virtual void getNotification() = 0;
    virtual void addPresentation(Arguments args) = 0;
    virtual void addToMyCourses(Arguments args) = 0;
    virtual void deleteFromMyCourses(Arguments args) = 0;
    virtual void getMyCourses() = 0;
    virtual void sendTAForm(Arguments args) = 0;
    virtual void setProfile(Arguments args) = 0;
    virtual void sendTARequest(Arguments args) = 0;
    virtual void closeTAForm(Arguments args) = 0;
    virtual void addCoursePost(Arguments args) = 0;
    virtual void getCourseChannel(Arguments args) = 0;
    virtual void getCoursePost(Arguments args) = 0;

    // TODO find a better name for this function :)
    static bool validateArgumentExistance(Arguments args,
                                          std::vector<std::string> wanted_args) {
        for (std::string argum : wanted_args) {
            if (args.find(argum) == args.end())
                return false;
        }
        return true;
    }

protected:
    Utgram* utgram_;
    Token token_;
};

#endif // UTGRAM_BASE_RESPONDER_HPP_INCLUDE
