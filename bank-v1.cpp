#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
const string clientsFileName = "Clients.txt";

void showMainMenu();

struct sClient {
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

vector<string> splitString(string S1, string Delim) {
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos) {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "") {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "") {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;
}

sClient convertLinetoRecord(string Line, string Seperator = "#//#") {
    sClient Client;
    vector<string> vClientData;
    vClientData = splitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double
    return Client;
}

string convertRecordToLine(sClient Client, string Seperator = "#//#") {

    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

bool clientExistsByAccountNumber(string AccountNumber, string FileName) {

    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open()) {
        string Line;
        sClient Client;

        while (getline(MyFile, Line)) {
            Client = convertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber) {
                MyFile.close();
                return true;
            }
            vClients.push_back(Client);
        }

        MyFile.close();

    }
    return false;
}

sClient readNewClient() {
    sClient Client;
    cout << "Enter Account Number? ";

    // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (clientExistsByAccountNumber(Client.AccountNumber, clientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;

    return Client;
}

vector <sClient> loadCleintsDataFromFile(string FileName) {
    vector <sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open()) {
        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {
            Client = convertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void printClientRecordLine(sClient Client) {
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void showAllClientsScreen() {
    vector <sClient> vClients = loadCleintsDataFromFile(clientsFileName);

    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

    if (vClients.size() == 0)
        cout << "\t\t\t\tNo Clients Available In the System!";
    else

        for (sClient Client : vClients)
        {

            printClientRecordLine(Client);
            cout << endl;
        }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

void printClientCard(sClient Client) {
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool findClientByAccountNumber(string AccountNumber, vector <sClient> vClients, sClient& Client) {
    for (sClient C : vClients) {

        if (C.AccountNumber == AccountNumber) {
            Client = C;
            return true;
        }

    }
    return false;
}

sClient changeClientRecord(string AccountNumber) {
    sClient Client;

    Client.AccountNumber = AccountNumber;

    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);

    cout << "Enter Name? ";
    getline(cin, Client.Name);

    cout << "Enter Phone? ";
    getline(cin, Client.Phone);

    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool markClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients) {

    for (sClient& C : vClients) {

        if (C.AccountNumber == AccountNumber) {
            C.MarkForDelete = true;
            return true;
        }
    }

    return false;
}

vector <sClient> saveCleintsDataToFile(string FileName, vector <sClient> vClients) {
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open()) {
        for (sClient C : vClients) {

            if (C.MarkForDelete == false) {
                //we only write records that are not marked for delete.  
                DataLine = convertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }

    return vClients;
}

void addDataLineToFile(string FileName, string  stDataLine) {
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);

    if (MyFile.is_open()) {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void addNewClient() {
    sClient Client;
    Client = readNewClient();
    addDataLineToFile(clientsFileName, convertRecordToLine(Client));
}

void addNewClients() {
    char AddMore = 'Y';
    do {
        //system("cls");
        cout << "Adding New Client:\n\n";

        addNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? Y/N? ";
        cin >> AddMore;

    } while (toupper(AddMore) == 'Y');
}

bool deleteClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {
    sClient Client;
    char Answer = 'n';

    if (findClientByAccountNumber(AccountNumber, vClients, Client)) {

        printClientCard(Client);

        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            markClientForDeleteByAccountNumber(AccountNumber, vClients);
            saveCleintsDataToFile(clientsFileName, vClients);

            //Refresh Clients 
            vClients = loadCleintsDataFromFile(clientsFileName);

            cout << "\n\nClient Deleted Successfully.";
            return true;
        }
    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool updateClientByAccountNumber(string AccountNumber, vector <sClient>& vClients) {

    sClient Client;
    char Answer = 'n';

    if (findClientByAccountNumber(AccountNumber, vClients, Client)) {

        printClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y') {
            for (sClient& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C = changeClientRecord(AccountNumber);
                    break;
                }
            }

            saveCleintsDataToFile(clientsFileName, vClients);

            cout << "\n\nClient Updated Successfully.";
            return true;
        }

    }
    else {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

string readClientAccountNumber() {
    string AccountNumber = "";

    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void showDeleteClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = loadCleintsDataFromFile(clientsFileName);
    string AccountNumber = readClientAccountNumber();
    deleteClientByAccountNumber(AccountNumber, vClients);
}

void showUpdateClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = loadCleintsDataFromFile(clientsFileName);
    string AccountNumber = readClientAccountNumber();
    updateClientByAccountNumber(AccountNumber, vClients);
}

void showAddNewClientsScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";

    addNewClients();
}

void showFindClientScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";

    vector <sClient> vClients = loadCleintsDataFromFile(clientsFileName);
    sClient Client;
    string AccountNumber = readClientAccountNumber();
    if (findClientByAccountNumber(AccountNumber, vClients, Client))
        printClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void showEndScreen() {
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends.";
    cout << "\n-----------------------------------\n";
}

enum enMainMenuOptions {
    eListClients = 1, eAddNewClient = 2,
    eDeleteClient = 3, eUpdateClient = 4,
    eFindClient = 5, eExit = 6
};

void goBackToMainMenu() {
    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    showMainMenu();
}

short readMainMenuOption() {
    cout << "Choose what do you want to do? [1 to 6]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}

void performMainMenueOption(enMainMenuOptions MainMenueOption) {
    switch (MainMenueOption)
    {
    case enMainMenuOptions::eListClients:
    {
        system("cls");
        showAllClientsScreen();
        goBackToMainMenu();
        break;
    }
    case enMainMenuOptions::eAddNewClient:
        system("cls");
        showAddNewClientsScreen();
        goBackToMainMenu();
        break;

    case enMainMenuOptions::eDeleteClient:
        system("cls");
        showDeleteClientScreen();
        goBackToMainMenu();
        break;

    case enMainMenuOptions::eUpdateClient:
        system("cls");
        showUpdateClientScreen();
        goBackToMainMenu();
        break;

    case enMainMenuOptions::eFindClient:
        system("cls");
        showFindClientScreen();
        goBackToMainMenu();
        break;

    case enMainMenuOptions::eExit:
        system("cls");
        showEndScreen();
        break;
    }
}

void showMainMenu() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Exit.\n";
    cout << "===========================================\n";
    performMainMenueOption((enMainMenuOptions)readMainMenuOption());
}

int main() {
    showMainMenu();
    system("pause>0");
    return 0;
}