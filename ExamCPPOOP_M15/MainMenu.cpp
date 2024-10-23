#include "MainMenu.h"

void MainMenu::Menu() {
    cout << "============ WELCOME TO IT STEP-ACADEMY ============\n";
    cout << " \n1 ) Admin \n";
    cout << " \n2 ) Student \n";
    cout << "\n====================================================\n";

    string input;
    int opt;

    while (true) {
        cout << "\nEnter Option: ";
        getline(cin, input);

        if (input.empty()) {
            cout << "Invalid input. Please enter a number." << endl;
            continue; 
        }
        if (input.length() > 1 || !isdigit(input[0])) {
            cout << "Invalid input. Please enter a single valid integer." << endl;
            continue; 
        }
        try {
            opt = stoi(input);
        }
        catch (const invalid_argument&) {
            cout << "Invalid input. Please enter a valid number." << endl;
            continue; 
        }

        switch (opt) {
        case 1:
            system("cls");
            adminMenu();
            return;
        case 2:
            system("cls");
            studentMenu();
            return;
        default:
            cout << "Error: Invalid option. Please try again." << endl;
            break; 
        }
    }
}

void MainMenu::studentMenu()
{
	StudentMenu sm;
	sm.DisplayMenu();
}

void MainMenu::adminMenu()
{
	AdminMenu am;
	am.Login();
}

