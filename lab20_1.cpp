#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(const string& filename, vector<string>& names, vector<int>& scores, vector<char>& grades){
    ifstream file(filename);
    if(file.is_open()){
        string line;
        while(getline(file, line)){
            unsigned int pos = line.find(":");
            if (pos != string::npos && pos > 0 && pos < line.length() - 1) {
                string name = line.substr(0, pos);
                names.push_back(name);
                string scoreStr = line.substr(pos + 1);
                size_t space_pos;
                int scoreSum = 0;
                while ((space_pos = scoreStr.find(" ")) != string::npos) {
                    string numStr = scoreStr.substr(0, space_pos);
                    int score = atoi(numStr.c_str());
                    scoreSum += score;
                    scoreStr = scoreStr.substr(space_pos + 1);
                }
                if (!scoreStr.empty()) {
                    int score = atoi(scoreStr.c_str());
                    scoreSum += score;
                }
                char grade = score2grade(scoreSum);
                scores.push_back(scoreSum); 
                grades.push_back(grade);
            }
        }
        file.close();
    }
}

void getCommand(string &command, string &key){
    cout << "Please input your command: ";
    cin >> command;
    if(toUpperStr(command) == "GRADE" or toUpperStr(command) == "EXIT" or toUpperStr(command) == "NAME"){
        cin.ignore();
        getline(cin,key);

    }
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < names.size(); i++){
        if(toUpperStr(names[i]) == key){
            found = true;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
        }
    }
    if(found==false){
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    cout << "---------------------------------\n";
    for(size_t i = 0; i < grades.size(); i++){
        if(toupper(grades[i]) == toupper(key.at(0))){
            found = true;
            cout << names[i] << " (" << scores[i] << ")\n";
        }
    }
    if(found == false){;
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}