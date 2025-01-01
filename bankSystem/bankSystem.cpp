#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip> 

using namespace std;
const string fileName = "BanckClient.txt";
// Show Client List 
struct ClientSt
{
    string name;
    string AccountNumber;
    string pinCode;
    string phone;
    double AccountBalance;
};


ClientSt AddClientSt() {
    ClientSt StClient;
    cout << "Add Client to Vector" << endl;

    cout << "Enter the name: ";
    cin.ignore(); // Ignore any leftover newline character from previous inputs
    getline(cin, StClient.name);

    cout << "Enter Account Number: ";
    getline(cin, StClient.AccountNumber);

    cout << "Enter PIN Code: ";
    getline(cin, StClient.pinCode);

    cout << "Enter Phone: ";
    getline(cin, StClient.phone);

    cout << "Enter Account Balance: ";
    cin >> StClient.AccountBalance;

    return StClient;
}
//void AddClientToVector(vector<ClientSt>& ClientVector) {
//    ClientVector.push_back(AddClientSt());
//}


// Add New Client 

string StructToLine(ClientSt StData,string delemiter) {
    string line;
    line += StData.name + delemiter;
    line += StData.AccountNumber + delemiter;
    line += StData.phone + delemiter;
    line += StData.pinCode + delemiter;
    line += to_string(StData.AccountBalance);
    return line;
}
// Show All Client 
vector <string> Split(string line,string Demletr) {
    vector<string> Words;
    string word;
    int pos = 0;
    while ((pos = line.find(Demletr)) != std::string::npos) {
        word = line.substr(0, pos);
        if (word != "")
        {
            Words.push_back(word);
        }

        line.erase(0, pos + Demletr.length());
    }
    if (line !="")
    {
        Words.push_back(line);

    }
    return Words;
}
ClientSt FromLineToClientStrucu(string line,string Delemeter) {
    vector <string> Words = Split(line, Delemeter);
    ClientSt NewClient;
    NewClient.name = Words[0];
    NewClient.AccountNumber = Words[1];
    NewClient.pinCode = Words[2];
    NewClient.phone = Words[3];
    NewClient.AccountBalance = stod(Words[4]);
    return NewClient;
}
vector <ClientSt> loadClientFromFileToVector(string fileName) {
    vector <ClientSt> ClientVector;
    fstream file;
    string line;
    ClientSt newClient;
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        while (getline(file, line)) {
            newClient = FromLineToClientStrucu(line,"//");
            ClientVector.push_back(newClient);
        }
        
    }
    return ClientVector;
}
void addNewClient(vector <ClientSt>& ClientVector) {
    fstream file;
    string line;
    file.open(fileName, ios::app);
    if (file.is_open())
    {
        ClientSt Client = AddClientSt();
       file << StructToLine(Client,"//") << endl;
        
        file.close();
    }
    ClientVector = loadClientFromFileToVector(fileName);
}
// update client info
//Find Client

void PrintClientCard(ClientSt Client) {
    cout << "-------------------------------------" << endl;
    cout << "name: ";
    cout << Client.name << endl;
    cout << "Account number: ";
    cout << Client.AccountNumber << endl;
    cout << "Balance: ";
    cout << Client.AccountBalance << endl;
    cout << "Phne: ";
    cout << Client.phone << endl;
    cout << "pinCode: ";
    cout << Client.pinCode << endl;
    cout << "-------------------------------------" << endl;
}
bool GetClientByAccountNumber(string AccountNumber,vector<ClientSt>ClientVector) {
    for (ClientSt&Client :ClientVector) {
        if (Client.AccountNumber == AccountNumber)
        {
            PrintClientCard(Client);
            return true;
        }
       
    }
    return  false;
}

void ShowAllClient(vector<ClientSt>ClientVector) {
    for (ClientSt& Client : ClientVector) {
        cout << "-------------------------------------" << endl;
        cout << "name: ";
        cout << Client.name << endl;
        cout << "Account number: ";
        cout << Client.AccountNumber << endl;
        cout << "Balance: ";
        cout << Client.AccountBalance << endl;
        cout << "Phne: ";
        cout << Client.phone << endl;
        cout << "pinCode: ";
        cout << Client.pinCode << endl;
        cout << "-------------------------------------" << endl;
    }
}

//Delete Client
void DeleteClient(string AccountNumber, vector <ClientSt>& ClientVector) {
    string Delete = "yes";
    fstream file;
    if (GetClientByAccountNumber(AccountNumber, ClientVector)) {
        cout << "Do you Want Delete This Recored? [yes]" << endl;
        cin >> Delete;
        if (Delete == "yes")
        {
            file.open(fileName, ios::out);
            for (ClientSt& client : ClientVector) {

                if (client.AccountNumber != AccountNumber)
                {
                    file << StructToLine(client, "//") << endl;

                }

            }
            cout << "Deleted Done";
            ClientVector = loadClientFromFileToVector(fileName);
            file.close();
        }
        else
        {
            return;
        }
       
    }
    else
    {
        cout << "there is no Client With this Account Number" << endl;
    }  
    
}
void UpdaedByAccountNumber(string AccountNumber, vector <ClientSt>& ClientVector) {
    string line;
    string update = "yes";
    fstream file;
    if (GetClientByAccountNumber(AccountNumber, ClientVector))
    {
        cout << "Do You Want Update This recored? [yes]" << endl;
        cin >> update;
        if (update == "yes") {
            file.open(fileName, ios::out);
            for (ClientSt& client : ClientVector) {
                if (client.AccountNumber != AccountNumber)
                {
                    file << StructToLine(client, "//") << endl;
                }
                else {
                    cout << "enter the name" << endl;
                    cin.ignore(); // Clear the newline character left in the input buffer
                    getline(cin, client.name);
                    cout << "enter pinCode" << endl;
                    getline(cin, client.pinCode);
                    cout << "enter Phone" << endl;
                    getline(cin, client.phone);
                    cout << "enter Account Balance" << endl;
                    cin >> client.AccountBalance;
                    cout << "Updated Done";
                    file << StructToLine(client, "//") << endl;
                }
            }
        }
        else
        {
            return;
        }

    }
    else
    {
        cout << "there is no Client with this Account Number" << endl;
    }
    

}

//Helper Funtions 
string WriteString(string message) {
    string s1;
    cout << message << endl;
    cin >> s1;
    return s1;
}
//Exit


// Function Hold All project 
enum ClientChoose
{
    ShowAll = 1,
    AddNew = 2,
    Update = 3,
    Delete = 4,
    Transaction = 5,
    Exit = 6
};

ClientChoose Options(int num) {   
    return static_cast<ClientChoose>(num);
}
enum ETranscions
{
    AllBalance = 1,
    Deposit = 2,
    withDraw = 3,
    mainMeun = 4
};
short ReadShort() {
    short num = 0;
    cout << "Enter Your Choose" << endl;
    cin >> num;
    return num;
}
void PrintTransactions() {
    cout << "Transactions" << endl;
    cout << "-------------------" << endl;
    cout << "1 - All Balance" << endl;
    cout << "2 - Deposit" << endl;
    cout << "3- witdraw" << endl;
    cout << "4 - Main menu" << endl;
}


void AllBalancefn(vector<ClientSt>& ClientV) {
    ClientV = loadClientFromFileToVector(fileName);
    double sumAllBalance = 0;

    cout << left << setw(20) << "Name"
        << setw(20) << "Account Number"
        << setw(10) << "Pin Code"
        << setw(15) << "Phone"
        << setw(15) << "Account Balance" << endl;
    cout << string(80, '-') << endl; 

    for (const ClientSt& Client : ClientV) {
        cout << left << setw(20) << Client.name
            << setw(20) << Client.AccountNumber
            << setw(10) << Client.pinCode
            << setw(15) << Client.phone
            << setw(15) << fixed << setprecision(2) << Client.AccountBalance << endl;
        sumAllBalance += Client.AccountBalance;
    }

    cout << string(80, '-') << endl; 
    cout << "All Balance Is = " << (int)sumAllBalance << endl;
}

void DepositFn(string AccountNumber, vector <ClientSt>& ClientVector) {
    string line;
    string update = "yes";
    fstream file;
    double Balance = 0;
    if (GetClientByAccountNumber(AccountNumber, ClientVector))
    {
        cout << "Do You Want Deposite Money to This recored? [yes]" << endl;
        cin >> update;
        if (update == "yes") {
            file.open(fileName, ios::out);
            for (ClientSt& client : ClientVector) {
                if (client.AccountNumber != AccountNumber)
                {
                    file << StructToLine(client, "//") << endl;
                }
                else {
                    cout << "Enter the Amount " << endl;
                    cin >> Balance;
                    client.AccountBalance = client.AccountBalance + Balance;
                    file << StructToLine(client, "//") << endl;
                    cout << "Deposite Done" << endl;
                }
            }
        }
        else
        {
            return;
        }

    }
    else
    {
        cout << "there is no Client with this Account Number" << endl;
    }

}

void WitardFn(string AccountNumber, vector <ClientSt>& ClientVector) {
    string line;
    string update = "yes";
    fstream file;
    double Balance = 0;
    if (GetClientByAccountNumber(AccountNumber, ClientVector))
    {
        cout << "Do You Want Deposite Money to This recored? [yes]" << endl;
        cin >> update;
        cout << "Enter the Amount " << endl;
        cin >> Balance;

        if (update == "yes") {

            file.open(fileName, ios::out);
            for (ClientSt& client : ClientVector) {
                if (client.AccountNumber != AccountNumber)
                {
                    file << StructToLine(client, "//") << endl;
                }
                else {

                    if (Balance > client.AccountBalance)
                    {
                        cout << "The balance in this account less than the about you want withard" << endl;
                        file << StructToLine(client, "//") << endl;
                    }
                    else {

                        client.AccountBalance = client.AccountBalance - Balance;
                        file << StructToLine(client, "//") << endl;
                        cout << "witard Done" << endl;
                    }
                }
            }
        }
        else
        {
            return;
        }
    }
    else
    {
        cout << "there is no Client with this Account Number" << endl;
    }

}
void TransactionFn(ETranscions TChoose, vector<ClientSt>& ClientV) {
    string back = "no";
        switch (TChoose)
        {
        case ETranscions::AllBalance:
            system("cls");
            AllBalancefn(ClientV);
            break;
        case ETranscions::Deposit:
            system("cls");
            DepositFn(WriteString("Write The Account Number: "), ClientV);
            break;
        case ETranscions::withDraw:
            system("cls");
            WitardFn(WriteString("Write The Account Number: "), ClientV);
            break;
        case ETranscions::mainMeun:
            system("cls");
            cout << " We Transfer You to Main Menu ,, Why you login here ?? Are You Hacker +_+ !!" << endl;
            system("pause");
            break;
        default:
            break;
        }
}
void StartProject(vector<ClientSt>&ClientV) {
    string containuo = "yes";
    int num = 0;
    ClientChoose Choose;
    do
    { 
        
        cout << "1 - Show All Client" << endl;
        cout << "2 - Add New Client" << endl;
        cout << "3 - UpdateClient" << endl;
        cout << "4 - DeleteClient" << endl;
        cout << "5 - Transactions" << endl;
        cout << "6 - Exit" << endl;
        cout << "--------------------------" << endl;
        cout << "WhatIs Your Chosse" << endl;
        cin >> num;
        system("cls");
        switch (Options(num))
        {
        case ClientChoose::ShowAll:
            ShowAllClient(ClientV);
            break;
        case ClientChoose::AddNew:
            addNewClient(ClientV);
            break;
        case ClientChoose::Update:
            UpdaedByAccountNumber(WriteString("Write The Account Number"), ClientV);
            break;
        case ClientChoose::Delete:
            DeleteClient(WriteString("Write The Account Number: "), ClientV);
            break;
        case ClientChoose::Transaction:
            PrintTransactions();
            TransactionFn((ETranscions)ReadShort(), ClientV);
            break;
        case ClientChoose::Exit:
            cout << "You Exit From Bank System";
            return;


        }
        system("pause");
        system("cls");


    } while ( containuo == "yes");
}
int main()
{
    vector <ClientSt> ClientVector = loadClientFromFileToVector(fileName);

    StartProject(ClientVector);
    return 0;
}

