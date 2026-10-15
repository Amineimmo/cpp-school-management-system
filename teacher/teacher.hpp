#pragma once
#include <string>
#include <fstream>
#include "../include/json.hpp"
using namespace std;
using json = nlohmann::json;
class teacher{
    private:
    int teacher_num;
    string fullname;
    string password;
    public:
    teacher(int n,string fulln,string p){
        teacher_num = n;
        fullname = fulln;
        password = p;
        ofstream file("teacher/teachers.json", ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open teacher/teachers.json for writing.");
        }
        json teacherJson = {
            {"teacher_num", teacher_num},
            {"fullname", fullname},
            {"password", password}
        };
        file << teacherJson.dump(4) << std::endl;
        file.close();
    }
    teacher(){
        teacher_num = 0;
        fullname = "";
        password = "";
        ofstream file("teacher/teachers.json", ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open teacher/teachers.json for writing.");
        }
        json teacherJson = {
            {"teacher_num", teacher_num},
            {"fullname", fullname},
            {"password", password}
        };
        file << teacherJson.dump(4) << std::endl;
        file.close();
    }
    int getTeacher_num();
    string getFullname();
    string getPassword();
    void setTeacher_num(int n);
    void setFullname(string fulln);
    void setPassword(string p);
};