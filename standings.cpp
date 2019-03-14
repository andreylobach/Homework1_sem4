#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <utility>
#include <algorithm>
#include <iomanip>
#define nNumberMatches 6
#define nNumberTeams 6 
using namespace std;

map<string, int> Place(map<string, int> Scores, map<string, int> Wins) {
    map<string, int> mPlaces;
    int nMaxScore = 0, nCount = 0, nCountMaxScore = 0, nPreviousWins = 0;
    string sTeam;
    
    while((nCount != 4) && (Scores.size() != 0)) {
        for (auto item : Scores) {
            
            if (item.second >= nCountMaxScore) {
                sTeam = item.first;
                nCountMaxScore = item.second;
            }
        }

        if ((nMaxScore != nCountMaxScore) || ((nCountMaxScore == nMaxScore) && (Wins[sTeam] > nPreviousWins))) {
            nCount++;
            nMaxScore = nCountMaxScore;
        }

        cout << Scores.size() << " " << sTeam <<  " " << nCount << " " << Wins[sTeam] << endl;
        nPreviousWins = Wins[sTeam];
        if (nCount < 4)
            mPlaces[sTeam] = nCount;
        Scores.erase(sTeam);
        nCountMaxScore = 0;
    }
    return mPlaces;
}

int main() {
    int MaxLen = 0, first, second;
    set<string> Teams;
    map<string, int> Scores;
    map<string, int> Wins;
    map<pair<string, string>, pair<string, string>> Results; 
    string team1, team2;

    for (int i = 0; i < nNumberMatches; i++) {
        cin >> team1;
        cin.ignore(3);
        cin >> team2;
        cin.ignore(3);
        cin >> first;
        cin.ignore(1);
        cin >> second;
    
        Teams.insert(team1);
        Teams.insert(team2);

        if (Results.count(make_pair(team1, team2))) {
            cout << "Error! This commands already have played" << endl;
        } 

        if (team1.size() > MaxLen)
            MaxLen = team1.size();
        if (team2.size() > MaxLen)
            MaxLen = team2.size();    
        
        if (first > second) {
            Scores[team1] += 3;
            Scores[team2] += 0;
            Wins[team1] += 1;
            Results[make_pair(team1, team2)] = make_pair("W", "L");
            Results[make_pair(team2, team1)] = make_pair("L", "W");
        }
        else if (first == second) {
            Scores[team1] += 1;
            Scores[team2] += 1;
            Results[make_pair(team1, team2)] = make_pair("D", "D");
            Results[make_pair(team2, team1)] = make_pair("D", "D");
        }
        else if (first < second) {
            Scores[team2] += 3;
            Scores[team1] += 0;
            Wins[team2] += 1;
            Results[make_pair(team1, team2)] = make_pair("L", "W");
            Results[make_pair(team2, team1)] = make_pair("W", "L");
        }
    }

    vector<string> AllTeams(Teams.begin(), Teams.end());

    map<string, int> Places = Place(Scores, Wins);

    string separate = "+-+";
    for (int i = 0; i < MaxLen; i++) {
        separate += "-";
    }

    for (int i = 0; i < nNumberTeams; i++) {
        separate += "+-";
    }
    separate += "+-+-+";

    cout << separate << endl;
    string team = "Name";
    cout << left;
    cout << "|N|" << setw(MaxLen) << team << "|";

    for (int i = 0; i < nNumberTeams; i++) 
        cout << i+1 << "|";
    cout << "S|P|" << endl;
    cout << separate << endl;

    for (int i = 0; i < nNumberTeams; i++) {
        cout << left;
        cout << "|" << i+1 << "|" << setw(MaxLen) << AllTeams[i] << "|";
        for(int j = 0; j < 6; j++) {
            if (AllTeams[j] == AllTeams[i]) {
                 cout << "X|"; 
            }
            else {
                if (Results[make_pair(AllTeams[i], AllTeams[j])].first == "") {
                    cout << " |";
                } 

                else {
                    cout << Results[make_pair(AllTeams[i], AllTeams[j])].first << "|";
                }
            }
        }
        cout << Scores[AllTeams[i]] << "|";
        if (Places[AllTeams[i]] == 0)
            cout << " |" << endl;
        else
            cout << Places[AllTeams[i]] << "|" << endl;
        

        cout << separate << endl;
    }




    return 0;
} 