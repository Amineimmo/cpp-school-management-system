#pragma once
#include <cstring>
#include "teacher.hpp"
#include <fstream>
#include "../include/json.hpp"
using namespace std;
using json = nlohmann::json;
class subject{
    private:
    char* sub;
    teacher* t;
    public:
    subject(){
        sub = nullptr;
        t = nullptr;
        json subjectJson = {
            {"subname", sub},
            {"teacher_num", t ? t->getTeacher_num() : 0}
        };
        std::ofstream file("subject/subjects.json", ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open subject/subjects.json for writing.");
        }
        file << subjectJson.dump(4) << std::endl;
        file.close();
    }
    subject(const char* s,teacher* te) {
        sub = new char[strlen(s) + 1];
        strcpy(sub,s);
        t = te;
        json subjectJson = {
            {"subname", sub},
            {"teacher_num", t ? t->getTeacher_num() : 0}
        };
        std::ofstream file("subject/subjects.json", ios::app);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open subject/subjects.json for writing.");
        }
        file << subjectJson.dump(4) << std::endl;
        file.close();
    }
    char* getSubname();
    teacher* getTeacher();
    void setTeacher(teacher* te);
    void setSubname(const char* s);
};