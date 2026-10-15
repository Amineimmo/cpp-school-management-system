#include "teacher.hpp"
#include <cstdio>
#include <stdexcept>
#include <vector>

namespace {
const char* teacherFilePath = "teacher/teachers.json";

void updateTeacherRecord(int teacherNumber, const char* field, const json& value) {
    std::ifstream input(teacherFilePath);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open teacher/teachers.json for reading.");
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
            throw std::runtime_error("Invalid teacher record in teacher/teachers.json.");
        }
        records.push_back(record);
    }
    input.close();

    bool updated = false;
    for (json& record : records) {
        if (record.value("teacher_num", -1) == teacherNumber) {
            record[field] = value;
            updated = true;
            break;
        }
    }
    if (!updated) {
        throw std::runtime_error("Teacher record not found in teacher/teachers.json.");
    }

    const std::string temporaryFilePath = "teacher/teachers.json.tmp";
    std::ofstream output(temporaryFilePath, std::ios::trunc);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open temporary teacher file for writing.");
    }
    for (const json& record : records) {
        output << record.dump(4) << '\n';
    }
    output.close();
    if (!output) {
        std::remove(temporaryFilePath.c_str());
        throw std::runtime_error("Failed to write teacher/teachers.json.");
    }

    if (std::rename(temporaryFilePath.c_str(), teacherFilePath) != 0) {
        std::remove(temporaryFilePath.c_str());
        throw std::runtime_error("Failed to replace teacher/teachers.json.");
    }
}
}

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
    updateTeacherRecord(teacher_num, "teacher_num", n);
    teacher_num = n;
}

void teacher::setFullname(string fulln){
    updateTeacherRecord(teacher_num, "fullname", fulln);
    fullname = fulln;
}

void teacher::setPassword(string p){
    updateTeacherRecord(teacher_num, "password", p);
    password = p;
}