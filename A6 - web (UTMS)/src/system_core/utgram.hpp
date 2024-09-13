#ifndef UTGRAM_HPP_INCLUDE
#define UTGRAM_HPP_INCLUDE

#include <string>
#include <vector>

#include "../data_loader/data_loader.hpp"
#include "member/member.hpp"
#include "member/ut_member.hpp"
#include "notification/notification.hpp"
#include "shared_area/post.hpp"
#include "token/token.hpp"
#include "university_entities/course.hpp"
#include "university_entities/major.hpp"
#include "university_entities/presentation.hpp"

class Presentation;

class Utgram {
public:
    Utgram(DataLoader loader);
    virtual ~Utgram();

    Token login(std::string id, std::string password);
    void logout(Token& token);
    std::vector<Presentation*> getCourses(std::vector<unsigned int> courseIds);
    void addPost(Token token, std::string title, std::string messages);
    void addPost(Token token, std::string title, std::string messages,
                 std::string image);
    void deletePost(Token token, unsigned int postId);
    std::vector<std::string> getPersonalPage(std::string id);
    std::string getPost(std::string id, std::vector<unsigned int> postIds);
    void connect(Token token, std::string id);
    std::vector<Notification> getNotification(Token token);
    void addPresentation(Token token, unsigned int courseId,
                         std::string professorId, int cap, std::string time,
                         std::string examData, int classNum);
    void addToMyCourses(Token token, unsigned int courseId);
    void deleteFromMyCourses(Token token, unsigned int courseId);
    std::vector<Presentation*> getMyCourses(Token token);
    void sendTAForm(Token token, unsigned int courseId, std::string messages);
    void setProfile(Token token, std::string photoAddress);
    void sendTARequest(Token token, std::string professorId, unsigned int formId);
    Member* findMemberById(std::string id);
    void closeTAForm(Token token, unsigned int formId, std::vector<bool> results);
    std::vector<std::string> collectStudentInfoForTAForm(Token token,
                                                         unsigned int formId);
    void addCoursePost(Token token, unsigned int presentationId,
                       std::string title, std::string message);
    void addCoursePost(Token token, unsigned int presentationId,
                       std::string title, std::string message, std::string image);
    std::vector<std::string> getCourseChanel(Token token,
                                             unsigned int presentationId);
    std::vector<std::string>
    getCoursePost(Token token, unsigned int presentationId, unsigned int postId);
    Member* authentication(Token token);

private:
    UtMember* setupUtMember();

    std::vector<Member*> members_;
    std::vector<Course*> courses_;
    std::vector<Major*> majors_;
    std::vector<Presentation*> presentations_;
};

#endif // UTGRAM_HPP_INCLUDE
