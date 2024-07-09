/* UI.cpp 
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Jason Lee
--------------------------------------------------------------------*/
#include "UI.hpp"
#include "ScenarioControl.hpp"

int Main_Menu();
void New_User();
int Create_Menu();
int Update_Menu();
int Report_Menu();
int ActivateUI();

int Start()
{
    int run = ActivateUI();
    return run;
}

int ActivateUI()
{
    int choice; int subchoice;
    do 
    {
        cout << endl;
        choice = Main_Menu();
        switch (choice)
        {
            case 1:
                subchoice = 1;
                cout << "User Created" << endl;
                cout << "Main: " << choice << " " << "Submenu: "<< subchoice << endl;
                // ScenarioControl(choice, subchoice);
                break;
            case 2:
                subchoice = Create_Menu();
                cout << "Main: " << choice << " " << "Submenu: "<< subchoice << endl;
                // ScenarioControl(choice, subchoice);
                break;
            case 3:
                subchoice = Update_Menu();
                cout << "Main: " << choice << " " << "Submenu: "<< subchoice << endl;
                // ScenarioControl(choice, subchoice);
                break;
            case 4:
                subchoice = Report_Menu();
                cout << "Main: " << choice << " " << "Submenu: "<< subchoice << endl;
                // ScenarioControl(choice, subchoice);
                break;
            case 0:
                subchoice = 0;
                cout << "Thank you for using Bug Foundry." << endl;
                cout << "Main: " << choice << " " << "Submenu: "<< subchoice << endl;
                // ScenarioControl(choice, subchoice);
                break;
            default:
                cout << "Error: Your option is not an available choice" << endl;
                break;
        }
    } while (choice != 0);
    cin.ignore();
    return 0;
}

int Main_Menu()
{
    int choice;
    cout << "===Main Menu===" << endl;
    cout << "1) New User" << endl;
    cout << "2) Create" << endl;
    cout << "3) Update" << endl;
    cout << "4) Reports" << endl;
    cout << "0) Exit" << endl;

    cout << "Choose an option and enter (0-4): ";
    cin >> choice;
    cout << endl;

    return choice;
};

int Create_Menu()
{
    int choice;
    cout << "===Create===" << endl;
    cout << "1) Create Complaint" << endl;
    cout << "2) Create Product" << endl;
    cout << "3) Create Product Release" << endl;
    cout << "0) Go back to main menu" << endl;

    cout << "Choose an option and enter (0-3): ";
    cin >> choice;
    cout << endl;

    return choice;
};

int Update_Menu()
{
    int choice;
    cout << "===Update===" << endl;
    cout << "1) Update Specific Change" << endl;
    cout << "2) Update one of the latest Change" << endl;
    cout << "0) Go back to main menu" << endl;

    cout << "Choose an option and enter (0-2): ";
    cin >> choice;
    cout << endl;

    return choice;
};

int Report_Menu()
{
    int choice;
    cout << "===Report===" << endl;
    cout << "1) Report of Changes" << endl;
    cout << "2) Report of Anticipated Changes for a product" << endl;
    cout << "3) Report of Users to be informed on update on Change" << endl;
    cout << "0) Go back to main menu" << endl;

    cout << "Choose an option and enter (0-3): ";
    cin >> choice;
    cout << endl;

    return choice;
};