#ifndef SHARED_AREA_HPP_INCLUDE
#define SHARED_AREA_HPP_INCLUDE

#include <string>
#include <vector>

class Member;
class Post;
class Presentation;

class SharedArea {
public:
    SharedArea();
    ~SharedArea();
    void addPost(std::string title, std::string message, Member* publisher);
    void addPost(std::string title, std::string message, std::string image,
                 Member* publisher);
    void addTAForm(Presentation* coursePresentation, std::string message,
                   Member* publisher);
    void deletePost(unsigned int id);
    std::vector<std::string> getSummary();
    std::vector<std::string> getSummaryWithName();
    Post* getPostById(unsigned int id);
    std::string getPostDetail(unsigned int postId);
    void addStudentToTAForm(Member* student, unsigned int formId);
    void closeTAForm(unsigned int formId, std::vector<bool> results);
    std::vector<std::string> collectStudentInfoForTAForm(unsigned int formId);

private:
    unsigned int nextPostId_;
    std::vector<Post*> posts_;
};

#endif // SHARED_AREA_HPP_INCLUDE
