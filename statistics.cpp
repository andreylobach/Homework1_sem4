#include <iostream>
#include <vector>
#include <iomanip>
#include <utility>
#include <set>
#include <cmath>
#define Min 2000000000
using namespace std;

double Median(set<int> vNum, set<int>& vD, set<int>& vH) {
    int nMean = vNum.size() / 2;
    double nMin = Min, nMax = 0;
    for (int i = 0; i < nMean; i++) {
        for (auto item : vNum) {
            if (item > nMax)
                nMax = item;
            if (item < nMin)
                nMin = item;
        }
        vNum.erase(nMin);
        vNum.erase(nMax);
        vD.insert(nMin);
        vH.insert(nMax);
        if (i == nMean - 1) {
            if (vNum.size() % 2 == 0) {
                return (nMin + nMax) / 2;
            }
            else {
                vD.insert(*vNum.begin());
                vH.insert(*vNum.begin());
                return *vNum.begin();
            }
        }
        nMax = 0;
        nMin = Min;
    }
}

int main() {
    set<int> vNumbers, vDown, vHigh, vDD, vHH;
    int nItem;
    double mean, std, nSum = 0, s = 0;
    string input_str;

    getline(cin, input_str);

    stringstream ss(input_str);

    while (ss >> nItem) {
        vNumbers.insert(nItem);
        nSum += nItem;
        if (ss.peek() == ',')
            ss.ignore();
    }

    int nNum = vNumbers.size();

    mean = nSum / nNum;
    cout << "mean = " << mean << ", ";
    
    for (auto item : vNumbers) {
        s += (item - mean) * (item - mean);
    }

    std = s / nNum;
    std = sqrt(std);

    cout << "std = " << std << ", ";
    cout << fixed << setprecision(1);
    cout << "median = " << Median(vNumbers, vDown, vHigh) << ", ";
    cout << "0.25q = " << Median(vDown, vDD, vHH) << ", ";
    cout << "0.75q = " << Median(vHigh, vDD, vHH) << endl;

}   