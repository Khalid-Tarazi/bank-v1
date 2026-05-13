#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

const string clientsFileName = "clients.txt";

struct sClient{
    string accountnumber;
    string pinCode;
    string name;
    string phone;
    double accountBalance;
};

int readNumber() {
    int number;
    cout << "\n Choose what do you want to do? [1 to 6]\n";
    while (number > 0 && number < 7) {
        cin >> number;
        cout << '\n';
    }
    return number;
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


void mainMenuScreen() {
    vector<sClient> vClient;


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
    case 1: printAllClientData(vClient);
        break;
    case 2: addNewClient();
          break;
    case 3: deleteClient();
          break;
    case 4: updateClientInfo();
          break;
    case 5: searchClient();
          break;
    case 6: exit();
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
