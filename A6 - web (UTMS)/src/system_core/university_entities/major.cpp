#include "major.hpp"

#include <string>
#include <vector>

#include "../../exceptions/exceptions.hpp"
#include "university_consts.hpp"

using namespace university_cosnts;

Major::Major(unsigned int id, std::string name) {
    id_ = id;
    name_ = name;
}

std::string Major::getName() { return name_; }

unsigned int Major::getId() { return id_; }

Major* Major::findById(const std::vector<Major*>& majors, unsigned int id) {
    for (Major* major : majors) {
        if (major->id_ == id)
            return major;
    }
    throw NotFoundException(messages::CAN_NOT_FIND_MAJOR);
}
