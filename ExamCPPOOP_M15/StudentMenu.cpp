#include "StudentMenu.h"

void StudentMenu::DisplayMenu()
{
    cout << "============ WELCOME TO IT STEP-ACADEMY ============" << endl;
    cout << "\n1 ) Register " << endl;
    cout << "\n2 ) Login " << endl;
    cout << "\n3 ) Exit" << endl;
    cout << "\n==================================================" << endl;

    char opt;
    
    cout << "\nEnter Option : "; cin >> opt;     cin.ignore();

    switch (opt)
    {
    case '1':
        Register();
        break;
    case '2':
        Login();
        break;
    case '3':
        break;
    default:
        system("cls");
        DisplayMenu();
        break;
    }
}

void StudentMenu::ExamMenu() {
    bool menu = true;
    while (menu) {
        cout << "================= IT-STEP Exam =================" << endl;
        cout << "\n1 ) View Categories" << endl;
        cout << "\n2 ) Take a Test" << endl;
        cout << "\n3 ) View Exam Results" << endl;
        cout << "\n4 ) My Information" << endl;
        cout << "\n5 ) Exit" << endl;
        cout << "\n===============================================" << endl;

        int opt;
        cout << "Enter Option: ";

        while (!(cin >> opt)) {
            cout << "Invalid input. Please enter a number: ";
            cin.clear(); 
            cin.ignore();
        }

        switch (opt) {
        case 1:
            ViewCategories();
            break;
        case 2:
            TakeExam();
            break;
        case 3:
            ViewExamResults();
            break;
        case 4:
            ViewStudentInformation();
            break;
        case 5:
            cout << "\nExiting..." << endl;
            menu = false;
            break;
        default:
            system("cls");
            cout << "Invalid option. Please try again." << endl;
            break; 
        }
    }
}

void StudentMenu::TakeExam() {
    system("cls");
    string category;
    cout << "=================== Exam =================== " << endl;
    getchar();
    while (true) {
        cout << "\nEnter the exam category you want to take: ";
        getline(cin, category);

        if (category.empty() || category.find(' ') != string::npos) {
            cout << "Category cannot be empty or contain spaces. Please try again." << endl;
        }
        else {
            break; 
        }
    }

    student.TakeExam(category);

    cout << "\n============================================ " << endl;
    cout << "# Press Enter To Continue..." << endl;
     getchar(); system("cls");
    ExamMenu();
}

void StudentMenu::ViewCategories()
{
    system("cls");
    cout << "================= View Categories =================" << endl << endl;
    student.ViewCategories();
    cout << "\n\n===================================================" << endl << endl;
    cout << "# Press Enter To Continue..." << endl;
    getchar(); getchar(); system("cls");
    ExamMenu();
}

void StudentMenu::ViewExamResults()
{
    system("cls");
    cout << "================ "<< student.fullName<<"'s Exam Results ================" << endl << endl;

    student.ViewStatistics(student.fullName);
    cout << "\n=============================================================" << endl << endl;
    cout << "# Press Enter To Continue..." << endl;
    getchar();  getchar(); system("cls");
    ExamMenu();
}

void StudentMenu::ViewStudentInformation()
{
    system("cls");
    cout << "===================== My Information =====================";
    student.ViewStudentInformation();
    cout << "\n==========================================================" << endl;
    cout << "# Press Enter To Continue..." << endl;
    getchar(); getchar();system("cls");
    ExamMenu();
}

void StudentMenu::Register() {
    system("cls");
    cout << "================= Registering =================" << endl;

    string fullName, address, phone, loginId, password;

    while (true) {
        cout << "\nEnter Full Name: ";
        getline(cin, fullName);
        if (!fullName.empty() && fullName.find_first_not_of(' ') != string::npos) break;
        cout << "Full Name cannot be empty or consist only of spaces. Please try again." << endl;
    }

    while (true) {
        cout << "\nEnter Address: ";
        getline(cin, address);
        if (!address.empty() && address.find_first_not_of(' ') != string::npos) break;
        cout << "Address cannot be empty or consist only of spaces. Please try again." << endl;
    }

    while (true) {
        cout << "\nEnter Phone Number: ";
        getline(cin, phone);
        if (!phone.empty() && phone.find_first_not_of(' ') != string::npos) break;
        cout << "Phone Number cannot be empty or consist only of spaces. Please try again." << endl;
    }

    while (true) {
        cout << "\nEnter Your Login ID: ";
        getline(cin, loginId);
        if (loginId.empty()) {
            cout << "Login ID cannot be empty." << endl;
        }
        else if (loginId.find(' ') != string::npos) {
            cout << "Login ID cannot contain spaces." << endl;
        }
        else if (loginId.find_first_not_of(' ') == string::npos) {
            cout << "Login ID cannot consist only of spaces." << endl;
        }
        else {
            break; 
        }
    }

    while (true) {
        cout << "\nEnter Your Password: ";
        cin >> password;
        if (!password.empty() && password.find_first_not_of(' ') != string::npos) break;
        cout << "Password cannot be empty or consist only of spaces. Please try again." << endl;
    }

    try {
        student.Register(loginId, password, fullName, address, phone);
        cout << "Registration successful!" << endl;

    }
    catch (exception e) {
        cout << "Registration failed: " << e.what() << endl;
    }

    DisplayMenu();;
}

bool StudentMenu::Login()
{
    system("cls");
    cout << "====================== Login ======================" << endl;

    cout << "\nEnter Your ID : "; cin >> loginId;
    cout << "\nEnter Your Password : "; cin >> password;
    cout << "\n===================================================" << endl;

    if (!student.Login(loginId, password)) {
        cout << "Login successfully. " << endl;
        cout << "\n# Press Enter To Continue..." << endl;
        getchar(); getchar(); system("cls");
        ExamMenu();
        return true;
    }
    else if (student.Login(loginId,password)) {
        cout << "Login Unsuccessful" << endl;
        cout << "# Press Enter To Continue..." << endl;
        getchar(); getchar(); system("cls");
        DisplayMenu();
        return false;
    }
}
