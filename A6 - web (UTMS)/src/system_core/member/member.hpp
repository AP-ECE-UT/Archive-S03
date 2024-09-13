#ifndef MEMBER_HPP_INCLUDE
#define MEMBER_HPP_INCLUDE

#include <string>
#include <vector>

#include "../../communication/communication_consts.hpp"
#include "../shared_area/social_entity_interface.hpp"
#include "../time/class_time.hpp"
#include "../time/exam_date.hpp"
#include "../university_entities/course.hpp"

class Notification;
class SharedArea;
class Post;
class Professor;
class Presentation;

class Member : public ISocialEntity {
public:
    Member(std::string id, std::string name, std::string password);
    virtual ~Member();
    void setProfile(std::string photoAddress);
    void addPost(std::string title, std::string message, Member* publisher);
    void addPost(std::string title, std::string message, Member* publisher,
                 std::string image);
    void deletePost(unsigned int postId, Member* deleter);
    virtual std::string getInformationStr() = 0;
    std::vector<std::string> getContentSummary(Member* visitor);
    std::string getPostDetail(unsigned int postId, Member* visitor);
    void connectTo(Member* member);
    std::vector<Notification> getNotifications();
    void notifyYourConnections(Notification* notification);
    void getNotified(Notification* notification);
    bool isPassword(std::string password);
    std::string getId();
    std::string getName();
    static Member* findById(const std::vector<Member*>& members, std::string id);
    Post* getPostById(unsigned int postId);
    bool isAlreadyConnected(Member* member);
    virtual bool canRequestService(communication_consts::Services service) = 0;

protected:
    std::string id_;
    std::string name_;
    std::string password_;
    std::string profilePhotoAddress_;
    std::vector<Member*> connections_;
    SharedArea* personalPage_;
    std::vector<Notification*> notifications_;
};

#endif // MEMBER_HPP_INCLUDE
