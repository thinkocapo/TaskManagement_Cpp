// Ta// Task Management.cpp : Defines the entry point for the console application.
// the switch case flow statement must appear inside of int main()?
// what if instead of Array I used a property of the object to indicate which one it is... like task.1 task.2 task.3
#include "stdafx.h"
#include <iostream>
#include <istream>
#include <string>
#include <vector>
#include <map>
#include <typeinfo>
using namespace std;
//CLASSES OF OBJECTS
class Tasks
{
public:
	string TaskName;
	string TaskStartDate;
	string TaskAssignedTo;
	string TaskStatus; //how to give only 2 options for this, enumerated constant? or boolean?
	int ID;
};
class Users
{
public:
	string UserID; //index #
	string UserName;
};

//VECTORS AND GLOBAL VARIABLES
vector<Users> vectorUsers;
vector<Tasks> vectorTasks; // can write std::vector <int> vectorTasks (100) ?
int x = 0; //this is for the switch-case construct
int z = 1; //counter variable that counts how many tasks have been created
int lister = 1;
int inputdigit = 0;
int a = 9; //for funcInputmap, which is part of validating user's input to funcEditTask
string sign_in_Name_check = "";
string input;
string inputstring;
string taskEdit;
enum xID
{
	N = 0,
	U = 1,
	e = 2,
	error = 3,
};
map<string, xID> choices;

//FUNCTION DECLARATIONS
void funcHomescreen();
void funcNewTask();
void funcUsers();
void funcEditTask();
void funcInputmap();
void register_choices();

//MAIN FUNCTION
void main()
{
	//cout << vectorTasks.size() << endl;
	//vectorTasks.pop_back();
	//cout << vectorTasks.size();

	//INTRO, SIGN-ON SCREEN, for logging in
	cout << "Enter your User Name" << endl << endl;
	
	Users newUser;
	cin >> newUser.UserName;
	vectorUsers.push_back (newUser);

	sign_in_Name_check = vectorUsers[0].UserName; //assigns user's name to the sign-in variable
	vectorUsers[0].UserID = 1; //this assigns a UserID # to the User object

	//This function contains the switch-case construct which invokes funcNewTask, funcUsers, funcEditTask
	funcHomescreen();

	cout << "GOODBYE" << endl;
	system("PAUSE");
}

//FUNCTION DEFINITIONS
void funcHomescreen()
{
	while (x != 3)
	{
		lister = 1;
		cout << endl << "***WELCOME " << vectorUsers[0].UserName << " TO THE HOMESCREEN*****************************" << endl;
		cout << "***Tasks that are currently Open and Assigned to YOU are:*** \n";
		
		if (vectorTasks.size() != 0)
		{
			for (unsigned long int i = 0; i <= vectorTasks.size() - 1; ++i) //this displays the tasks assignd to the signed-in User
			{
				if (vectorTasks[i].TaskAssignedTo == sign_in_Name_check) //checks if the person task was assigned to is same as signed-in user
				{
					cout << lister << " " << vectorTasks[i].TaskName << endl;
					vectorTasks[i].ID = lister;
					lister = lister + 1; //lister tries to increase +1 even when sign_in_Name_check isn't equal to the signed in user, during a new iteration, so this ensures it won't!		
				}
			}
		}

		cout << "Enter 'N' for a New Task\n" << "Enter 'U' for Users\n" << "Enter 'E' followed by the # of your task to Edit its details\n" << "Enter 'e' for exit\n" << endl;
		cin >> input;
		cout << endl;

		register_choices();
		switch (choices[input])
		{
		case N:
			funcNewTask();
			break;
		case U:
			funcUsers();
			break;
		case e: //this is for satisfying the condition to exiting the while...do statement
			x = 3;
			break;
		default:;
			funcEditTask();
		}
	}
}
void funcNewTask()
{
	Tasks newTask;
	vectorTasks.push_back(newTask);
	cout << "Enter the TaskName" << endl << "Enter the TaskStartDate" << endl << "Enter the TaskAssignedTo" << endl << endl; cin.ignore();
	getline(cin, vectorTasks[vectorTasks.size() - 1].TaskName); //can choose from 0 to 99
	getline(cin, vectorTasks[vectorTasks.size() - 1].TaskStartDate);
	getline(cin, vectorTasks[vectorTasks.size() - 1].TaskAssignedTo);
	cout << endl;
	
	cout << "Your task is named " << vectorTasks[vectorTasks.size() - 1].TaskName << endl;
	cout << " and it was started on " << vectorTasks[vectorTasks.size() - 1].TaskStartDate << endl;
	cout << " and its assigned to " << vectorTasks[vectorTasks.size() - 1].TaskAssignedTo << endl << endl;
	z = z + 1; //this counts the total # of Tasks objects that have been created
}
void funcEditTask()
{
	a = -1; //because 'a' wasn't getting reset to 0 after funcInputmap()
	inputdigit = input[1] - '0';//inputdigit somehow gets a value of 48 if I don't subtract 0 from input[1] (bc string to int)...
	if ((choices[input] = error) && (input[0] == 'E') && (input[1] >= '0') && (inputdigit < z) && (input[1] != '0'))
	{
		funcInputmap();
	}
	else
	{
		cout << endl << "That task doesn't exist yet (or maybe its not assigned to you!)" << endl;
		system("PAUSE");
		return; //ends the function so that the next if statement doesn't run
	}
	if (a == -1)
			cout << endl << "THAT task doesn't exist yet (or maybe its not assigned to you!)" << endl;//
	system("PAUSE");
}
void funcInputmap()
{
	for (unsigned long int i = 0; i <= vectorTasks.size() - 1; i++)
	{
		if ((vectorTasks[i].ID == inputdigit) && (vectorTasks[i].TaskAssignedTo == sign_in_Name_check))
		{
			cout << "The Name, StartDate and AssignedTo of the task you wish to edit is...\n\n";
			cout << vectorTasks[i].TaskName << endl << endl;
			a = i; //can't put a return in here or for won't run on all Tasks
		}
	}
}
void funcUsers()
{
	cout << "***USER'S SCREEN**************************************" << endl << "***Type the User's name to view the tasks assigned to it***" << endl;
	for (unsigned long int i = 0; i <= vectorUsers.size() - 1; i++) //WHY did I have to make this an unsigned int? because the value of  vectorTasks.size() is unsigned int type?
	{
		cout << vectorUsers[i].UserName << endl;
	}
	system("PAUSE");
}
void register_choices()
{
	choices[input] = error;//I am not sure why this 'input' for 'error' has to be listed before N U E e...
	choices["N"] = N; // 0
	choices["U"] = U; // 1
	choices["e"] = e; // 2 this is for exiting the program.
	/*the user's 'input' will give an error if cases N U E e aren't met first!
	*without this, the index gets set to 0 and hence the program used to keep running selection N,
	*because N was set to 0
	*/
}
 