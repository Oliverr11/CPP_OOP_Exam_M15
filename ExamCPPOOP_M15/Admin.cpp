#include "Admin.h"

bool Admin::Login(string loginId, string loginpassword)
{
    ifstream inputFile(adminFile);
    if (!inputFile.is_open()) {
        cout << "Error opening file." << std::endl;
        return false;
    }
    else {
        json accountData;
        inputFile >> accountData;
        inputFile.close();

        string storedUsername = accountData["id"];
        string storedPassword = accountData["password"];
        return (loginId == storedUsername && loginpassword == storedPassword);
    }
}

void Admin::CreateAccount(string RegisterID, string RegisterPassword, string fullname, string address, string phone)
{
    student.Register(RegisterID, RegisterPassword, fullname, address, phone); 
}

void Admin::DeleteAccount(string userName)
{
    if (student.DeleteStudent(userName)) {
        if (DeleteExamRecords(userName)) {
            cout << "\nAccount and exam records deleted successfully!" << endl;
        }
        else {
            cout << "\nAccount deleted, but failed to delete exam records." << endl;
        }
    }
    else {
        cout << "\nError: Account deletion failed. User may not exist." << endl;
    }
}

bool Admin::DeleteExamRecords(string username)
{
    ifstream resultFile(fm.resultsFile);
    if (!resultFile.is_open()) {
        cout << "Error opening exam_results.json!" << endl;
        return false;
    }

    json results;
    resultFile >> results;
    resultFile.close();

    json updatedResults;
    bool recordsDeleted = false;

    for (const auto& record : results) {
        if (record["name"] != username) { 
            updatedResults.push_back(record);
        }
        else {
            recordsDeleted = true; 
        }
    }

    ofstream outFile(fm.resultsFile);
    if (outFile.is_open()) {
        outFile << updatedResults.dump(4);
        outFile.close();
        return recordsDeleted; 
    }
    else {
        cout << "Error: Unable to open file for writing..." << endl;
        return false;
    }
}

void Admin::ChangeUserInformation(string userName)
{
    if (!student.UserExists(userName)) {
        cout << "Error: User does not exist." << endl;
        cout << "# Press Enter To Continue..."; getchar(); system("cls");

        return;
    }
    for (const auto& user : student.users) { 
        if (user.fullName == userName) {
            oldName = user.fullName;
            oldId = user.RegisterID;
            break;
        }
    }

    int choice;
    cout << "\n=================================================" << endl;
    cout << "\n1) Change ID" << endl;
    cout << "\n2) Change Password" << endl;
    cout << "\n3) Change Full Name" << endl;
    cout << "\n4) Change Address" << endl;
    cout << "\n5) Change Phone" << endl;
    cout << "\n6) Back" << endl;
    cout << "\n=================================================" << endl;
    cout << "\nEnter your choice: ";
    cin >> choice; cin.ignore();

    switch (choice) {
    case 1: {
        string newID;
        cout << "\nEnter new Register ID: ";
        getline(cin, newID);
        if (newID.empty() || all_of(newID.begin(), newID.end(), isspace)) {
            cout << "Error : ID cannot be empty." << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        else {
            student.UpdateUserID(userName, newID);
            UpdateExamRecords(oldId, newID, oldName, oldName);
            cout << "User ID updated successfully!" << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        break;
    }
    case 2: {
        string newPassword;
        cout << "\nEnter new password: ";
        getline(cin, newPassword);
        if (newPassword.empty() || all_of(newPassword.begin(), newPassword.end(), isspace)) {
            cout << "Error : Password cannot be empty." << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");
        }
        else {
            student.UpdateUserPassword(userName, newPassword);
            cout << "Password updated successfully!" << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");
        }
        break;
    }
    case 3: {
        string newFullName;
        cout << "\nEnter new full name: ";
        getline(cin, newFullName);

        if (newFullName.empty() || all_of(newFullName.begin(), newFullName.end(), isspace)) {
            cout << "Error: Full name cannot be empty." << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        else {
            student.UpdateUserFullName(userName, newFullName);
            UpdateExamRecords(oldId, oldId, oldName, newFullName);
            cout << "\nFull name updated successfully!" << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        break;
    }
    case 4: {
        string newAddress;
        cout << "\nEnter new address: ";
        getline(cin, newAddress);
        if (newAddress.empty() || all_of(newAddress.begin(), newAddress.end(), isspace)) {
            cout << "Error : Address cannot be empty." << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        else {
            student.UpdateUserAddress(userName, newAddress);
            cout << "Address updated successfully!" << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        break;
    }
    case 5: {
        string newPhone;
        cout << "\nEnter new phone number: ";
        getline(cin, newPhone);
        if(newPhone.empty() || all_of(newPhone.begin(), newPhone.end(), isspace)){
            cout << "Error : Phone cannot be empty." << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        else {
            student.UpdateUserPhone(userName, newPhone);
            cout << "Phone number updated successfully!" << endl;
            cout << "# Press Enter To Continue..."; getchar(); system("cls");

        }
        break;
    }
    case 6:
        cout << "# Press Enter To Continue..."; getchar(); system("cls");

        return;
    default:
        cout << "Invalid option. Please try again." << endl;
        cout << "# Press Enter To Continue..."; getchar(); system("cls");
        ChangeUserInformation(userName);
        break;
    }
}

void Admin::UpdateExamRecords(string oldID, string newID, string oldName, string newName)
{
    ifstream resultFile(fm.resultsFile);
    if (!resultFile.is_open()) {
        cout << "Error opening exam_results.json!" << endl;
        return;
    }

    json results;
    resultFile >> results;
    resultFile.close();

    bool updated = false;

    for (auto& record : results) {
        if (record["id"] == oldID) {
            record["id"] = newID; 
            updated = true;
        }
        if (record["name"] == oldName) {
            record["name"] = newName; 
            updated = true;
        }
    }

    if (updated) {
        ofstream outFile("exam_results.json");
        if (outFile.is_open()) {
            outFile << results.dump(4); 
            outFile.close();
        }
        else {
            cout << "Error: Unable to open file for writing..." << endl;
        }
    }
}

void Admin::ViewStatistics(string studentName) {
    student.ViewStatistics(studentName);
}

void Admin::addCategory(string category)
{

    Test newTest(category);
    newTest.questions = {};
    tests.push_back(newTest);   
    fm.saveTests(tests,fileName);
}

void Admin::AddQuestionCategory() {

    cout << "==================== Add Questions ====================" << endl << endl;

    displayCategories();

    cout << "=======================================================" << endl << endl;

    int testIndex;
    cout << "Enter number to choose category (press 0 to exit): ";

    while (true) {
        string input;
        getline(cin, input); 
        if (input.empty() || all_of(input.begin(), input.end(), ::isspace)) {
            cout << "Error: Input cannot be empty." << endl;
            cout << "Enter number to choose category: ";
            continue;
        }
        if (input == "0") {
            system("cls");
            return;
        }
        try {
            testIndex = stoi(input) - 1; 
            if (testIndex < 0 || testIndex >= tests.size()) {
                cout << "Error: Invalid test index. Please enter a valid index." << endl;
                cout << "Enter number to choose category: ";
            }
            else {
                break; 
            }
        }
        catch (invalid_argument e) {
            cout << "Error : " << e.what() << endl;
            cout << "Enter number to choose category: ";
        }
    }

    string questionText;
    vector<string> options;
    string option;
    int correctAnswer;

    cout << "\nEnter question text: ";
    getline(cin, questionText);

    cout << "\nEnter the number of options: ";
    int numOptions;
    while (true) {
        cin >> numOptions;
        if (cin.fail() || numOptions < 2) {
            cin.clear(); cin.ignore();
            cerr << "Error: At least two options are required." << endl;
            cout << "Enter the number of options: ";
        } else {
            break;
        }
    }

    cout << "\nEnter the options:" << endl;
    for (int i = 0; i < numOptions; ++i) {
        cout << "Option " << i + 1 << ": ";
        cin >> option;

        if (option.empty()) {
            cerr << "Error: Option cannot be empty." << endl;
            return;
        }
        
        options.push_back(option);
    }

    cout << "\nEnter number of correct answer : ";
    while (true) {
        cin >> correctAnswer;
        correctAnswer --;
        if (cin.fail() || correctAnswer < 0 || correctAnswer >= numOptions) {
            cin.clear(); cin.ignore();
            cout << "Error: Correct answer index is out of range. Please enter a valid index." << endl;
            cout << "\nEnter the number of options: ";
        } else {
            break;
        }
    }

    Question newQuestion;
    newQuestion.questionText = questionText;
    newQuestion.options = options;
    newQuestion.correctAnswer = correctAnswer;

    tests[testIndex].questions.push_back(newQuestion);

    cout << "\nQuestion added successfully!" << endl;

    cout << "\n=======================================================" << endl << endl;
    cout << "# Press Enter To Continue..." << endl;
    json j;
    for (const auto& test : tests) {
        json testJson;
        testJson["category"] = test.category;
        testJson["questions"] = json::array();

        for (const auto& question : test.questions) {
            json questionJson;
            questionJson["questionText"] = question.questionText;
            questionJson["options"] = question.options;
            questionJson["correctAnswer"] = question.correctAnswer;

            testJson["questions"].push_back(questionJson);
        }
        j.push_back(testJson);
    }
    getchar(); getchar(); system("cls");
    ofstream outFile("tests.json");
    outFile << j.dump(4); 
    outFile.close();
}

void Admin::deleteCategory(int testIndex)
{
    if (testIndex < 0 || testIndex >= tests.size()) {
        cerr << "Error: Invalid test index." << endl;
        return;
    }

    try {
        if (testIndex < 0 || testIndex >= tests.size()) {
            throw out_of_range("Test index is out of range.");
        }
        tests.erase(tests.begin() + testIndex);
        fm.saveTests(tests, fileName);
        cout << "\nCategory deleted successfully!" << endl << endl;

    }
    catch (const out_of_range& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

void Admin::deleteQuestionFromCategory() {
    int testIndex, questionIndex;
    cout << "==================== Delete Questions ====================" << endl << endl;

    displayCategories();

    cout << "==========================================================" << endl << endl;

    while (true) {
        try {
            cout << "Enter number to choose category (or 0 to go back): ";
            cin >> testIndex;

            if (cin.fail()) {
                cin.clear(); cin.ignore();
                throw invalid_argument("Invalid input. Please enter a valid integer.");

            }

            if (testIndex == 0) {
                cout << "Going back..." << endl;
                return;
            }

            testIndex--; 
            if (testIndex < 0 || testIndex >= tests.size()) {
                throw invalid_argument("Error: Invalid test index.");

            }
            break; 
        }
        catch (invalid_argument e) {
            cout << "Error: " << e.what() << endl;

        }
    }

    cout << "\nQuestions in category \"" << tests[testIndex].category << "\":" << endl;
    for (int i = 0; i < tests[testIndex].questions.size(); ++i) {
        cout << i + 1 << ": " << tests[testIndex].questions[i].questionText << endl;
    }
    while (true) {
        try {
            cout << "Enter number to delete question (or 0 to go back): ";
            cin >> questionIndex;

            if (cin.fail()) {
                cin.clear(); cin.ignore();
                throw invalid_argument("Invalid input. Please enter a valid integer.");
            }

            if (questionIndex == 0) {
                cout << "Going back..." << endl;
                return;
            }

            questionIndex--;
            if (questionIndex < 0 || questionIndex >= tests[testIndex].questions.size()) {
                throw invalid_argument("Error: Invalid question index.");
            }
        }
        catch (invalid_argument e) {
            cout << "Error: " << e.what() << endl;

        }
    }
    tests[testIndex].questions.erase(tests[testIndex].questions.begin() + questionIndex);
    fm.saveTests(tests, fileName); 

    cout << "Question deleted successfully!" << endl;
}

void Admin::displayCategories()
{
    Test test;
    test.displayCategories(tests);
}

//void Admin::addExamRecord(string studentId, string category, string name, int score)
//{
//    ExamRecord newRecord(studentId, category, name, score); 
//    vector<ExamRecord> records;
//    fm.LoadExamRecord(records); 
//    records.push_back(newRecord); 
//    fm.SaveExamRecord(records); 
//    cout << "Exam record added for " << name << " with score: " << score << endl;
//}

void Admin::loadExamRecords(vector<ExamRecord>& records)
{
    fm.LoadExamRecord(records);
    cout << "Exam records loaded." << endl;
}

//
//json Admin::toJson()
//{
//    json j;
//    for (auto& test : tests) {
//        j.push_back(test.toJson());
//    }
//    return j;
//}
//
//void Admin::fromjson(json j)
//{
//    Test t;
//    for (auto cateJson : j) {
//        tests.push_back(t.fromJson(cateJson));
//    }
//}
//
