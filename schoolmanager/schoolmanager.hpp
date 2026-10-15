#pragma once
#include "student.hpp"
#include "teacher.hpp"
#include "subject.hpp"
#include "schoolclass.hpp"
#include "grade.hpp"
#include "teachingassignement.hpp"
#include <vector>
using namespace std;

class SchoolManager {
private:
    vector<student> students;
    vector<teacher> teachers;
    vector<subject> subjects;
    vector<schoolclass> classes;
    vector<grade> grades;
    vector<teachingassignment> assignments;
public:
    SchoolManager() = default;
    
    void addStudent(const student& s);
    void addTeacher(const teacher& t);
    void addSubject(const subject& s);
    void addClass(const schoolclass& c);
    void addGrade(const grade& g);
    void addAssignment(const teachingassignment& a);

    vector<student>& getStudents();
    vector<teacher>& getTeachers();
    vector<subject>& getSubjects();
    vector<schoolclass>& getClasses();
    vector<grade>& getGrades();
    vector<teachingassignment>& getAssignments();
};