#include <iostream>
#include <map>
#include <vector>
#include <exception>
#define nNumWords 5
using namespace std;


int main() {
    map<string, int> Encoder;
    map <int, string> ReverseEncoder;
    string word;
    vector<int> List;
    int nCount = 0;

    for(int i = 0; i < nNumWords; i++) {
        cin >> word;

        if (!Encoder.count(word)) {
            Encoder[word] = nCount;
            ReverseEncoder[nCount] = word;
            List.push_back(nCount);
            nCount++;
        } else {
            List.push_back(Encoder[word]);
        }
    }

    for (auto item : List) {
        cout << item << endl;
    }

    try {
    int nNum;
    cin >> nNum;
    cout << ReverseEncoder.at(nNum) << endl;
    }
    catch (out_of_range&){
        cout << "Error!" << endl;
    }

}