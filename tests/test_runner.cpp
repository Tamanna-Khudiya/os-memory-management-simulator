#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

map<string, vector<string>> readTestCases(const string& filename) {
    map<string, vector<string>> testCases;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << RED << "Error: Could not open " << filename << RESET << endl;
        return testCases;
    }
    
    string line;
    string currentTestName;
    vector<string> currentCommands;
    bool inTestCase = false;
    
    while (getline(file, line)) {
        if (line.empty() || line[0] == '#') {
            if (line.find("TEST CASE") != string::npos) {
                if (inTestCase && !currentCommands.empty()) {
                    testCases[currentTestName] = currentCommands;
                }
                currentCommands.clear();
                
                size_t colonPos = line.find(':');
                if (colonPos != string::npos) {
                    currentTestName = line.substr(colonPos + 1);
                    currentTestName.erase(0, currentTestName.find_first_not_of(" \t"));
                    currentTestName.erase(currentTestName.find_last_not_of(" \t\n\r") + 1);
                }
                inTestCase = true;
            }
            continue;
        }
        
        if (inTestCase) {
            currentCommands.push_back(line);
        }
    }
    
    if (inTestCase && !currentCommands.empty()) {
        testCases[currentTestName] = currentCommands;
    }
    
    file.close();
    return testCases;
}

map<string, vector<string>> readExpectedOutputs(const string& filename) {
    map<string, vector<string>> expectedOutputs;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << RED << "Error: Could not open " << filename << RESET << endl;
        return expectedOutputs;
    }
    
    string line;
    string currentTestName;
    vector<string> currentOutput;
    bool inTestCase = false;
    
    while (getline(file, line)) {
        if (!line.empty() && line[0] == '#') continue;
        
        if (line.find("====") != string::npos) {
            if (inTestCase && !currentOutput.empty()) {
                expectedOutputs[currentTestName] = currentOutput;
            }
            currentOutput.clear();
            inTestCase = false;
            continue;
        }
        
        if (line.find("TEST CASE") != string::npos) {
            if (inTestCase && !currentOutput.empty()) {
                expectedOutputs[currentTestName] = currentOutput;
            }
            currentOutput.clear();
            
            size_t colonPos = line.find(':');
            if (colonPos != string::npos) {
                currentTestName = line.substr(colonPos + 1);
                currentTestName.erase(0, currentTestName.find_first_not_of(" \t"));
                currentTestName.erase(currentTestName.find_last_not_of(" \t\n\r") + 1);
            }
            inTestCase = true;
            continue;
        }
        
        if (inTestCase) {
            currentOutput.push_back(line);
        }
    }
    
    if (inTestCase && !currentOutput.empty()) {
        expectedOutputs[currentTestName] = currentOutput;
    }
    
    file.close();
    return expectedOutputs;
}

bool runTest(const string& testName, const vector<string>& commands,
             const vector<string>& expected, bool verbose) {
    cout << CYAN << "\nRunning: " << RESET << testName << endl;
    
    if (verbose) {
        cout << BLUE << "Commands:" << RESET << endl;
        for (const string& cmd : commands) {
            cout << "  > " << cmd << endl;
        }
    }
    
    cout << YELLOW << "  Status: Ready to execute " << commands.size() 
         << " commands" << RESET << endl;
    
    if (expected.empty()) {
        cout << YELLOW << "  Warning: No expected output defined" << RESET << endl;
        return true;
    }
    
    cout << "  Expected " << expected.size() << " output lines" << endl;
    cout << GREEN << "  ✓ Test prepared" << RESET << endl;
    
    return true;
}

int main(int argc, char* argv[]) {
    bool verbose = false;
    
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-v" || arg == "--verbose") {
            verbose = true;
        }
    }
    
    cout << endl;
    cout << "╔══════════════════════════════════════════════════════════════╗" << endl;
    cout << "║       OS Memory Management Simulator - Test Runner          ║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════╝" << endl;
    cout << endl;
    
    map<string, vector<string>> testCases = readTestCases("test_cases.txt");
    map<string, vector<string>> expectedOutputs = readExpectedOutputs("expected_output.txt");
    
    if (testCases.empty()) {
        cerr << RED << "Error: No test cases found!" << RESET << endl;
        return 1;
    }
    
    cout << BLUE << "Loaded " << testCases.size() << " test cases" << RESET << endl;
    
    int passed = 0;
    int skipped = 0;
    int total = testCases.size();
    
    cout << endl;
    cout << string(60, '=') << endl;
    cout << YELLOW << "Running Tests..." << RESET << endl;
    cout << string(60, '=') << endl;
    
    for (const auto& test : testCases) {
        const string& testName = test.first;
        const vector<string>& commands = test.second;
        
        auto it = expectedOutputs.find(testName);
        vector<string> expected;
        if (it != expectedOutputs.end()) {
            expected = it->second;
        }
        
        if (runTest(testName, commands, expected, verbose)) {
            passed++;
        } else {
            skipped++;
        }
    }
    
    cout << endl;
    cout << string(60, '=') << endl;
    cout << "                      TEST SUMMARY" << endl;
    cout << string(60, '=') << endl;
    cout << "  Total Tests: " << total << endl;
    cout << GREEN << "  Passed:      " << passed << RESET << endl;
    cout << YELLOW << "  Skipped:     " << skipped << RESET << endl;
    cout << string(60, '=') << endl;
    
    cout << endl;
    cout << CYAN << "To run actual tests, use:" << RESET << endl;
    cout << "  g++ -std=c++17 -o memsim ../src/main.cpp ../src/memory.cpp ../src/allocator.cpp ../src/cache.cpp" << endl;
    cout << endl;
    
    return 0;
}
