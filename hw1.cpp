#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Alp Onder Yener

// A file has a matrix with -'s and #'s in it. Checks if it is rectangular.
// Then, it gets an input where s is star, b is blank and / is new line
// Example input: ssbs/sbs//
// Then it checks if the input matrix can be put on the matrix in the file (s and # cannot go over each other)

int main() {
    string filename;
    cout << "Please enter the file name: " << endl;
    cin >> filename;
    ifstream file(filename);  // first attempt to open the file

    while(file.fail()) // going to keep wanting the name of the file if it is unavailable in the files
    {
        file.clear();
        cout << "Could not open the file. Please enter a valid file name:" << endl;
        cin >> filename;
        file.open(filename.c_str());
    }

    vector<vector<char>> charVector; // the char matrix with - and #

    string line;

    while (getline(file, line)) // reading the lines and adding them to the vector
    {
        vector<char> tempVect; // created a temporary vector to add to the main vector
        for (int i = 0; i < line.length(); i++) {
            tempVect.push_back(line[i]);
        }
        charVector.push_back(tempVect); // adding the vector of char to the vector of vector of char
    }

    for (int i = 0; i < charVector.size(); i++) {
        for (int j = 0; j < charVector[i].size(); j++) {
            if (charVector[i][j] != '-' && charVector[i][j] != '#') // checks if there are only - and # as characters
            {
                cout << "Erroneous file content. Program terminates.";
                return 0;
            }

        }
        if (charVector[i].size() != charVector[0].size()) // checks the size of the rows, must be a rectangle
        {
            cout << "Erroneous file content. Program terminates.";
            return 0;
        }
    }

    cout << "The matrix file contains:" << endl;

    for (int i = 0; i < charVector.size(); i++) // to display the file
    {
        for (int j = 0; j < charVector[i].size(); j++) {
            cout << charVector[i][j];
        }
        cout << endl;
    }

    while (true) { // will go on forever until the input it Quit
        cout << "Enter the string query for a shape, or \"Quit\" to terminate the program:" << endl;
        string query;
        cin >> query;
        if (query == "Quit") {
            return 0;
        }

        vector<string> queryLines;
        while (query.find('/') != string::npos) // seperated by the slash, adds the strings into vector queryLines
        {
            string toAdd = query.substr(0, query.find('/'));
            queryLines.push_back(toAdd);
            query = query.substr(query.find('/') + 1);
        }
        queryLines.push_back(query); // to add the part after the last /

        for (int i = 0; i < queryLines.size(); i++) // convert the elements of queryLines from, for example, 1s2s1b to sssb
        {                                           // now, both 2s1b and 1s1s1b will be ssb and some confusion will be extracted
            string toAdd = "";
            for (int j = 0; j < queryLines[i].size(); j += 2) {
                int multiply = (int) queryLines[i][j] - '0';
                toAdd += string(multiply, queryLines[i][j + 1]);
            }
            queryLines[i] = toAdd;
        }

        vector<vector<char>> inputCharMatrix; // will get the string vector of the input (queryLines) to a char matrix. Now we have 2 char matrices

        for (int i = 0; i < queryLines.size(); i++)
        {
            vector<char> temp;
            for(int j = 0; j < queryLines[i].size(); j++)
            {
                temp.push_back((char)queryLines[i][j]);
            }
            inputCharMatrix.push_back(temp);
        }

        int heightFile = charVector.size(), widthFile = charVector[0].size();
        int heightInp = inputCharMatrix.size(), widthInp = inputCharMatrix[0].size();

        if(heightFile < heightInp || widthFile < widthInp){ //general check. If the input exceeds the file's limits then no placement if found.
            cout << "No placements found." << endl;
        }
        else{

            vector<int> startR, startC; // startR is the vector which contains the placement's starting index's row number
                                        // startC is the same but for column number, these two will be used later
            bool nope = true; //will be explained when it is used, this should be declared before the for loop,
//                                                  thats why it is declared way up here
            for (int i = 0; i < charVector.size() - inputCharMatrix.size() + 1; i++) // the rows to be tried, for the first input char
            {
                for (int j = 0; j < charVector[i].size() - inputCharMatrix[0].size() + 1; j++) // the elements of that row to be tried, for the first input char
                {
                    if (inputCharMatrix[0][0] == 'b' || (inputCharMatrix[0][0] == 's' && charVector[i][j] == '-')) // now we have the possible starting points
                    {
                        bool fail = false;
                        for (int k = 1; k < inputCharMatrix[0].size(); k++) // after the starting point, it checks for the other characters in that row,
                        {                                                   // it checks whether they fit or not
                            if (inputCharMatrix[0][k] == 's' && charVector[i][j+k] == '#')
                            {
                                fail = true; // our attempt failed
                            }

                        }
                        if (!fail) // if our attempt does not fail, we have successfully placed the first row, it starts at row i, column j in our file
                        {                                                                                      // (this will be important to keep in mind)
                            for (int m = 1; m < inputCharMatrix.size(); m++) // remaining rows of inputCharMatrix, a.k.a the one with sbss chars
                            {
                                for (int l = 0; l < inputCharMatrix[m].size(); l++) // every char of that row
                                {
                                    if ((inputCharMatrix[m][l] == 's' && charVector[i+m][j+l] == '#') || i + m > charVector.size() || j+l > charVector[i].size())
                                    { //checks the remaining chars                  i+ and j+ is because we started from row i column j in the charVector
                                        fail = true;                                // in other words, (i,j) is our starting point
                                    }
                                }
                            }

                            if (!fail) //we have successfully did a full placement
                            {
                                startR.push_back(i); // adds the starting row's index into the vector
                                startC.push_back(j); // adds the starting column's index into the vector
                                nope = false; // this is to show that we have been successful in doing a full placement
                            }                 // with this boolean, the code can continue

                        }
                    }
                }
            }
            vector<vector<int>> indexS; //indices of the chars s

            if (nope) //if nope is true, we have failed
            {
               cout << "No placements found." << endl;
            }
            else //so we have not failed
            {
                for (int i = 0; i < inputCharMatrix.size(); i++) //this double loop obtains the indices of s
                {
                    vector <int> temp;
                    for (int j = 0; j < inputCharMatrix[i].size(); j++)
                    {
                        if (inputCharMatrix[i][j] == 's'){temp.push_back(j);}
                    }
                    indexS.push_back(temp);
                }

                vector <int> indexQueue; //indices of our points

                for (int i = 0; i < startR.size(); i++) //startR and startC have the same size
                {
                    for (int k = 0; k < indexS.size(); k++)
                    {
                        for (int m = 0; m < indexS[k].size(); m++)
                        {
                            int x = startR[i] + k;  // x is the x value in (x,y), same for y. k is the row number and indexS[k][m] is the column number
                            int y = startC[i] + indexS[k][m];
                            indexQueue.push_back(x);
                            indexQueue.push_back(y); // we have added the points back to back. for points (0,2) (0,4)
                        }                               // indexQueue will be 0204
                    }

                }


                int noOfS = 0; //s count
                for (int i = 0; i < inputCharMatrix.size(); i++)
                {
                    for (int j = 0; j < inputCharMatrix[i].size(); j++)
                    {
                       if (inputCharMatrix[i][j] == 's'){noOfS++;}  //counts the number of s's
                    }
                }

                int placement = 0; // which placement are we on

                for (int i = 0; i < indexQueue.size(); i+=noOfS*2) // number of s = number of points showcased per placement hence
                {                                                   // double of that will work since every point is equivalent to 2 elements from
                    placement++;                                            // indexQueue
                    cout << "Placement number " << placement << ":" << endl;
                    int two = 1; // we will use this to cout the points. Modular arithmetic will be used
                    for (int j = 0; j < noOfS*2; j++) // the number of integers we are obtaining is double the number of s's
                    {                                   // (this was explained in more detail a couple of lines above)
                        if (two%2 == 1){cout << "(" << indexQueue[i+j] << ",";}
                        if (two%2 == 0){cout << indexQueue[i+j] << ") ";} // these are to form the parentheses in our points,
                        two++;                                              // variable "two" is used
                    }
                    cout << endl;
                }
            }
        }
    }
    return 0;
}