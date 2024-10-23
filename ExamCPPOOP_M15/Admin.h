#pragma once
#include <iostream>
#include <fstream>
#include "Test.h"
#include <sstream> 
#include "Student.h"
#include "User.h"
#include "FileManager.h"
using namespace std;
class Admin
{
public : 

	vector<Test> tests;
	string fileName = "tests.json";
	string adminFile = "admin.json";
	string oldName;
	string oldId;

	bool Login(string loginId, string loginpassword);

	FileManager fm;
	Student student;
	Admin() {
		fm.loadTests(tests,fileName);
	}

	//modify user
	void CreateAccount(string RegisterID, string RegisterPassword, string fullname, string address, string phone);
	void DeleteAccount(string userName);
	bool DeleteExamRecords(string username);
	void ChangeUserInformation(string userName);

	void UpdateExamRecords(string oldID, string newID, string oldName, string newName);
	
	void ViewStatistics(string studentName);

	void addCategory(string category);
	void AddQuestionCategory();
	void deleteCategory(int testIndex);
	void deleteQuestionFromCategory();

	void displayCategories();

	void addExamRecord(string studentId,string category, string name, int score);
	void loadExamRecords(vector<ExamRecord>& records);

	//json toJson();
	//void fromjson(json j);
};

