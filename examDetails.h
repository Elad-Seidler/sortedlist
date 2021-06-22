#include <iostream>
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std:: ostream;

namespace mtm
{
class ExamDetails
{
int course_number;
int month_test;
int day_test;
double hour_test;
int length_test;
std::string link_zoom = "";

public:
class InvalidDateException{};
class InvalidTimeException{};
class InvalidArgsException{};
ExamDetails(int course_number, int month_test, int day_test, double hour_test, int length_test, std::string link_zoom = "");
~ExamDetails();
ExamDetails& operator=(const ExamDetails& examDetails);
ExamDetails(const ExamDetails& examDetails);
std::string getLink() const;
void setLink(string link_zoom);
int operator - (const ExamDetails& examDetails);
bool operator < (const ExamDetails& examDetails);
friend std::ostream& operator<<(ostream& os , ExamDetails exam);
static ExamDetails makeMatamExam();
};
}


