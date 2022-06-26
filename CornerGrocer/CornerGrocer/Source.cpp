#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int userInput;
string str;
string fileLine;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void UserMenu()
{

	// User Menue
	cout << "----------------- User Menu -----------------\n";
	cout << "1: Produce a list of all items purchased with quantities \n";
	cout << "2: Display how many times a specific item was sold \n";
	cout << "3: Produce a histogram of sales data \n";
	cout << "4: Exit \n\n";
	cout << "Enter your selection as a number: 1, 2, 3, or 4. \n";
	cout << "---------------------------------------------\n\n";
	// Take user input as menu selection
	cin >> userInput;

	if (userInput == 1)
	{
		// Use CallProcedure wrapper to call ItemCounter.
		cout << "\n\nPrinting items and quantities sold today: \n\n";
		CallProcedure("ItemCounter");
		cout << "\n\n";
		
	}
	else if (userInput == 2)
	{
		// Prompt the user for a item
		cout << "\n\nPlease enter the item name: \n\n";
		cin >> str;
		cout << endl;
		cout << endl;
		cout << "Printing the sales for " << str << ":\n\n";
		//Use CallIntFunc wrapper to call NumItemCounter
		cout << str << ": " << callIntFunc("NumItemCounter", str) << "\n\n";

	}
	else if (userInput == 3)
	{
		//Write counts from the input file to the output file
		cout << "\n\nWriting items and quantities sold today to a file: \n\n";
		CallProcedure("ItemWriter");
		cout << endl; 
		cout << endl; 
		// Open the output file and read the data
		ifstream frequencyFile("frequency.dat");
		string item;
		int count;
		// Parse through the file line by line and print the histogram
		while (getline(frequencyFile, fileLine))
		{
			istringstream iss(fileLine);
			if (!(iss >> item >> count)) { break; } //Break loop 
			// Print the item name and number of asterisks
			cout << item << " " << string(count, '*') << endl;
		}
		cout << "\n\n";
	}
	else if (userInput == 4)
	{
		// Exit the program
		cout << "\n\nExiting program . . .  \n" << endl ;
		exit(EXIT_SUCCESS);
	}
	else
	{
		// Validate input
		cout << "\n\nPlease enter a valid input . . . \n\n";
		exit(EXIT_SUCCESS);
	}
}


void main()
{
// Loop to diplay menu. Can be exited by inputting the Sentinel value
	
	while (true)
	{
		UserMenu();
	}
}