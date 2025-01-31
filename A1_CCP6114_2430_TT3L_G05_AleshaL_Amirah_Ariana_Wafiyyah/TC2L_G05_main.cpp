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
string database_name; // For the database's name.
string file_name;
bool database_name_check = false; // Database's name has not been determined yet.
vector<string> input;

// All the needed vectors
vector<string> col1;
vector<string> col2;
vector<string> col3;
vector<string> col4;
vector<string> col5;
vector<string> col6;
vector<string> col7;
vector<string> col8;
vector<string> col9;
vector<string> col10;

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
    cout << "*  > UPDATE TABLE            *" << endl;
    cout << "*  > DELETE FROM TABLE       *" << endl;
    cout << "*  > SELECT FROM TABLE       *" << endl;
    cout << "*  > READ FROM FILE          *" << endl;
    cout << "******************************" << endl;
}

int main()
{
    ifstream inputfile;
    string words;
    string file_name;

    intro();
    while(loop == "True") // Check to see if the program still needs to run.
    {
        input = {}; // Resetting the vector size to zero each time the user inputs something will allow us to reuse it.
        if(loop =="True") // Making sure that the vector size is always 0 when we loop the program.
        {
            input_user();
            if(input.size() == 3) // Making sure that there are at least three words in the user's input.
            {
                // CREATE DATABASE
                if(input[0] == "CREATE" && input[1] == "DATABASE") // Making sure that the user's input has 'CREATE DATABASE' in it.
                {
                    if(database_name_check == false){
                        cout << "Valid input!" << endl;
                        database_name = input[2]; // Initializing the database's name.
                        cout << "The database's name is " << database_name << "." << endl << endl;
                        database_name_check = true;
                    }
                    else{
                    cout << "You already have a database! " << endl;
                    cout << "The database's name is " << database_name << "." << endl << endl;
                    }
                }
                // LIST ALL COMMANDS
                else if(input[0] == "LIST" && input[1] == "ALL" && input[2] == "COMMANDS"){
                    list_commands();
                }
                // READ FROM FILE (THE MAIN PART OF THE ASSIGNMENT)
                else
                {
                    cout << "Not a valid input!" << endl;
                }
            }
            else if(input.size() == 4){
                if(input[0] == "READ" && input[1] == "FROM" && input[2] == "FILE"){
                    file_name = input[3];
                    inputfile.open(file_name);

                    if (inputfile.is_open()) {
                        while (getline(inputfile, words)){

                            // 1. CALL string.find() function to search for a specific string from
                            //    each line of quote, and store the location in variable dashloc. Look up
                            //    the C++ reference for strings to see in detail how to use this function.
                            //    Notice that the author of the quote always appears after a double dash.
                            int create_place = words.find("CREATE ");
                            int file_place = words.find(".txt;");
                            int database_place = words.find("DATABASES");

                            if (create_place != string::npos && file_place != string::npos){
                                // Extract the substring containing the author name using the found location
                                // of the double dash.
                                file_name = words.substr(create_place + 7, file_place - 7); // File name finally completed!

                                cout << "> CREATE " << file_name << ".txt;" << endl;
                            }
                            else if(database_place != string::npos){
                            cout << "> " << "DATABASES" << ";" << endl;
                            cout << "C:\\" << "mariadb\\" << file_name << ".mdb" << endl;
                            }
                            else{
                                cout << endl;
                            }
                        }
                    // close file
                    inputfile.close();
                    }
                }

            }
            // code from here
            else if(input.size() > 4){
                cout << "Lol" << endl;
            }
            else{
                cout << "Not a valid input!" << endl;
            }
        }
    }
}