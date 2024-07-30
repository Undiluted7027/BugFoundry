/* UI.cpp 
REVISION HISTORY:
Rev. 2 - 24/07/11 Moved New User to be part of Create submenu by Jason Lee
Rev. 1 - 24/07/03 Original by Jason Lee
--------------------------------------------------------------------*/
#include "UI.hpp"
#include "ScenarioControl.cpp"
//--------------------------------------------------------------------

int Main_Menu()
{
    int choice;
    cout << "===Main Menu===" << endl;
    cout << "1) Create" << endl;
    cout << "2) Update" << endl;
    cout << "3) Reports" << endl;
    cout << "0) Exit" << endl;

    cout << "Choose an option and enter (0-3): ";
    cin >> choice;
    cout << endl;

    return choice;
};
/*
To display the main menu and get choice from the user
No noticeable algorithm or data structure used.
-------------------------------------------------*/
int Create_Menu()
{
    int choice;
    do
    {
        cout << "===Create===" << endl;
        cout << "1) Create User" << endl;
        cout << "2) Create Complaint" << endl;
        cout << "3) Create Product Release" << endl;
        cout << "0) Go back to main menu" << endl;

        cout << "Choose an option and enter (0-4): ";
        cin >> choice;
        cout << endl;

        ScenarioControl(1, choice);
    } while (choice != 0);
    
    return 1;
};
/*
To display the create submenu and get choice from the user
No noticeable algorithm or data structure used.
-------------------------------------------------*/
int Update_Menu()
{
    int choice;
    do
    {
        cout << "===Update===" << endl;
        cout << "1) Update Specific Change" << endl;
        cout << "2) Update one of the latest Change" << endl;
        cout << "0) Go back to main menu" << endl;

        cout << "Choose an option and enter (0-2): ";
        cin >> choice;
        cout << endl;

        ScenarioControl(2, choice);
    } while (choice != 0);
    
    return 2;
};
/*
To display the update submenu and get choice from the user 
No noticeable algorithm or data structure used.
-------------------------------------------------*/
int Report_Menu()
{
    int choice;
    do
    {
        cout << "===Report===" << endl;
        cout << "1) Report of Changes" << endl;
        cout << "2) Report of Anticipated Changes for a product" << endl;
        cout << "3) Report of Users to be informed on update on Change" << endl;
        cout << "0) Go back to main menu" << endl;

        cout << "Choose an option and enter (0-3): ";
        cin >> choice;
        cout << endl;

        ScenarioControl(3, choice);
    } while (choice != 0);
    
    return 3;
};
/*
To display the report submenu and get choice from the user 
No noticeable algorithm or data structure used.
-------------------------------------------------*/

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
                subchoice = Create_Menu();
                break;
            case 2:
                subchoice = Update_Menu();
                break;
            case 3:
                subchoice = Report_Menu();
                break;
            case 0:
                subchoice = 0;
                cout << "Thank you for using Bug Foundry." << endl;
                break;
            default:
                cout << "Error: Your option is not an available choice" << endl;
                break;
        }
    } while (choice != 0);
    cin.ignore();
    return 1;
}
/*
Controling the menu UI
No noticeable algorithm or data structure used.
-------------------------------------------------*/
int Start()
{
    int run = ActivateUI();
    return run;
}
/*
To activate the UI from the main module.
No noticeable algorithm or data structure used.
-------------------------------------------------*/