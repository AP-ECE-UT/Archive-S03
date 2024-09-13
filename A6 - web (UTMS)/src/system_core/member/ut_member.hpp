#ifndef UT_MEMBER_HPP_INCLUDE
#define UT_MEMBER_HPP_INCLUDE

#include <string>

#include "member.hpp"

class UtMember : public Member {
public:
    UtMember();
    virtual std::string getInformationStr() override;
    Presentation* createPresentation(Course* course, Professor* professor,
                                     int cap, ClassTime* classTime,
                                     ExamDate* data, int classNum);
    bool canRequestService(communication_consts::Services service) override;
};

#endif // UT_MEMBER_HPP_INCLUDE
