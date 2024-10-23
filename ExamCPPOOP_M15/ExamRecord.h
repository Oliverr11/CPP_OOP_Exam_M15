#pragma once
#include <iostream>
#include <vector>
#include "json.hpp" 
#include <fstream>
using json = nlohmann::json;
using namespace std;
class ExamRecord
{
public : 
	string studentID;
	string studentName; 
	string category;
	int score;
	int totalQuestions;
	string status;
	ExamRecord() = default;
	ExamRecord(string id, string category, string studentName, int score, int totalQuestions, string status);

	json toJson();
	ExamRecord fromJson(json j);
};

