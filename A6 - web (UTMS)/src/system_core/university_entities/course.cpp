#include "course.hpp"

#include <string>
#include <vector>

#include "../../exceptions/not_found_exception.hpp"
#include "../../general/io_utils.hpp"
#include "../member/student.hpp"
#include "major.hpp"

Course::Course(unsigned int id, std::string name, int credit, int prerequisite,
               std::vector<Major*> validMajors) {
    id_ = id;
    name_ = name;
    credit_ = credit;
    prerequisite_ = prerequisite;
    validMajors_ = validMajors;
}

std::string Course::getName() { return name_; }

std::vector<Major*> Course::getValidMajors() { return validMajors_; }

unsigned int Course::getId() { return id_; }

Course* Course::findById(const std::vector<Course*>& courses,
                         unsigned int courseId) {
    for (auto course : courses) {
        if (courseId == course->getId())
            return course;
    }
    throw NotFoundException();
}

bool Course::canBeTakenBy(Student* student) {
    if (student->getSemester() < prerequisite_) {
        return false;
    }

    for (auto major : validMajors_) {
        if (student->getMajor() == major) {
            return true;
        }
    }

    return false;
}

int Course::getPrerequisite() { return prerequisite_; }
