/*******************************************************************************************
 *
 *  Author: Sanithu Hulathduwage
 *  Email: s.v.imansith@gmail.com
 *  Name : P02
 *  Title : Linear Search: Using JSON and GETCH
 *  Course : CMPS 3013
 *  Semester : Spring 2024
 *
 *  Description:
 *        This program employs getch and JSON to retrieve information from a
 *dictionary file. Once a word is found, it prints the corresponding definition
 *below the word.
 *
 ********************************************************************************************/

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

unordered_map<string, string> loadDictionary(const string &filePath) {
  ifstream fileStream(filePath);
  unordered_map<string, string> dictionary;
  if (fileStream.is_open()) {
    json data;
    fileStream >> data;
    for (auto it = data.begin(); it != data.end(); ++it) {
      dictionary[it.key()] = it.value();
    }
    fileStream.close();
  } else {
    cerr << "Failed to open file: " << filePath << endl;
  }
  return dictionary;
}

vector<string> partialMatch(const unordered_map<string, string> &dictionary,
                            const string &substring) {
  vector<string> matches;
  for (const auto &entry : dictionary) {
    if (entry.first.find(substring) != string::npos) {
      matches.push_back(entry.first);
    }
  }
  return matches;
}

void titleBar(const string &title, int length) {
  string padding = string((length / 2) - (title.size() / 2), ' ');
  cout << padding << title << padding << endl;
}

void printMenu(const vector<string> &options) {
  for (size_t i = 0; i < options.size(); ++i) {
    cout << i + 1 << ". " << options[i] << endl;
  }
}

int main() {
  // Load dictionary
  string dictionaryFilePath = "./data/dictionary.json";
  unordered_map<string, string> dictionary = loadDictionary(dictionaryFilePath);

  // Main loop
  while (true) {
    // Display menu
    system("clear"); // Clear screen (Linux/Unix)
    cout << "Dictionary Search" << endl;
    vector<string> mainMenu = {
        "Type letters and watch the results change.",
        "Hit the DEL key to erase a letter from your search string.",
        "When a single word is found, the definition will print below."};
    printMenu(mainMenu);

    // Get user input
    cout << "Enter search string ('Z' to quit): ";
    string searchStr;
    getline(cin, searchStr);
    if (searchStr == "Z" || searchStr == "z") {
      break;
    }

    // Perform partial matching
    vector<string> matches = partialMatch(dictionary, searchStr);

    // Display matches
    system("clear"); // Clear screen (Linux/Unix)
    cout << "Matches found for '" << searchStr << "':" << endl;
    for (const auto &match : matches) {
      cout << match << ": " << dictionary[match] << endl;
    }

    // Wait for user to continue
    cout << "Press Enter to continue...";
    cin.ignore(); // Ignore any leftover newline characters
    cin.get();    // Wait for Enter key
  }

  cout << "Goodbye!" << endl;

  return 0;
}
