#ifndef MAJOR_HPP_INCLUDE
#define MAJOR_HPP_INCLUDE

#include <string>
#include <vector>

class Major {
public:
    Major(unsigned int id, std::string name);
    std::string getName();
    unsigned int getId();
    static Major* findById(const std::vector<Major*>& majors, unsigned int id);

private:
    unsigned int id_;
    std::string name_;
};

#endif // MAJOR_HPP_INCLUDE
