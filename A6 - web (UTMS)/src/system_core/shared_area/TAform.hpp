#ifndef TAFORM_HPP_INCLUDE
#define TAFORM_HPP_INCLUDE

#include <string>
#include <vector>

#include "post.hpp"

class Presentation;
class Student;

class TAform : public Post {
public:
    enum Status { ACTIVE,
                  INACTIVE };
    TAform(unsigned int id, std::string message, Member* publisher,
           Presentation* coursePresentation);
    std::string getSummary() override;
    std::string getDetail() override;
    void addStudentToTAForm(Member* Student);
    std::vector<std::string> studentInfos();
    void sendRequestResults(std::vector<bool> resutls);
    void checkRequestedStudent(Student* student);
    std::vector<Member*> getRequestedStudents();
    Presentation* getCoursePresentation();
    virtual bool isTAform();

private:
    Status status_;
    Presentation* coursePresentation_;
    std::vector<Member*> requestedStudents_;
};
#endif