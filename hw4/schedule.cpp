//
// Created by ALP on 4/16/2023.
//
using namespace std;
#include "schedule.h"
#include <iostream>

Schedule::Schedule() // default constructor
{
    time_slots = 0;
    data = new string * [7];
    for (int i = 0; i < 7; i++)
    {
        data[i] = nullptr;
    }
}

Schedule::Schedule(int c) // parametric constructor (matrix of "free"s)
{
    time_slots = c;
    data = new string * [7]; // dynamically allocated string pointer array
    for (int i = 0; i < 7; i++)
    {
        data[i] = new string[c]; // all those elements of the array point to an array of strings
        for (int j = 0; j < c; j++)
        {
            data[i][j] = "free";
        }
    }
}

Schedule::Schedule(const Schedule &copy) // deep copy
{
    time_slots = (copy.time_slots);
    data = new string * [7]; // create new private data

    for(int i = 0; i < 7; i++)
    {
        data[i] = new string[time_slots]; // create the matrix once again, all the elements same to the parameter copy
        for(int j = 0; j < time_slots; j++)
        {
            data[i][j] = (copy.data)[i][j];
        }
    }
}

Schedule::~Schedule() // destructor
{
    for(int i = 0; i < 7; i++)
    {
        delete [] data[i]; // delete all the pointers in the array
    }
    delete data; // delete the pointer of pointer itself
}

Schedule &Schedule::operator=(const Schedule &rhs) // lhs will be equal to rhs
{
    if (this != &rhs)
    {
        for(int i = 0; i < 7; i++) // first delete lhs
        {
            delete [] data[i];
        }
        delete data;

        time_slots = (rhs.time_slots); // create new private data
        data = new string * [7];

        for(int i = 0; i < 7; i++)
        {
            data[i] = new string[time_slots]; // reconstruct the matrix with the elements of rhs
            for(int j = 0; j < time_slots; j++)
            {
                data[i][j] = (rhs.data)[i][j];
            }
        }
    }
    return *this;
}

// Getters and setters for two private members:
string **Schedule::getterData() const{return data;}
int Schedule::getterSlot() const {return time_slots;}
void Schedule::setterData(string **ptr) {data = ptr;}
void Schedule::setterSlot(int slot) {time_slots = slot;}

Schedule Schedule::operator+(Schedule & rhs)
{
    Schedule result; // we will return this
    string ** ourData;
    int our_time_slots = rhs.getterSlot();
    ourData = new string * [7];
    for (int i = 0; i < 7; i++) // first, create with all "free"
    {
        ourData[i] = new string[our_time_slots];
        for (int j = 0; j < our_time_slots; j++)
        {
            ourData[i][j] = "free";
        }
    } // this matrix will be manipulated

    string ** rhsData = rhs.getterData();
    if (this != &rhs) // if they are not the same
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < time_slots; j++)
            {
                if(!(data[i][j] == "free" && rhsData[i][j] == "free")){ourData[i][j] = "busy";} // if they are not both free
            }
        }

        result.setterSlot(our_time_slots);
        result.setterData(ourData); // set our private data to the object result
    }
    else{result = *this;} // if they are the same then just return lhs
    return result;
}

const Schedule Schedule::operator*(const Schedule & rhs)
{
    Schedule result;
    string ** ourData;
    int our_time_slots = rhs.getterSlot();
    ourData = new string * [7];
    for (int i = 0; i < 7; i++)
    {
        ourData[i] = new string[our_time_slots];
        for (int j = 0; j < our_time_slots; j++)
        {
            ourData[i][j] = "busy"; // create a matrix with all busy
        }
    }

    string ** rhsData = rhs.getterData();
    if (this != &rhs) // if they are not equal
    {
        for (int i = 0; i < 7; i++)
        {
            for (int j = 0; j < time_slots; j++)
            {
                if(!(data[i][j] == "busy" && rhsData[i][j] == "busy")){ourData[i][j] = "free";} // if even one is free then change it to free
            }
        }

        result.setterSlot(our_time_slots);
        result.setterData(ourData); // set our private data to the object result
    }
    else{result = *this;}
    return result;
}

string *Schedule::operator[](const Days rhs) const
{
    int row = rhs; // if Monday, row = 0 etc
    string * result;
    result = data[row]; // we are using and equalizing the data of the lhs
    return result;
}

const bool Schedule::operator<(const Schedule rhs)
{
    int rhsCount = 0, lhsCount = 0;
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < time_slots; j++)
        {
            if(data[i][j] == "busy"){lhsCount++;} // count the busy slots of lhs
        }
    }
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < rhs.getterSlot(); j++)
        {
            if((rhs.getterData())[i][j] == "busy"){rhsCount++;} // count the busy slots of rhs
        }
    }

    if (lhsCount < rhsCount){return true;} // return according to the busy slot counts
    return false;
}


// Free functions:

Schedule operator+(Schedule lhs, Days rhs)
{
    Schedule result = lhs;
    int row = rhs; // if rhs = Monday, row = 0 etc

    string ** ourData = result.getterData();
    for (int i = 0; i < (result.getterSlot()); i++){ourData[row][i] = "busy";} // make that Day equal to busy for all slots

    result.setterData(ourData); // set the data to our result

    return result; // return
}

Schedule operator+(Schedule lhs, int rhs)
{
    Schedule result = lhs;
    string ** ourData = result.getterData();
    for (int i = 0; i < 7; i++){ourData[i][rhs] = "busy";} // make that time slot all busy

    result.setterData(ourData); // set the data to our result
    return result;
}

ostream& operator<<(ostream &output, const Schedule & rhs)
{
    string dayNames[7] = {"Mo: ", "Tu: ","We: ","Th: ","Fr: ","Sa: ", "Su: "}; // to display with <<
    string result = "";
    string ** ourData = rhs.getterData();
    for (int i = 0; i < 7; i++)
    {
        result += dayNames[i]; // first it will go Mo: , then Tu:  etc...
        for(int j = 0; j < rhs.getterSlot(); j++)
        {
            result += (ourData[i][j] + " "); // add to result string
        }
        result += '\n'; // go to new line
    }
    output << result;
    return output;
}

ostream& operator<<(ostream &output, const Days & rhs)
{
    string dayNames[7] = {"Monday", "Tuesday","Wednesday","Thursday","Friday","Saturday", "Sunday"};
    output << dayNames[rhs]; // From dayNames, cout the parametered enum rhs
    return output;
}