#include "schoolmanager.hpp"

void SchoolManager::addStudent(const student& s) {
    students.push_back(s);
}

void SchoolManager::addTeacher(const teacher& t) {
    teachers.push_back(t);
}

void SchoolManager::addSubject(const subject& s) {
    subjects.push_back(s);
}

void SchoolManager::addClass(const schoolclass& c) {
    classes.push_back(c);
}

void SchoolManager::addGrade(const grade& g) {
    grades.push_back(g);
}

void SchoolManager::addAssignment(const teachingassignment& a) {
    assignments.push_back(a);
}

vector<student>& SchoolManager::getStudents() {
    return students;
}

vector<teacher>& SchoolManager::getTeachers() {
    return teachers;
}

vector<subject>& SchoolManager::getSubjects() {
    return subjects;
}

vector<schoolclass>& SchoolManager::getClasses() {
    return classes;
}

vector<grade>& SchoolManager::getGrades() {
    return grades;
}

vector<teachingassignment>& SchoolManager::getAssignments() {
    return assignments;
}