#ifndef CLASS_TIME_HPP_INCLUDE
#define CLASS_TIME_HPP_INCLUDE

#include <string>

constexpr char CLASSTIME_DELIM = ':';
constexpr char HOURS_DELIM = '-';

class ClassTime {
public:
    enum Day { SAT,
               SUN,
               MON,
               TUE,
               WED };

    ClassTime(Day day, int startTime, int endTime);
    ClassTime(std::string str);
    bool hasOverlapWith(ClassTime other);
    std::string toString();
    static std::string dayToStr(Day day);
    static ClassTime::Day getWeekdayFromString(std::string str);

private:
    Day day_;
    int startTime_;
    int endTime_;
};

#endif // CLASS_TIME_HPP_INCLUDE
