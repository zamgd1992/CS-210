#include <Python.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonFunctions");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

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
	pName = PyUnicode_FromString((char*)"PythonFunctions");
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

void printMenu() { // displays menu for user
	cout << "What do you want to do?" << endl;
	cout << "   1- List items purchased in day" << endl;
	cout << "   2- Number of purchases for specific item" << endl;
	cout << "   3- Graph of items purchased" << endl;
	cout << "   4- Exit" << endl;
	cout << "Enter selection as number 1, 2, 3, or 4..." << endl;
}

void printCountPerItem() { // displays each item and the number of times it was purchased
	CallProcedure("CalculateFrequency"); // calls Python function to read file of grocery items purchased
	// Python function also displays this information
	cout << endl;
}

int countOfSpecificItem(string specificItem) { // gets the number of times a specific item was purchased
	int buyCount = 0;
	
	buyCount = callIntFunc("ItemFrequency", specificItem); // calls Python Function to get number of purchases for item

	return buyCount;
}

void printGraphOfItems() { // displays histogram of ammount of times each item was purchased
	ifstream inFS; // this function reads from a file created by Python
	int buyCount;
	string groceryItem;

	CallProcedure("WriteFrequencyFile"); // calls Python function to write a file with number of times each item was purchased

	inFS.open("frequency.dat"); // open file created by Python
	if (!inFS.is_open()) { // checks to make sure file was opened
		cout << "Error: frequency.dat did not open" << endl;
		cout << "can not print graph" << endl;
	}

	inFS >> groceryItem; // initialize reading from file
	while (!inFS.fail()) { // loops until end of file
		cout << setfill(' '); 
		cout << setw(14) << left << groceryItem << "|"; //formats histogram
		inFS >> buyCount;
		for (int i = 0; i < buyCount; ++i) { // prints '=' for each time the item was purchased
			cout << "=";
		}
		cout << endl;
		inFS >> groceryItem; // reads next item in file
	}

	inFS.close(); // closes file
	cout << endl;
}

int getMenuSelection() { // gets menu selection from user
	int menuSelection;

	cin >> menuSelection;

	if (cin.fail()) { // checks that user entered an integer
		throw invalid_argument("Must enter an integer");
	}

	if ((menuSelection < 1) || (menuSelection > 4)) { // checks that user entered a valid selection
		throw runtime_error("Invalid selection. Must enter 1, 2, 3 or 4");
	}

	return menuSelection;
}

string getGroceryItem() { // gets string for the name of a specific grocery item
	string itemString;
	int validationNum; // integer used to validate string

	cout << "Enter item name to find quantity" << endl;

	cin >> itemString;

	validationNum = callIntFunc("ValidateItem", itemString); // calls Python function that checks if string is in list of grocery items
	// returns 1 for valid item and 0 for invalid item

	if (validationNum == 0) { // checks for strings that are not in grocery list
		throw invalid_argument("Entered item not in list of grocery items");
	}

	return itemString;
}

int main()
{
	string groceryItem;
	int menuValue = 0;

	while (menuValue != 4) { // loops menu until selection is 4
		printMenu();
		cout << endl;

		try {
			menuValue = getMenuSelection();
		}
		catch (invalid_argument& excpt) { //catches exceptions for invalid input
			cout << excpt.what() << endl;

			cin.clear();
			cin.ignore();

			continue;
		}
		catch (runtime_error& excpt) { // catches exceptions for incorrect selection 
			cout << excpt.what() << endl;

			continue;
		}

		if (menuValue == 1) {
			printCountPerItem();
		}

		if (menuValue == 2) {
			int numTimesPurchased;
			bool inputValidation = false;

			while (inputValidation != true) { // loops until user enters a string that is in grocery list
				inputValidation = true; // assume correct input to exit loop

				try {					
					groceryItem = getGroceryItem();
				}
				catch (invalid_argument& excpt) { //catches exceptions for invalid input
					cout << excpt.what() << endl;
					inputValidation = false; // set back to false if invalid item name

					continue;
				}
			}

			cout << endl;

			numTimesPurchased = countOfSpecificItem(groceryItem);

			cout << groceryItem << ": purchased " << numTimesPurchased << " times." << endl;
			cout << endl;
		}

		if (menuValue == 3) {
			printGraphOfItems();
		}
	}

	return 0;
}