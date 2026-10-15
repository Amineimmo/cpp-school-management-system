#include "teachingassignement.hpp"

teacher* teachingassignment::getTeacherPtr() const {
    return teacher_ptr;
}

subject* teachingassignment::getSubjectPtr() const {
    return subject_ptr;
}

void teachingassignment::setTeacherPtr(teacher* t) {
    teacher_ptr = t;
}

void teachingassignment::setSubjectPtr(subject* s) {
    subject_ptr = s;
}