#include "examDetails.h"
#include <iostream>
using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;
using std::ostream;

namespace mtm
{
//1
 ExamDetails::ExamDetails (int course_number, int month_test, int day_test, double hour_test, int length_test, std::string link_zoom)
 {
   if(month_test>12||month_test<=0)
   {
     throw InvalidDateException();
   }
  if(day_test>30||day_test<=0)
   {
     throw InvalidDateException();
   }
   if(hour_test>24||hour_test<=0)
   {
     throw InvalidTimeException();
   }
   this->course_number = course_number;
   this->month_test = month_test;
   this->day_test =  day_test;
   this->hour_test = hour_test;
   this->length_test = length_test;
   this->link_zoom = link_zoom;
 }
//2
 ExamDetails::~ExamDetails()
 {
 }

//3

ExamDetails& ExamDetails::operator = (const ExamDetails& examDetails)
{
  if (this->course_number == examDetails.course_number)
  {
    return *this;
  }
 
  this->course_number =  examDetails.course_number;
  this->month_test =  examDetails.month_test;
  this->day_test =  examDetails.day_test;
  this->hour_test =  examDetails.hour_test;
  this->link_zoom =  examDetails.link_zoom;
  this->length_test = examDetails.length_test;
  return *this;
}
ExamDetails::ExamDetails(const ExamDetails& examDetails)
 {
     this->course_number=examDetails.course_number;
     this->month_test = examDetails.month_test;
     this->day_test = examDetails.day_test;
     this->hour_test = examDetails.hour_test;
     this->length_test=examDetails.length_test;
     this->link_zoom=examDetails.link_zoom;
 }
 //4
std::string ExamDetails::getLink() const
  {
    return this->link_zoom;
  }
//5
void ExamDetails::setLink(string link_zoom)
  {
    this->link_zoom = link_zoom;
    return;
  }
//6
int ExamDetails::operator - (const ExamDetails& examDetails)
  {
    if(this->month_test == examDetails.month_test)
    {
      return(this->day_test - examDetails.day_test);
    }
    int days = 30*(this->month_test-examDetails.month_test);
    return(days - (this->day_test - examDetails.day_test)); // need to work on that
  }
//7
bool ExamDetails::operator < (const ExamDetails& examDetails)
  {
  if(this->month_test == examDetails.month_test)
    {
      if(this->day_test<examDetails.day_test)
       {
        return true;
       }
      return false;
    }

  if(this->month_test < examDetails.month_test)
    {
      return true;
    }

  return false; 
  }
//8
std::ostream& operator<<(ostream& os , ExamDetails exam)
{
  int hour, minuets;
  
  int x = 2*(exam.hour_test);
  hour = (int)exam.hour_test;
  if(((int)x)%2 == 0)
  {
    minuets = 0;
  }
  else
  {
    minuets = 3;
  }
     os << "Course Number: " << (exam.course_number) << endl;
     os << "Time: " <<(exam.day_test)<< "." <<(exam.month_test)<< " at " <<(hour)<<":"<<(minuets)<<"0" << endl;
     os << "Duration: "<<(exam.length_test)<<":00"<< endl;
     os << "Zoom Link: "<<(exam.link_zoom) << endl;
     return os;
}
//9
ExamDetails ExamDetails::makeMatamExam()
{
  return mtm::ExamDetails(234124, 7, 28, 13, 3 , "https://tinyurl.com/59hzps6m");
}

}
