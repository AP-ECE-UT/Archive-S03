#include "presentation.hpp"

#include <string>
#include <vector>

#include "../../exceptions/exceptions.hpp"
#include "../../exceptions/not_found_exception.hpp"
#include "../../general/io_utils.hpp"
#include "../member/member.hpp"
#include "../member/professor.hpp"
#include "../member/student.hpp"
#include "../notification/notification.hpp"
#include "../shared_area/post.hpp"
#include "../shared_area/shared_area.hpp"
#include "../shared_area/social_entity_interface.hpp"
#include "../time/class_time.hpp"
#include "../time/exam_date.hpp"
#include "course.hpp"
#include "major.hpp"

Presentation::Presentation(Course* course, Professor* professor, int capacity,
                           ClassTime* classTime, ExamDate* examDate,
                           int classNumber) {
    id_ = nextId_++;
    course_ = course;
    professor_ = professor;
    capacity_ = capacity;
    classTime_ = classTime;
    examDate_ = examDate;
    classNumber_ = classNumber;
    group_ = new SharedArea();
}

Presentation::~Presentation() {
    delete group_;
    delete classTime_;
    delete examDate_;
}

unsigned int Presentation::nextId_ = 1;

std::vector<Major*> Presentation::getValidMajors() {
    return course_->getValidMajors();
}

std::string Presentation::summaryStr() {
    return std::to_string(id_) + " " + course_->getName() + " " +
           std::to_string(capacity_) + " " + professor_->getName();
}

std::string Presentation::detailedStr() {
    return summaryStr() + " " + classTime_->toString() + " " +
           examDate_->toString() + " " + std::to_string(classNumber_);
}

std::string Presentation::getCourseName() { return course_->getName(); }

unsigned int Presentation::getCourseId() { return course_->getId(); }

Presentation*
Presentation::findById(const std::vector<Presentation*>& presentations,
                       unsigned int presentationId) {
    for (auto presentation : presentations) {
        if (presentationId == presentation->getId())
            return presentation;
    }
    throw NotFoundException();
}

unsigned int Presentation::getId() { return id_; }

bool Presentation::checkRequirements(Student* student) {
    for (auto studentCourse : student->getCourses()) {
        if (studentCourse->doesOverlap(*classTime_, *examDate_)) {
            return false;
        }
    }

    return course_->canBeTakenBy(student);
}

bool Presentation::doesOverlap(ClassTime classTime, ExamDate examDate) {
    if (doesOverlapClassTime(classTime)) {
        return true;
    }

    if (examDate.compare(*examDate_) == 0) {
        return true;
    }

    return false;
}

bool Presentation::doesOverlapClassTime(ClassTime classTime) {
    return classTime.hasOverlapWith(*classTime_);
}

void Presentation::addPost(std::string title, std::string message,
                           Member* publisher) {
    contentCreatorValidation(publisher);
    group_->addPost(title, message, publisher);
}

void Presentation::addPost(std::string title, std::string message,
                           Member* publisher, std::string image) {
    contentCreatorValidation(publisher);
    group_->addPost(title, message, image, publisher);
}

void Presentation::deletePost(unsigned int postId, Member* deleter) {
    contentCreatorValidation(deleter);
    group_->deletePost(postId);
}

std::string Presentation::getPostDetail(unsigned int postId, Member* visitor) {
    contentVisitorValidation(visitor);

    Post* post = group_->getPostById(postId);
    Member* publisher = post->getPublisher();
    std::string postDetail = detailedStr() + "\n";
    postDetail += std::to_string(postId) + " " + publisher->getName() + " " +
                  post->getContent();

    return postDetail;
}

std::vector<std::string> Presentation::getContentSummary(Member* visitor) {
    contentVisitorValidation(visitor);

    std::vector<std::string> summary = group_->getSummaryWithName();
    summary.insert(summary.begin(), detailedStr());
    return summary;
}

void Presentation::contentCreatorValidation(Member* publisher) {
    if (publisher == professor_)
        return;

    for (Member* ta : teacherAssistants_) {
        if (ta == publisher)
            return;
    }

    throw PermissionDeniedException("Permission while posting in course channel");
}

void Presentation::contentVisitorValidation(Member* visitor) {
    if (visitor == professor_)
        return;

    for (Member* ta : teacherAssistants_) {
        if (ta == visitor)
            return;
    }

    for (Member* student : students_) {
        if (student == visitor)
            return;
    }

    throw PermissionDeniedException();
}

bool Presentation::canGetThisPresentation(Student* student) {
    return student->getSemester() > course_->getPrerequisite();
}

void Presentation::addTA(Member* ta) {
    Student* st = dynamic_cast<Student*>(ta);
    if (st == nullptr)
        throw PermissionDeniedException();
    this->teacherAssistants_.push_back(ta);
}

void Presentation::notifyMembers(Notification* notif) {
    for (auto student : students_) {
        notif->sent();
        student->getNotified(notif);
    }
    for (auto ta : teacherAssistants_) {
        if (ta != notif->getPublisher()) {
            notif->sent();
            ta->getNotified(notif);
        }
    }
    if (professor_ != notif->getPublisher()) {
        notif->sent();
        professor_->getNotified(notif);
    }
}

void Presentation::addStudent(Student* student) {
    if (student == nullptr)
        throw PermissionDeniedException();
    this->students_.push_back(student);
}
