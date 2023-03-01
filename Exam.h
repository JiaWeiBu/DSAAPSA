/*
Exam Struct:

Refer to the file Exam.h for all the members in the struct. Refer to the table below for the format of the data stores for each attribute in Exam struct.

Attributes	Format
trimester	Store the trimester of the exam using integer to represent the 3 trimester in a year as follow:
1 – January Trimester
5 – May Trimester
10 – October Trimester
year	A four digit integer to represent the year of the exam.
gpa	GPA obtained for a trimester. Use 5 decimal points to represent the value.
numOfSubjects	The number of subjects taken in that trimester.
sub[]	The subject information taken in that trimester. Each element is an object of class Subject. Maximum only 6 subjects can be taken and minimum is 1 subject.

The following member functions are given in the Exam struct:

1.	Constructor Exam() to initialized trimester, year, gpa and numOfSubjects to 0.

2.	Function bool calculateGPA() to calculate the gpa for an exam in a trimester
based on the grade and number of subjects take. Refer to file Figure2.doc for the   grade point based on the marks obtained.

3.	Function void print(ostream &) to print the Exam struct variable. The argument   pass to the function is used to determine which stream to print the output.
*/

#ifndef Exam_obj
#define Exam_obj

#include "Subject.h"

using namespace std;

struct Exam
{
	int trimester;
	int year;
	double gpa;
	int numOfSubjects;
	Subject sub[6];

	Exam();
	bool calculateGPA();
	void print(ostream &);
	const char* printTrimester();
};

#endif // !Exam_obj