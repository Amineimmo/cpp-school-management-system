#include "student.hpp"
#include <fstream>
#include <cstdio>
#include <stdexcept>
#include <vector>
#include "../include/json.hpp"
using json = nlohmann::json;

namespace {
const char* studentFilePath = "student/students.json";

void updateStudentRecord(int studentNumber, const char* field, const json& value) {
    std::ifstream input(studentFilePath);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open student/students.json for reading.");
    }

    std::vector<json> records;
    while (true) {
        input >> std::ws;
        if (input.peek() == std::char_traits<char>::eof()) {
            break;
        }
        json record;
        input >> record;
        if (!record.is_object()) {
            throw std::runtime_error("Invalid student record in student/students.json.");
        }
        records.push_back(record);
    }
    input.close();

    bool updated = false;
    for (json& currentRecord : records) {
        if (currentRecord.value("student_num", -1) == studentNumber) {
            currentRecord[field] = value;
            updated = true;
            break;
        }
    }
    if (!updated) {
        throw std::runtime_error("Student record not found in student/students.json.");
    }

    const std::string temporaryFilePath = "student/students.json.tmp";
    std::ofstream output(temporaryFilePath, std::ios::trunc);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open temporary student file for writing.");
    }
    for (const json& currentRecord : records) {
        output << currentRecord.dump(4) << '\n';
    }
    output.close();
    if (!output) {
        std::remove(temporaryFilePath.c_str());
        throw std::runtime_error("Failed to write student/students.json.");
    }

    if (std::rename(temporaryFilePath.c_str(), studentFilePath) != 0) {
        std::remove(temporaryFilePath.c_str());
        throw std::runtime_error("Failed to replace student/students.json.");
    }
}
}

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
    updateStudentRecord(
        student_num,
        "class_chosen",
        c ? c->getClassname() : ""
    );
    class_chosen = c;
}

void student::setPassword(const string& p){
    updateStudentRecord(student_num, "password", p);
    password = p;
}

void student::setFullname(const string& f){
    updateStudentRecord(student_num, "fullname", f);
    fullname = f;
}

void student::setStudent_num(int n){
    updateStudentRecord(student_num, "student_num", n);
    student_num = n;
}