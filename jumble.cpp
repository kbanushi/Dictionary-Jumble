#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <unordered_set>
#include <sstream>
using namespace std;

int loadFile(string filename, unordered_map<string, unordered_set<string> >& map){
    int count = 0;
    ifstream inFS(filename);

    if (!inFS.is_open())
        return -1;
    
    cout << "reading input file..." << endl;
    string line, word, key;
    while (getline(inFS, line)){
        stringstream ss(line);
        ss >> word;
        key = word;
        sort(key.begin(), key.end());

        map[key].insert(word);

        count++;
    }

    inFS.close();
    return count;
}

void createReport(const unordered_map<string, unordered_set<string> >& map, int& numClasses, int& sizeOfLargest, string& keyOfLargest, unordered_set<string>& largestSet){
    numClasses = 0, sizeOfLargest = 0;

    int size;
    for (auto key : map){
        size = key.second.size();
        numClasses++;

        if (size > sizeOfLargest){
            keyOfLargest = key.first;
            largestSet = key.second;
            sizeOfLargest = size;
        }
    }
}

void printReport(const int& numWords, const int& numClasses, const int& sizeOfLargest, const string& keyOfLargest, const unordered_set<string>& largestSet){
    cout << "REPORT" << endl;
    cout << "num_words\t\t: " << numWords << endl;
    cout << "num_classes\t\t: " << numClasses << endl;
    cout << "size-of-largest-class\t: " << sizeOfLargest << endl;
    cout << "largest-class key\t: " << keyOfLargest << endl;
    cout << "members of largest class:" << endl << endl;
    for (auto word : largestSet)
        cout << "'" << word << "'" << endl;
}

int main(int argc, char* argv[]){
    ifstream inFS;
    unordered_map<string, unordered_set<string> > map;
    string filename;

    if (argc == 1){
        cout << "Enter filename as command line argument and try again." << endl;
        return 1;
    }

    filename = argv[1];
    int numWords = loadFile(filename, map);
    if (numWords == -1){
        cout << "Error: file " << filename << " not found." << endl;
        return 1;
    }

    cout << "start entering jumbled words (ctrl-d to terminate)" << endl;

    string query, line;
    while (getline(cin, line)){
        stringstream ss(line);
        ss >> query;
        sort(query.begin(), query.end());

        if (map.count(query) > 0){
            cout << "English Anagrams Found:" << endl;
            for (auto word : map[query]){
                cout << "\t" << word << endl;
            }
        }
        else{
            cout << "no anagrams found...try again" << endl;
        }
    }
    
    int numClasses, sizeOfLargest;
    string keyOfLargest;
    unordered_set<string> largestSet;
    createReport(map, numClasses, sizeOfLargest, keyOfLargest, largestSet);
    printReport(numWords, numClasses, sizeOfLargest, keyOfLargest, largestSet);
    
    return 0;
}