#include "grades/grade.hpp"
#include "schoolclass/schoolclass.hpp"
#include "student/student.hpp"
#include "subject/subject.hpp"
#include "teacher/teacher.hpp"
#include "teachingassignement/teachingassignement.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <vector>

namespace {

struct StudentAccount {
    std::unique_ptr<student> account;
    std::vector<subject*> subjects;
};

struct TeacherAccount {
    std::unique_ptr<teacher> account;
    std::vector<subject*> subjects;
};

int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cout << "Please enter a valid number.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string readText(const std::string& prompt) {
    std::string value;
    do {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (value.empty()) {
            std::cout << "This value cannot be empty.\n";
        }
    } while (value.empty());
    return value;
}

bool containsSubject(const std::vector<subject*>& subjects, const subject* wanted) {
    return std::find(subjects.begin(), subjects.end(), wanted) != subjects.end();
}

subject* chooseSubject(const std::vector<std::unique_ptr<subject>>& subjects) {
    if (subjects.empty()) {
        std::cout << "No subjects are available yet.\n";
        return nullptr;
    }

    std::cout << "\nAvailable subjects:\n";
    for (std::size_t i = 0; i < subjects.size(); ++i) {
        std::cout << i + 1 << ". " << subjects[i]->getSubname() << '\n';
    }

    const int choice = readInt("Choose a subject (0 to cancel): ");
    if (choice == 0) {
        return nullptr;
    }
    if (choice < 1 || static_cast<std::size_t>(choice) > subjects.size()) {
        std::cout << "Invalid subject choice.\n";
        return nullptr;
    }
    return subjects[choice - 1].get();
}

StudentAccount* findStudent(
    std::vector<StudentAccount>& students,
    int studentNumber
) {
    for (StudentAccount& current : students) {
        if (current.account->getStudent_num() == studentNumber) {
            return &current;
        }
    }
    return nullptr;
}

TeacherAccount* findTeacher(
    std::vector<TeacherAccount>& teachers,
    int teacherNumber
) {
    for (TeacherAccount& current : teachers) {
        if (current.account->getTeacher_num() == teacherNumber) {
            return &current;
        }
    }
    return nullptr;
}

void showStudentMarks(
    const StudentAccount& current,
    const std::vector<grade>& grades
) {
    std::cout << "\nYour marks:\n";
    if (current.subjects.empty()) {
        std::cout << "You are not enrolled in any subject.\n";
        return;
    }

    for (subject* currentSubject : current.subjects) {
        std::cout << "- " << currentSubject->getSubname() << ": ";
        bool found = false;
        for (const grade& currentGrade : grades) {
            if (currentGrade.getStudentPtr() == current.account.get()
                && currentGrade.getSubjectPtr() == currentSubject) {
                std::cout << currentGrade.getGradeValue();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "not graded";
        }
        std::cout << '\n';
    }
}

void studentMenu(
    StudentAccount& current,
    const std::vector<std::unique_ptr<subject>>& subjects,
    std::vector<grade>& grades
) {
    while (true) {
        std::cout << "\nStudent menu\n"
                  << "1. View my marks\n"
                  << "2. Enroll in a subject\n"
                  << "3. Change my password\n"
                  << "0. Sign out\n";
        const int choice = readInt("Choose an option: ");

        if (choice == 0) {
            return;
        }
        if (choice == 1) {
            showStudentMarks(current, grades);
        } else if (choice == 2) {
            subject* selected = chooseSubject(subjects);
            if (selected != nullptr && !containsSubject(current.subjects, selected)) {
                current.subjects.push_back(selected);
                std::cout << "Enrollment completed.\n";
            } else if (selected != nullptr) {
                std::cout << "You are already enrolled in this subject.\n";
            }
        } else if (choice == 3) {
            const std::string password = readText("New password: ");
            current.account->setPassword(password);
            std::cout << "Password updated.\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

void createSubject(
    TeacherAccount& current,
    std::vector<std::unique_ptr<subject>>& subjects,
    std::vector<teachingassignment>& assignments
) {
    const std::string name = readText("Subject name: ");
    for (const std::unique_ptr<subject>& existing : subjects) {
        if (name == existing->getSubname()) {
            std::cout << "That subject already exists.\n";
            return;
        }
    }

    subjects.push_back(std::make_unique<subject>(name.c_str(), current.account.get()));
    subject* created = subjects.back().get();
    current.subjects.push_back(created);
    assignments.emplace_back(current.account.get(), created);
    std::cout << "Subject created and assigned to you.\n";
}

void showTeacherStudents(
    const TeacherAccount& current,
    const std::vector<StudentAccount>& students
) {
    std::cout << "\nYour students:\n";
    bool found = false;
    for (const StudentAccount& studentAccount : students) {
        const bool enrolledInOwnSubject = std::any_of(
            current.subjects.begin(),
            current.subjects.end(),
            [&studentAccount](subject* currentSubject) {
                return containsSubject(studentAccount.subjects, currentSubject);
            }
        );
        if (enrolledInOwnSubject) {
            std::cout << "- " << studentAccount.account->getStudent_num()
                      << ": " << studentAccount.account->getFullname() << '\n';
            found = true;
        }
    }
    if (!found) {
        std::cout << "No students are enrolled in your subjects.\n";
    }
}

void assignGrade(
    TeacherAccount& current,
    std::vector<StudentAccount>& students,
    std::vector<grade>& grades
) {
    if (current.subjects.empty()) {
        std::cout << "You do not teach any subjects yet.\n";
        return;
    }

    std::cout << "\nYour subjects:\n";
    for (std::size_t i = 0; i < current.subjects.size(); ++i) {
        std::cout << i + 1 << ". " << current.subjects[i]->getSubname() << '\n';
    }
    const int subjectChoice = readInt("Choose a subject (0 to cancel): ");
    if (subjectChoice == 0
        || subjectChoice < 1
        || static_cast<std::size_t>(subjectChoice) > current.subjects.size()) {
        std::cout << "Invalid subject choice.\n";
        return;
    }
    subject* selectedSubject = current.subjects[subjectChoice - 1];

    std::vector<StudentAccount*> eligibleStudents;
    for (StudentAccount& studentAccount : students) {
        if (containsSubject(studentAccount.subjects, selectedSubject)) {
            eligibleStudents.push_back(&studentAccount);
        }
    }
    if (eligibleStudents.empty()) {
        std::cout << "No students are enrolled in this subject.\n";
        return;
    }

    std::cout << "\nStudents in " << selectedSubject->getSubname() << ":\n";
    for (std::size_t i = 0; i < eligibleStudents.size(); ++i) {
        std::cout << i + 1 << ". "
                  << eligibleStudents[i]->account->getFullname()
                  << " (" << eligibleStudents[i]->account->getStudent_num()
                  << ")\n";
    }
    const int studentChoice = readInt("Choose a student (0 to cancel): ");
    if (studentChoice == 0
        || studentChoice < 1
        || static_cast<std::size_t>(studentChoice) > eligibleStudents.size()) {
        std::cout << "Invalid student choice.\n";
        return;
    }

    StudentAccount* selectedStudent = eligibleStudents[studentChoice - 1];
    const int mark = readInt("Enter the mark (0-100): ");
    if (mark < 0 || mark > 100) {
        std::cout << "A mark must be between 0 and 100.\n";
        return;
    }

    for (grade& currentGrade : grades) {
        if (currentGrade.getStudentPtr() == selectedStudent->account.get()
            && currentGrade.getSubjectPtr() == selectedSubject) {
            currentGrade.setGradeValue(mark);
            std::cout << "Mark updated.\n";
            return;
        }
    }

    grades.emplace_back(selectedStudent->account.get(), mark, selectedSubject);
    std::cout << "Mark assigned.\n";
}

void teacherMenu(
    TeacherAccount& current,
    std::vector<StudentAccount>& students,
    std::vector<std::unique_ptr<subject>>& subjects,
    std::vector<teachingassignment>& assignments,
    std::vector<grade>& grades
) {
    while (true) {
        std::cout << "\nTeacher menu\n"
                  << "1. Create a subject\n"
                  << "2. View my students\n"
                  << "3. Assign or update a mark\n"
                  << "4. Change my password\n"
                  << "0. Sign out\n";
        const int choice = readInt("Choose an option: ");

        if (choice == 0) {
            return;
        }
        if (choice == 1) {
            createSubject(current, subjects, assignments);
        } else if (choice == 2) {
            showTeacherStudents(current, students);
        } else if (choice == 3) {
            assignGrade(current, students, grades);
        } else if (choice == 4) {
            const std::string password = readText("New password: ");
            current.account->setPassword(password);
            std::cout << "Password updated.\n";
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

void signUpStudent(
    std::vector<StudentAccount>& students,
    const std::vector<std::unique_ptr<schoolclass>>& classes,
    const std::vector<std::unique_ptr<subject>>& subjects
) {
    const int number = readInt("Student number: ");
    if (findStudent(students, number) != nullptr) {
        std::cout << "That student number is already registered.\n";
        return;
    }

    const std::string name = readText("Full name: ");
    const std::string password = readText("Password: ");
    std::unique_ptr<student> account = std::make_unique<student>(
        number,
        name,
        nullptr,
        password
    );
    StudentAccount newAccount{std::move(account), {}};

    if (!classes.empty()) {
        std::cout << "\nAvailable classes:\n";
        for (std::size_t i = 0; i < classes.size(); ++i) {
            std::cout << i + 1 << ". " << classes[i]->getClassname() << '\n';
        }
        const int classChoice = readInt("Choose a class (0 for none): ");
        if (classChoice > 0
            && static_cast<std::size_t>(classChoice) <= classes.size()) {
            newAccount.account->setClass_chosen(classes[classChoice - 1].get());
        }
    }

    while (!subjects.empty()) {
        subject* selected = chooseSubject(subjects);
        if (selected == nullptr) {
            break;
        }
        if (!containsSubject(newAccount.subjects, selected)) {
            newAccount.subjects.push_back(selected);
        }
        const std::string answer = readText("Enroll in another subject? (y/n): ");
        if (answer != "y" && answer != "Y") {
            break;
        }
    }

    students.push_back(std::move(newAccount));
    std::cout << "Student account created.\n";
}

void signUpTeacher(std::vector<TeacherAccount>& teachers) {
    const int number = readInt("Teacher number: ");
    if (findTeacher(teachers, number) != nullptr) {
        std::cout << "That teacher number is already registered.\n";
        return;
    }

    const std::string name = readText("Full name: ");
    const std::string password = readText("Password: ");
    teachers.push_back({
        std::make_unique<teacher>(number, name, password),
        {}
    });
    std::cout << "Teacher account created.\n";
}

void studentSignIn(
    std::vector<StudentAccount>& students,
    const std::vector<std::unique_ptr<subject>>& subjects,
    std::vector<grade>& grades
) {
    const int number = readInt("Student number: ");
    StudentAccount* current = findStudent(students, number);
    if (current == nullptr
        || current->account->getPassword() != readText("Password: ")) {
        std::cout << "Invalid student credentials.\n";
        return;
    }
    studentMenu(*current, subjects, grades);
}

void teacherSignIn(
    std::vector<TeacherAccount>& teachers,
    std::vector<StudentAccount>& students,
    std::vector<std::unique_ptr<subject>>& subjects,
    std::vector<teachingassignment>& assignments,
    std::vector<grade>& grades
) {
    const int number = readInt("Teacher number: ");
    TeacherAccount* current = findTeacher(teachers, number);
    if (current == nullptr
        || current->account->getPassword() != readText("Password: ")) {
        std::cout << "Invalid teacher credentials.\n";
        return;
    }
    teacherMenu(*current, students, subjects, assignments, grades);
}

} // namespace

int main() {
    std::vector<StudentAccount> students;
    std::vector<TeacherAccount> teachers;
    std::vector<std::unique_ptr<subject>> subjects;
    std::vector<std::unique_ptr<schoolclass>> classes;
    std::vector<grade> grades;
    std::vector<teachingassignment> assignments;

    classes.push_back(std::make_unique<schoolclass>("Class A", 30));
    classes.push_back(std::make_unique<schoolclass>("Class B", 30));

    while (true) {
        std::cout << "\nSchool management system\n"
                  << "1. Sign up as student\n"
                  << "2. Sign in as student\n"
                  << "3. Sign up as teacher\n"
                  << "4. Sign in as teacher\n"
                  << "0. Exit\n";
        const int choice = readInt("Choose an option: ");

        if (choice == 0) {
            std::cout << "Goodbye.\n";
            return 0;
        }
        if (choice == 1) {
            signUpStudent(students, classes, subjects);
        } else if (choice == 2) {
            studentSignIn(students, subjects, grades);
        } else if (choice == 3) {
            signUpTeacher(teachers);
        } else if (choice == 4) {
            teacherSignIn(teachers, students, subjects, assignments, grades);
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}
