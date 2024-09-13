#include "data_loader.hpp"

#include "../general/io_utils.hpp"
#include "../system_core/member/member_consts.hpp"

using namespace std;

DataLoader::DataLoader(string majorPath, string coursePath, string studentPath,
                       string teacherPath) {
    majorPath_ = majorPath;
    coursePath_ = coursePath;
    studentPath_ = studentPath;
    teacherPath_ = teacherPath;
}

Major* DataLoader::newMajor(const vector<string>& line) {
    unsigned int mid = stoi(line[0]);
    string maj = line[1];

    return new Major(mid, maj);
}

vector<Major*> DataLoader::loadMajors() {
    auto dataTable = io_utils::readCSV(majorPath_);
    vector<Major*> res;

    for (int i = 1; i < (int)dataTable.size(); i++) {
        res.push_back(newMajor(dataTable[i]));
    }

    return res;
}

vector<Major*>
DataLoader::fetchMajorsByStringIds(const vector<Major*>& majors,
                                   const vector<string>& majorIds) {
    vector<Major*> res;
    for (auto mid : majorIds) {
        res.push_back(Major::findById(majors, (unsigned int)stoi(mid)));
    }
    return res;
}

Course* DataLoader::newCourse(const vector<Major*>& majors,
                              const vector<string>& line) {
    unsigned int cid = stoi(line[0]);
    string name = line[1];
    int credit = stoi(line[2]);
    int prerequisite = stoi(line[3]);
    auto majorIDsString = io_utils::splitString(line[4], MAJOR_IDS_DELIM);
    auto courseMajors = fetchMajorsByStringIds(majors, majorIDsString);

    return new Course(cid, name, credit, prerequisite, courseMajors);
}

vector<Course*> DataLoader::loadCourses(const vector<Major*>& majors) {
    auto dataTable = io_utils::readCSV(coursePath_);
    vector<Course*> res;

    for (int i = 1; i < (int)dataTable.size(); i++) {
        res.push_back(newCourse(majors, dataTable[i]));
    }

    return res;
}

Student* DataLoader::newStudent(const vector<Major*>& majors,
                                const vector<string>& line) {
    auto sid = line[0];
    string name = line[1];
    Major* major = Major::findById(majors, stoi(line[2]));
    int semester = stoi(line[3]);
    string password = line[4];

    return new Student(sid, name, password, major, semester);
}

vector<Student*> DataLoader::loadStudents(const vector<Major*>& majors) {
    auto dataTable = io_utils::readCSV(studentPath_);
    vector<Student*> res;

    for (int i = 1; i < (int)dataTable.size(); i++) {
        res.push_back(newStudent(majors, dataTable[i]));
    }

    return res;
}

// TODO: FIX THIS
// Professor::Position getPos(string pos) {
//     if (pos == member_consts::teacher_position_str::ASSOCIATE) return
//     Professor::Position::ASSOCIATE; if (pos ==
//     member_consts::teacher_position_str::ASSISTANT_PROFESSOR) return
//     Professor::Position::ASSISTANT_PROFESSOR; if (pos ==
//     member_consts::teacher_position_str::INSTRUCTOR_PROFESSOR) return
//     Professor::Position::INSTRUCTOR_PROFESSOR; return
//     Professor::Position::PROFESSOR;
// }

Professor::Position getPos(string pos) {
    return member_consts::teacher_position_map.find(pos).operator*().second;
    //  return member_consts::teacher_position_map[pos];  => This didn't work :(
}

Professor* DataLoader::newProfessor(const vector<Major*>& majors,
                                    const vector<string>& line) {
    auto pid = line[0];
    string name = line[1];
    Major* major = Major::findById(majors, stoi(line[2]));
    auto pos = getPos(line[3]);
    string password = line[4];

    return new Professor(pid, name, password, major, pos);
}

vector<Professor*> DataLoader::loadProfessor(const vector<Major*>& majors) {
    auto dataTable = io_utils::readCSV(teacherPath_);
    vector<Professor*> res;

    for (int i = 1; i < (int)dataTable.size(); i++) {
        res.push_back(newProfessor(majors, dataTable[i]));
    }

    return res;
}

vector<Member*> DataLoader::loadAllMembers(const vector<Major*>& majors) {
    vector<Member*> res;
    for (auto teacher : loadProfessor(majors)) {
        res.push_back(teacher);
    }
    for (auto student : loadStudents(majors)) {
        res.push_back(student);
    }
    return res;
}
