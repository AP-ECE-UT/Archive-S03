#ifndef STR_UTILS_HPP_INCLUDE
#define STR_UTILS_HPP_INCLUDE

#include <string>
#include <vector>

constexpr char CSV_DELIM = ',';
const int VALID_NUM_DOUBLE_QUOTATION = 4;
const int FULL_DOUBLE_QUOTATION = 2;
const int HALF_DOUBLE_QUOTATION = 1;

namespace io_utils {

std::string trimBoth(std::string str);
std::vector<std::string> splitString(std::string str, char delim);
std::vector<std::vector<std::string>> readCSV(std::string fileName);
std::vector<unsigned int> convertToUnsigned(std::vector<std::string> stringIds);
std::vector<std::string> mergeInside(std::vector<std::string> vec, char delim);
bool isNumber(std::string s);

} // namespace io_utils

#endif // STR_UTILS_HPP_INCLUDE
