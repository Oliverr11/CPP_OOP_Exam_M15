#include "ExamRecord.h"

ExamRecord::ExamRecord(string id, string category, string studentName,  int score, int totalQuestions, string status)
{
	this->studentID = id;
    this->studentName = studentName;
	this->category = category;
	this->score = score;
    this->totalQuestions = totalQuestions;
    this->status = status;
}

json ExamRecord::toJson()
{
    return {
             {"category", category},
             {"id", studentID},
             {"name", studentName},
             {"score", score},
             {"totalQuestions",totalQuestions},
             {"status",status}
    };
}

ExamRecord ExamRecord::fromJson(json j)
{
    ExamRecord record;
    record.category = j["category"];
    record.studentID = j["id"];
    record.studentName = j["name"];
    record.score = j["score"];
    record.totalQuestions = j["totalQuestions"];
    record.status = j["status"];
    return record;
}
