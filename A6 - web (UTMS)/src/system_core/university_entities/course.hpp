#ifndef COURSE_HPP_INCLUDE
#define COURSE_HPP_INCLUDE

#include <string>
#include <vector>

class Major;
class Student;

class Course {
public:
    Course(unsigned int id, std::string name, int credit, int prerequisite,
           std::vector<Major*> validMajors);
    std::string getName();
    std::vector<Major*> getValidMajors();
    unsigned int getId();
    static Course* findById(const std::vector<Course*>& courses,
                            unsigned int courseId);
    bool canBeTakenBy(Student* student);
    int getPrerequisite();

private:
    unsigned int id_;
    std::string name_;
    int credit_;
    int prerequisite_;
    std::vector<Major*> validMajors_;
};

#endif // COURSE_HPP_INCLUDE
