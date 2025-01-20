#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip> 

using namespace std;
const string fileName = "BanckClient.txt";
const string UsersFile = "UsersFile.txt";
// Show Client List 
struct ClientSt
{
    string name;
    string AccountNumber;
    string pinCode;
    string phone;
    double AccountBalance;
};

struct User
{
    string name;
    string password;
    int permssion;
};

User CurrentUser;
enum enMainMenuePermissions {
    eAll = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient
    = 4,
    pUpdateClients = 8, pFindClient = 16, pTranactions = 32,
    pManageUsers = 64
};

int ReadPermission() {
    int permission = 0;
    char answer;

    // Check if the user wants all permissions
    cout << "Add All Permissions? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        return enMainMenuePermissions::eAll; // Return -1 for all permissions
    }

    // Check individual permissions
    cout << "Can Show All Clients? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        permission += enMainMenuePermissions::pListClients;
    }

    cout << "Can Add New Client? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        permission += enMainMenuePermissions::pAddNewClient;
    }

    cout << "Can Delete Client? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        permission += enMainMenuePermissions::pDeleteClient;
    }

    cout << "Can Update Client? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        permission += enMainMenuePermissions::pUpdateClients;
    }

    cout << "Can Find Client? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        permission += enMainMenuePermissions::pFindClient;
    }

    cout << "Can Perform Transactions? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        permission += enMainMenuePermissions::pTranactions;
    }

    cout << "Can Manage Users? [y/n]: ";
    cin >> answer;
    if (answer == 'Y' || answer == 'y') {
        permission += enMainMenuePermissions::pManageUsers;
    }

    return permission; // Return the calculated permission value
}

void AccessDenied() {
  cout << "You do not have permission to perform this action." << endl;
}
bool IsHavePermssion(enMainMenuePermissions permssion) {
    if (CurrentUser.permssion == permssion)
    {
        return true;
    }
    if ((permssion & CurrentUser.permssion) == permssion)
    {
        return true;
    }
    
    return false;
}
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
User AddUserSt() {
    User StUser;
    cout << "Add User to Vector" << endl;

    cout << "Enter the UserName: ";
    cin.ignore(); // Ignore any leftover newline character from previous inputs
    getline(cin, StUser.name);

    cout << "Enter password: ";
    getline(cin, StUser.password);
    cout << "Enter Permssion: ";
    StUser.permssion = ReadPermission();

    return StUser;
}

string StructToLine(ClientSt StData,string delemiter) {
    string line;
    line += StData.name + delemiter;
    line += StData.AccountNumber + delemiter;
    line += StData.phone + delemiter;
    line += StData.pinCode + delemiter;
    line += to_string(StData.AccountBalance);
    return line;
}
string StructToLineUser(User StData, string delemiter) {
    string line;
    line += StData.name + delemiter;
    line += StData.password + delemiter;
    line += to_string(StData.permssion);
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
User FromLineToUserStrucu(string line, string Delemeter) {
    vector <string> Words = Split(line, Delemeter);
    User NewUser;
    NewUser.name = Words[0];
    NewUser.password = Words[1];
    NewUser.permssion =stoi(Words[2]);
    return NewUser;
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
vector <User> loadUsersFromFileToVector(string fileName) {
    vector <User> UserVector;
    fstream file;
    string line;
    User newUser;
    file.open(fileName, ios::in);
    if (file.is_open())
    {
        while (getline(file, line)) {
            newUser = FromLineToUserStrucu(line, "//");
            UserVector.push_back(newUser);
        }

    }
    return UserVector;
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
void PrintUserCard(User user) {
    cout << "-------------------------------------" << endl;
    cout << "name: ";
    cout << user.name << endl;
    cout << " Password: ";
    cout << user.password << endl;
    cout << "-------------------------------------" << endl;
}
bool GetUserByUserName(string UserName, vector<User>userVector) {
    for (User& user : userVector) {
        if (user.name == UserName)
        {
            PrintUserCard(user);
            return true;
        }
    }
    cout << "There is no User have user name = " << UserName << endl;
    return false;
}
bool IsUserExsit(string UserName, vector<User>userVector) {
    for (User& user : userVector) {
        if (user.name == UserName)
        {
            return true;
        }
    }
    return false;
}
void AddNewUser(vector <User>& UserVector) {
    fstream file;
    string line;
    file.open(UsersFile, ios::app);
    if (file.is_open())
    {
        User user = AddUserSt();
        if (IsUserExsit(user.name, UserVector))
        {
            cout << "This User Name is Alreay Exite " << endl;
            return;
        }
        file << StructToLineUser(user, "//") << endl;
        file.close();
    }
    UserVector = loadUsersFromFileToVector(UsersFile);
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
void ShowAllUsers(vector<User>UserVector) {
    for (User& user : UserVector) {
        cout << "-------------------------------------" << endl;
        cout << "name: ";
        cout << user.name << endl;
        cout << "Password: ";
        cout << user.password << endl;
        cout << "permssion: ";
        cout << user.permssion << endl;
        cout << "-------------------------------------" << endl;
    }
}
void DeleteUserFn(string userName, vector <User>& UserVector) {
    string Delete = "yes";
    fstream file;
    if (GetUserByUserName(userName, UserVector)) {
        cout << "Do you Want Delete This Recored? [yes]" << endl;
        cin >> Delete;
        if (Delete == "yes")
        {
            file.open(UsersFile, ios::out);
            for (User& user : UserVector) {

                if (user.name != userName)
                {
                    file << StructToLineUser(user, "//") << endl;

                }

            }
            cout << "Deleted Done";
            UserVector = loadUsersFromFileToVector(UsersFile);
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
void UpdaedUserFn(string Username, vector <User>& userVector) {
    string line;
    string update = "yes";
    fstream file;
    if (GetUserByUserName(Username, userVector))
    {
        cout << "Do You Want Update This recored? [yes]" << endl;
        cin >> update;
        if (update == "yes") {
            file.open(UsersFile, ios::out);
            for (User& user : userVector) {
                if (user.name != Username)
                {
                    file << StructToLineUser(user, "//") << endl;
                }
                else {
                    cout << "enter the name" << endl;
                    cin.ignore(); // Clear the newline character left in the input buffer
                    getline(cin, user.name);
                    cout << "enter Password" << endl;
                    getline(cin, user.password);
                    cout << "Updated Done";
                    file << StructToLineUser(user, "//") << endl;
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
        cout << "there is no User with this User Name" << endl;
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
    UsersMangment = 6,
    Exit = 7
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
enum EUsers
{
    AllUsers = 1,
    AddUser = 2,
    findUser =3,
    UpdateUser = 4,
    DeleteUser = 5
};
void PrintUserMenu() {
    cout << "Welcom In User Manmget" << endl;
    cout << "1 - AllUsers" << endl;
    cout << "2 - AddUser" << endl;
    cout << "3 - FindUser" << endl;
    cout << "4 - Update User" << endl;
    cout << "5 - Delete User" << endl;
}
void UsersFn(EUsers TChoose, vector<User>& UserVector) {
    string back = "no";
    switch (TChoose)
    {
    case EUsers::AllUsers:
        system("cls");
        ShowAllUsers(UserVector);
        //AllBalancefn(ClientV);
        break;
    case EUsers::findUser:
        system("cls");
        GetUserByUserName(WriteString("write username:"),UserVector);
        //AllBalancefn(ClientV);
        break;
    case EUsers::AddUser:
        system("cls");
        AddNewUser(UserVector);
        //DepositFn(WriteString("Write The Account Number: "), ClientV);
        break;
    case EUsers::DeleteUser:
        system("cls");
        DeleteUserFn(WriteString("write username:"), UserVector);
        break;
    case EUsers::UpdateUser:
        system("cls");
        UpdaedUserFn(WriteString("write username:"), UserVector);
      /*  cout << " We Transfer You to Main Menu ,, Why you login here ?? Are You Hacker +_+ !!" << endl;
        system("pause");*/
        break;
    default:
        break;
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
bool HasAccesToLogin(vector<User>& UserVector,User &CurrtentUser) {
    string UserName;
    string password;
    cout << "---- Login -----" << endl;
    cout << "UserName: " << endl;
    cin >> UserName;
    cout << "Password: " << endl;
    cin >> password;
    for (User& user : UserVector) {
        if (user.name == UserName)
        {
            if (user.password == password)
            {
                CurrentUser = user;
                return true;
            }
        }
    }
    return false;
}
void StartProject(vector<ClientSt>&ClientV,vector<User>& UserVector) {

    if (HasAccesToLogin(UserVector,CurrentUser))
    {
        system("cls");
        string containuo = "yes";
        int num = 0;
        ClientChoose Choose;
        do
        {
            cout << "----- Welcome " << CurrentUser.name << " --------" << endl;
            cout << "1 - Show All Client" << endl;
            cout << "2 - Add New Client" << endl;
            cout << "3 - UpdateClient" << endl;
            cout << "4 - DeleteClient" << endl;
            cout << "5 - Transactions" << endl;
            cout << "6 - UsersMangment" << endl;
            cout << "7 - Exit" << endl;
            cout << "--------------------------" << endl;
            cout << "WhatIs Your Chosse" << endl;
            cin >> num;
            system("cls");
            switch (Options(num))
            {
            case ClientChoose::ShowAll:
                if (IsHavePermssion(enMainMenuePermissions::pListClients))
                {
                    ShowAllClient(ClientV);
                }
                else
                {
                    AccessDenied();
                }
                break;
            case ClientChoose::AddNew:
                if (IsHavePermssion(enMainMenuePermissions::pAddNewClient))
                {
                    addNewClient(ClientV);
                }
                else
                {
                    AccessDenied();
                }
                break;
            case ClientChoose::Update:
                if (IsHavePermssion(enMainMenuePermissions::pUpdateClients))
                {
                    UpdaedByAccountNumber(WriteString("Write The Account Number"), ClientV);
                }
                else
                {
                    AccessDenied();
                }
                break;
            case ClientChoose::Delete:
                if (IsHavePermssion(enMainMenuePermissions::pDeleteClient))
                {
                    DeleteClient(WriteString("Write The Account Number: "), ClientV);
                }
                else
                {
                    AccessDenied();
                }
                break;
            case ClientChoose::Transaction:
                if (IsHavePermssion(enMainMenuePermissions::pTranactions))
                {
                    PrintTransactions();
                    TransactionFn((ETranscions)ReadShort(), ClientV);
                }
                else
                {
                    AccessDenied();
                }
            
                break;
            case ClientChoose::UsersMangment:
                if (IsHavePermssion(enMainMenuePermissions::pManageUsers))
                {
                    PrintUserMenu();
                    UsersFn((EUsers)ReadShort(), UserVector);
                }
                else
                {
                    AccessDenied();
                }
              
                break;
            case ClientChoose::Exit:
                cout << "You Exit From Bank System";
                return;
            }
            system("pause");
            system("cls");

        } while (containuo == "yes");
    }
    else {
        cout << "Invaled UserName Or Password!" << endl;
    }
}

int main()
{
    vector <ClientSt> ClientVector = loadClientFromFileToVector(fileName);
    vector <User> UserVector = loadUsersFromFileToVector(UsersFile);

    StartProject(ClientVector, UserVector);
    return 0;
}

