#include "subject.hpp"

char* subject::getSubname(){
    return sub;
}

teacher* subject::getTeacher(){
    return t;
}

void subject::setTeacher(teacher* te){
    t = te;
    ifstream file("subject/subjects.json", ios::app);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open subject/subjects.json for writing.");
    }
    for(json subjectJson; file >> subjectJson;){
        if(subjectJson["subname"] == sub){
            subjectJson["teacher_num"] = t ? t->getTeacher_num() : 0;
            break;
        }
    }
    file.close();
}

void subject::setSubname(const char* s){
    if(sub) {
        delete[] sub;
    }
    sub = new char[strlen(s) + 1];
    strcpy(sub, s);
}