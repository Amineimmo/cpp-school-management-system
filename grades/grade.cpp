#include "grade.hpp"

int grade::getGradeValue() const {
    return grade_value;
}

student* grade::getStudentPtr() const {
    return student_ptr;
}

void grade::setGradeValue(int g) {
    grade_value = g;
}
subject* grade::getSubjectPtr() const {
    return subject_ptr;
}
void grade::setSubjectPtr(subject* sub) {
    subject_ptr = sub;
}

void grade::setStudentPtr(student* s) {
    student_ptr = s;
}