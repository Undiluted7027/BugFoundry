#ifndef UI_HPP
#define UI_HPP

/* UI.hpp 
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Jason Lee
----------------------------------------------------------------------
This module, UI.hpp, hides the implementation of the main menu, 
submenus, and how the overall UI gets structured. 
UI.hpp keeps its high cohesion by encapsulating all possible 
menus display in the system.
---------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include "ScenarioControl.hpp"
#include "UI.cpp"

using namespace std;

/*---------------------------------------------------------------------
// Exported constants/types/variables
Variables
 - int choice
 - int subchoice
*/

//--------------------------------------------------------------------
//This module does not include any classes

//------------------------------------------------------------------//
int ActivateUI(

);
/*
ActivateUI is used to display the full user interaction design with main and submenus.
--------------------------------------------------------------------*/
int Main_Menu(
                   
);
/*
Main_Menu is used to display the main menu and let the user to pick one of the options:
New User, Create, Update, Reports, and Exits.
This function will return an integer that represents one of the choices above.
The input from the user must be from 0 to 4. 
--------------------------------------------------------------------*/
int Create_Menu(
    
);
/*
Create_Menu is used to display the Create submenu and let the user to pick one of the options:
Create Complaint, Create Product, Create Product Release, and Go back to main menu.
This function will return an integer that represents one of the choices above.
The input from the user must be from 0 to 3. 
--------------------------------------------------------------------*/
int Update_Menu(

);
/*
Update_Menu is used to display the Update submenu and let the user to pick one of the options:
Update Specific Change, Update one of the latest Change, and Go back to main menu.
This function will return an integer that represents one of the choices above.
The input from the user must be from 0 to 2.
--------------------------------------------------------------------*/
int Report_Menu(

);
/*
Report_Menu is used to display the Report submenu and let the user to pick one of the options:
Report of Changes, Report of Anticipated Changes for a product, 
Report of Users to be informed on update on a Change and Go back to main menu.
This function will return an integer that represents one of the choices above.
The input from the user must be from 0 to 3.
--------------------------------------------------------------------*/
#endif