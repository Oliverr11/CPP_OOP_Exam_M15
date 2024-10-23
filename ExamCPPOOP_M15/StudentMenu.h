#pragma once
#include <iostream>
#include "Student.h"
#include <random>
#include <filesystem>

using namespace std;
class StudentMenu
{
public : 
	Student student;
	string selectedCategory;
	string loginId, password, name;

	StudentMenu() {
		student.Load();
	}
	void DisplayMenu();
	void ExamMenu();

	void TakeExam();
	void ViewCategories();
	void ViewExamResults();

	void Register();
	bool Login();
};

