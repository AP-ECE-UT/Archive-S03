#include "exam_date.hpp"

#include <string>

#include "../../general/io_utils.hpp"

ExamDate::ExamDate(int day, int month, int year) {
    day_ = day;
    month_ = month;
    year_ = year;
}

ExamDate::ExamDate(std::string str) {
    auto splitedString = io_utils::splitString(str, DATE_DELIM);

    year_ = stoi(splitedString[0]);
    month_ = stoi(splitedString[1]);
    day_ = stoi(splitedString[2]);
}

int ExamDate::compare(ExamDate other) {
    if (year_ != other.year_) {
        return (year_ > other.year_) ? 1 : -1;
    }
    else if (month_ != other.month_) {
        return (month_ > other.month_) ? 1 : -1;
    }
    else if (day_ != other.day_) {
        return (day_ > other.day_) ? 1 : -1;
    }
    else {
        return 0;
    }
}

std::string ExamDate::toString() {
    return std::to_string(year_) + "/" + std::to_string(month_) + "/" +
           std::to_string(day_);
}
