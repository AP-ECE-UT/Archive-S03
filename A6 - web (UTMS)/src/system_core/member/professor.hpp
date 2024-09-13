#ifndef PROFFESOR_HPP_INCLUDE
#define PROFFESOR_HPP_INCLUDE

#include <string>
#include <vector>

#include "member.hpp"

class Major;
class Presentation;
class TAform;

class Professor : public Member {
public:
    enum Position {
        ASSOCIATE,
        ASSISTANT_PROFESSOR,
        INSTRUCTOR_PROFESSOR,
        PROFESSOR
    };

    Professor(std::string id, std::string name, std::string password,
              Major* teachingField, Position position);
    ~Professor() override;
    virtual std::string getInformationStr() override;
    void addPresentation(Presentation* presentation);
    static std::string getPositionStr(Position position);
    bool canPresent(Course* course, ClassTime classTime);
    bool canRequestService(communication_consts::Services service) override;
    void sendTAForm(unsigned int courseId, std::string message);
    void addStudentToTAForm(Member* student, unsigned int formId);
    void closeTAForm(unsigned int formId, std::vector<bool> results);
    std::vector<std::string> collectStudentInfoForTAForm(unsigned int formId);
    void addAssistantsToPresentation(TAform* ta_form, std::vector<bool> results);

private:
    std::string getPresentationsStr();
    Major* teachingField_;
    Position position_;
    std::vector<Presentation*> presentations_;
};

#endif // PROFFESOR_HPP_INCLUDE
