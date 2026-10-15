#pragma once
#include <string>
#include "../schoolclass/schoolclass.hpp"
#include "../include/json.hpp"
#include <fstream>
using namespace std;
using json = nlohmann::json;
class student{
    private:
    int student_num;
    string fullname;
    schoolclass* class_chosen;
    string password;
    public:
    student(int n,string fulln,schoolclass* c,string p){
        student_num = n;
        fullname = fulln;
        class_chosen = c;
        password = p;
        json studentJson = {
            {"student_num", student_num},
            {"fullname", fullname},
            {"class_chosen", class_chosen ? class_chosen->getClassname() : ""},
            {"password", password}
        };
        std::ofstream file("student/students.json", ios::app); // to save the student data in json file
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open student/students.json for writing.");
        }
        file << studentJson.dump(4) << std::endl;
        file.close();
    }
    student(){
        student_num = 0;
        fullname = "";
        class_chosen = nullptr;
        password = "";
        std::ofstream file("student/students.json", ios::app); // to save the student data in json file
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open student/students.json for writing.");
        }
        json studentJson = {
            {"student_num", student_num},
            {"fullname", fullname},
            {"class_chosen", class_chosen ? class_chosen->getClassname() : ""},
            {"password", password}
        };
        file << studentJson.dump(4) << std::endl;
        file.close();
    }
    int getStudent_num();
    string getFullname();
    schoolclass* getClass_chosen();
    string getPassword();
    void setClass_chosen(schoolclass* c);
    void setPassword(const string& p);
    void setFullname(const string& f);
    void setStudent_num(int n);
};