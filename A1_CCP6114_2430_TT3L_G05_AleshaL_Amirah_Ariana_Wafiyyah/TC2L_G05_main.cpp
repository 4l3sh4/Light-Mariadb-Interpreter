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

// Going to use this code a lot so might as well turn it into a function, LOL!
// For user input.
vector<string> input_user() {

    // We use getline to split the user's sentence into words.
    getline(cin, words);

    // To avoid user from inputting an empty input.
    while (words == "") {
        cout << "Not a valid input!" << endl;
        // Get another input from the user.
        getline(cin, words);
    }

    string s;
    stringstream ss(words);

    while (getline(ss, s, ' ')) {
        // Store individual words into the vector.
        input.push_back(s);
    }

    // Return the vector.
    return input;
}

void intro() {
    cout << "*************************************************" << endl;
    cout << "*   WELCOME TO THE LIGHT MARIADB INTERPRETER!   *" << endl;
    cout << "*************************************************" << endl;
    cout << "* TO SEE THE LIST OF ALL THE AVAILABLE COMMANDS *" << endl;
    cout << "*        PLEASE TYPE 'LIST ALL COMMANDS'        *" << endl;
    cout << "*************************************************" << endl;
}

void list_commands() {
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

bool validateColumns(const vector<string>& column) {
    if (column.size() > 10) {
        cout << "Only maximum 10 columns is allowed." << endl;
        return false;
    }

    for (const string& col : column) {
        istringstream colStream(col);
        string colName, colType;
        colStream >> colName >> colType;

        if (colType != "INT" && colType != "TEXT") {
            cout << "Invalid data type: " << colType << " in column " << col << endl;
            return false;
        }
    }
    return true;
}

// Function to process the "CREATE TABLE"
void createTable(string& command, ofstream& outputFile) {
    istringstream ss(command);
    string word, tableName, columns;
    bool foundCreateTable = false;

    // Search "CREATE TABLE" from input file and extract table name
    while (ss >> word) {
        if (word == "CREATE") {
            ss >> word; // read the next word
            if (word == "TABLE") {
                ss >> tableName; // the next word will be the table name
                foundCreateTable = true;
                break;
            }
        }
    }

    // Extract columns between parentheses
    size_t start = command.find("(");
    size_t finish = command.find(")");
    if (start != string::npos && finish != string::npos && finish > start) {
        columns = command.substr(start + 1, finish - start - 1);
    } else {
        cout << "Invalid syntax: missing parentheses." << endl;
        return;
    }

    // Split columns by commas
    vector<string> columnList;
    istringstream columnStream(columns);
    string column;
    while (getline(columnStream >> ws, column, ',')) { // `ws` skips leading whitespace
        columnList.push_back(column);
    }

    // Use vector<vector<string>> to store columns dynamically
    vector<vector<string>> columnData(columnList.size());
    for (size_t i = 0; i < columnList.size(); ++i) {
        istringstream colStream(columnList[i]);
        string colName;
        colStream >> colName;
        columnData[i].push_back(colName); // Store column name
    }

    // Check if the columns meet requirements
    if (!validateColumns(columnList)) {
        return;
    }


    // Write output into the output file
    outputFile << "> CREATE TABLE " << tableName << endl;
    for (size_t i = 0; i < columnList.size(); ++i) {
        size_t spacePos = columnList[i].find(' ');
        if (spacePos != string::npos) {
            outputFile << "   " << columnList[i].substr(0, spacePos); // Write column name without type
        } else {
            outputFile << "   " << columnList[i]; // If no type, write full column
        }
        if (i < columnList.size() - 1) {
            outputFile << ",";
        }
        outputFile << endl;
    }
    outputFile << ");" << endl << endl;

    // Print to screen
    cout << "> CREATE TABLE " << tableName << endl;
    for (size_t i = 0; i < columnList.size(); ++i) {
        size_t spacePos = columnList[i].find(' ');
        if (spacePos != string::npos) {
            cout << "    " << columnList[i].substr(0, spacePos); // Print column name without type
        } else {
            cout << "    " << columnList[i]; // If no type, print full column
        }
        if (i < columnList.size() - 1) {
            cout << ",";
        }
        cout << endl;
    }
    cout << ");" << endl << endl;
}

int main() {
    ifstream inputfile;
    string words;
    string file_name;

    intro();
    while (loop == "True") // Check to see if the program still needs to run.
    {
        input = {}; // Resetting the vector size to zero each time the user inputs something will allow us to reuse it.
        if (loop == "True") // Making sure that the vector size is always 0 when we loop the program.
        {
            input_user();
            if (input.size() == 3) // Making sure that there are at least three words in the user's input.
            {
                // CREATE DATABASE
                if (input[0] == "CREATE" && input[1] == "DATABASE") // Making sure that the user's input has 'CREATE DATABASE' in it.
                {
                    if (database_name_check == false) {
                        cout << "Valid input!" << endl;
                        database_name = input[2]; // Initializing the database's name.
                        cout << "The database's name is " << database_name << "." << endl << endl;
                        database_name_check = true;
                    } else {
                        cout << "You already have a database! " << endl;
                        cout << "The database's name is " << database_name << "." << endl << endl;
                    }
                }
                // LIST ALL COMMANDS
                else if (input[0] == "LIST" && input[1] == "ALL" && input[2] == "COMMANDS") {
                    list_commands();
                }
                // READ FROM FILE (THE MAIN PART OF THE ASSIGNMENT)
                else {
                    cout << "Not a valid input!" << endl;
                }
            } else if (input.size() == 4) {
                if (input[0] == "READ" && input[1] == "FROM" && input[2] == "FILE") {
                    file_name = input[3];
                    inputfile.open(file_name);

                    if (inputfile.is_open()) {
                            string words, command;
                            bool creatingTable = false;
                        while (getline(inputfile, words)) {

                            // 1. CALL string.find() function to search for a specific string from
                            //    each line of quote, and store the location in variable dashloc. Look up
                            //    the C++ reference for strings to see in detail how to use this function.
                            //    Notice that the author of the quote always appears after a double dash.
                            int create_place = words.find("CREATE ");
                            int file_place = words.find(".txt;");
                            int database_place = words.find("DATABASES");

                            if (create_place != string::npos && file_place != string::npos) {
                                // Extract the substring containing the author name using the found location
                                // of the double dash.
                                file_name = words.substr(create_place + 7, file_place - 7); // File name finally completed!

                                cout << "> CREATE " << file_name << ".txt;" << endl;
                            } else if (database_place != string::npos) {
                                cout << "> " << "DATABASES" << ";" << endl;
                                cout << "C:\\" << "mariadb\\" << file_name << ".mdb" << endl;
                            }
                            // Check for "CREATE TABLE"
                            else if (words.find("CREATE TABLE") != string::npos) {
                                creatingTable = true;
                                command = words;
                            } else if (creatingTable) {
                                // Append lines until ')' is found
                                command += " " + words;
                                if (words.find(")") != string::npos) {
                                    creatingTable = false;
                                    ofstream outputFile;
                                    createTable(command, outputFile);
                                    command.clear();
                                }
                            }
                              }
                            }

                        }
                        // close file
                        inputfile.close();
                    }
            else {
                cout << "Not a valid input!" << endl;
            }
        }
    }
}
