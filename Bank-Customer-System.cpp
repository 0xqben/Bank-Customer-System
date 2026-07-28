// Bank-Customer-System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

const string FileName = "Clients.txt";

void ShowMainMenu();

enum enMainMenuOptions
{
    ShowClientList = 1,
    AddNewClient = 2,
    DeleteClient = 3,
    UpdateClient = 4,
    FindClient = 5,
    ExitProgram = 6,
};

enum enTransactionMenuOptions
{
    Deposit = 1,
    Withdraw = 2,
    TotalBalance =3,
    MainMenuo = 4,
};

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool MarkForDelete = false;
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

vector <stClient> LoadClientsDataFromFile(string FileName)
{
    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

bool FindClientByAccountNumber(string AccountNumber, vector<stClient>& vClients, stClient& ClientFound) {
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            ClientFound = C;
            return true;
        }
    }
    return false;
}

bool MarkForDeleteByAccountNumber(string AccountNumber, vector<stClient>& vClients) {
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

void PrintRecord(stClient Record) {
    cout << " Account Number : " << Record.AccountNumber << endl;
    cout << " PinCode        : " << Record.PinCode << endl;
    cout << " Name           : " << Record.Name << endl;
    cout << " Phone          : " << Record.Phone << endl;
    cout << " Account Balance: " << Record.Balance << endl;

}

stClient ChangeClientRecord(string AccountNumber) {
    stClient ClientData;
    ClientData.AccountNumber = AccountNumber;
    cout << "Enter PinCode ?" << endl;
    getline(cin >> ws, ClientData.PinCode);

    cout << "Enter Name ?" << endl;
    getline(cin, ClientData.Name);

    cout << "Enter Phone ? " << endl;
    getline(cin, ClientData.Phone);

    cout << "Enter Account balance ?" << endl;
    cin >> ClientData.Balance;

    return ClientData;
}

string ReadClientAccountNumber() {
    string AccountNumber = "";

    cout << "\nPlease enter account Number ?";
    getline(cin >> ws, AccountNumber);
    return AccountNumber;
}

void PrintClientRecord(stClient Client) {

    cout << "\n| " << left << setw(15) << Client.AccountNumber;
    cout << "| " << left << setw(10) << Client.PinCode;
    cout << "| " << left << setw(35) << Client.Name;
    cout << "| " << left << setw(15) << Client.Phone;
    cout << "| " << left << setw(15) << Client.Balance;
}

void PrintAllClientsData() {
    vector <stClient> vClients = LoadClientsDataFromFile(FileName);

    cout << "\n\t\t\tClient List (" << vClients.size() << ") Client(s).\t\t\t\n" << endl;
    cout << "__________________________________";
    cout << "__________________________________";
    cout << "__________________________________\n";

    cout << "| " << left << setw(15) << "Account Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(35) << "Client Name";
    cout << "| " << left << setw(15) << "Phone";
    cout << "| " << left << setw(15) << "Balance";

    cout << "\n__________________________________";
    cout << "__________________________________";
    cout << "__________________________________\n";

    for (stClient& Client : vClients) // read-only use here, & just avoids copying every record
    {
        PrintClientRecord(Client);

    }

    cout << "\n__________________________________";
    cout << "__________________________________";
    cout << "__________________________________\n";


}

void ShowClientDetails(stClient Client) {
  
    cout << "The following are the client details : \n";
    cout << "\n-----------------------------------------------\n";
    cout << "\tAccount Number :" << Client.AccountNumber << endl;
    cout << "\tPin code:" << Client.PinCode << endl;
    cout << "\tName:" << Client.Name << endl;
    cout << "\tPhone:" << Client.Phone << endl;
    cout << "\tAccount Balance:" << Client.Balance;
    cout << "\n-----------------------------------------------\n";
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

bool ClientExistsByAccountNumber(string AccountNumber, string
    FileName)
{
    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLineToRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return false;
}

stClient ReadNewClient()
{
    stClient Client;
    cout << "Enter Account Number? ";
    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);
    while (ClientExistsByAccountNumber(Client.AccountNumber,
        FileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number ?";
            getline(cin >> ws, Client.AccountNumber);
    }
    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.Balance;
    return Client;
}

void AddANewClient() {
    stClient Client = ReadNewClient();
    SaveClientToFile(FileName, ConvertRecordToLine(Client));
}

void AddClients() {


    char AddMore = 'y';
    do
    {
        system("cls");
        cout << "adding new client : " << endl;
        AddANewClient();
        cout << "client added successfully , do you want to add more clients ? y / n ? " << endl;
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');

}

bool DeleteClientByAccountNumber(string AccountNumber, vector
    <stClient>& vClients) {
    
    char Answer = 'n';
    stClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        ShowClientDetails(Client);
        cout << "\nAre you sure you want to delete this client ? y / n ? " << endl;
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            MarkForDeleteByAccountNumber(AccountNumber, vClients);
            SaveClientsDataToFile(FileName, vClients);


            vClients = LoadClientsDataFromFile(FileName);

            cout << "\nClient Deleted Successfully.\n";
            return true;
        }
        else
        {
            cout << "\nAccount Has not been deleted\n";
            return false;
        }


    }
    else
    {
        cout << "client with account number (" << AccountNumber << ") is not found \n";
        return false;
    }

}

bool UpdateClientByAccountNumber(string AccountNumber, vector
    <stClient>& vClients) {


    char Answer = 'n';
    stClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        ShowClientDetails(Client);
        cout << "\nAre you sure you want to update this client ? y/n ?\n";
        cin >> Answer;
        if (toupper(Answer) == 'Y')
        {
            for (stClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }

            // Update File and Vector to The New Info
            SaveClientsDataToFile(FileName, vClients);
            vClients = LoadClientsDataFromFile(FileName);
            cout << "\nClient Updated Successfully.\n";
            return true;
        }
        else
        {
            cout << "Account Hasnt been updated due to wrong input.\n";
            return false;
        }


    }
    else
    {
        cout << "\nError . Account Not Found ! \n";
        return false;
    }
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

void DeleteClientScreen() {
    system("cls");
    cout << "\n----------------------------------------\n";
    cout << "\tDelete client Screen";
    cout << "\n----------------------------------------\n";

    vector<stClient> vClients = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadClientAccountNumber();

    DeleteClientByAccountNumber(AccountNumber,vClients);

}

void UpdateClientScreen() {
    system("cls");
    cout << "\n----------------------------------------\n";
    cout << "\tUpdate client Info Screen";
    cout << "\n----------------------------------------\n";

    vector <stClient> vClients = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadClientAccountNumber();

    UpdateClientByAccountNumber(AccountNumber, vClients);


}

void AddClientsScreen() {
    system("cls");
    cout << "\n----------------------------------------\n";
    cout << "\tAdd new client Screen";
    cout << "\n----------------------------------------\n";
    AddClients();

}

bool SearchClient() {
    
    vector<stClient> vClients = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadClientAccountNumber();
    stClient Client;
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        ShowClientDetails(Client);
        return true;
    }
    else
    {
        cout << "\nClient with [" << AccountNumber << "] is not found ! \n";
        return false;
    }
}

void FindClientScreen() {
    system("cls");
    cout << "\n----------------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n----------------------------------------\n";
    SearchClient();
}

void DepositClient(string AccountNumber, vector<stClient> &vClients) {
    stClient Client;
    char answer = 'n';
    int depo = 0;

    // Validation
    while (!FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        cout << "Client with [" << AccountNumber << "] does not exist.";
        AccountNumber = ReadClientAccountNumber();
    }


    ShowClientDetails(Client);

    cout << "\nEnter Deposite amount?" << endl;
    cin >> depo;
    cout << "Are you sure ? y/n";
    cin >> answer;

    if (toupper(answer) == 'Y')
    {
        for (stClient& C : vClients)
        {
            if (AccountNumber== C.AccountNumber)
            {
                C.Balance += depo;
                cout << "done successfully new balance is : " << C.Balance << endl;
                break;

            }
        }
        SaveClientsDataToFile(FileName, vClients);
        vClients = LoadClientsDataFromFile(FileName);
        
    }
    else
    {
        cout << "error , wrong input";
    }
}

void ShowDepositClientScreen() {
    cout << "--------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n--------------------------------\n";
    vector <stClient> vClients = LoadClientsDataFromFile(FileName);
    string AccountNumber = ReadClientAccountNumber();


    DepositClient(AccountNumber,vClients);
}
void ShowDepositWithdrawClientScreen() {
    cout << "--------------------------------\n";
    cout << "\tWithDraw Screen";
    cout << "\n--------------------------------\n";


    //WithdrawClient();

}
void TotalBanacess() {

    TotalBanacess();
}

void PerformTransactionOption(enTransactionMenuOptions SelectedOption) {
    switch (SelectedOption) {
    case enTransactionMenuOptions::Deposit :
        system("cls");
        ShowDepositClientScreen();
        break;
    case enTransactionMenuOptions::Withdraw:
        system("cls");
        //WithdrawClient();
        break;
    case enTransactionMenuOptions::TotalBalance:
        system("cls");
        //TotalBanacess();
        break;
    case enTransactionMenuOptions::MainMenuo:
        system("cls");
        //ShowMainMenu();
        break;
    }
}

enTransactionMenuOptions SelectTransactionOption() {
    int OP;
    do
    {
        cout << "choose what do you want to do ? [1 to 4]?";
        cin >> OP;
    } while (OP > 4 || OP < 1);
    return (enTransactionMenuOptions)OP;
}

void ShowTransactionsScreen() {
    system("cls");
    cout << "\n----------------------------------------\n";
    cout << "\tTransactions Screen";
    cout << "\n----------------------------------------\n";
    cout << "\t[1] Deposit.";
    cout << "\t[2] Withdraw.";
    cout << "\t[3] Total Balances.";
    cout << "\t[4] MainMenu.";


    PerformTransactionOption(SelectTransactionOption());
}

void GoBackToMainMenu() {
    cout << "Press Any key to go to main menu...";
    system("pause>0");
    ShowMainMenu();
}

void ShowEndScreen() {
    cout << "\n=======================\n";
    cout << "\tEnd Screen";
    cout << "\n=======================";

}

void PerformMainMenuOption(enMainMenuOptions SelectedOption) {
    
    
    switch (SelectedOption) {
    case enMainMenuOptions::ShowClientList :
        system("cls");
        PrintAllClientsData();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::AddNewClient :
        system("cls");  
        AddClientsScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::DeleteClient :
        system("cls");
        DeleteClientScreen();
        GoBackToMainMenu();

        break;
    case enMainMenuOptions::UpdateClient :
        system("cls");
        UpdateClientScreen();
        GoBackToMainMenu();

        break;
    case enMainMenuOptions::FindClient :
        system("cls");
        FindClientScreen();
        GoBackToMainMenu();
        break;
    case enMainMenuOptions::ExitProgram :
        system("cls");
        ShowEndScreen();

    }

}

void ShowMainMenu() {
    system("cls");
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
    PerformMainMenuOption(ChooseOperation());
}

int main()
{
    ShowMainMenu();
    
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
