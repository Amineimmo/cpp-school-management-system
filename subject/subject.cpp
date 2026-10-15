#include "subject.hpp"
#include <cstdio>
#include <stdexcept>
#include <vector>

namespace {
const char* subjectFilePath = "subject/subjects.json";

void updateSubjectRecord(const char* subjectName, const char* field, const json& value) {
    std::ifstream input(subjectFilePath);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open subject/subjects.json for reading.");
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
            throw std::runtime_error("Invalid subject record in subject/subjects.json.");
        }
        records.push_back(record);
    }
    input.close();

    bool updated = false;
    for (json& record : records) {
        const bool sameName = subjectName
            ? record.value("subname", "") == subjectName
            : record.value("subname", json()).is_null();
        if (sameName) {
            record[field] = value;
            updated = true;
            break;
        }
    }
    if (!updated) {
        throw std::runtime_error("Subject record not found in subject/subjects.json.");
    }

    const std::string temporaryFilePath = "subject/subjects.json.tmp";
    std::ofstream output(temporaryFilePath, std::ios::trunc);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to open temporary subject file for writing.");
    }
    for (const json& record : records) {
        output << record.dump(4) << '\n';
    }
    output.close();
    if (!output) {
        std::remove(temporaryFilePath.c_str());
        throw std::runtime_error("Failed to write subject/subjects.json.");
    }

    if (std::rename(temporaryFilePath.c_str(), subjectFilePath) != 0) {
        std::remove(temporaryFilePath.c_str());
        throw std::runtime_error("Failed to replace subject/subjects.json.");
    }
}
}

char* subject::getSubname(){
    return sub;
}

teacher* subject::getTeacher(){
    return t;
}

void subject::setTeacher(teacher* te){
    updateSubjectRecord(sub, "teacher_num", te ? te->getTeacher_num() : 0);
    t = te;
}

void subject::setSubname(const char* s){
    updateSubjectRecord(sub, "subname", s);
    if(sub) {
        delete[] sub;
    }
    sub = new char[strlen(s) + 1];
    strcpy(sub, s);
}