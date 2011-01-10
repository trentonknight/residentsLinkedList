#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctype.h>


using namespace std;

const int MAX_RES = 500;
const string RES_LOG = "RESIDENT.txt";

enum phoneType
{
    WORK, HOME, CELL
        };

struct residentInfo
{
    string SSN;
    string fInitial;
    string surName;
    string phoneNum;
    enum phoneType phone;
    int sizeOfarray;
};

void displayIntro(residentInfo resLog[],bool& ver);
void newRes(residentInfo resLog[], bool& ver, int& index);
void existRes(residentInfo resLog[], bool& ver, int& index);
void checkSSN(const residentInfo resLog[],bool& ver,int& index);
void checkPHONE(const residentInfo resLog[],bool& ver, int& index);
void checkInitial(const residentInfo resLog[],bool& ver,int& index);
void checkSurname(const residentInfo resLog[],bool& ver, int& index);
void menuDisplay(residentInfo resLog[],bool& ver, int& index);
void searchResident(residentInfo resLog[], bool& ver, int& index);
void deleteResident(residentInfo resLog[], bool& ver, int& index);

int main()
{


    bool ver;
    residentInfo resLog[MAX_RES];
    displayIntro(resLog, ver);
    return 0;

}

void displayIntro(residentInfo resLog[],bool& ver)
{

    char userSelection;
    int index;
    cout << "Which data would you like to use?" << endl;
    cout << "\tN - New resident data" << endl;
    cout << "\tE - Existing resident data" << endl;
    cout << "Enter choice: " << endl;
    cin >> userSelection;
    if ((userSelection == 'n') || (userSelection == 'N'))
    {
        newRes(resLog, ver, index);

    }
    else if((userSelection == 'e') || (userSelection == 'E'))
    {
        existRes(resLog, ver, index);

    }
    else
    {
        cout << "That is not a selection!" << endl;
    }
}

void newRes(residentInfo resLog[], bool& ver, int& index){

    char ch;
    char cont = 'c';
    ofstream inData;

    inData.open(RES_LOG.c_str(), ios::app);

    if(!inData)
    {
        cout << "ERROR: cannot read from RESIDENT.txt" << endl;
    }

    while ((cont == 'c') && (index < 501))
    {
        do{
            cout << "What is residents SSN? " << endl;
            cin >> resLog[index].SSN;
            checkSSN(resLog, ver, index);
        }while(!ver);

        do {
            cout << "What is residents first initial? " << endl;
            cin >> resLog[index].fInitial;
            checkInitial(resLog, ver, index);
        } while(!ver);

        do{
            cout << "What is residents surname? " << endl;
            cin >> resLog[index].surName;
            checkSurname(resLog, ver, index);
        }while(!ver);

        do{
            cout << "What is residents phone number? " << endl;
            cin >> resLog[index].phoneNum;
            checkPHONE(resLog, ver, index);
        } while(!ver);


        do {
            cout << "Where is this number located? " << endl;
            cout << "Enter the appropriate letter for location" << endl;
            cout << "Work = W" << endl;
            cout << "Home = H" << endl;
            cout << "Cell = C" << endl;
            cin >> ch;

            switch(ch)
            {
            case 'W':
                resLog[index].phone = WORK;
                ver = true;
                break;
            case 'w':
                resLog[index].phone = WORK;
                ver = true;
                break;
            case 'H':
                resLog[index].phone = HOME;
                ver = true;
                break;
            case 'h':
                resLog[index].phone = HOME;
                ver = true;
                break;
            case 'C':
                resLog[index].phone = CELL;
                ver = true;
                break;
            case 'c':
                resLog[index].phone = CELL;
                ver = true;
                break;
            default:
                cout << "this was not a choice" << endl;
                ver = false;
            }
            inData  << resLog[index].fInitial
                    << "\t" << resLog[index].surName
                    <<"\t" << resLog[index].SSN
                    <<"\t"<< resLog[index].phoneNum;

        }while(!ver);

        switch(resLog[index].phone)
        {
        case 0:
            inData << " W" << endl;
            break;
        case 1:
            inData << " H" << endl;
            break;
        default:
            inData << " C" << endl;
        }

        cout << "Type c to continue with another entry" << endl;
        cout << "or q to quit: ";
        cin >> cont;

        index++;
        cout << index << " Records Entered" << endl;

    }
    inData.close();
    existRes(resLog, ver, index);
}

void existRes(residentInfo resLog[], bool& ver, int& index){


    int counterR = 0;
    ifstream outData;
    char forEnum[MAX_RES];
    outData.open(RES_LOG.c_str());

    if(!outData){
        cout << "Error opening file!" << endl << endl;
    }
    else{


     cout << "NAME           SSN          PHONE          TYPE" << endl;
     cout << "-------------- ------------ -------------- ----" << endl;

        while (!outData.eof())
        {

            outData.peek();
            cout << left;
            outData >> setprecision(1);
            outData >> resLog[counterR].fInitial;
            cout << setw(2)<< resLog[counterR].fInitial;
            outData >> resLog[counterR].surName;
            cout << setw(13)<< resLog[counterR].surName;
            outData >> resLog[counterR].SSN;
            cout << setw(14)<< resLog[counterR].SSN;
            outData >> resLog[counterR].phoneNum;
            cout << setw(13)<< resLog[counterR].phoneNum;
            outData >> forEnum[counterR];

            switch(forEnum[counterR])
            {
            case 'W':
                resLog[counterR].phone = WORK;
                cout << " WORK"<< endl;
                break;
            case 'H':
                resLog[counterR].phone = HOME;
                cout << " HOME" << endl;
                break;
            case 'C':
                resLog[counterR].phone = CELL;
                cout << " CELL" << endl;
                break;
            }
              counterR++;
        }
        outData.close();
        index = counterR;

        menuDisplay(resLog, ver, index);
    }
}
void checkSSN(const residentInfo resLog[],bool& ver, int& index)
{
    size_t found;
    //EXAMINE SSN
    if(resLog[index].SSN.length() != 10)
    {
        cout << "You entered an odd number of digits" << endl;
        cout << "EXAMPLE: Social Security Numbers: 55-55-5555" << endl;
        cout << "Try again: " << endl;
        ver = false;
    }
    found=resLog[index].SSN.find_first_not_of("1234567890-");
    if (found!=string::npos)
    {
        cout << "Sorry your "<< (int(found) + 1) << " character is incorrect" << endl;
        cout << "EXAMPLE: Social Security Numbers: 55-55-5555" << endl;
        ver = false;
    }
    else if((resLog[index].SSN.at(2) != '-') || (resLog[index].SSN.at(5) != '-'))
    {
        cout << "Please check your format" << endl;
        cout << "EXAMPLE: Social Security Numbers: 55-55-5555" << endl;
        ver = false;
    }
    else
    {
        ver = true;
    }

}

void checkPHONE(const residentInfo resLog[], bool& ver, int& index)
{
    size_t found;
    //EXAMINE PHONE NUMBER
    if(resLog[index].phoneNum.length() != 12)
    {
        cout << "You entered an odd number of digits" << endl;
        cout << "EXAMPLE: Phone Numbers: 555-555-5555" << endl;
        cout << "Try again: " << endl;
        ver = false;
    }
    found=resLog[index].phoneNum.find_first_not_of("1234567890-");
    if (found!=string::npos)
    {
        cout << "Sorry your "<< (int(found) + 1) << " character is incorrect" << endl;
        cout << "EXAMPLE: Phone Numbers: 555-555-5555" << endl;
        ver = false;
    }
    else if((resLog[index].phoneNum.at(3) != '-') || (resLog[index].phoneNum.at(7) != '-'))
    {
        cout << "Please check your format" << endl;
        cout << "EXAMPLE: Social Security Numbers: 55-55-5555" << endl;
        ver = false;
    }
    else
    {
        ver = true;
    }
}

void checkInitial(const residentInfo resLog[],bool& ver, int& index)
{
    size_t found;
    ver = false;
    //EXAMINE ALL ALPHA INPUTS

    if(resLog[index].fInitial.length() > 1)
    {
        cout << "One initial for first name only please" << endl;
        cout << "Try again: " << endl;
        ver = false;
    }
    found=resLog[index].fInitial.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (found!=string::npos)
    {
        cout << "Sorry "<< (int(found) + 1) << " is not an alphabetic character" << endl;
        ver = false;
    }
    else
    {
        ver = true;
    }

}

void checkSurname(const residentInfo resLog[],bool& ver, int& index)
{
    size_t found;
    ver = false;
    //EXAMINE ALL ALPHA INPUTS

    if(resLog[index].surName.length() > 15)
    {
        cout << "Only 15 characters allowed" << endl;
        cout << "Try again: " << endl;
        ver = false;
    }
    found=resLog[index].surName.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    if (found!=string::npos)
    {
        cout << "Sorry "<< (int(found) + 1) << " is not an alphabetic character" << endl;
        ver = false;
    }
    else
    {
        ver = true;
    }

}

void menuDisplay(residentInfo resLog[], bool& ver, int& index)
{
    char letter;

    cout << "\n\t\tMAIN MENU\n" << endl;
    cout << "To Add a Resident use A" << endl;
    cout << "To Find a Resident use F" << endl;
    cout << "To Delete a Resident use D" << endl;
    cout << "To quit this program use Q" << endl;
    cout << "$";
    cin >> letter;

    switch(letter)
    {
    case 'A':
        newRes(resLog, ver, index);
        break;
    case 'a':
        newRes(resLog, ver, index);
        break;
    case 'F':
        searchResident(resLog,ver, index);
        break;
    case 'f':
        searchResident(resLog,ver, index);
        break;
    case 'D':
        deleteResident(resLog, ver, index);
        break;
    case 'd':
        deleteResident(resLog, ver, index);
        break;
    case 'Q':
        cout << "Quiting..." << endl;
        break;
    case 'q':
        cout << "Quiting..." << endl;
        break;
    default:
        cout << "This was not a selection." << endl;
    }

}

void searchResident(residentInfo resLog[],bool& ver, int& index){

    int locate, count;
    count = index;
    string searchString;

    cout << "To search pick from the following: " << endl;
    while(count != 0)
    {
        cout << resLog[count].fInitial <<"\t"<< resLog[count].surName
                << "\t"<< resLog[count].SSN << endl;
        count--;
    }

    do{
        cout << "What is residents SSN? " << endl;
        cout << "$" << endl;
        cin >> resLog[count].SSN;
        checkSSN(resLog, ver, count);
    }while(!ver);
    if(ver){
        searchString = resLog[count].SSN;
        cout << "You selected " << searchString << endl;
        cout << "Searching....." << endl;

        for(locate = 0; locate < index; locate++)
            if(resLog[locate].SSN == searchString)
            {
            cout << resLog[locate].fInitial
                    <<"\t"<< resLog[locate].surName
                    << "\t"<< resLog[locate].SSN
                    << "\t" << resLog[locate].phoneNum;

            switch(resLog[locate].phone)
            {
            case WORK:
                cout << "\tWORK" << endl;
                break;
            case HOME:
                cout << "\tHOME" << endl;
                break;
            default:
                cout << "\tCELL" << endl;
            }
        }
    }

    cout << "\n\n\n\nReturning to Main Menu..." << endl;
    existRes(resLog, ver, index);
}
void deleteResident(residentInfo resLog[],bool& ver, int& index){

    ofstream inData;

    inData.open(RES_LOG.c_str());

    int locate, count, del = 0;
    count = index;
    string searchString;
    cout << "Select the Resident record you wish to delete: " << endl;
    while(count != 0)
    {
        cout << resLog[count].fInitial <<"\t"<< resLog[count].surName
                << "\t"<< resLog[count].SSN << endl;
        count--;
    }

    do{
        cout << "What is residents SSN? " << endl;
        cout << "$" << endl;
        cin >> resLog[count].SSN;
        checkSSN(resLog, ver, count);
    }while(!ver);
    if(ver){
        searchString = resLog[count].SSN;
        cout << "You selected " << searchString << endl;
        cout << "Searching....." << endl;

        for(locate = 0; locate < index; locate++)
            if(resLog[locate].SSN == searchString)
            {
            cout << "Deleting: " << endl;
            for(int i = del; i < locate; i++)
            {
                resLog[del] = resLog[del + 1];
                resLog[locate -1].fInitial = '\0';
                resLog[locate -1].phoneNum = '\0';
                resLog[locate -1].SSN = '\0';
                resLog[locate -1].surName = '\0';
            }
        }
    }
    while(index > 0)
    {
        inData  << resLog[index].fInitial
                << "\t" << resLog[index].surName
                <<"\t" << resLog[index].SSN
                <<"\t"<< resLog[index].phoneNum
                << endl;
        index--;
    }
    inData.close();
    cout << "\n\n\n\nReturning to Main Menu..." << endl;
    existRes(resLog, ver, index);
}
