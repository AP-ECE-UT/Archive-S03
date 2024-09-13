#ifndef STUDENT_HPP_INCLUDE
#define STUDENT_HPP_INCLUDE

#include <string>
#include <vector>

#include "member.hpp"

class Major;
class Presentation;

class Student : public Member {
public:
    Student(std::string id, std::string name, std::string password,
            Major* studingField, int semester);
    virtual std::string getInformationStr() override;
    void addCourse(Presentation* course);
    void removeCourse(Presentation* course);
    std::vector<Presentation*> getCourses();
    int getSemester();
    Major* getMajor();
    bool canRequestService(communication_consts::Services service) override;
    std::string getInformationForTaForm();

private:
    std::string getCoursesStr();

    int semester_;
    std::vector<Presentation*> courses_;
    Major* studingField_;
};

#endif // STUDENT_HPP_INCLUDE
