#include "AdminMenu.h"

void AdminMenu::MainMenu() {
    system("cls");
    cout << "================== WELCOME ==================\n";
    cout << "\n1 ) Modify User \n"; // can create account, delete account, change information and password
    cout << "\n2 ) View Statistics\n";
    cout << "\n3 ) Manage Test\n\n";
    cout << "=============================================\n";

    string input; 
    int opt;

        cout << "\nEnter Option: ";
        getline(cin, input); 
        system("cls");
            if (input.length() > 1) {
                throw invalid_argument("Invalid input. Please enter a single valid integer.");
            }

            // string -> int 
            opt = stoi(input);

            switch (opt) {
            case 1:
                system("cls");
                ModifyUserMenu();   
                break;
            case 2:
                system("cls");
                ViewStatistics();
                break;
            case 3:
                system("cls");
                ManageTestMenu();
                break;
            default:
                cout << "Error: Invalid option. Please try again." << endl;
                break; 
            }
        
       
    
}

void AdminMenu::ModifyUserMenu() {
    system("cls");

    cout << "================== MODIFY USER ==================\n";
    
    cout << "\n1 ) Create Account\n";
    cout << "\n2 ) Delete Account\n";
    cout << "\n3 ) Change Information\n";
    cout << "\n4 ) Back\n\n";
    cout << "=================================================\n";

    string input; 
    int opt;

    while (true) {
        cout << "Enter Option: ";
        getline(cin, input); 

        try {
            if (input.length() > 1) {
                throw invalid_argument("Invalid input. Please enter a single valid integer .");
            }

            opt = stoi(input);

            switch (opt) {
            case 1:
                system("cls");

                CreateAccount();
                break;
            case 2:
                system("cls");

                DeleteAccount();
                break;
            case 3:
                system("cls");

                ChangeUserInformation();
                break;
            case 4:
                system("cls");

                MainMenu(); 
                system("cls");
                break;
            default:
                cout << "Error: Invalid option. Please try again." << endl;
                system("cls");
                break; 
            }
        }
        catch (invalid_argument e) {
            cout << "Error: " << e.what() << endl;
        }
    }
}


void AdminMenu::ViewStatistics()
{
    cout << "================== View Statistics ==================" << endl << endl;
    string studentName;
    cout << "Enter Student's full name: ";
    getline(cin, studentName); 
    cout << "-> " << endl;
    admin.ViewStatistics(studentName);
    cout << "=====================================================" << endl;
    cout << "# Press enter to continue." << endl;
    getchar(); system("cls");
    MainMenu();
}


void AdminMenu::ManageTestMenu() {
    system("cls");
    cout << "==================== Mange Test ====================" << endl;
    cout << "\n1 ) Add Category" << endl;
    cout << "\n2 ) Add Questions to category" << endl;
    cout << "\n3 ) Delete Category" << endl;
    cout << "\n4 ) Delete Questions from category" << endl;
    cout << "\n5 ) Display Category" << endl;
    cout << "\n6 ) Back" << endl;
    cout << "\n=====================================================" << endl;

    string input;
    int opt;

        cout << "Enter Option: ";
    while (true) {
        getline(cin, input); 
        try {
            if (input.length() > 1) {
                throw invalid_argument("Invalid input. Please enter a single valid integer.");
            }
            opt = stoi(input);
            switch (opt) {
            case 1:
                system("cls");

                AddCategory();
                break;
            case 2:
                system("cls");

                AddQuestionCategory();
                break;
            case 3:
                system("cls");

                DeleteCategory();
                break;
            case 4:
                system("cls");

                DeleteQuestionFromCategory();
                break;
            case 5:
                system("cls");

                displayCategories();
                break;
            case 6:
                system("cls");

                MainMenu();
                break;
            default:
                cout << "Error: Invalid option. Please try again." << endl;
                break;
            }
        }
        catch (invalid_argument e) {
            if(!input.empty())
            cout << "Error: " << e.what() << endl;
        }
    }
}

void AdminMenu::CreateAccount()
{
    system("cls");
    string RegisterID, RegisterPassword, fullname, address, phone;
    cout << "================= Create Account =================" << endl;

       try {
           cout << "\nEnter Register ID : ";
           getline(cin, RegisterID);
        if (RegisterID.empty() || RegisterID.find(' ') != string::npos) {
            throw invalid_argument("Register ID cannot be empty or contain spaces.");
        }

            cout << "\nEnter Register Password: ";
            getline(cin, RegisterPassword);
        if (RegisterPassword.empty()) {
            throw invalid_argument("Register Password cannot be empty.");
        }

            cout << "\nEnter Full Name: ";
            getline(cin, fullname);
        if (fullname.empty()) {
            throw invalid_argument("Full Name cannot be empty.");
        }

            cout << "\nEnter Address: ";
            getline(cin, address);
        if (address.empty()) {
            throw invalid_argument("Address cannot be empty.");
        }

            cout << "\nEnter Phone: ";
            getline(cin, phone);
        if (phone.empty()) {
            throw invalid_argument("Phone cannot be empty.");
        }

            admin.CreateAccount(RegisterID, RegisterPassword, fullname, address, phone); 
       cout << "=================================================" << endl;

            cout << "#Press Enter To Continue..." << endl;
            getchar(); system("cls");
    } catch (exception e) {
            cout << "Error: " << e.what() << endl;
            ModifyUserMenu(); 
    }
    ModifyUserMenu();
}

void AdminMenu::DeleteAccount()
{
    system("cls");
    string username;
    cout << "================= Delete Account =================" << endl;

    cout << "\nEnter username to delete: ";
    getline(cin, username); 
    admin.DeleteAccount(username);
    cout << "==================================================" << endl;
    cout << "# Press Enter To Continue..." << endl;
    getchar(); system("cls");
    MainMenu();
}


void AdminMenu::ChangeUserInformation()
{
    system("cls");
    cout << "============ CHANGE USER INFORMATION ============" << endl;

    string username;
    cout << "\nEnter username to modify: ";
    getline(cin, username);
    admin.ChangeUserInformation(username);
    MainMenu();
}

void AdminMenu::AddCategory() {
    cout << "==================== Add Categories ====================" << endl << endl;

    string category;
    cout << "Enter Category name (press 0 to exit ): ";
    getline(cin, category);
    if (category != "0") {
        try {
            if (category.empty() || all_of(category.begin(), category.end(), isspace)) {
                throw invalid_argument("Category cannot be empty");
            }

            admin.addCategory(category);
            cout << "\nCategory name: " << category << " added successfully!" << endl << endl;
            cout << "=====================================================" << endl << endl;
            cout << "# Press Enter To Continue..." << endl; getchar(); system("cls");
            ManageTestMenu();
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
            AddCategory();
        }
    }
    ManageTestMenu();
}

void AdminMenu::AddQuestionCategory()
{
   admin.AddQuestionCategory();
    ManageTestMenu();
}

void AdminMenu::DeleteCategory()
{
    cout << "==================== Delete Categories ====================" << endl << endl;

    int index = -1;
    admin.displayCategories();
    cout << "===========================================================" << endl << endl;

    while (true) {
        try {
            cout << "Enter number to delete (press other number to exit ): ";
            cin >> index;
            if (cin.fail()) {
                cin.clear(); 
                throw invalid_argument("Invalid input. Please enter a valid integer.");
            }
            
            if (index < 0) {
                throw invalid_argument("Index cannot be negative.");
            }
            break;
        }
        catch (invalid_argument e) {
            cin.ignore();
            cout << "Error: " << e.what() << std::endl;
        }
    }
    index--;
    getchar(); 
    admin.deleteCategory(index);
    cout << "# Press Enter To Continue..."; getchar(); system("cls");
    ManageTestMenu();
}

void AdminMenu::DeleteQuestionFromCategory()
{
    
  
    admin.deleteQuestionFromCategory();

    ManageTestMenu(); 
}

void AdminMenu::displayCategories()
{
    cout << "==================== All Categories ====================" << endl << endl;

    admin.displayCategories();

    cout << "========================================================" << endl << endl;
    cout << "# Press Enter To Continue..." << endl;
    getchar();
    ManageTestMenu();
}


void AdminMenu::Login()
{
    string username;
    string password;
    cout << "================= WELCOME TO IT STEP-ACADEMY =================" << endl << endl;

    cout << "Enter username: ";
    
    cin.clear(); getline(cin, username);
    cout << "\nEnter password: ";
    cin.clear(); getline(cin, password);
        
    if (admin.Login(username, password)) {
        cout << "\n\n====================== Login successful! ======================" << endl;
         cout << "\n\n# Press Enter To Continue..." << endl;
        getchar(); system("cls");
        MainMenu();
    }
    else {
        cout << "\n\n==========Login failed. Invalid username or password==========" << endl;
         cout << "\n\n# Press Enter To Continue..." << endl;
         getchar(); system("cls");
         Login(); 
    }
}