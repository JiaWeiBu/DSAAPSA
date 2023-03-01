/*
Refer to the file Student.h for all the members in the struct. Refer to the table below for the format of the data stores for each attribute in Student struct.

Attributes	Format
name	A c-string with 30 characters
id	A c-string to represent id. Student id consists of 7 digits with the first 2 digit represent years enroll. E,g.: 1300345
course	Use 2 characters to represent:
CS – Computer Science
IA – Information Systems Engineering
IB – Business Information Systems
CN – Communication and Networking
CT – Computer Engineering
phone_no	A 7 digits number in the following format: 123-4567
current_cpga	The latest cgpa for a student with 5 decimal places. E.g.: 3.51762
totalCreditsEarned	Total credits earned so far.
exam 	An array to store past exam for a student according to trimester. This array can store up to 10 trimester result.
exam_cnt	A counter to keep track of the number of past exam result store in exam array.

The following member functions are given in the struct:

1.	Constructor Student() to initialized name, id, course and phone_no to empty string (use strcpy) and current_cgpa, exam_cnt and totalCreditsEarned to 0.

2.	Function bool compareName1 (Student) to compare student name using >= operator. You can use this function to compare which student’s name come first according to alphabetical order. It is used in the second insert function.

3.	Function bool compareID (Student) to compare student id using == operator. You can use this function to search for student in a linked list based on id.

4.	Function void print(ostream &) to print Student struct variable. The argument pass to the function is used to determine which stream to print the output.

5.	Function bool calculateCurrentCGPA() to calculate the current cgpa for a student.
*/

#ifndef Student_obj
#define Student_obj

#include "Exam.h"

struct Student
{
	char name[30];
	char id[7];
	char course[2];
	char phone_no[8];
	double current_cgpa;
	int totalCreditsEarned;
	Exam exam[10];
	int exam_cnt;

	Student();
	bool compareName1(Student);
	bool compareID(Student);
	void print(ostream &);
	bool calculateCurrentCGPA();
};

#endif // !Student_obj