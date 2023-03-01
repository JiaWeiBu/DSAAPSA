#include "Subject.h"

Subject::Subject()
{
	strcpy_s(subject_code, "");
	strcpy_s(subject_name, "");
	credit_hours = 0;
	marks = 0;
}

const char* Subject::getGrade()
{
	if (marks < 0 && marks > 100)
		return "N/A";
	else if (marks <= 49)
		return "F";
	else if (marks <= 54)
		return "C";
	else if (marks <= 59)
		return "C+";
	else if (marks <= 64)
		return "B-";
	else if (marks <= 69)
		return "B";
	else if (marks <= 74)
		return "B+";
	else if (marks <= 79)
		return "A-";
	else if (marks <= 89)
		return "A";
	else
		return "A+";
}

double Subject::getGradePoint()
{
	if (marks < 0 && marks > 100)
		return -1.0;
	else if (marks <= 49)
		return 0.00;
	else if (marks <= 54)
		return 2.00;
	else if (marks <= 59)
		return 2.33;
	else if (marks <= 64)
		return 2.67;
	else if (marks <= 69)
		return 3.00;
	else if (marks <= 74)
		return 3.33;
	else if (marks <= 79)
		return 3.67;
	else if (marks <= 100)
		return 4.00;
}

void Subject::print(ostream& out)
{
	out << "\n";
	out << subject_code << "\t" << setw(35) << left << subject_name << setw(7) << right << credit_hours <<
		"\t" << setw(3) << left << " " << getGrade() << "\t" << setprecision(5) << fixed << showpoint <<
		getGradePoint();
}