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
    int nameWidth = std::max(static_cast<int>(s.first_name.length() + s.last_name.length() + 1), 1); // +1 for space between first and last name
    
    out << "Name:   " << std::left << std::setw(nameWidth) << s.first_name + " " + s.last_name << '\n'
        << "HW Ave: " << std::left << s.hw_avg << '\n'
        << "QZ Ave: " << std::left << s.quiz_avg << '\n'
        << "Final:  " << std::left << s.final_score << '\n'
        << "Total:  " << std::left << s.course_score << '\n'
        << "Grade:  " << std::left << s.course_grade << '\n'
        << '\n'; // Maintain the two newlines for the expected blank line

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

    return in;
}


std::ostream& operator<<(std::ostream& out, const Gradebook& b) {
    for (const auto& student : b.students) {
        out << student; // Assuming Student class has an implemented operator<< to write its data
    }
    return out;
}


