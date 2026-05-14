#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string clientsFileName = "clients.txt";

struct sClient{
    string accountNumber;
    string pinCode;
    string name;
    string phone;
    double accountBalance;
};

int readNumber() {
    int number = 0;
    cout << "\n Choose what do you want to do? [1 to 6]\n";
    cin >> number;
    return number;
}

vector<string> splitString(string s, string delim) {
    vector<string> vString;
    short pos = 0;
    string sWord;

    while ((pos = s.find(delim)) != std::string::npos) {
        sWord = s.substr(0, pos);

        if (sWord != "") {
            vString.push_back(sWord);
        }
        s.erase(0, pos + delim.length());
    }

    if (s != "") {
        vString.push_back(s);
    }

    return vString;
}

sClient convertLineToRecord(string line, string seperator = "#//#") {
    sClient client;
    vector<string> vClientData;

    vClientData = splitString(line, seperator);

    client.accountNumber = vClientData[0];
    client.pinCode = vClientData[1];
    client.name = vClientData[2];
    client.phone = vClientData[3];
    client.accountBalance = stod(vClientData[4]);

    return client;
}

vector<sClient> loadClientDataFromFile(string fileName) {
    vector<sClient> vClients;
    fstream myFile;

    myFile.open(fileName, ios::in); // read mode

    if (myFile.is_open()) {
        string line;
        sClient client;

        while (getline(myFile, line)) {
            client = convertLineToRecord(line);
            vClients.push_back(client);
        }
        myFile.close();
    }

    return vClients;
}

void printClientRecord(sClient client) {
    cout << "| " << setw(15) << left << client.accountNumber;
    cout << "| " << setw(10) << left << client.pinCode;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.phone;
    cout << "| " << setw(12) << left << client.accountBalance;
}

void printAllClientData(vector <sClient> vClients) {
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

    for (sClient Client : vClients)
    {
        printClientRecord(Client);
        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

sClient readNewClient() {
    sClient client;

    // Usage of std::ws will extract(ignore) all the whitespace character
    cout << "Enter account number: \n";
    getline(cin >> ws, client.accountNumber);

    cout << "Enter pin code: \n";
    getline(cin, client.pinCode);

    cout << "Enter name: \n";
    getline(cin, client.name);

    cout << "Enter phone number: \n";
    getline(cin, client.phone);

    cout << "Enter account balance: \n";
    cin >> client.accountBalance;

    return client;
}

string convertRecordToLine(sClient client, string seperator = "#//#") {

    string stClientRecord = "";

    stClientRecord += client.accountNumber + seperator;
    stClientRecord += client.pinCode + seperator;
    stClientRecord += client.name + seperator;
    stClientRecord += client.phone + seperator;
    stClientRecord += to_string(client.accountBalance);

    return stClientRecord;
}

void addDataLineToFile(string fileName, string stDataLine) {
    fstream myFile;
    myFile.open(fileName, ios::out | ios::app); // bitwise OR | merges the flags together so the file knows to both output (out) and append (app).

    if (myFile.is_open()) {
        myFile << stDataLine << endl;
        myFile.close();
    }
}

void addNewClient() {
    sClient client;
    client = readNewClient();
    addDataLineToFile(clientsFileName, convertRecordToLine(client));
}

void addClients() {
    char addMore = 'Y';

    do {
        system("cls");
        cout << "Adding new client:\n\n";

        addNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients ? Y / N ? ";
        cin >> addMore;
    } while (toupper(addMore) == 'Y');
}


void mainMenuScreen() {
    vector<sClient> vClients = loadClientDataFromFile(clientsFileName);

    cout << "============================\n";
    cout << "       Main Menu Screen     \n";
    cout << "============================\n";
    cout << setw(8) << "[1] Show Client List." << "\n";
    cout << setw(8) << "[2] Add New Client." << "\n";
    cout << setw(8) << "[3] Delete Client." << "\n";
    cout << setw(8) << "[4] Update Client Info." << "\n";
    cout << setw(8) << "[5] Find Client." << "\n";
    cout << setw(8) << "[6] Exit." << "\n";
    cout << "============================\n";

    int choice = readNumber();
    switch (choice) {
    case 1: printAllClientData(vClients);
        break;
    case 2: addClients();
          break;
    //case 3: deleteClient();
          break;
    //case 4: updateClientInfo();
          break;
    //case 5: searchClient();
          break;
    //case 6: exit();
          break;
    default: cout << "\nEnter another number from 1 - 6\n";
           readNumber();
           break;
    }
}

int main() {
    
    mainMenuScreen();

    system("pause>0");
    return 0;
}
