#include "Student.h"
#include <random>

void Student::Register(string RegisterID, string RegisterPassword, string fullname, string address, string phone)
{
	
	User* user = FindDiplicateName(fullname);
	if (user == nullptr) {
		users.push_back(User(RegisterID, RegisterPassword, fullname, address, phone));
		cout << "\nRegister Successfully!\n" << endl;
        cout << "# Press Enter To Continue..." << endl;
        getchar(); system("cls");
		Save();
	}
	else {
		cout << "\nAccount already Exist!\n" << endl;
	}
}

bool Student::Login(string LoginId, string LoginPassword)
{
	User* user = FindUserToLogin(LoginId, LoginPassword);
	if (user == nullptr) {
		return true; 
	}
    RegisterID = user->RegisterID; 
    fullName = user->fullName;      
	return false; 
}

bool Student::DeleteStudent(string username)
{
	for (auto it = users.begin(); it != users.end(); it++) {
		if (it->fullName == username) {
			users.erase(it);
			Save(); 
			return true; 
		}
	}
	return false; 
}

void Student::UpdateUserID(string username, string newID)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.RegisterID = newID; 
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserPassword(string username, string newPassword)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.RegisterPassword = newPassword;    
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserFullName(string username, string newFullName)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.fullName = newFullName; 
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserAddress(string username, string newAddress)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.address = newAddress; 
			Save(); 
			return;
		}
	}
}

void Student::UpdateUserPhone(string username, string newPhone)
{
	for (auto& user : users) {
		if (user.fullName == username) {
			user.phone = newPhone;  
			Save(); 
			return;
		}
	}
}

void Student::TakeExam(string category) {
    ifstream file(filemanager.testsFile);
    if (!file.is_open()) {
        cout << "Error opening tests.json!" << endl;
        return;
    }

    json tests;
    file >> tests;

    json selectedCategory;
    bool categoryFound = false;

    for (auto& test : tests) {
        if (test["category"] == category) {
            selectedCategory = test["questions"];
            categoryFound = true;
            break;
        }
    }

    if (!categoryFound) {
        cout << "Category not found." << endl;
        return;
    }

    int score = 0;
    vector<int> askedQuestions;
    int currentIndex = 0;

    // Load previous state if it exists
    ifstream stateFile("exam_state.json");
    if (stateFile.is_open()) {
        json state;
        stateFile >> state;
        score = state["score"].get<int>();
        if (state.contains("askedQuestions")) {
            askedQuestions = state["askedQuestions"].get<vector<int>>();
        }
        stateFile.close();
    }

    // Collect all question indices, excluding already asked questions
    vector<int> questionIndices;
    for (int i = 0; i < selectedCategory.size(); ++i) {
        if (find(askedQuestions.begin(), askedQuestions.end(), i) == askedQuestions.end()) {
            questionIndices.push_back(i);
        }
    }

    // Shuffle available questions
    random_device rd;
    mt19937 g(rd());
    shuffle(questionIndices.begin(), questionIndices.end(), g);

    // Determine how many questions can still be asked
    int maxQuestions = 12;
    int questionsLeft = maxQuestions - askedQuestions.size();

    // Ask questions until reaching the limit
    for (int i = 0; i < std::min(questionsLeft, static_cast<int>(questionIndices.size())); ++i) {
        const json& question = selectedCategory[questionIndices[i]];

        cout << "\n" << askedQuestions.size() + 1 << " ) " << question["questionText"] << endl;

        for (int j = 0; j < question["options"].size(); ++j) {
            cout << j + 1 << ". " << question["options"][j] << endl;
        }

        cout << "Enter your answer (1-" << question["options"].size() << "): ";

        int answer;
        while (true) {
            string input;
            getline(cin, input); 

            if (input.empty() || input.find(' ') != string::npos) {
                cout << "Invalid input! Please enter a number between 1 and " << question["options"].size() << " (no spaces allowed): ";
                continue; 
            }

            try {
                answer = stoi(input); 
                if (answer < 1 || answer > question["options"].size()) {
                    cout << "Invalid answer! Please enter a number between 1 and " << question["options"].size() << ": ";
                }
                else {
                    break; 
                }
            }
            catch (invalid_argument) {
                cout << "Invalid input! Please enter a valid number between 1 and " << question["options"].size() << ": ";
            }
        }


        if (answer < 1 || answer > question["options"].size()) {
            cout << "Invalid answer! Please enter a number between 1 and " << question["options"].size() << "." << endl;
            --i; // Repeat this question
            continue;
        }

        int correctIndex = question["correctAnswer"].get<int>();
        if (answer - 1 == correctIndex) {
            cout << "Correct!" << endl;
            score++;
        }
        else {
            cout << "Incorrect! The correct answer was: " << question["options"][correctIndex] << endl;
        }

        // Save state after each question
        askedQuestions.push_back(questionIndices[i]); // Track this question as asked
        json state;
        state["score"] = score;
        state["askedQuestions"] = askedQuestions;

        ofstream stateOut("exam_state.json");
        if (stateOut.is_open()) {
            stateOut << state.dump(4);
            stateOut.close();
        }
        else {
            cout << "Error saving exam state." << endl;
        }
    }

    cout << "\nExam completed! You scored " << score << " out of " << askedQuestions.size() << "." << endl;

    // Store the exam result
    ExamRecord record;
    record.studentID = this->RegisterID;
    record.category = category;
    record.studentName = this->fullName;
    record.score = score;
    record.totalQuestions = askedQuestions.size(); // Store total questions asked
    record.status = (score < 5) ? "Fail" : "Pass";

    // Load existing records
    ifstream resultFile("exam_results.json");
    json results;

    if (resultFile.is_open()) {
        resultFile >> results;
        resultFile.close();
    }

    results.push_back(record.toJson());

    ofstream outFile(filemanager.resultsFile);
    if (outFile.is_open()) {
        outFile << results.dump(4);
        outFile.close();
    }
    else {
        cout << "Error: Unable to open file for writing..." << endl;
    }

    // Clear state file if exam completed
    remove("exam_state.json");
}

void Student::ViewStatistics(string studentName) {
    vector<ExamRecord> records;
    filemanager.LoadExamRecord(records);

    if (records.empty()) {
        cout << "No exam records available." << endl;
        return;
    }

    int count = 0;
    int highestScore = -1;
    int lowestScore = 101;
    double totalScore = 0;
    int passCount = 0;
    int failCount = 0;


    int index = 1;
    for (const ExamRecord& record : records) {

        if (record.studentName == studentName) {
            cout << index++ << " ) Category: " << record.category << ", Score: " << record.score << endl;
            totalScore += record.score;
            count++;

            // Update highest score
            if (record.score > highestScore) {
                highestScore = record.score;
            }

            // Update lowest score
            if (record.score < lowestScore) {
                lowestScore = record.score;
            }

            // Count pass and fail
            if (record.score >= 5) {
                passCount++;
            }
            else {
                failCount++;
            }
        }
    }

    if (count > 0) {
        double averageScore = totalScore / count;

        cout << "\n\n=============================================================" << endl << endl;


        cout << "Statistics for student " << studentName << " : " << endl;
        cout << " \n->> Highest Score: " << highestScore << endl;
        cout << " \n->> Lowest Score: " << (lowestScore == 101 ? 0 : lowestScore) << endl; // Handle case when no scores were found
        cout << " \n->> Average Score: " << averageScore << endl;
        cout << " \n->> Number of Records: " << count << endl;
        cout << " \n->> Pass Count: " << passCount << endl;
        cout << " \n->> Fail Count: " << failCount << endl;

    }
    else {
        cout << "No records found for student: " << studentName << endl;
    }
}

void Student::ViewCategories()
{

    ifstream file(filemanager.testsFile);
    if (!file.is_open()) {
        cout << "Error opening tests.json!" << endl;
        return;
    }

    json tests;
    file >> tests;

    cout << "Number of Available Categories: " << tests.size() << endl;

    cout << "\nAvailable Categories:" << endl;
    for (auto item : tests) {
        cout << "\n- " << item["category"] << endl;
    }
}

bool Student::UserExists(string username)
{
	for (const auto& user : users) {
		if (user.fullName == username) { 
			return true; // User exists
		}
	}
	return false; // User not found
}

void Student::Save()
{
	json contentJson = json::array();
	for (auto user : users) {
		contentJson.push_back(user.ConvertToJson());
	}
	filemanager.SaveUserInformationDataJson(contentJson);
}

void Student::Load()
{
	users.clear(); // for clear old user file 
    json contentJson = filemanager.LoadUserInformationDataJson();
    for (auto& j : contentJson) {
        User user;
        user.FromJson(j);
        users.push_back(user);
    }
} 

User* Student::FindDiplicateName(string fullname)
{
	for (auto& account : users) {
		if (account.fullName == fullname) {
			return &account;
		}
	}
	return nullptr;
}

User* Student::FindUserToLogin(string LoginId, string LoginPassword)
{
	for (auto& account : users) {
		if (account.RegisterID == LoginId && account.RegisterPassword == LoginPassword) {
			
			return &account;
		}
	}
	return nullptr;
}



