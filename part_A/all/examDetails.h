#include <string>
#include <ostream>

namespace mtm {

    class ExamDetails {
    private:
        int course_id;
        int month;
        int day;
        double start_time;
        int total_time;
        std::string zoom_link;
        static int dateDifference(int month1, int day1, int month2, int day2);
        static bool equalNums(double num1, double num2);
        static bool validHour(double hour);
    public:
        ExamDetails(int course_id, int month, int day, double start_time, int total_time, const std::string zoom_link=""); // not sure if zoom_link should be const
        ~ExamDetails() = default;
        ExamDetails(const ExamDetails& exam_details) = default;
        ExamDetails& operator=(const ExamDetails& exam_details) = default;
        std::string getLink() const;
        void setLink(std::string new_link);
        int operator-(const ExamDetails& exam_details) const;
        bool operator<(const ExamDetails& exam_details) const;
        static ExamDetails makeMatamExam();

        class InvalidDateException {};
        class InvalidTimeException {};
        class InvalidArgsException {};

        friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam_details);
    };

}
