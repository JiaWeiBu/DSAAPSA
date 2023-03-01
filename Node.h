#ifndef Node_obj
#define Node_obj

#include "Student.h"

using type = Student;

struct Node
{
	type item;
	Node *next;
	Node(type);
};

#endif // !Node_obj