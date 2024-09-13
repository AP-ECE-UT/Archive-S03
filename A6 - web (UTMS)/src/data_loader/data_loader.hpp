#ifndef DATA_LOADER_HPP_INCLUDE
#define DATA_LOADER_HPP_INCLUDE

#include <string>
#include <vector>

#include "../system_core/member/member.hpp"
#include "../system_core/member/professor.hpp"
#include "../system_core/member/student.hpp"
#include "../system_core/university_entities/course.hpp"
#include "../system_core/university_entities/major.hpp"

constexpr char MAJOR_IDS_DELIM = ';';

class DataLoader {
public:
    DataLoader(std::string majorPath, std::string coursePath,
               std::string studentPath, std::string teacherPath);
    std::vector<Major*> loadMajors();
    std::vector<Course*> loadCourses(const std::vector<Major*>& majors);
    std::vector<Member*> loadAllMembers(const std::vector<Major*>& majors);

private:
    std::vector<Student*> loadStudents(const std::vector<Major*>& majors);
    std::vector<Professor*> loadProfessor(const std::vector<Major*>& majors);

    std::vector<Major*>
    fetchMajorsByStringIds(const std::vector<Major*>& majors,
                           const std::vector<std::string>& majorIds);
    Major* newMajor(const std::vector<std::string>& line);
    Course* newCourse(const std::vector<Major*>& majors,
                      const std::vector<std::string>& line);
    Student* newStudent(const std::vector<Major*>& majors,
                        const std::vector<std::string>& line);
    Professor* newProfessor(const std::vector<Major*>& majors,
                            const std::vector<std::string>& line);
    std::string majorPath_;
    std::string coursePath_;
    std::string studentPath_;
    std::string teacherPath_;
};

#endif // DATA_LOADER_HPP_INCLUDE
