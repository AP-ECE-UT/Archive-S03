#include "class_time.hpp"

#include <string>

#include "../../exceptions/bad_request_exception.hpp"
#include "../../general/io_utils.hpp"
#include "time_consts.hpp"

using namespace time_cosnts;

ClassTime::ClassTime(Day day, int startTime, int endTime) {
    day_ = day;
    startTime_ = startTime;
    endTime_ = endTime;
}

ClassTime::ClassTime(std::string str) {
    auto splitedString = io_utils::splitString(str, CLASSTIME_DELIM);

    day_ = getWeekdayFromString(splitedString[0]);

    auto hoursSplited = io_utils::splitString(splitedString[1], HOURS_DELIM);
    startTime_ = stoi(hoursSplited[0]);
    endTime_ = stoi(hoursSplited[1]);
}

ClassTime::Day ClassTime::getWeekdayFromString(std::string str) {
    if (str == week_day_str::SATURDAY)
        return ClassTime::Day::SAT;
    if (str == week_day_str::SUNDAY)
        return ClassTime::Day::SUN;
    if (str == week_day_str::MONDAY)
        return ClassTime::Day::MON;
    if (str == week_day_str::TUESDAY)
        return ClassTime::Day::TUE;
    if (str == week_day_str::WEDNESDAY)
        return ClassTime::Day::WED;
    throw BadRequestException();
}

bool ClassTime::hasOverlapWith(ClassTime other) {
    if (day_ != other.day_) {
        return false;
    }

    return ((startTime_ >= other.startTime_ && startTime_ < other.endTime_) ||
            (other.startTime_ >= startTime_ && other.startTime_ < endTime_));
}

std::string ClassTime::toString() {
    return dayToStr(day_) + ":" + std::to_string(startTime_) + "-" +
           std::to_string(endTime_);
}

std::string ClassTime::dayToStr(Day day) {
    switch (day) {
    case SAT:
        return week_day_str::SATURDAY;
    case SUN:
        return week_day_str::SUNDAY;
    case MON:
        return week_day_str::MONDAY;
    case TUE:
        return week_day_str::TUESDAY;
    case WED:
        return week_day_str::WEDNESDAY;
    default:
        return week_day_str::UNKNOWN_DAY;
    }
}
