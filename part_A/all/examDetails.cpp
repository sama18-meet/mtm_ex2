#include <iostream>
#include <string>
#include "examDetails.h"
#include <cmath>
#define DAYS_IN_MONTH 30
#define HOURS_IN_DAY 24
#define MONTHS_IN_YEAR 12
#define TWO 2
#define DOUBLE_ACCURACY 0.000001
#define MTM_COURSE_NUM 234124
#define MTM_EXAM_MONTH 7
#define MTM_EXAM_DAY 28
#define MTM_EXAM_START_TIME 13
#define MTM_EXAM_TOTAL_TIME 3
#define MTM_EXAM_URL "https://tinyurl.com/59hzps6m"
#define WHOLE_HOUR "00"
#define HALF_HOUR "30"


using std::endl;
using std::string;
using namespace mtm;

ExamDetails::ExamDetails(int course_id, int month, int day, double start_time, int total_time, const string zoom_link) : course_id(course_id), month(month), day(day), start_time(start_time), total_time(total_time), zoom_link(zoom_link)
{
    if (course_id < 0)
    {
        throw InvalidArgsException();
    }
    if (month < 1 || month > MONTHS_IN_YEAR || day < 1 || day > DAYS_IN_MONTH)
    {
        throw InvalidDateException();
    }
    if (!validHour(start_time))
    {
        throw InvalidTimeException();
    }
    if (total_time < 0)
    {
        throw InvalidArgsException();
    }
}

string ExamDetails::getLink() const
{
    return this->zoom_link;
}

void ExamDetails::setLink(const string& new_link)
{
    this->zoom_link = new_link;
}

int ExamDetails::operator-(const ExamDetails &exam_details) const
{
    return dateDifference(this->month, this->day, exam_details.month, exam_details.day);
}

int ExamDetails::dateDifference(int month1, int day1, int month2, int day2)
{
    return DAYS_IN_MONTH * (month1 - month2) + day1 - day2;
}

bool ExamDetails::equalNums(double num1, double num2)
{
    return std::abs(num2 - num1) <  DOUBLE_ACCURACY ; 
}

bool ExamDetails::validHour(double hour) {
    return hour >= 0 && hour < HOURS_IN_DAY && equalNums((int)(hour * TWO), hour * TWO);
}

bool ExamDetails::operator<(const ExamDetails &exam_details1) const
{
    int date_difference = dateDifference(this->month, this->day, exam_details1.month, exam_details1.day);
    if (date_difference != 0)
    {
        return date_difference < 0;
    }
    else
    {
        return (this->start_time < exam_details1.start_time);
    }
}

ExamDetails ExamDetails::makeMatamExam()
{
    return ExamDetails(MTM_COURSE_NUM, MTM_EXAM_MONTH, MTM_EXAM_DAY, MTM_EXAM_START_TIME, MTM_EXAM_TOTAL_TIME, MTM_EXAM_URL);
}

namespace mtm
{
    std::ostream &operator<<(std::ostream &os, const ExamDetails &exam_details)
    {
        os << "Course Number: " << exam_details.course_id << endl;
        string minutes = ExamDetails::equalNums(exam_details.start_time, (int)exam_details.start_time) ? WHOLE_HOUR : HALF_HOUR;
        os << "Time: " << exam_details.day << "." << exam_details.month << " at " << (int)exam_details.start_time << ":" << minutes << endl;
        os << "Duration: " << exam_details.total_time << ":" << WHOLE_HOUR << endl;
        os << "Zoom Link: " << exam_details.zoom_link << endl;
        return os;
    }
}
