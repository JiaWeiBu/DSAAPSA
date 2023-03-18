#include "List.h"
#include <fstream>
#include <string>

using namespace std;

bool CreateStuList(const char*, List*);
bool DeleteStudent(List*, char*);
bool PrintList(List, int);
bool PrintStatistic(List);
bool FilterStudent(List, List*, char*, int, int);
bool UpdateIDandPhone(List*);
bool FindPotentialFirstClass(List, List*, char*);
int menu();

void main() {
	//variable initialization
	int choice, source, year, totalCredit;
	bool function;
	const char STUDENT_FILE[] = "student.txt";
	const char EXAM_FILE[] = "exam.txt";
	List* stud_list, * temp_list;
	char* char_ptr = new char;
	stud_list = new List;

	//run menu first, only when sentinel is called the loop will stop iterate
	do {
		switch (choice = menu())
		{
		case 1:
			stud_list = new List;//create a new list for new dataset
			if (CreateStuList(STUDENT_FILE, stud_list)) cout << "Student list created successfully" << endl;
			else cout << "Student list created unsuccessfully" << endl;
			break;
		case 2:
			cout << "Enter student ID to delete: ";
			cin >> char_ptr;
			cin.clear();
			cin.ignore();

			if (DeleteStudent(stud_list, char_ptr)) cout << "Student deleted successfully" << endl;
			else cout << "Student deleted unsuccessfully" << endl;
			break;
		case 3:
			cout << "Enter 1 to print student list or 2 to print temp list: ";
			cin >> source;
			cin.clear();
			cin.ignore();

			if (PrintList(*stud_list, source)) cout << "Student list printed successfully" << endl;
			else cout << "Student list printed unsuccessfully" << endl;
			break;
		case 4:
			if (InsertExamResult(EXAM_FILE, stud_list)) cout << "Exam result inserted successfully" << endl;
			else cout << "Exam result inserted unsuccessfully" << endl;
			break;
		case 5:
			if (PrintStatistic(*stud_list)) cout << "Print Statistic successfully" << endl;
			else cout << "Print Statistic unsuccessfully" << endl;
			break;
		case 6:
			temp_list = new List;

			cout << "Filter course: ";
			cin >> char_ptr;
			cin.clear();
			cin.ignore();
			cout << "Filter year: ";
			cin >> year;
			cin.clear();
			cin.ignore();
			cout << "Filter totalCredit: ";
			cin >> totalCredit;
			cin.clear();
			cin.ignore();

			if (FilterStudent(*stud_list, temp_list, char_ptr, year, totalCredit)) {
				cout << "Filter Statistic successfully" << endl;
				//check before prompting user to print
				if (temp_list->empty()) cout << "No student selected.";
				else {
					cout << "Enter 1 to print student list or 2 to print temp list: ";
					cin >> source;
					if (PrintList(*temp_list, source)) cout << "Student list printed successfully" << endl;
					else cout << "Student list printed unsuccessfully" << endl;
				}
			}
			else cout << "Filter Statistic unsuccessfully" << endl;
			break;
		case 7:
			if (UpdateIDandPhone(stud_list)) {
				cout << "Update successfully" << endl;
				cout << "Enter 1 to print student list or 2 to print temp list: ";
				cin >> source;
				if (PrintList(*stud_list, source)) cout << "Student list printed successfully" << endl;
				else cout << "Student list printed unsuccessfully" << endl;
			}
			else cout << "Update unsuccessfully" << endl;
			break;
		case 8:
			temp_list = new List;

			cout << "Enter course: ";
			cin >> char_ptr;
			if (FindPotentialFirstClass(*stud_list, temp_list, char_ptr)) {
				cout << "Find Potential First Class Student successfully" << endl;
				cout << "Enter 1 to print student list or 2 to print temp list: ";
				cin >> source;
				if (PrintList(*temp_list, source)) cout << "Student list printed successfully" << endl;
				else cout << "There is no student in "<< char_ptr << " that has potential to get first class." << endl;
			}
			else cout << "Find Potential First Class Student unsuccessfully" << endl;
			break;
		default:
			break;
		}
		system("pause");
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
	string temp_string;

	//detect if the id is in BXXNNNNNNN format , X is course , N is number
	if (id[0] == 'B') { 
		string temp_id(id);
		temp_id.erase(0, 3);
		id = (char*)temp_id.c_str();
	}

	//find node and delete by its position, if id not in node return false
	if (node->item.id[0] != 'B')
		for (int i = 1; node != NULL; i++) {
			if (strcmp(node->item.id, id) == 0) {
				list->remove(i);
				return true;
			}
			node = node->next;
		}
	else {
		for (int i = 1; node != NULL; i++) {
			//temporary get back the default id format
			string temp_string(node->item.id);
			temp_string.erase(0, 3);

			if (strcmp(temp_string.c_str(), id) == 0) {
				list->remove(i);
				return true;
			}
			node = node->next;
		}
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
	char new_id[12];
	char new_pn[10];
	
	if (list->empty()) {
		cout << "Student list is empty." << endl;
		system("PAUSE");
		return false;
	}
	
	Node* temp = list->head;
	
	//check if the format already changed
	if (node->item.id[0] == 'B' || node->item.phone_no[3] != '-') {
		cout << "The format already changed. ";
		return false;
	}
	
	do {
		strcpy_s(new_id, "B");
		strcat_s(new_id, temp->item.course);
		strcat_s(new_id, temp->item.id);
		strcpy_s(temp->item.id, new_id);

		string temp_pn(temp->item.phone_no);
		temp_pn.erase(temp_pn.find('-'), 1);
		if (temp->item.phone_no[0] % 2 == 1)
			strcpy_s(new_pn, "01");
		else
			strcpy_s(new_pn, "02");
		strcat_s(new_pn, temp_pn.c_str());
		strcpy_s(temp->item.phone_no, new_pn);

		temp = temp->next;
	} while (temp != NULL);
	cout << "Student ID Updated." << endl;
	system("PAUSE");
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
