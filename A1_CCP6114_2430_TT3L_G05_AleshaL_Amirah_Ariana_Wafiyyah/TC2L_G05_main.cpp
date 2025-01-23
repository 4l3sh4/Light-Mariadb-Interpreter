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
string tableName;  // Variable to hold the table name
vector<string> colNames, colTypes;
vector<string> *pointer1 = &colNames;
vector<string> *pointer2 = &colTypes;

vector<vector<string>> columnAllData;
vector<vector<string>> *pointer3 = &columnAllData;

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

// ARIANA
// Function to process the "CREATE TABLE"
string createTable(string& command, ofstream& outputFile) {
    istringstream ss(command);
    string word, tableName, columns;
    bool foundCreateTable = false;

    // Search "CREATE TABLE" and extract table name
    while (ss >> word) {
        if (word == "CREATE") {
            ss >> word; // read the next word
            if (word == "TABLE") {
                ss >> tableName; // get the table name
                tableName.pop_back(); // Removing the ending semicolon or unwanted character
                foundCreateTable = true;
                break;
            }
        }
    }

    if (!foundCreateTable) {
        cout << "Invalid CREATE TABLE command!" << endl;
        return "";
    }

    // Extract columns between parentheses
    size_t start = command.find("(");
    size_t finish = command.find(")");
    if (start == string::npos || finish == string::npos || finish <= start) {
        cout << "Invalid syntax: missing parentheses or columns definition." << endl;
        return "";
    }

    columns = command.substr(start + 1, finish - start - 1); // Get the columns definition

    /*
    // Split columns by commas and separate name from type
    vector<string> columnList;
    istringstream columnStream(columns);
    string column;
    while (getline(columnStream >> ws, column, ',')) {
        columnList.push_back(column); // Add column to the list
    }

    // Separate column name and type into a vector of vectors for easy use
    vector<vector<string>> columnData(columnList.size());
    for (size_t i = 0; i < columnList.size(); ++i) {
        istringstream colStream(columnList[i]);
        string colName, colType;
        colStream >> colName >> colType; // Get column name and type
        columnData[i].push_back(colName); // Store column name
        columnData[i].push_back(colType); // Store column type
    }
    */

    // Split the column definitions
    vector<string> columnList;
    istringstream columnStream(columns);
    string column;
    while (getline(columnStream >> ws, column, ',')) {
        columnList.push_back(column); // Add each column definition to the list
    }

    // Separate column names and types into two vectors
    vector<string> colNames, colTypes;
    for (const string& colDef : columnList) {
        istringstream colStream(colDef);
        string colName, colType;
        if (!(colStream >> colName >> colType)) {
            cout << "Invalid column definition: " << colDef << endl;
            return "";
        }
        colNames.push_back(colName);
        colTypes.push_back(colType);
    }

    // Ensure columns meet requirements (if any function for validation exists)
    if (!validateColumns(columnList)) {
        return "";
    }

    // Output to file
    outputFile << "> CREATE TABLE " << tableName << endl;
    for (size_t i = 0; i < columnList.size(); ++i) {
        size_t spacePos = columnList[i].find(' ');
        if (spacePos != string::npos) {
            outputFile << "   " << columnList[i].substr(0, spacePos); // Column name only
        } else {
            outputFile << "   " << columnList[i]; // Full column definition
        }
        if (i < columnList.size() - 1) {
            outputFile << ","; // Comma after each column except the last
        }
        outputFile << endl;
    }
    outputFile << ");" << endl << endl;

    // Output to screen
    cout << "> CREATE TABLE " << tableName << endl;
    for (size_t i = 0; i < columnList.size(); ++i) {
        size_t spacePos = columnList[i].find(' ');
        if (spacePos != string::npos) {
            cout << "    " << columnList[i].substr(0, spacePos); // Column name only
        } else {
            cout << "    " << columnList[i]; // Full column definition
        }
        if (i < columnList.size() - 1) {
            cout << ","; // Comma after each column except the last
        }
        cout << endl;
    }
    cout << ");" << endl << endl;

    *pointer1 = colNames;
    *pointer2 = colTypes;

    return tableName; // Return tableName
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos) ? "" : str.substr(first, (last - first + 1));
}

bool validateColVal(const string& command, const vector<string>& colNames, const vector<string>& colTypes) {
    vector<string> inputColumns, inputValues;

    // Extract columns and values parts from the command
    size_t colStart = command.find("(");
    size_t colEnd = command.find(")");
    size_t valuesStart = command.find("VALUES");

    if (colStart == string::npos && colEnd == string::npos && valuesStart == string::npos) {
        cout << "Error: Invalid command format." << endl;
        return false;
    }

    string columnsPart = command.substr(colStart + 1, colEnd - colStart - 1);
    string valuesPart = command.substr(valuesStart + 7, command.find(");") - valuesStart - 6);

    istringstream columnsStream(columnsPart);
    string column;
    while (getline(columnsStream, column, ',')) {
        column.erase(remove(column.begin(), column.end(), ' '), column.end()); // Trim spaces
        inputColumns.push_back(column);
    }

    // Split the values into a vector
    istringstream valuesStream(valuesPart);
    string value;
    while (getline(valuesStream, value, ',')) {
        value.erase(remove(value.begin(), value.end(), ' '), value.end()); // Trim spaces
        if (!value.empty() && value[0] == '(') {
        value.erase(0, 1); // Remove the first character
        }
        inputValues.push_back(value);
    }

    /* Debug Purpose Only: Print colNames and inputColumns
    cout << "Table Columns (colNames): ";
    for (const auto& col : *pointer1) {
        cout << col << " ";
    }
    cout << endl;

    cout << "Input Columns (inputColumns): ";
    for (const auto& col : *pointer2) {
        cout << col << " ";
    }
    cout << endl;
    */

    // Ensure the number of columns and values match
    if (inputColumns.size() != inputValues.size()) {
        cout << "Error: Mismatch between columns and values." << endl;
        return false;
    }

    // Check if all input column names exist in the table column names
    for (const auto& inputCol : inputColumns) {
        if (find(colNames.begin(), colNames.end(), inputCol) == colNames.end()) {
            cout << "Error: Column " << inputCol << " does not exist in the table." << endl;
            return false;
        }
    }

    // Check if the data types match for each value
    for (size_t i = 0; i < inputColumns.size(); ++i) {
        auto it = find(colNames.begin(), colNames.end(), inputColumns[i]);
        if (it == colNames.end()) {
            cout << "Error: Column " << inputColumns[i] << " does not exist in the table." << endl;
            return false;
        }

        size_t colIndex = distance(colNames.begin(), it); // Get the index of the column in colNames

        if (colTypes[colIndex] == "INT") {
            // Check if the value is a valid integer
            if (inputValues[i].empty() || !all_of(inputValues[i].begin(), inputValues[i].end(), ::isdigit)) {
                cout << "Error: Value " << inputValues[i] << " is not an integer for column " << inputColumns[i] << "." << endl;
                return false;
            }
        } else if (colTypes[colIndex] == "TEXT") {
            // For text values, we assume all strings are valid
            continue;
        } else {
            cout << "Error: Unsupported data type " << colTypes[colIndex] << " for column " << inputColumns[i] << "." << endl;
            return false;
        }
    }

    return true; // Validation successful
}

string insertIntoTable(string& command, ofstream& outputFile, const string& tableName, vector<string> colNames, vector<string> colTypes){
    istringstream ss(command);
    string word, inputTableName, columns, values;
    vector<string> tableData;
    bool foundInsert = false;

    colNames = *pointer1;
    colTypes = *pointer2;

    size_t insertPos = command.find("INSERT INTO");
    size_t valuesPos = command.find("VALUES");

    if (insertPos == string::npos && valuesPos == string::npos) {
        cout << "Error: Invalid syntax." << endl;
        return "";}

    // Extract table name
    if(valuesPos != string::npos){
        size_t tableNamePos = 0; // Skip "INSERT INTO"
        int bracket_place = command.find("(");
        inputTableName = command.substr(tableNamePos, bracket_place);
        inputTableName = trim(inputTableName);  // Remove leading/trailing spaces
        cout << inputTableName;

        // Check if table name is valid
        if (inputTableName != tableName) {
            cout << "Error: Table " << inputTableName << " does not exist." << endl;
            return "";
        }
    }

    if(valuesPos != string::npos){
        if (!validateColVal(command, colNames, colTypes)) {
            return "";
        }
        string valuesPart = command.substr(valuesPos + 6); // Skip "VALUES"
        size_t valuesEnd = valuesPart.find_last_of(");");
        if (valuesEnd != string::npos) {
            valuesPart = valuesPart.substr(0, valuesEnd);
        }

        istringstream valuesStream(valuesPart);
        string value;
        while (getline(valuesStream, value, ',')) {
            value.erase(remove(value.begin(), value.end(), ' '), value.end()); // Remove spaces
            if (!value.empty() && value[0] == '(') {
                value.erase(0, 1); // Remove the leading '(' if present
            }
            if (!value.empty() && value.back() == ')') {
                value.pop_back(); // Remove the trailing ')' if present
            }
            tableData.push_back(value);
        }
    }

    // Write the insert statement to the output file
    if(insertPos != string::npos){
    cout << "> INSERT INTO " << endl;
    }

    if(valuesPos != string::npos){
    cout << "   (";
    for (size_t i = 0; i < colNames.size(); ++i) {
        cout << colNames[i];
        if (i < colNames.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;

    cout << "   VALUES (";
    for (size_t i = 0; i < tableData.size(); ++i) {
        cout << tableData[i];
        if (i < tableData.size() - 1) {
            cout << ", ";
        }
    }
    cout << ");" << endl << endl;
    }

    (*pointer3).push_back(tableData);

    /*
    // Print the insert statement to the console
    cout << "> INSERT INTO " << tableName << endl;
    cout << "   (";
    for (size_t i = 0; i < columns.size(); ++i) {
        cout << columns[i];
        if (i < columns.size() - 1) {
            cout << ", ";
        }
    }
    cout << ")" << endl;

    cout << "   VALUES (";
    for (size_t i = 0; i < values.size(); ++i) {
        cout << values[i];
        if (i < values.size() - 1) {
            cout << ", ";
        }
    }
    cout << ");" << endl << endl;
    */

    return "INSERT INTO processed";
}

string countRows (string& command, ofstream& outputFile, const string& tableName, const vector<vector<string>>& columnAllData){
    //dowoon
    istringstream ss(command);
    string word, inputTableName;
    int numRows;

    size_t countPos = command.find("COUNT(*)");
    size_t fromPos = command.find("FROM");

    if (countPos == string::npos || fromPos == string::npos) {
        cout << "Error: Invalid syntax." << endl;
        return "";
    }

    // Extract table name
    if(fromPos != string::npos){
        size_t tableNameStart = fromPos + 4; // Skip "FROM"
        string inputTableName = command.substr(tableNameStart);
        inputTableName = trim(inputTableName);  // Remove leading/trailing spaces
        if (!inputTableName.empty() && inputTableName.back() == ';') {
            inputTableName.pop_back();
        }

        // Check if table name is valid
        if (inputTableName != tableName) {
            cout << "Error: Table " << inputTableName << " does not exist." << endl;
            return "";
        }

        size_t numRows = 0;
        for (const auto& row : columnAllData) {
            bool isEmpty = true;
            for (const auto& value : row) {
                if (!value.empty()) { // Check if value is non-empty
                    isEmpty = false;
                    break;
                }
            }
            if (!isEmpty) {
                ++numRows;
            }
        }

        cout << "> SELECT COUNT(*) FROM " << inputTableName <<endl;
        cout << numRows << endl;

    }
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
                            }
                            else if (creatingTable) {
                                // Append lines until ')' is found
                                command += " " + words;
                                if (words.find(")") != string::npos) {
                                    creatingTable = false;
                                    ofstream outputFile;
                                    string createTableResult = createTable(command, outputFile);  // Make sure 'command' holds the user input for CREATE TABLE
                                    if (!createTableResult.empty()) {
                                        tableName = createTableResult;  // Store the created table name
                                    }
                                    command.clear();
                                    }
                                }
                            else if (words.find("INSERT INTO") != string::npos){
                                ofstream outputFile;
                                insertIntoTable(words, outputFile, tableName, *pointer1, *pointer2);
                            }
                            else if (words.find("VALUES") != string::npos){
                                ofstream outputFile;
                                insertIntoTable(words, outputFile, tableName, *pointer1, *pointer2);
                            }
                            else if (words.find("COUNT") != string::npos){
                                ofstream outputFile;
                                //wonpil
                                countRows(words, outputFile, tableName, *pointer3);
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
