#include "Test.h"


Test::Test(string category)
{
    this->category = category;
    this->questions = {};
}

void Test::addQuestion(string questionText, vector<string> options, int correctAnswer)
{
	questions.emplace_back(questionText, options, correctAnswer);
}

int Test::evaluateAnswer(vector<int> answers)
{
    int correctCount = 0;
    for (int i = 0; i < answers.size(); ++i) {
        if (i < questions.size() && answers[i] == questions[i].correctAnswer) {
            ++correctCount;
        }
    }
    return correctCount; 
}

double Test::calculateScore(int correctCount)
{
    if (questions.empty()) return 0.0; 
    return (static_cast<double>(correctCount) / questions.size()) * 12;
}

void Test::displayCategories(vector<Test> tests)
{
    for (int i = 0; i < tests.size(); ++i) {
        cout << i + 1 << ": " << tests[i].category << endl << endl;
    }
}

json Test::toJson()
{
    json j;
    j["category"] = category;
    j["questions"] = json::array();
    for (auto question : questions) {
        j["questions"].push_back(question.toJson());
    } 
    return j;
}

Test Test::fromJson(const json& j)
{
    Question q;
    Test test(j.at("category").get<string>());
    for (const auto& questionJson : j.at("questions")) {
        test.questions.push_back(q.fromJson(questionJson));
    }
    return test;
}

