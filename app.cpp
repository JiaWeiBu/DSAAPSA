/*
main() Tasks:

You need to write the following functions in main().

1.	Write a function bool CreateStuList(const char *filename, List *list) to read student information from a file and store in a linked list. Ensure there is no duplicate record of student stored in the list. The function will return true if successfully read and false otherwise. A sample of the textfile is in “student.txt”.

2.	Write a function bool DeleteStudent(List *list, char *id) to delete a student from the linked list based on student id. The function will return true if successfully delete and false if student cannot be found in the list.

3.	Write a function bool PrintList(List list, int source) that will display information to the screen. Function return false if list is empty and true otherwise. The source variable will indicate whether to display to screen (source = 1) or file (source = 2). If write to file, use the filename “student_result.txt” to write. A sample of each of the output option is given in text file in folder sample output. If the student’s exam_cnt = 0, then print “THIS STUDENT HAVEN’T TAKEN ANY EXAM YET”. You can design your own output format but the necessary details must be there.

4.	Write a function bool InsertExamResult(const char *filename, List *list) to insert student exam result to the linked list. Open the file with filename and read every record and find the student to insert the exam based on their id. A sample of the text file is in “exam.txt”.  Read every record in the file and put the exam info in an exam struct variable. Then find the correct student based on id to insert the exam struct variable. You need to calculate the current cgpa every time you insert a new exam to a student.


5.	Write a function bool PrintStatistic(List list) that will find and print the statistics for the student list as below. Average subject taken per semester is based on how many subjects are taken averagely for one student in one semester. Similar for average credit hours earned per semester. The function will return false for empty list and true otherwise.

      Sample Output:

      Total Students:  20
            CS Students – 6
            IA Students – 5
            IB Students – 3
            CN Students – 3
            CT Students – 3

      Average CGPA: 3.15670
              Average Subjects Taken Per Semester: 3.23
                  Average Credits Earned Per Semester: 10.57

6.	The function bool FilterStudent(List list1, List *list2, char *course, int year, int totalcredit) that will filter student in list1 according to course, year and totalcredit earned. For example, if the value passes in for course = “CS”, year = 2020 and totalcredit = 30, you need to traverse list1 to find all CS students that are enrolled in 2020 and the totalCreditsEarned is >= 30. If a student fulfills all the three conditions, then insert to list2. You can extract the year enrolled from the student id where the first 2 digits represent year enrolled (e.g.: if id is 2000345 then year enrolled is 2020). Call PrintList function in main after function call to display list2 content to screen. The function will return false if list1 is empty or if list2 is not empty when it is passed to the function. Otherwise, return true. (Note: list1 content will remain the same after function call)


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



8.	Write a function bool FindPotentialFirstClass(List list1, List *list2, char *course) to find potential student that has the potential to get first class in list list1 according to course. A student is considered to have potential to get first class if he/she gets GPA >= 3.75000 for >= 3 trimesters and other trimesters GPA cannot be < 3.50000. For each of the trimester with GPA>=3.75000 he/she must has taken >= 12 credit hours. Copy all the students that fulfill these criteria into list list2. list1 content will not be changed after function call. Call function Printlist in main after function call to print list2 in screen. If there is no student that fulfills these criteria, then print the message “There is no student in CS that has potential to get first class”.  The function will return false if list1 is empty or if list2 is not empty when it is passed to the function, otherwise return true. Note: If a student has taken < 3 exams then you don’t have to check if this student has potential for first class


9.	Write a int menu() function that contain menu with choice from 1 to 9 above to let user choose that task. Function will return the choice chosen. Make sure user can continuously choose for the menu until exit choice is chosen. Sample menu is displayed below:

1. Create student list
2. Delete Student
3. Print student list
4. Insert exam result
5. Print Exam Statistic
6. Filter Student
7. Update Student’s ID and Phone
8. Find Potential First Class Student
9. Exit.
*/

#include "List.h"
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

//file id filter for student.txt
//VARIABLE.substr(<INSERT HERE>, line.length() - <INSERT HERE>).c_str())

#define STU_F_ID 13
#define STU_F_NAME 7
#define STU_F_COURSE 9
#define STU_F_PHONE 15

bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool PrintStatistic(List);
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
	List* stud_list,* temp_list;
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
			/*if(InsertExamResult(EXAM_FILE, stud_list))
				cout << "Exam result inserted successfully" << endl;
			else
				cout << "Exam result inserted unsuccessfully" << endl;*/
			break;
		case 5:
			//PrintStatistic(*stud_list);
			break;
		case 6:
			//FilterStudent(*stud_list, temp_list, programme, 2020, 30);
			break;
		case 7:
			if (!UpdateIDandPhone(stud_list)) {
				cout << "failed\n";
			}
			break;
		case 8:
			cout << "Please choose a programme to search: ";
			cin >> programme;
			cin.ignore();
			cout << endl;
			if (!FindPotentialFirstClass(*stud_list, temp_list, programme)){
				cout << "There is no student in " << programme << " that has potential to get first class." << endl;
				system("PAUSE");
			}
			else{
				PrintList(*temp_list, 1);
				cout << "First class student list printed successfully" << endl;
				system("PAUSE");
			}
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
	//initialization of variables
	ifstream fin;
	Node* node;
	bool duplicate;
	char* line = new char;
	string temp;

	//check if file is open
	fin.open(filename);
	if (!fin.is_open()) {
		cout << filename << " cannot be opened. " << endl;
		return false;
	}

	//while (condition) to check if there is new tuple present, if halt iteration.
	while (fin >> line) {
		type* stu = new type; //create a new type record

		//format line student id = <id> , while loop take one, 3 more for the rest *note last part is ID
		fin >> line >> line >> line;
		strcpy_s(stu->id, line);

		//format line name = <name , unknown length *require getline>
		fin >> line >> line;
		getline(fin, temp);
		strcpy_s(stu->name, temp.c_str());

		//format line course = <course code>
		fin >> line >> line >> line;
		strcpy_s(stu->course, line);

		//format line phone number = <XXX-XXXX>
		fin >> line >> line >> line >> line;
		strcpy_s(stu->phone_no, line);

		//find duplicate record
		duplicate = false;
		node = list->head;
		while (node != NULL) {
			if (node->item.compareID(*stu)) {
				//duplicate record check
				if (strcmp(node->item.name, stu->name) == 0 && strcmp(node->item.course, stu->course) == 0 && strcmp(node->item.phone_no, stu->phone_no) == 0) cout << "Duplicate reocrd <" << stu->id << "> detected." << endl;

				//primary key check
				else cout << "Duplicate student ID <" << stu->id << "> detected." << endl;

				//set duplicate true and quit iteration
				duplicate = true;
				break;
			}
			//no duplicate will search the next node
			node = node->next;
		}
		if (duplicate) continue;

		//once all check pass, insert to list
		list->insert(*stu);
	}
	return true;
}

bool DeleteStudent(List* list, char* id) {
	//check if the list is empty
	if (list->empty()) {
		cout << "Student list is empty." << endl;
		return false;
	}

	//initialize variable
	Node* node = list->head;

	//find node and delete by its position, if id not in node return false
	for (int i = 1; node != NULL; i++) {
		if (strcmp(node->item.id, id) == 0) {

			list->remove(i);
			return true;
		}
		node = node->next;
	}
	return false;
}

bool PrintList(List list, int choice) {
    if (list.empty())
        return false;
    Node* temp = list.head;
    bool skip1 = false;
    ofstream outfile;
    switch (choice) {
    case 1:
        do {
            if (skip1)
                temp = temp->next;
            else
                skip1 = true;
            cout << "ID: " << temp->item.id << endl;
            cout << "Name: " << temp->item.name << endl;
            cout << "Course: " << temp->item.course << endl;
            cout << "Phone: " << temp->item.phone_no << endl;
            if (temp->item.exam_cnt == 0) {
                cout << "THIS STUDENT HAVENâ€™T TAKEN ANY EXAM YET" << endl;
            }
            cout << endl;
            } while (temp->next != NULL);
        break;
    case 2:
        outfile.open("student_result.txt");
        if (!outfile.is_open())
            return false;
        do {
            if (skip1)
                temp = temp->next;
            else
                skip1 = true;
            outfile << "ID: " << temp->item.id << endl;
            outfile << "Name: " << temp->item.name << endl;
            outfile << "Course: " << temp->item.course << endl;
            outfile << "Phone: " << temp->item.phone_no << endl;
            if (temp->item.exam_cnt == 0) {
                outfile << "THIS STUDENT HAVENâ€™T TAKEN ANY EXAM YET" << endl;
            }
            outfile << endl;
        } while (temp->next != NULL);
        outfile.close();
        break;
    default:
        break;
    }
    return true;
}

bool UpdateIDandPhone(List* list) {
	//check if list is empty
	if (list->empty()) {
		cout << "The list is empty.";
		return false;
	}


	//traverse each node and change the format of the list.
	Node* node = list->head;

	//check if the format already changed
	if (node->item.id[0] == 'B' || node->item.phone_no[3] != '-') {
		cout << "The format already changed. ";
		return false;
	}

	char temp_id[12];
	while (node != NULL) {
		//Student ID B <course> <ID>
		//initialization

		strcpy_s(temp_id, "B");
		strcat_s(temp_id, node->item.course);
		strcat_s(temp_id, node->item.id);
		strcpy_s(node->item.id, temp_id);

		//<ODD/EVEN> <PHONE NO first 3> <PHONE NO second 3>
		//xxx-xxxx //before
		//012345678
		//0XOOOOOOO //after

		string temp_pn(node->item.phone_no);
		temp_pn.erase(temp_pn.find('-'), 1);//remove - from phone no
		if ((temp_pn[0] - '0') % 2 == 1) temp_pn = "01" + temp_pn;
		else temp_pn = "02" + temp_pn;
		strcpy_s(node->item.phone_no, temp_pn.c_str());
		node = node->next;
	}

	return true;
}

bool FindPotentialFirstClass(List list1, List* list2, char* course) {
	Node* temp = list1.head;
	int gpa_count;
	int credit_hr;
	bool condition;

	if (list1.empty()) {
		cout << "Student list is empty." << endl;
		return false;
	}
	if (!list2->empty()) {
		cout << "List 2 is Not Empty." << endl;
		return false;
	}
	do {
		if (strcmp(temp->item.course, course) != 0 || temp->item.current_cgpa < 3.5 || temp->item.exam_cnt < 3 || temp->item.totalCreditsEarned < 36);
		else {
			gpa_count = 0;
			condition = true;
			for (int i = 0; i < temp->item.exam_cnt; i++) {
				if (temp->item.exam[i].gpa < 3.5) {
					condition = false;
					break;
				}
				if (temp->item.exam[i].gpa >= 3.75) {
					credit_hr = 0;
					for (int j = 0; j < temp->item.exam[i].numOfSubjects; j++) {
						credit_hr += temp->item.exam[i].sub[j].credit_hours;
					}
					if (credit_hr >= 12) gpa_count++;
				}
				// anything between 3.5 and 3.75 is not counted
			}
			if (condition && gpa_count >= 3) list2->insert(temp->item);
		}
		temp = temp->next;
	} while (temp != NULL);
	return true;
}
