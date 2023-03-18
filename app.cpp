/*
main() Tasks:

You need to write the following functions in main().

1.	Write a function bool CreateStuList(const char *filename, List *list) to read student information from a file and store in a linked list. Ensure there is no duplicate record of student stored in the list. The function will return true if successfully read and false otherwise. A sample of the textfile is in �student.txt�.

2.	Write a function bool DeleteStudent(List *list, char *id) to delete a student from the linked list based on student id. The function will return true if successfully delete and false if student cannot be found in the list.

3.	Write a function bool PrintList(List list, int source) that will display information to the screen. Function return false if list is empty and true otherwise. The source variable will indicate whether to display to screen (source = 1) or file (source = 2). If write to file, use the filename �student_result.txt� to write. A sample of each of the output option is given in text file in folder sample output. If the student�s exam_cnt = 0, then print �THIS STUDENT HAVEN�T TAKEN ANY EXAM YET�. You can design your own output format but the necessary details must be there.

4.	Write a function bool InsertExamResult(const char *filename, List *list) to insert student exam result to the linked list. Open the file with filename and read every record and find the student to insert the exam based on their id. A sample of the text file is in �exam.txt�.  Read every record in the file and put the exam info in an exam struct variable. Then find the correct student based on id to insert the exam struct variable. You need to calculate the current cgpa every time you insert a new exam to a student.


5.	Write a function bool PrintStatistic(List list) that will find and print the statistics for the student list as below. Average subject taken per semester is based on how many subjects are taken averagely for one student in one semester. Similar for average credit hours earned per semester. The function will return false for empty list and true otherwise.

	  Sample Output:

	  Total Students:  20
			CS Students � 6
			IA Students � 5
			IB Students � 3
			CN Students � 3
			CT Students � 3

	  Average CGPA: 3.15670
			  Average Subjects Taken Per Semester: 3.23
				  Average Credits Earned Per Semester: 10.57

6.	The function bool FilterStudent(List list1, List *list2, char *course, int year, int totalcredit) that will filter student in list1 according to course, year and totalcredit earned. For example, if the value passes in for course = �CS�, year = 2020 and totalcredit = 30, you need to traverse list1 to find all CS students that are enrolled in 2020 and the totalCreditsEarned is >= 30. If a student fulfills all the three conditions, then insert to list2. You can extract the year enrolled from the student id where the first 2 digits represent year enrolled (e.g.: if id is 2000345 then year enrolled is 2020). Call PrintList function in main after function call to display list2 content to screen. The function will return false if list1 is empty or if list2 is not empty when it is passed to the function. Otherwise, return true. (Note: list1 content will remain the same after function call)


7.	Write a function bool UpdateIDandPhone(List *list) that will update the student ID and phone number for all the students in list list.  The student ID will be updated according to their as shown in Table 1 below. To update phone number, you need to change all the phone numbers in list list from 7 digits to 9 digits as shown in Table 2. If the first digit in the phone number starts with odd number, add a leading digit 01 and remove the dash. If the first digit is even number, add a leading 02 and remove dash. The function will return false if list is empty or true otherwise. Call PrintList function in main to display the student list to screen after return from the function to display the changes in every student.

Table 1 Current ID and Updated ID

Course	Current ID	Updated ID
CS	1207893	BCS1207893
IA	1109236	BIA1109236
IB	1223456	BIB1223456
CN	1207832	BCN1207832
CT	1103672	BCT1103672


Table 2 Original Phone Numbers and Updated Phone Numbers

	Original phone numbers	Updated phone numbers
Case 1 (start with odd digit)	123-4567	011234567
Case 2 (start with even digit)	659-8776	026598776



8.	Write a function bool FindPotentialFirstClass(List list1, List *list2, char *course) to find potential student that has the potential to get first class in list list1 according to course. A student is considered to have potential to get first class if he/she gets GPA >= 3.75000 for >= 3 trimesters and other trimesters GPA cannot be < 3.50000. For each of the trimester with GPA>=3.75000 he/she must has taken >= 12 credit hours. Copy all the students that fulfill these criteria into list list2. list1 content will not be changed after function call. Call function Printlist in main after function call to print list2 in screen. If there is no student that fulfills these criteria, then print the message �There is no student in CS that has potential to get first class�.  The function will return false if list1 is empty or if list2 is not empty when it is passed to the function, otherwise return true. Note: If a student has taken < 3 exams then you don�t have to check if this student has potential for first class


9.	Write a int menu() function that contain menu with choice from 1 to 9 above to let user choose that task. Function will return the choice chosen. Make sure user can continuously choose for the menu until exit choice is chosen. Sample menu is displayed below:

1. Create student list
2. Delete Student
3. Print student list
4. Insert exam result
5. Print Exam Statistic
6. Filter Student
7. Update Student�s ID and Phone
8. Find Potential First Class Student
9. Exit.
*/

#include "List.h"
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;


#define STU_F_ID 13
#define STU_F_NAME 7
#define STU_F_COURSE 9
#define STU_F_PHONE 15

bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
//bool PrintStatistic(List);
bool InsertExamResult(const char*, List*);
//bool FilterStudent(List, List*, char*, int, int);
//bool UpdateIDandPhone(List*);
//bool FindPotentialFirstClass(List, List*, char*);
int menu();

void main() {
	system("cls");
	int choice;
	int source;
	bool function;
	const char STUDENT_FILE[] = "student.txt";
	const char EXAM_FILE[] = "exam.txt";
	List* stud_list, * temp_list;
	char* id = new char;
	char* programme = new char;
	stud_list = new List;
	temp_list = new List;
	do {
		switch (choice = menu())
		{
		case 1:
			stud_list = new List;
			if (CreateStuList(STUDENT_FILE, stud_list))
				cout << "Student list created successfully" << endl;
			else
				cout << "Student list created unsuccessfully" << endl;
			system("pause");
			break;
		case 2:
			cout << "Enter student ID to delete: ";
			cin >> id;
			if (DeleteStudent(stud_list, id))
				cout << "Student deleted successfully" << endl;
			else
				cout << "Student deleted unsuccessfully" << endl;
			system("pause");
			break;
		case 3:
			cout << "Enter 1 to print student list or 2 to print temp list: ";
			cin >> source;
			if (PrintList(*stud_list, source))
				cout << "Student list printed successfully" << endl;
			else
				cout << "Student list printed unsuccessfully" << endl;
			system("pause");
			break;
		case 4:
			if (InsertExamResult(EXAM_FILE, stud_list))
				cout << "Exam result inserted successfully" << endl;
			else
				cout << "Exam result inserted unsuccessfully" << endl;
			system("pause");
			break;
		case 5:
			//PrintStatistic(*stud_list);
			break;
		case 6:
			//FilterStudent(*stud_list, temp_list, programme, 2020, 30);
			break;
		case 7:
			//UpdateIDandPhone(stud_list);
			break;
		case 8:
			//FindPotentialFirstClass(*stud_list, temp_list, programme);
		default:
			break;
		}
	} while (choice != 9);
}

int menu() {
	system("cls");
	int choice;
	cout << "1. Create student list" << endl;
	cout << "2. Delete Student" << endl;
	cout << "3. Print student list" << endl;
	cout << "4. Insert exam result" << endl;
	cout << "5. Print Exam Statistic" << endl;
	cout << "6. Filter Student" << endl;
	cout << "7. Update Student's ID and Phone" << endl;
	cout << "8. Find Potential First Class Student" << endl;
	cout << "9. Exit." << endl;
	cout << "Enter your choice: ";
	cin >> choice;
	return choice;
}

bool CreateStuList(const char* filename, List* list) {
	ifstream infile;
	string line;

	infile.open(filename);
	if (!infile.is_open())
		return false;
	for (; !infile.eof();) {
		Student* student = new Student;
		for (int j = 0; j < 5; j++) {
			getline(infile, line);
			switch (j)
			{
			case 0:
				strcpy_s(student->id, line.substr(STU_F_ID, line.length() - STU_F_ID).c_str());
				break;
			case 1:
				strcpy_s(student->name, line.substr(STU_F_NAME, line.length() - STU_F_NAME).c_str());
				break;
			case 2:
				strcpy_s(student->course, line.substr(STU_F_COURSE, line.length() - STU_F_COURSE).c_str());
				break;
			case 3:
				strcpy_s(student->phone_no, line.substr(STU_F_PHONE, line.length() - STU_F_PHONE).c_str());
				break;
			default:
				break;
			}
		}
		// check if student is already in the list
		bool duplicate = false;
		if (!(list->empty())) {
			for (int i = 1; i <= list->count; i++) {
				Node* temp = list->find(i);
				if (temp->item.compareID(*student)) {
					cout << "Duplicate student ID <" << student->id << "> detected." << endl;
					duplicate = true;
					break;
				}
			}
		}
		if (duplicate)
			continue;
		list->insert(*student);
	}
	return true;
}


bool DeleteStudent(List* list, char* id) {
	Node* temp = list->head;
	int i = 1;

	while (temp != nullptr && strcmp(temp->item.id, id) != 0) {
		temp = temp->next;
		i++;
	}

	if (temp != nullptr) {
		list->remove(i);
		return true;
	}

	cout << "Student not found." << endl;
	return false;
}


bool InsertExamResult(const char* filename, List* list) {
	ifstream infile;
	char* name_student = new char;
	char* student_id = new char; // allocate an array of 8 character
	char del;
	bool con;
	int year, trimester, del1;

	//check files and list
	if (list->empty()) {
		cout << "List is empty.";
		return false;
	}
	infile.open(filename);
	if (!(infile.is_open())) {
		cout << "File cannot be open.";
		return false;
	}

	//read in data tuple by tuple
	con = false;
	while (infile >> student_id ) {
		Node* temp = list->head;//each search start from head
		do {// search id in linked list
			if (temp->item.id[0] == 'B') {
				while (temp->next != NULL && strcmp(student_id,temp->item.id+3) != 0) temp = temp->next; //exam_cnt reset here
				break;
		
			}

			else {
				while (temp->next != NULL && strcmp(student_id, temp->item.id) != 0) temp = temp->next;
				break;
			}
		} while (temp != nullptr);

		//insert tuple data
		infile >> trimester >> year;
		bool duplicate = false;
		for (int k = 0; k < temp->item.exam_cnt; k++) {
			if ((year == temp->item.exam[k].year) && (trimester == temp->item.exam[k].trimester)) {
				cout << "Duplicate Exam Record Detected for <" << student_id << ">." << endl;
				infile >> del1;
				for (int i = 0; i < del1; i++) {
					infile >> del;
					infile >> del;
					infile >> del;
					infile >> del;
				}
				duplicate = true;
				break;
			}
		}

		if (duplicate)
			continue;

		temp->item.exam[temp->item.exam_cnt].year = year;
		temp->item.exam[temp->item.exam_cnt].trimester = trimester;
		infile >> temp->item.exam[temp->item.exam_cnt].numOfSubjects;

		//insert subject
		int i = 0;
		while (i < temp->item.exam[temp->item.exam_cnt].numOfSubjects) {
			infile >> temp->item.exam[temp->item.exam_cnt].sub[i].subject_code;
			infile >> temp->item.exam[temp->item.exam_cnt].sub[i].subject_name;
			infile >> temp->item.exam[temp->item.exam_cnt].sub[i].credit_hours;
			infile >> temp->item.exam[temp->item.exam_cnt].sub[i].marks;
			i++;
		}
		//calculate gpa and cgpa
		temp->item.exam[temp->item.exam_cnt++].calculateGPA();
		temp->item.calculateCurrentCGPA();
	}

	infile.close();
	return true;
}

