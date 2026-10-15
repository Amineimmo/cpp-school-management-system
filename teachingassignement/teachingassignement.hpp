#pragma once
#include "teacher.hpp"
#include "subject.hpp"
class teachingassignment {
    private:
        teacher* teacher_ptr;
        subject* subject_ptr;
    public:
        teachingassignment(teacher* t, subject* s) : teacher_ptr(t), subject_ptr(s) {}
        teachingassignment() : teacher_ptr(nullptr), subject_ptr(nullptr) {}
        teacher* getTeacherPtr() const;
        subject* getSubjectPtr() const;
        void setTeacherPtr(teacher* t);
        void setSubjectPtr(subject* s);
};