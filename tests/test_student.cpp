#include <cassert>
#include <string>

#include "../student/student.hpp"

int main() {
    schoolclass chosen_class("Mathematics", 30);
    student student_with_values(42, "Amine", &chosen_class, "secret");

    assert(student_with_values.getStudent_num() == 42);
    assert(student_with_values.getFullname() == "Amine");
    assert(student_with_values.getClass_chosen() == &chosen_class);
    assert(student_with_values.getPassword() == "secret");

    student default_student;
    assert(default_student.getStudent_num() == 0);
    assert(default_student.getFullname().empty());
    assert(default_student.getClass_chosen() == nullptr);
    assert(default_student.getPassword().empty());

    default_student.setStudent_num(7);
    default_student.setFullname("Student Test");
    default_student.setClass_chosen(&chosen_class);
    default_student.setPassword("updated-password");

    assert(default_student.getStudent_num() == 7);
    assert(default_student.getFullname() == "Student Test");
    assert(default_student.getClass_chosen() == &chosen_class);
    assert(default_student.getPassword() == "updated-password");

    return 0;
}
