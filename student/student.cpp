#include "student.hpp"

int student::getStudent_num(){
    return student_num;
}

string student::getFullname(){
    return fullname;
}

schoolclass* student::getClass_chosen(){
    return class_chosen;
}

string student::getPassword(){
    return password;
}

void student::setClass_chosen(schoolclass* c){
    class_chosen = c;
}

void student::setPassword(const string& p){
    password = p;
}

void student::setFullname(const string& f){
    fullname = f;
}

void student::setStudent_num(int n){
    student_num = n;
}