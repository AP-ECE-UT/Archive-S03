#ifndef EXAM_DATE_HPP_INCLUDE
#define EXAM_DATE_HPP_INCLUDE

#include <string>

constexpr char DATE_DELIM = '/';

class ExamDate {
public:
    ExamDate(int day, int month, int year);
    ExamDate(std::string str);
    int compare(ExamDate other);
    std::string toString();

private:
    int day_;
    int month_;
    int year_;
};

#endif // EXAM_DATE_HPP_INCLUDE
