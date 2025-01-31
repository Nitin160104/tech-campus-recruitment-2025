#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h> // For Unix-based mkdir
#include <sys/types.h>

#ifdef _WIN32
    #include <direct.h>  // Windows-specific mkdir
    #define mkdir _mkdir  // Use _mkdir on Windows
#endif

using namespace std;

// Function to create a directory if it doesn't exist
void createDirectory(const string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) { // Check if directory exists
        if (mkdir(path.c_str()) != 0) { // Create directory (Windows `_mkdir` does not take mode argument)
            cerr << "Error creating directory: " << path << endl;
        }
    }
}

// Function to extract logs for a specific date
void extractLogs(const string& logFilePath, const string& date) {
    ifstream logFile(logFilePath);
    if (!logFile.is_open()) {
        cerr << "Error opening log file: " << logFilePath << endl;
        return;
    }

    string outputDir = "output"; // Simple relative output directory
    createDirectory(outputDir);

    string outputFilePath = outputDir + "/output_" + date + ".txt";
    ofstream outputFile(outputFilePath, ios::out | ios::trunc);
    if (!outputFile.is_open()) {
        cerr << "Error opening output file: " << outputFilePath << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(logFile, line)) {
        if (line.substr(0, 10) == date) {
            outputFile << line << endl;
            found = true;
        }
    }

    if (!found) {
        outputFile << "No logs found for " << date << endl;
    }

    logFile.close();
    outputFile.close();
}

int main() {
    string date;
    cout << "Enter the date (YYYY-MM-DD): ";
    cin >> date;

    string logFilePath = "logs_2024.log"; // Ensure this file exists in the same directory as the script

    ifstream checkFile(logFilePath);
    if (!checkFile.is_open()) {
        cerr << "Log file does not exist: " << logFilePath << endl;
        return 1;
    }
    checkFile.close();

    cout << "Extracting logs for " << date << "..." << endl;
    extractLogs(logFilePath, date);
    cout << "Logs have been saved to output/output_" << date << ".txt" << endl;

    return 0;
}

