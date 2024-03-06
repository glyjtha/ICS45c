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
    for (int q : quiz) {
        if (q < 0 || q > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(q));
        }
    }
    for (int h : hw) {
        if (h < 0 || h > 100) {
            throw std::domain_error("Error: invalid percentage " + std::to_string(h));
        }
    }
    if (final_score < 0 || final_score > 100) {
        throw std::domain_error("Error: invalid percentage " + std::to_string(final_score));
    }
}

void Student::compute_quiz_avg() {
    if (quiz.empty()) {
        quiz_avg = 0.0;
    } else {
        int sum = std::accumulate(quiz.begin(), quiz.end(), 0);
        int lowest = *std::min_element(quiz.begin(), quiz.end());
        quiz_avg = quiz.size() > 1 ? (sum - lowest) / static_cast<double>(quiz.size() - 1)
                                   : sum;
    }
}

void Student::compute_hw_avg() {
    hw_avg = hw.empty() ? 0.0
                        : std::accumulate(hw.begin(), hw.end(), 0.0) / hw.size();
}

void Student::compute_course_score() {
    compute_quiz_avg();
    compute_hw_avg();
    // Assuming the weights are as follows: quizzes 40%, homeworks 30%, final exam 30%
    course_score = std::round(quiz_avg * 0.4 + hw_avg * 0.3 + final_score * 0.3);
    course_grade = calculate_letter_grade(course_score);
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
            getline(iss, s.first_name);  // Assumes that the rest of the line is the name
            s.last_name = s.first_name.substr(s.first_name.rfind(' ') + 1); // Get the last name
            s.first_name.erase(s.first_name.rfind(' ')); // Remove last name from first_name
        } else if (token == "Quiz") {
            std::copy(std::istream_iterator<int>(iss),
                      std::istream_iterator<int>(),
                      std::back_inserter(s.quiz));
        } else if (token == "HW") {
            std::copy(std::istream_iterator<int>(iss),
                      std::istream_iterator<int>(),
                      std::back_inserter(s.hw));
        } else if (token == "Final") {
            iss >> s.final_score; // Assumes only one final score
        }
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Student& s) {
    out << "Name: " << std::left << std::setw(20) << s.first_name + " " + s.last_name << '\n'
        << "HW Ave: " << std::left << std::setw(8) << s.hw_avg << '\n'
        << "QZ Ave: " << std::left << std::setw(8) << s.quiz_avg << '\n'
        << "Final:  " << std::left << std::setw(8) << s.final_score << '\n'
        << "Total:  " << std::left << std::setw(8) << s.course_score << '\n'
        << "Grade:  " << std::left << std::setw(8) << s.course_grade << '\n'
        << std::endl; // Extra endl for a blank line between students
    return out;
}

// Gradebook class implementations
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
        // If the line is not empty, we continue to read this student's data
        if (!line.empty()) {
            std::istringstream iss(line);
            iss >> student;  // Assuming Student class has an implemented operator>> to read its data
        } else {
            // If we encounter an empty line, it means we finished reading one student's data
            b.students.push_back(student);
            student = Student();  // Reset the student object for the next student's data
        }
    }

    // Handle the last student record (if the file does not end with a blank line)
    if (!student.get_name().empty()) {
        b.students.push_back(student);
    }

    return in;
}


std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const auto& student : b.students) {
        out << student; // Assuming Student class has an implemented operator<< to write its data
    }
    return out;
}


// Auxiliary functions (if needed)
std::string calculate_letter_grade(int score) {
    if (score >= 97) return "A+";
    else if (score >= 93) return "A";
    else if (score >= 90) return "A-";
    else if (score >= 87) return "B+";
    else if (score >= 83) return "B";
    else if (score >= 80) return "B-";
    else if (score >= 77) return "C+";
    else if (score >= 73) return "C";
    else if (score >= 70) return "C-";
    else if (score >= 67) return "D+";
    else if (score >= 63) return "D";
    else if (score >= 60) return "D-";
    else return "F";
}
