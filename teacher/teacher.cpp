#include "teacher.hpp"

    int teacher::getTeacher_num(){
        return teacher_num;
    }
    string teacher::getFullname(){
        return fullname;
    }
    string teacher::getPassword(){
        return password;
    }
    void teacher::setTeacher_num(int n){
        teacher_num = n;
    }
    void teacher::setFullname(string fulln){
        fullname = fulln;
    }
    void teacher::setPassword(string p){
        password = p;
    }