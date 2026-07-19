// Bank-Customer-System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool MarkForDelete;
};

enum enMainMenuOptions
{
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClient = 4,
    FindClient = 5,
    ExitProgram = 6,
};

void ShowMainMenuText() {
    cout << "======================================================\n";
    cout << "\t\tMain Menu Screen\t\t\n";
    cout << "======================================================\n";
    cout << "\t[1] Show Client List." << endl;
    cout << "\t[2] Add New Client." << endl;
    cout << "\t[3] Delete Client." << endl;
    cout << "\t[4] Update Client." << endl;
    cout << "\t[5] Find Client." << endl;
    cout << "\t[6] Exit." << endl;
    cout << "======================================================\n";
}

enMainMenuOptions ChooseOperation() {
    int Choose;
    do
    {
        cout << "Choose what do you want to do ? [1 to 6]?" << endl;
        cin >> Choose;
    } while (Choose > 6 || Choose < 1);
    
    return (enMainMenuOptions)Choose;
}

void MainMenu(vector<stClient>& vClients) {
    ShowMainMenuText();
    
    
    switch (ChooseOperation()) {

    }
}

void StartApp() {
    vector<stClient> vClients;
    char GoToMainMenu = 'n';
    do
    {
        system("cls");
        MainMenu(vClients);
        cout << "Do you want to go to main menu ? Y/N ? " << endl;
        cin >> GoToMainMenu;

    } while (GoToMainMenu == 'y' || GoToMainMenu == 'Y');
}

int main()
{
    StartApp();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
