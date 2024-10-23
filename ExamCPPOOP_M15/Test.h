#pragma once
#include <iostream>
#include "Question.h"

using namespace std;
class Test
{
public : 
	string category;            

	vector<Question> questions; 
	Test(string category);
	Test() = default;
	void addQuestion(string questionText, vector<string> options , int correctAnswer);
	int evaluateAnswer(vector<int> answers);
	double calculateScore(int correctCount);

	void displayCategories(vector<Test> tests);

	json toJson();
	Test fromJson(const json& j);
};

