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

vector <string> SplitString(string Word, string Delimiter = " ") {
    vector <string> vWords;
    string sWord;
    int pos = 0;

    while ((pos = Word.find(Delimiter)) != std::string::npos) {
        sWord = Word.substr(0, pos);
        if (sWord != "") // skip empty pieces, e.g. two delimiters back to back
        {
            vWords.push_back(sWord);
        }
        Word.erase(0, pos + Delimiter.length());
    }
    if (Word != "") // don't forget the last piece after the final delimiter
    {
        vWords.push_back(Word);
    }
    return vWords;
}

stClient ConvertLineToRecord(string UserRecord, string Seperator = "#//#") {
    stClient ClientData;
    vector<string> vRec = SplitString(UserRecord, Seperator);
    ClientData.AccountNumber = vRec[0];
    ClientData.PinCode = vRec[1];
    ClientData.Name = vRec[2];
    ClientData.Phone = vRec[3];
    ClientData.Balance = stof(vRec[4]); // stof = string -> float

    return ClientData;

}

string ConvertRecordToLine(stClient ClientData, string Delimiter = "#//#") {
    string sData = "";
    sData += (ClientData.AccountNumber + Delimiter);
    sData += (ClientData.PinCode) + Delimiter;
    sData += (ClientData.Name + Delimiter);
    sData += (ClientData.Phone) + Delimiter;
    sData += (to_string(ClientData.Balance));

    return sData;
}

void SaveClientToFile(string FileName, string stDataLine) {
    fstream NewFile;
    NewFile.open(FileName, ios::out | ios::app); // app = append (keep existing content)
    if (NewFile.is_open())
    {
        NewFile << stDataLine << endl;
        NewFile.close();
    }

}

vector <stClient> SaveClientsDataToFile(string FileName, vector<stClient>& vClients) {
    fstream Myfile;
    Myfile.open(FileName, ios::out); // out (no app) = overwrite the whole file
    string DataLine;
    if (Myfile.is_open())
    {
        for (stClient& C : vClients) // & = the real elements, not copies
        {
            if (C.MarkForDelete == false) // rewrite everyone except whoever's marked for delete
            {
                DataLine = ConvertRecordToLine(C); // rewrite again but skip the mark for delete client
                Myfile << DataLine << endl;
            }
        }

        Myfile.close();
    }

    return vClients;
}


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
    case enMainMenuOptions::ShowClientList :
        cout << "show client list " << endl;
        break;
    case enMainMenuOptions::AddNewClient :
        cout << "Add new client " << endl;
        break;
    case enMainMenuOptions::DeleteClient :
        cout << "delete client " << endl;
        break;
    case enMainMenuOptions::UpdateClient :
        cout << "update client " << endl;
        break;
    case enMainMenuOptions::FindClient :
        cout << "Find client " << endl;
        break;
    case enMainMenuOptions::ExitProgram :
        cout << "exit program" << endl;
        break;
    default :
        cout << "default" << endl;
        break;

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
