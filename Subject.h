/*
Refer to the file Subject.h for all the members in the Subject struct. Refer to the table below for the format of the data stores for each attribute in Subject struct.

Attributes	Format
subject_code	A string with 10 characters to represent a code for a subject. First four characters represent must be alphabet and last four are digits.
subject_name	A string represents the subject names.
credit_hours	Number of credit hours for a subject.
marks	Marks obtained for a subject. Range is from 1 to 100.

The following member functions are given in the Subject struct:

1.	Constructor Subject() to initialized subject_code and subject_name to empty string (use strcpy) and credit_hours, and marks to 0.

2.	Function const char *getGrade() to return the grade (A+, A, B+, …) for a subject based on the marks. Refer to file Figure2.doc for the grade return based on the marks obtained.

3.	Function double getGradePoint() to return the grade point for a subject based on the marks obtained. Refer to file Figure2.doc for the grade point return.

4.	Function void print(ostream &) to print Subject struct variable. The argument pass to the function is used to determine which stream to print the output.

*/

#ifndef Subject_obj
#define Subject_obj

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

struct Subject
{
	char subject_code[10];
	char subject_name[30];
	int credit_hours;
	double marks;

	Subject();
	const char *getGrade();
	double getGradePoint();
	void print(ostream &);
};

#endif // !Subject_obj