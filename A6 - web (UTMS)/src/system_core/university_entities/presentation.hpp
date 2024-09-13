#ifndef PRESENTATION_HPP_INCLUDE
#define PRESENTATION_HPP_INCLUDE

#include <string>
#include <vector>

#include "../shared_area/social_entity_interface.hpp"

class ClassTime;
class Course;
class ExamDate;
class Major;
class Member;
class Professor;
class Student;
class SharedArea;
class Notification;

class Presentation : public ISocialEntity {
public:
    Presentation(Course* course, Professor* proffesor, int capacity,
                 ClassTime* classTime, ExamDate* examDate, int classNumber);
    virtual ~Presentation();
    std::vector<Major*> getValidMajors();
    std::string summaryStr();
    std::string detailedStr();
    std::string getCourseName();
    unsigned int getCourseId();
    bool canGetThisPresentation(Student* student);
    static Presentation*
    findById(const std::vector<Presentation*>& presentations,
             unsigned int presentationId);
    unsigned int getId();
    bool checkRequirements(Student* student);
    bool doesOverlap(ClassTime classTime, ExamDate examDate);
    bool doesOverlapClassTime(ClassTime classTime);
    virtual void addPost(std::string title, std::string message,
                         Member* publisher) override;
    virtual void addPost(std::string title, std::string message,
                         Member* publisher, std::string image) override;
    virtual void deletePost(unsigned int postId, Member* deleter) override;
    virtual std::string getPostDetail(unsigned int postId,
                                      Member* visitor) override;
    virtual std::vector<std::string> getContentSummary(Member* visitor) override;

    void addTA(Member* ta);
    void notifyMembers(Notification* notif);
    void addStudent(Student* student);

private:
    static unsigned int nextId_;
    unsigned int id_;
    Course* course_;
    Professor* professor_;
    std::vector<Member*> teacherAssistants_;
    std::vector<Student*> students_;
    int capacity_;
    ClassTime* classTime_;
    ExamDate* examDate_;
    int classNumber_;
    SharedArea* group_;

    void contentCreatorValidation(Member* publisher);
    void contentVisitorValidation(Member* visitoro);
};

#endif // PRESENTATION_HPP_INCLUDE
