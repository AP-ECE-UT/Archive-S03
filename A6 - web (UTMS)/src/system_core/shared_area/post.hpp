#ifndef POST_HPP_INCLUDE
#define POST_HPP_INCLUDE

#include <string>
#include <vector>

class Member;

class Post {
public:
    Post(unsigned int id, std::string title, std::string message,
         std::string image, Member* publisher);
    Post(unsigned int id, std::string title, std::string message,
         Member* publisher);
    Post(unsigned int id, std::string message, Member* publisher);
    virtual ~Post();
    virtual std::string getSummary();
    virtual std::string getSummaryWithName();
    virtual std::string getDetail();
    virtual std::string getContent();
    Member* getPublisher();
    virtual bool isTAform();
    static Post* findById(const std::vector<Post*>& posts, unsigned int id);
    static unsigned int getIndexById(const std::vector<Post*>& posts,
                                     unsigned int id);

protected:
    unsigned int id_;
    std::string title_;
    std::string message_;
    std::string image_;
    Member* publisher_;
};

#endif // POST_HPP_INCLUDE
