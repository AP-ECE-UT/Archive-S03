#ifndef SOCIAL_ENTITY_INTERFACE_HPP_INCLUDE
#define SOCIAL_ENTITY_INTERFACE_HPP_INCLUDE

#include <string>
#include <vector>

class Member;

class ISocialEntity {
public:
    virtual void addPost(std::string title, std::string message,
                         Member* publisher) = 0;
    virtual void addPost(std::string title, std::string message,
                         Member* publisher, std::string image) = 0;
    virtual void deletePost(unsigned int postId, Member* deleter) = 0;
    virtual std::string getPostDetail(unsigned int postId, Member* visitor) = 0;
    virtual std::vector<std::string> getContentSummary(Member* visitor) = 0;
};

#endif // SOCIAL_ENTITY_INTERFACE_HPP_INCLUDE
