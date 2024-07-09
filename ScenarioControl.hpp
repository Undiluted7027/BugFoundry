#ifndef SCENARIOCONTROL_HPP
#define SCENARIOCONTROL_HPP

/* ScenarioControl.hpp
REVISION HISTORY:
Rev. 1 - 24/07/03 Original by Jason Lee
----------------------------------------------------------------------
This module, ScenarioControl.hpp, hides the implementation of the 
general orchestration of system by obtaining the requested event from
the UI module. ScenarioControl.hpp keeps its high cohesion by encapsulating
all event calls for customer, complaint, change, and product objects. 
Furthermore, it has a scenariocontrol function that controls the flow 
of the system with the event calls.
--------------------------------------------------------------------*/
#include "Customer.hpp"
#include "Complaint.hpp"
#include "Change.hpp"
#include "Product.hpp"
#include "Globals.hpp"
/*--------------------------------------------------------------------
// Exported constants/types/variables
This module does not export any constant/types/variables

--------------------------------------------------------------------*/
// This module does not include any classes

//--------------------------------------------------------------------
int ScenarioControl(
    int choice,     // in
                    // Indicates the choice made in the main menu

    int subchoice   // in 
                    // Indicates the choice made in a sub menu
);
/*
ScenarioControl is used to orchestrate the system flow based on the 
choice and subchoice made by the user from the main menu and a sub menu.
The choice and the subchoice must have a match to call the appropriate event.
However, the UI module checks the restriction. 

Main menu 1, Submenu 1: New User
Main menu 2, Submenu 1: Create Complaint
Main menu 2, Submenu 2: Create Product
Main menu 2, Submenu 3: Create Product Release
Main menu 2, Submenu 0: Go back to main menu
Main menu 3, Submenu 1: Update Specific Change
Main menu 3, Submenu 2: Update one of the latest Change
Main menu 3, Submenu 0: Go back to main menu
Main menu 4, Submenu 1: Report of Changes
Main menu 4, Submenu 2: Report of Anticipated Changes for a product
Main menu 4, Submenu 3: Report of Users to be informed on Update on Change
Main menu 0, Submenu 0: Shutdown
--------------------------------------------------------------------*/
int InitControl(

);
/*
InitControl is used to initialize all other objects: Complaint, Change, Customer, Product.
This function gets called whenever the system starts up. When the function
successfully finishes, returns 1. Else, returns 0. 
--------------------------------------------------------------------*/
void Shutdown(

);
/*
Shutdown is used to exit the whole system. The restriction is not applicable
--------------------------------------------------------------------*/
Complaint CreateNewComplaint(

);
/*
CreateNewComplaint is used to create a new complaint by retrieving the 
complaint information through the input from the user. 
The restriction for each attributes for a complaint is mentioned in the User Manual.
--------------------------------------------------------------------*/
Product CreateNewProduct(

);
/*
CreateNewProduct is used to create a new product by retrieving the 
product information through the input from user.
The restriction for each attributes for a product is mentioned in the User Manual
----------------------------------------------------------------------*/
Change CreateNewChange(

);
/*
CreateNewChange is used to create a new change by retrieving the change
information through the input from user. 
The restriction for each attributes for a change is mentioned in the User Manual
----------------------------------------------------------------------*/
int UpdateChangeInfo(
    Change aChange      // inout
                        // A change element to update its attributes
);
/*
UpdateChangeInfo is used to update the attribute of the 'change' in the
function parameter. The output will be 1 if successful and 0 if unsuccessful
The restriction for each attributes for a change is mentioned in the User Manual.
----------------------------------------------------------------------*/
int ListAndSelectChange(

);
/*
ListAndSelectChange is used to display the next 10 latest changes and take
the user input of an option selecting one of the change that displayed, 
display the next 10 latest changes, or exit the event. The output will be
the user selection. For the user input restriction, refer to the
Update one of the latest Change event in the User Manual.
----------------------------------------------------------------------*/
int ExistingChanges(

);
/*
ExistingChanges is used to check if there are at least one change.
If exists, returns 1. If not, returns 0. The restriction for this function
is not applicable.
----------------------------------------------------------------------*/
int DisplayChangeReport(

);
/*
DisplayChangeReport is used to display the next 10 latest changes and take
the user input of an option of displaying the next 10 latest changes, 
or exit the event. For the user input restriction, refer to the
Report Changes event in the User Manual.
----------------------------------------------------------------------*/
int DisplayProductChangeReport(
    Product aProduct    // in
                        // a product to display its changes
);
/*
DisplayProductChangeReport is used to display the next 10 latest changes 
of the 'product' in the parameter. The user input is either 
display the next 10 latest changes, or exit the event.
For the user input restriction, refer to the
Report Anticipated Changes for a Product event in the User Manual.
----------------------------------------------------------------------*/
int DisplayUsersOnUpdateChange(
    Change aChange     // in
                        // a change to display all related users
);
/*
DisplayProductChangeReport is used to display the next 10 users that are 
related to the 'change' parameter.  The user input is either 
display the next 10 users, or exit the event.
For the user input restriction, refer to the
Report of the Users to be informed on Update on Change event in the User Manual.
----------------------------------------------------------------------*/
#endif