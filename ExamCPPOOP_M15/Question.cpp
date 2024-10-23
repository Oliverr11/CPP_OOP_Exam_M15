#include "Question.h"

Question::Question(string questionText, vector<string> opts, int answer)
{
	this->questionText = questionText;
	this->options = opts;
	this->correctAnswer = answer;
}

json Question::toJson()
{
	return json{
		{"questionText",questionText},
		{"options",options},
		{"correctAnswer",correctAnswer}
	};
}

Question Question::fromJson(json j)
{

	return Question{
		   j.at("questionText").get<string>(),
		   j.at("options").get<vector<string>>(),
		   j.at("correctAnswer").get<int>()
	};
}
