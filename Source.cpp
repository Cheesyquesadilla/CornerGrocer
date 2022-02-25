#include <Python.h>
#include <iostream>
#define NOMINMAX
#include <Windows.h>
#undef NOMINMAX
#include <cmath>
#include <string>
#include<iomanip>
#include <vector>
#include<fstream>
#include<tuple>
#include<cassert>

using namespace std;

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

void Menu() {		//created function to call menu in order to reduce code in main
	int userInput, itemQuantity;	//Variables being used throughout
	bool exitLoop = false;
	string term, item;
	ifstream fileInput;

	while (exitLoop = false) { //while loop to keep menu while validating input
		
		cout << "Please make your selection" << endl;	//prompt user for input
		cout << "1. Show amount of times items were bought" << endl;
		cout << "2. Specific item frequency" << endl;
		cout << "3. Histogram" << endl;
		cout << "4. Quit" << endl;

		cin >> userInput;

		/*
		switch used to go through each selection and call appropriate function
		last case is used for validating user input
		*/
		switch (userInput) { 
		case 1:			//selection one, call appropriate funtion to get item names and quanity
			system("CLS");
			CallProcedure("NumberEachItem");
			std::cout << std::endl;
			break;
		case 2:		//Selection two for check specific items quantity
			system("CLS");
			cout << "What item would you like to check?" << endl;
			cin >> term;
			itemQuantity = callIntFunc("NumberInstances", term);
			std::cout << std::endl << term << ":" << itemQuantity << std::endl;
			break;
		case 3:		//histogram made by calling function and printing out until done
			system("CLS");
			CallProcedure("CollectData");
			fileInput.open("frequency.dat");
			fileInput >> item;
			fileInput >> itemQuantity;
			while (!fileInput.fail()) {
				std::cout << std::setw(14) << item << std::setw(6);
				for (int i = 0; i < itemQuantity; i++){
					std::cout << std::right << "*";
				}
				std::cout << std::endl;
				fileInput >> item;
				fileInput >> itemQuantity;
			}
			fileInput.close();
			break;
		case 4:
			cout << "Goodbye" << endl;
			exitLoop = true; //bool added for good measure
			return;

		default: //validate input
			cout << "Please only select 1, 2, 3, 0r 4" << endl;
			break;
		}
		
	}
}


void main()
{
	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);
	Menu();
}
