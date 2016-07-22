#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

void store();
void search();
void searchDate();
void searchAll();
void quit();
void editInfo();
void deleteInfo();
void editEntry();

bool choiceOption = true;



int main() {
	int choice1;
	choiceOption = true;

	system("cls");
	system("title Lottery Analyzer");
	system("color 0F");

	cout << "Welcome to the 'Lottery Analyzer'.\nThis program can store or search for information stored in the data file:\n'Lottery.txt'.\n\n";
	cout << "Please choose an option: \n 1. Store Information\n 2. Search Data File\n 3. Delete Info\n 4. Quit\n";
	cout << "Your numerical choice: ";

	cin >> choice1;

	while (choiceOption == true) {

		switch (choice1) {
		case 1:
			choiceOption = false;
			store();
			break;
		case 2: 
			choiceOption = false;
			search();
			break;
		case 3: 
			choiceOption = false;
			deleteInfo();
			break;
		case 4:
			choiceOption = false;
			quit();
			break;
		default:
			system("cls");
			cout << "That is not an available choice!\nPlease re-enter your choice:\n 1. Store Information\n 2. Search Data File\n 3. Delete an Entry in the Database\n 4. Quit\n";
			cin >> choice1;
		}
	}

	return 0;
}

void store(){	
		string originalDate;
		string date;
		int month;
		int day;
		int year;
		int dateDelim;
		int dateLength;
		int choice2;

		ofstream storeObject("Lottery.txt", ios::app);
		system("cls");
		choiceOption = true;
		cout << "Enter the date of drawing: mm/dd/yyyy: \n";
		cin >> originalDate;

			date = originalDate;
			date.erase(date.find("/"), date.length());
			stringstream convert(date);
			convert >> month;
			date = originalDate;
			date = date.substr(1 + date.find("/"), date.rfind("/") - (date.find("/") + 1));
			stringstream convert2(date);
			convert2 >> day;
			date = originalDate;
			date = date.substr(date.rfind("/") + 1, date.length() - (date.rfind("/") + 1));
			stringstream convert3(date);
			convert3 >> year;
			storeObject << month << "/" << day << "/" << year << " ";


		int num1, num2, num3, num4, num5, pBall;

		cout << "For this drawing, enter the first lottery number: \n";
		cin >> num1;
		cout << "For this drawing, enter the second lottery number: \n";
		cin >> num2;
		cout << "For this drawing, enter the third lottery number: \n";
		cin >> num3;
		cout << "For this drawing, enter the fourth lottery number: \n";
		cin >> num4;
		cout << "For this drawing, enter the fifth lottery number: \n";
		cin >> num5;
		cout << "For this drawing, enter the Powerball number: \n";
		cin >> pBall;

		storeObject << num1 << " " << num2 << " " << num3 << " " << num4 << " " << num5 << " " << pBall << " @\n";
		system("cls");
		
		storeObject.close();

		cout << "Lottery for " << month << "/" << day << "/" << year << " has been stored.\nWould you like to:\n 1. Add another entry\n 2. Go back to main menu\n 3. Quit\n";
		cin >> choice2;

		while (choiceOption == true) {
			switch (choice2) {
			case 1:
				choiceOption = false;
				store();
				break;
			case 2:
				choiceOption = false;
				main();
				break;
			case 3:
				choiceOption = false;
				quit();
				break;
			default:
				system("cls");
				cout << "That is not an available option.\nPlease re-enter your choice:\n 1. Add another entry\n 2. Go back to main menu\n 3. Quit\n";
				cin >> choice2;
			}
		}
		
}

void search() {
	choiceOption = true;
	int choice3;

	system("cls");

	cout << "We will be searching 'Lottery.txt'\nWhat would you like to search?\n 1. Date\n 2. lotto numbers\n 3. Go back to main menu\n";
	cin >> choice3;

	while (choiceOption == true) {
		switch (choice3) {
		case 1:
			choiceOption = false;
			searchDate();
			break;
		case 2: 
			choiceOption = false;
			searchAll();
			break;
		case 3: 
			choiceOption = false;
			main();
			break;
		default:
			system("cls");
			cout << "That is not an available choice.\nPlease re-enter your choice:\n 1. By date\n 2. By lotto numbers 3. Go back to main menu\n";
			cin >> choice3;
		}
	}
}

void searchDate() {
	string rawData;
	string dataHolder;
	int row = 0;
	int numHolder;
	string previousLine = "";
	string sOriginalDate;
	int matchFound = 0;
	int choice4;
	string sDate;
	int month, day, year;
	string sMonth, sDay, sYear;
	choiceOption = true;

	system("cls");

	ifstream searchObject1;
	searchObject1.open("Lottery.txt");

	//find # of rows
	while (bool searchCount = true) {
		getline(searchObject1, rawData);
		if (rawData != "") {
			row++;
			previousLine = rawData;
		}
		else
			break;
	}

	searchObject1.close();

	//allocate arrays: int array and char array, respectively:

	// Allocate dynamic int array

	int** dataArray = new int *[row];
	for (int i = 0; i < row; i++)
		dataArray[i] = new int[6];

	// Allocate dynamic char array
	char **dateOfDrawing = new char*[row];
	for (int i = 0; i < row; i++) {
		dateOfDrawing[i] = new char[11];
	}


	//intro + search for date
	cout << "You chose to search the file 'Lottery.txt' by a specific date.\nPlease enter the date in the form: 'mm/dd/yyyy'\n";
	cin >> sOriginalDate;

	//convert sOriginalDate to integer values, separated by '/'

	sDate = sOriginalDate;
	sDate.erase(sDate.find("/"), sDate.length());
	stringstream convertToInt(sDate);
	convertToInt >> month;
	stringstream convertBackToString;
	convertBackToString << month;
	sMonth = convertBackToString.str();
	sDate = sOriginalDate;
	sDate = sDate.substr(1 + sDate.find("/"), sDate.rfind("/") - (sDate.find("/") + 1));
	stringstream convertToInt2(sDate);
	convertToInt2 >> day;
	stringstream convertBackToString2;
	convertBackToString2 << day;
	sDay = convertBackToString2.str();
	sDate = sOriginalDate;
	sDate = sDate.substr(sDate.rfind("/") + 1, sDate.length() - (sDate.rfind("/") + 1));
	stringstream convertToInt3(sDate);
	convertToInt3 >> year;
	stringstream convertBackToString3;
	convertBackToString3 << year;
	sYear = convertBackToString3.str();
	sDate = sMonth + "/" + sDay + "/" + sYear;

	//use dataArray
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][0]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ");
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][0] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][1]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ") + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][1] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][2]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][2] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][3]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][3] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][4]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][4] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][5]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][5] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");

	// Use dynamic char array to store the file	
	for (int i = 0; i < row; i++) {
		getline(searchObject1, rawData);
		size_t pos1 = 0;
		size_t pos2 = rawData.find(" ");
		dataHolder = rawData.substr(pos1, pos2);
		int size = dataHolder.size();
		for (int j = 0; j < size; j++) {
			dateOfDrawing[i][j] = dataHolder[j];
		}
		for (int j = size; j < 11; j++) {
			dateOfDrawing[i][j] = dataHolder[pos2];
		}
	}

	//Search algorithm
	for (int i = 0; i < row; i++) {
		if (sDate == dateOfDrawing[i]) {
			cout << "Match Found!\n";
			cout << "Date\t\t#1\t#2\t#3\t#4\t#5\tPB#\n";
			cout << dateOfDrawing[i] << "\t" << dataArray[i][0] << "\t" << dataArray[i][1] << "\t" << dataArray[i][2] << "\t" << dataArray[i][3] << "\t" << dataArray[i][4] << "\t" << dataArray[i][5] << endl;
			matchFound++;
		}
	}
	if (matchFound == 0) {
		cout << "No matches found in the database.\n\n";
	}

	//deallocate array (relearn this topic in more detail)
	for (int i = 0; i < row; i++)
		delete[] dataArray[i];
	delete[] dataArray;

	//deallocate char array
	for (int i = 0; i < row; i++)
		delete[] dateOfDrawing[i];
	delete[] dateOfDrawing;

	cout << "If you would like to do another search, enter '1'. If you would like to go back to the main menu, enter '2'.\n";
	cin >> choice4;

	while (choiceOption == true) {
		switch (choice4) {
		case 1:
			choiceOption = false;
			search();
			break;
		case 2:
			choiceOption = false;
			main();
			break;
		default:
			system("cls");
			cout << "That is not an available option, please enter '1' if you would like to perform another search. /nIf you would like to go back to the main menu, please enter '2'./n";
			cin >> choice4;
		}
	}
	
}

void searchAll() {
	choiceOption = true;
	string rawData;
	string dataHolder;
	int row = 0;
	int numHolder;
	string previousLine = "";
	int sNum;
	int matchFound = 0;
	int choice5;

	system("cls");

	ifstream searchObject1;
	searchObject1.open("Lottery.txt");

	//find # of rows
	while (bool searchCount = true) {
		getline(searchObject1, rawData);
		if (rawData != "") {
			row++;
			previousLine = rawData;
		}
		else
			break;
	}

	searchObject1.close();

	//allocate array

	// Allocate dynamic int array

	int** dataArray = new int *[row];
	for (int i = 0; i < row; i++)
		dataArray[i] = new int[6];

	// Allocate dynamic char array
	char **dateOfDrawing = new char*[row];
	for (int i = 0; i < row; i++) {
		dateOfDrawing[i] = new char[11];
	}


	//intro + search for date
	cout << "You chose to search the file 'Lottery.txt' by the initial numbers.\nPlease type a number to search for: \n";
	cin >> sNum;


	//use dataArray
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][0]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ");
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][0] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][1]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ") + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][1] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][2]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][2] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][3]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][3] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][4]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][4] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][5]
		getline(searchObject1, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][5] = numHolder;
	}
	searchObject1.close();
	searchObject1.open("Lottery.txt");
	
	// Use dynamic char array to store the file	
	for (int i = 0; i < row; i++) {
		getline(searchObject1, rawData);
		size_t pos1 = 0;
		size_t pos2 = rawData.find(" ");
		dataHolder = rawData.substr(pos1, pos2);
		int size = dataHolder.size();
		for (int j = 0; j < size; j++) {
			dateOfDrawing[i][j] = dataHolder[j];
		}
		for (int j = size; j < 11; j++) {
			dateOfDrawing[i][j] =dataHolder[pos2];
		}
	}
	
	//Search algorithm
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < 6; j++) {
			if (sNum == dataArray[i][j]) {
				cout << "Match Found!\n";
				cout << "Date\t\t#1\t#2\t#3\t#4\t#5\tPB#\n";
				cout << dateOfDrawing[i] << "\t" << dataArray[i][0] << "\t" << dataArray[i][1] << "\t" << dataArray[i][2] << "\t" << dataArray[i][3] << "\t" << dataArray[i][4] << "\t" << dataArray[i][5] << endl;
				matchFound++;
			}
		}
	}
	if (matchFound == 0) {
		cout << "No matches found in the database.\n\n";
	}

	//deallocate array (relearn this topic in more detail)
	for (int i = 0; i < row; i++)
		delete[] dataArray[i];
	delete[] dataArray;

	//deallocate char array
	for (int i = 0; i < row; i++)
		delete[] dateOfDrawing[i];
	delete[] dateOfDrawing;

	cout << "If you would like to do another search, enter '1'. If you would like to go back to the main menu, enter '2'.\n";
	cin >> choice5;

	while (choiceOption == true) {
		switch (choice5) {
		case 1:
			choiceOption = false;
			search();
			break;
		case 2:
			choiceOption = false;
			main();
			break;
		default:
			system("cls");
			cout << "That is not an available option, please enter '1' if you would like to perform another search. \nIf you would like to go back to the main menu, please enter '2'.\n";
			cin >> choice5;
		}
	}
}

void quit() {
	system("cls");
	cout << "Thank you for using this database.\n";
	system("pause");
	cin.get();
}

void deleteInfo()
{
	choiceOption = true;
	string rawData;
	string previousLine;
	string dataHolder;
	int numHolder;
	int row=0;
	int idNumber;
	int choice7;
	

	system("cls");

	cout << "You have chosen to delete an entry.\n";

	ifstream inputFileObject;
	inputFileObject.open("Lottery.txt");

	//find # of rows
	while (bool searchCount = true) {
		getline(inputFileObject, rawData);
		if (rawData != "") {
			row++;
			previousLine = rawData;
		}
		else
			break;
	}
	
	inputFileObject.close();

	//allocate array

	// Allocate dynamic int array

	int** dataArray = new int *[row];
	for (int i = 0; i < row; i++)
		dataArray[i] = new int[6];

	// Allocate dynamic char array
	char **dateOfDrawing = new char*[row];
	for (int i = 0; i < row; i++) {
		dateOfDrawing[i] = new char[11];
	}


	//use dataArray
	inputFileObject.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][0]
		getline(inputFileObject, rawData);
		size_t pos1 = rawData.find(" ");
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][0] = numHolder;
	}
	inputFileObject.close();
	inputFileObject.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][1]
		getline(inputFileObject, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ") + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][1] = numHolder;
	}
	inputFileObject.close();
	inputFileObject.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][2]
		getline(inputFileObject, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][2] = numHolder;
	}
	inputFileObject.close();
	inputFileObject.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][3]
		getline(inputFileObject, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][3] = numHolder;
	}
	inputFileObject.close();
	inputFileObject.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][4]
		getline(inputFileObject, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][4] = numHolder;
	}
	inputFileObject.close();
	inputFileObject.open("Lottery.txt");
	for (int i = 0; i < row; i++) { //For dataArray[row][5]
		getline(inputFileObject, rawData);
		size_t pos1 = rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ", rawData.find(" ") + 1) + 1) + 1) + 1) + 1);
		size_t pos2 = rawData.find(" ", pos1 + 1);
		dataHolder = rawData.substr(pos1 + 1, pos2 - (pos1 + 1));
		stringstream convert(dataHolder);
		convert >> numHolder;
		dataArray[i][5] = numHolder;
	}
	inputFileObject.close();
	inputFileObject.open("Lottery.txt");

	// Use dynamic char array to store the file	into array
	for (int i = 0; i < row; i++) {
		getline(inputFileObject, rawData);
		size_t pos1 = 0;
		size_t pos2 = rawData.find(" ");
		dataHolder = rawData.substr(pos1, pos2);
		int size = dataHolder.size();
		for (int j = 0; j < size; j++) {
			dateOfDrawing[i][j] = dataHolder[j];
		}
		for (int j = size; j < 11; j++) {
			dateOfDrawing[i][j] = dataHolder[pos2];
		}
	}
	inputFileObject.close();

	// Display id# followed by information.
	cout << "-------------------------------------------------------------------------------\n";
	cout << "ID#\tDate\t\t\tLottery #s\tPB#\n";
	for (int i = 0; i < row; i++) {
		cout << i+1 << ".\t" << dateOfDrawing[i] << "\t\t";
		for (int j = 0; j < 5; j++) {
			cout << dataArray[i][j] << " ";
		}
		cout << "\t";
		for (int j = 5; j < 6; j++) {
			cout << dataArray[i][j];
		}
		cout << endl;
	}
	cout << row + 1 << ".\tDon't Delete.\n";
	cout << "-------------------------------------------------------------------------------\n";

	cout << "Which entry would you like to delete?\n";
	cin >> idNumber;
	if (idNumber <= row && idNumber > 0) {
		inputFileObject.open("Lottery.txt");
		for (int i = 0; i < idNumber; i++) {
			getline(inputFileObject, rawData);
			dataHolder = rawData;
		}
		inputFileObject.close();
		ofstream temp;
		temp.open("LotteryTemp.txt");
		inputFileObject.open("Lottery.txt");
		while (rawData != "") {
			for (int i = 0; i < row; i++) {
				getline(inputFileObject, rawData);
				if (rawData == dataHolder) {
					cout << "The entry has been removed\n";
				}
				else {
					temp << rawData << endl;
				}
			}
		}
		inputFileObject.close();
		temp.close();
		ifstream inputFileObjectTemp;
		inputFileObjectTemp.open("LotteryTemp.txt");
		inputFileObject.open("Lottery.txt");
		inputFileObject.clear();
		inputFileObject.close();
		ofstream recreateLottery;
		recreateLottery.open("Lottery.txt");
		for (int i = 0; i < row - 1; i++) {
			getline(inputFileObjectTemp, rawData);
			recreateLottery << rawData << endl;
		}
		recreateLottery.close();
		inputFileObject.close();
	}
	else if (idNumber > row + 1 || idNumber <= 0) {
		cout << "That is not a listed entry!\nPlease re-enter the entry you would like to delete: \n";
		cin >> idNumber;
	}
	else {
		cout << "You chose not to delete an entry.\n";
	}


	//deallocate array (relearn this topic in more detail)
	for (int i = 0; i < row; i++)
		delete[] dataArray[i];
	delete[] dataArray;

	//deallocate char array
	for (int i = 0; i < row; i++)
		delete[] dateOfDrawing[i];
	delete[] dateOfDrawing;

	system("cls");
	cout << "If you wish to delete another entry, please enter '1'.\nIf you would like to go back to the main menu, please enter '2'.\nTo exit the program, enter '3'.\n";
	cin >> choice7;

	while (choiceOption == true) {
		switch (choice7) {
		case 1:
			choiceOption = false;
			deleteInfo();
			break;
		case 2:
			choiceOption = false;
			main();
			break;
		case 3:
			choiceOption = false;
			quit();
			break;
		default:
			system("cls");
			cout << "That is not an available option.\n If you wish to delete another entry, please enter '1'.\nIf you would like to go back to the main menu, please enter '2'.\nTo exit the program, enter '3'.\n";
			cin >> choice7;
		}
	}

}
