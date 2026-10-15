#pragma once
#include "student.hpp"
#include "subject.hpp"
class grade {
    private:
        student* student_ptr;
        subject* subject_ptr;
        int grade_value;
    public:
        grade(student* s, int g, subject* sub) : student_ptr(s), grade_value(g), subject_ptr(sub) {}
        grade() : student_ptr(nullptr), grade_value(0) {}
        int getGradeValue() const;
        student* getStudentPtr() const;
        subject* getSubjectPtr() const;
        void setGradeValue(int g);
        void setStudentPtr(student* s);
        void setSubjectPtr(subject* sub);
};