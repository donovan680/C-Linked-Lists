#include <iostream>
#include <fstream>
#include <string.h>//for functions in date function
#include <time.h> //for functions in date function
#include <sys/stat.h>//for mkdir functions
#include <unistd.h>//for usleep function
#include <ctype.h>//for toupper function in swap function

using namespace std;

struct PersonInfo
{
    char FirstName[20];
    char LastName[20];
    char Address[40];
    char PhoneNumber[20];

    int Age;

    PersonInfo* Link;
};

bool EmptyFileChecker(ifstream& FI, const char* P);
void AddPeopleToList(PersonInfo*& HeadPointer);
void RebuildOldList(ifstream& FI, PersonInfo*& HeadPointer, const char* P);
void DisplayList(PersonInfo* HeadPointer);
void SaveSettings(ofstream& FO, const PersonInfo* HeadPointer, const char* P);
void DisplayMenu(PersonInfo*& HeadPointer, const char* P, ifstream& FileIn, ofstream& FileOut);
void SortContacts(PersonInfo*& HeadPointer);
bool NamesInOrder(const char LastName1[], const char LastName2[]);
string Date();

//Delete Contact
//ENCRYPT LIST?

//Check for memory leaks in code and destructor?
//Return something - noun-like
//void adjective - like

int main()
{
    PersonInfo* HeadPointer;

    const char* Path = "/Users/josephlyons/Library/Application Support/The Lyons' Den Labs/TheLyons'DenContactInformation.txt";//code variable for username

    ifstream FileIn;
    ofstream FileOut;

    mkdir("/Users/josephlyons/Library/Application Support/The Lyons' Den Labs", ACCESSPERMS);//MODE??

    if (!EmptyFileChecker(FileIn, Path))
        AddPeopleToList(HeadPointer);

    else
        RebuildOldList(FileIn, HeadPointer, Path);

    DisplayMenu(HeadPointer, Path, FileIn, FileOut);

    //SortContacts(HeadPointer);

    SaveSettings(FileOut, HeadPointer, Path);
}

void DisplayMenu(PersonInfo*& HeadPointer, const char* P, ifstream& FileIn, ofstream& FileOut)
{
    short int MenuChoice;

    do
    {
        cout << "(1) Display Contact List\n";
        cout << "(2) Organize Contact List\n";//delete when done with program and automatically sort list before saving.
        cout << "(3) Add Contact/s\n";
        cout << "(4) Delete Contact/s\n";
        cout << "(5) Quit\n\n";

        cout << "Choice: ";
        cin >> MenuChoice;

        if (MenuChoice == 1)
            DisplayList(HeadPointer);

        else if (MenuChoice == 2)
            SortContacts(HeadPointer);

        else if (MenuChoice == 3)
            AddPeopleToList(HeadPointer);

        else if (MenuChoice == 4)
            cout << "choice 4";
    }     while (MenuChoice != 5);
}

bool EmptyFileChecker(ifstream& FI, const char* P)//DONE
{
    FI.open(P);

    if (FI.fail())
        return false;

    else if (FI.eof())//return 0 if file doesnt exist or if file is empty
        return false;

    else
        return true;
}

void AddPeopleToList(PersonInfo*& HeadPointer)
{
    PersonInfo* CurrentPosition;

    char UserChoice;

    do
    {
        CurrentPosition = new PersonInfo;

        if (CurrentPosition == NULL)
        {
            cout << "Not enough memmory to make new contact.";
            return;
        }

        cout << "\nEnter First Name:   ";
        cin >> CurrentPosition->FirstName;
        CurrentPosition->FirstName[0] = toupper(CurrentPosition->FirstName[0]);//automatically capitalize first name

        cout << "Enter Last Name:    ";
        cin >> CurrentPosition->LastName;
        CurrentPosition->LastName[0] = toupper(CurrentPosition->LastName[0]);//automatically capitalize last name

        cin.ignore();//flushes a single newline left in input buffer from previous cin >>
        cout << "Enter Adress:       ";
        cin.getline(CurrentPosition->Address, 40);//using cin.get() to allow for spaces in address

        cout << "Enter Phone Number: ";
        cin.getline(CurrentPosition->PhoneNumber, 20);//using cin.get() to allow for spaces in number

        cout << "Enter Age:          ";
        cin >> CurrentPosition->Age;

        cout << "\nAdd another contact? Y/N: ";
        cin >> UserChoice;

        cout << "\n";

        CurrentPosition->Link = HeadPointer;

        HeadPointer = CurrentPosition;
    }     while (UserChoice == 'y' || UserChoice == 'Y');

    SortContacts(HeadPointer);
}

void RebuildOldList(ifstream& FI, PersonInfo*& HeadPointer, const char* P)
{
    PersonInfo* TemporaryPersonPointer;
    char EndOfListChecker = 1;//initialized at a not 0 to allow entrance into loop

    while (EndOfListChecker != 0)
    {
        TemporaryPersonPointer = new PersonInfo;

        if (TemporaryPersonPointer == NULL)
            cout << "Not enough memory to generate the full list";

        FI >> TemporaryPersonPointer->FirstName;
        FI >> TemporaryPersonPointer->LastName;

        FI.ignore();//flushes a single newline from input
        FI.getline(TemporaryPersonPointer->Address, 40);

        FI.ignore();
        FI.getline(TemporaryPersonPointer->PhoneNumber, 20);

        FI >> TemporaryPersonPointer->Age;

        TemporaryPersonPointer->Link = HeadPointer;

        HeadPointer = TemporaryPersonPointer;

        FI.get(EndOfListChecker);

        while (EndOfListChecker == '\n')
        {
            FI.get(EndOfListChecker);
        }

        if (EndOfListChecker != 0)
            FI.putback(EndOfListChecker);
    }
}

void DisplayList(PersonInfo* HeadPointer)
{
    do
    {
        cout << "\nFirst Name:   ";
        cout << HeadPointer->FirstName << endl;

        cout << "Last Name:    ";
        cout << HeadPointer->LastName << endl;

        cout << "Adress:       ";
        cout << HeadPointer->Address << endl;

        cout << "Phone Number: ";
        cout << HeadPointer->PhoneNumber << endl;

        cout << "Age:          ";
        cout << HeadPointer->Age;

        cout << "\n\n";

        HeadPointer = HeadPointer->Link;

        usleep(75000);
    }     while (HeadPointer != NULL);

    cout << "Press enter to go to main menu: ";

    cin.ignore(2);

    cout << "\n";
}

void SaveSettings(ofstream& FO, const PersonInfo* HeadPointer, const char* P)
{
    FO.open(P);

    if (FO.fail())
        cout << "Couldn't Open File\n";

    while (HeadPointer != NULL)
    {
        FO << HeadPointer->FirstName << endl;
        FO << HeadPointer->LastName << endl;
        FO << HeadPointer->Address << endl;
        FO << HeadPointer->PhoneNumber << endl;
        FO << HeadPointer->Age << endl << endl;

        HeadPointer = HeadPointer->Link;
    }

    FO << (char)0 << endl;

    FO << "Date of Settings: " << Date() << endl;

    FO.close();
}

void SortContacts(PersonInfo*& HeadPointer)
{
    PersonInfo* MovingPointer1;//used to "crawl" down list
    PersonInfo* MovingPointer2;//used to "crawl" down list
    PersonInfo* StaticPointer;//always points at first node to give HeadPointer a way to link back to the list at end
    PersonInfo* TemporaryPointer;//holds a node during a swap

    bool ZeroSwapsOccured = false;//initialized at false to allow entrance into loop once

    MovingPointer1 = StaticPointer = HeadPointer;//set all to point at first node

    MovingPointer2 = HeadPointer->Link;

    while (ZeroSwapsOccured == false)
    {
        ZeroSwapsOccured = true;

        while (MovingPointer2->Link != NULL)
        {
            if (!NamesInOrder(MovingPointer1->LastName, MovingPointer2->LastName))
            {
                ZeroSwapsOccured = false;

                //Temp = MP1
                //MP1  = MP2
                //MP2  = TEMP

                MovingPointer1->Link = MovingPointer2->Link;
                MovingPointer2->Link = MovingPointer1;
                HeadPointer->Link = MovingPointer2;
            }
        }
    }

    HeadPointer = StaticPointer;//link HeadPointer back to list after sort
}

bool NamesInOrder(const char LastName1[], const char LastName2[])
{
    for (int i = 0; LastName1[i] || LastName2[i]; ++i)//go until you get to the end of the larger name
    {
        if (toupper(LastName1[i]) < toupper(LastName2[i]))
            return true;

        if (toupper(LastName1[i]) > toupper(LastName2[i]))
            return false;
    }

    return true;//this will only be used if same last name

    //build in fucntionality to then go to first name after last name, if both last names are the same
}

string Date()//not my code here - just modified it to read easier
{
    char Time[50];
    time_t now = time(NULL);
    strftime(Time, 50, "%b, %d, %Y", localtime(&now)); //short month name
    return string(Time);
}