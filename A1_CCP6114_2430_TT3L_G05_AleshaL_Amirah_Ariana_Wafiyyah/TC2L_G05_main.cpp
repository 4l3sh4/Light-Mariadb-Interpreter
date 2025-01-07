// *********************************************************
// Program: TC2L_G05_main.cpp
// Course: CCP6114 Programming Fundamentals
// Lecture Class: TC2L
// Tutorial Class: TT3L
// Trimester: 2430
// Member_1: 242UC244SU | ALESHA NOOR BINTI MOHAMMAD SALIM | ALESHA.NOOR.MOHAMMAD@student.mmu.edu.my | +60 18-789 3381
// Member_2: 242UC244LC | AMIRAH BALQIS BINTI AZLAN | AMIRAH.BALQIS.AZLAN@student.mmu.edu.my | +60 13-397 6759
// Member_3: 242UC244PW | ARIANA FALISYA BINTI AIDY @ MOHAMED SHAWAL | ARIANA.FALISYA.AIDY@student.mmu.edu.my | +60 13-436 8182
// Member_4: 242UC244T9 | WAFIYYAH DIANNAH BINTI HUSSIN | WAFIYYAH.DIANNAH.HUSSIN@student.mmu.edu.my | +60 12-235 2861
// *********************************************************
// Task Distribution
// Member_1: Coding the base for the assignment, and CREATE DATABASE.
// Member_2: Drawing the CREATE DATABASE flowchart. Helped to combine it all together.
// Member_3: Drawing the CREATE TABLE flowchart. Helped to combine it all together.
// Member_4: Drawing the INSERT ROWS flowchart. Helped to combine it all together.
// *********************************************************

#include <iostream> // Input and output.
#include <string> // For string-type variables and inputs.
#include <vector> // For vectors, mainly used for detecting words in a user's input.
#include <array> // For arrays, will be used for tables in the future.
#include <sstream> // For getting individual words from a string.
#include <algorithm> // For transform, so that we could change the user's input into all caps.
#include <fstream> // To read files, and write inside files.
using namespace std;

string loop = "True"; // This allows the program to function in a loop.
string words; // To get individual words from a user's input. Used in the input_user() function.
string database_name;
vector<string> input;

// Going to use this code a lot so might as well turn it into a function, LOL!
// For user input.
vector<string> input_user() {

    // We use getline to split the user's sentence into words.
    getline(cin,words);

    // To avoid user from inputting an empty input.
    while(words == "")
    {
        cout << "Not a valid input!" << endl;
        // Get another input from the user.
        getline(cin,words);
    }

    // Turning the user's input into all caps.
    // https://www.geeksforgeeks.org/how-to-convert-std-string-to-lower-case-in-cpp/
    transform(words.begin(), words.end(), words.begin(), ::toupper);

    // I heavily referenced this website link to create the code below.
    // https://www.geeksforgeeks.org/split-string-by-space-into-vector-in-cpp-stl/

    string s;

    stringstream ss(words);

    while (getline(ss, s, ' ')) {

        // Store individual words into the vector.
        input.push_back(s);
    }

    // Return the vector.
    return input;
}

void intro(){
    cout << "*************************************************" << endl;
    cout << "*   WELCOME TO THE LIGHT MARIADB INTERPRETER!   *" << endl;
    cout << "*************************************************" << endl;
    cout << "* TO SEE THE LIST OF ALL THE AVAILABLE COMMANDS *" << endl;
    cout << "*        PLEASE TYPE 'LIST ALL COMMANDS'        *" << endl;
    cout << "*************************************************" << endl;
}

void list_commands(){
    cout << "******************************" << endl;
    cout << "*   LIST OF EVERY COMMAND:   *" << endl;
    cout << "******************************" << endl;
    cout << "*  > CREATE DATABASE         *" << endl;
    cout << "*  > CREATE TABLE            *" << endl;
    cout << "*  > SELECT * FROM TABLE     *" << endl;
    cout << "*  > READ FROM FILE          *" << endl;
    cout << "******************************" << endl;
}

int main()
{
    ifstream inputfile;

    intro();
    while(loop == "True") // Check to see if the program still needs to run.
    {
        input = {}; // Resetting the vector size to zero each time the user inputs something will allow us to reuse it.
        if(loop =="True") // Making sure that the vector size is always 0 when we loop the program.
        {
            input_user();
            if(input.size() == 3) // Making sure that there are at least three words in the user's input.
            {
                if(input[0] == "CREATE" && input[1] == "DATABASE") // Making sure that the user's input has 'CREATE DATABASE' in it.
                {
                    cout << "Valid input!" << endl;
                    database_name = input[2]; // Initializing the database's name.
                    cout << "The database's name is " << database_name << "." << endl;
                    // This is where the program ends for now. CREATE DATABASE function finished, yahoo! � Alesha
                }
                else if(input[0] == "LIST" && input[1] == "ALL" && input[2] == "COMMANDS"){
                    list_commands();
                }
                else if(input[0] == "READ" && input[1] == "FROM" && input[2] == "FILE"){
                    inputfile.open("fileInput.mdb");
                }
                else
                {
                    cout << "Not a valid input!" << endl;
                }
            }
            else{
                cout << "Not a valid input!" << endl;
            }
        }
    }
}