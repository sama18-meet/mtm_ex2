#include <iostream>
#include <string>
#include "examDetails.h"
#include <cmath>
#define DAYS_IN_MONTH 30
#define DOUBLE_ACCURACY 0.000001

using std::endl;
using std::string;
using namespace mtm;

ExamDetails::ExamDetails(int course_id, int month, int day, double start_time, int total_time, const string zoom_link) :
    course_id(course_id), month(month), day(day), start_time(start_time), total_time(total_time), zoom_link(zoom_link) {
        if (course_id < 0) {
            throw InvalidArgsException();
        }
        if (month<1 || month>12 || day<1 || day>30) {
            throw InvalidDateException();
        }
        if (((int)(start_time*2))%2 != 0) {
            throw InvalidTimeException();
        }
        if (total_time < 0) {
            throw InvalidArgsException();
        }
}

string ExamDetails::getLink() const {
    return this->zoom_link;
}

void ExamDetails::setLink(string new_link) {
    this->zoom_link = new_link;
}

int ExamDetails::operator-(const ExamDetails& exam_details) const {
    return dateDifference(this->month, this->day, exam_details.month, exam_details.day); 
}

int ExamDetails::dateDifference(int month1, int day1, int month2, int day2) {
    return DAYS_IN_MONTH*(month1-month2) + day1-day2;
}

bool ExamDetails::equalNums(double num1, double num2) {
    return std::abs(num2 - num1) <  DOUBLE_ACCURACY ; 
}
bool ExamDetails::operator<(const ExamDetails& exam_details) const {
    int date_difference = dateDifference(this->month, this->day, exam_details.month, exam_details.day);
    if (date_difference != 0) {
        return date_difference<0;
    }
    else {
        return (this->start_time < exam_details.start_time);
    }
}

ExamDetails ExamDetails::makeMatamExam() {
    ExamDetails mtm_exam = ExamDetails(234124, 7, 28, 13, 3, "https://tinyurl.com/59hzps6m");
    return mtm_exam;
}

namespace mtm {
    std::ostream& operator<<(std::ostream& os, const ExamDetails& exam_details) {
        os << "Course Number: " << exam_details.course_id << endl;
        string minutes = ExamDetails::equalNums(exam_details.start_time, (int)exam_details.start_time) ? "00" : "30";
        os << "Time: " << exam_details.day << "." << exam_details.month << " at " << (int)exam_details.start_time << ":" << minutes << endl;
        os << "Duration: " << exam_details.total_time << ":00" << endl;
        os << "Zoom Link: " << exam_details.zoom_link << endl;
        return os;
}

}



