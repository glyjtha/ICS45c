#include "compute_grades.hpp"
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

// Student class implementations
void Student::validate() const {
    auto is_invalid = [](int score) { return score < 0 || score > 100; };
    
    if (any_of(quiz.begin(), quiz.end(), is_invalid)) {
        throw std::domain_error("Error: invalid quiz score found.");
    }
    if (any_of(hw.begin(), hw.end(), is_invalid)) {
        throw std::domain_error("Error: invalid homework score found.");
    }
    if (is_invalid(final_score)) {
        throw std::domain_error("Error: invalid final score " + std::to_string(final_score));
    }
}


void Student::compute_quiz_avg() {
    if (quiz.empty()) {
        quiz_avg = 0.0;
    } else {
        int sum = accumulate(quiz.begin(), quiz.end(), 0);
        int lowest = *min_element(quiz.begin(), quiz.end());
        quiz_avg = quiz.size() > 1 ? static_cast<double>(sum - lowest) / (quiz.size() - 1) : sum;
    }
}


void Student::compute_hw_avg() {
    hw_avg = hw.empty() ? 0.0
                        : std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
}

void Student::compute_course_score() {
    compute_quiz_avg();
    compute_hw_avg();
    course_score = std::round(quiz_avg * 0.4 + hw_avg * 0.3 + final_score * 0.3);
    if (course_score >= 97) {
        course_grade = "A+";
    } else if (course_score >= 93) {
        course_grade = "A";
    } else if (course_score >= 90) {
        course_grade = "A-";
    } else if (course_score >= 87) {
        course_grade = "B+";
    } else if (course_score >= 83) {
        course_grade = "B";
    } else if (course_score >= 80) {
        course_grade = "B-";
    } else if (course_score >= 77) {
        course_grade = "C+";
    } else if (course_score >= 73) {
        course_grade = "C";
    } else if (course_score >= 70) {
        course_grade = "C-";
    } else if (course_score >= 67) {
        course_grade = "D+";
    } else if (course_score >= 63) {
        course_grade = "D";
    } else if (course_score >= 60) {
        course_grade = "D-";
    } else {
        course_grade = "F";
    }
}
void Student::compute_grade() {
    compute_course_score();
}

std::strong_ordering Student::operator<=>(const Student& other) const {
    if (auto cmp = last_name <=> other.last_name; cmp != 0) return cmp;
    return first_name <=> other.first_name;
}

bool Student::operator==(const Student& other) const {
    return last_name == other.last_name && first_name == other.first_name;
}

std::istream& operator>>(std::istream& in, Student& s) {
    std::string line, token;
    while (getline(in, line) && !line.empty()) {
        std::istringstream iss(line);
        iss >> token;
        if (token == "Name") {
            getline(iss, s.first_name);  
            s.last_name = s.first_name.substr(s.first_name.rfind(' ') + 1);
            s.first_name.erase(s.first_name.rfind(' '));
        } else if (token == "Quiz") {
            std::copy(std::istream_iterator<int>(iss),
                      std::istream_iterator<int>(),
                      std::back_inserter(s.quiz));
        } else if (token == "HW") {
            std::copy(std::istream_iterator<int>(iss),
                      std::istream_iterator<int>(),
                      std::back_inserter(s.hw));
        } else if (token == "Final") {
            iss >> s.final_score; 
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << std::left << std::setw(8) << "Name:" << s.first_name << " " << s.last_name << '\n'
        << std::left << std::setw(8) << "HW Ave:" << s.hw_avg << '\n'
        << std::left << std::setw(8) << "QZ Ave:" << s.quiz_avg << '\n'
        << std::left << std::setw(8) << "Final:" << s.final_score << '\n'
        << std::left << std::setw(8) << "Total:" << s.course_score << '\n'
        << std::left << std::setw(8) << "Grade:" << s.course_grade << "\n";
    return out;
}




void Gradebook::compute_grades() {
    for (Student& student : students) {
        student.compute_grade();
    }
}

void Gradebook::sort() {
    std::sort(students.begin(), students.end());
}

void Gradebook::validate() const {
    for (const Student& student : students) {
        student.validate();
    }
}

std::istream& operator>>(std::istream& in, Gradebook& b) {
    Student student;
    std::string line;

    while (getline(in, line)) {
        if (!line.empty()) {
            std::istringstream iss(line);
            iss >> student; 
        } else {
            b.students.push_back(student);
            student = Student(); 
        }
    }

    return in;
}


std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const Student& student : b.students) {
        out << student;
        out << "\n";

    }
    return out;
}



