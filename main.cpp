#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>

using namespace std;

void task1(const string &path);
void task2(const string &path);
void PrintLeastFuel(const function<int(int, int)>&, const string &path);

int main() {
    string path;
    fstream fileStream;
    char confirmChar('m');

    cout << "AoC, day 7.\n";
    do {
        cout << "Type path to input file with puzzles:\n";
        cin >> path;

        fileStream.open(path);
        if(fileStream.is_open())
        {
            fileStream.close();
            cout << "File successfully opened!\n";
            cout << "First task data:\n";
            task1(path);

            cout << "Second task data:\n";
            task2(path);

            break;
        }
        else
        {
            fileStream.close();
            cout << "Wrong path to file. Not opened. Try again? y/n - ";
            cin >> confirmChar;
            if(confirmChar == 'y' || confirmChar == 'Y') confirmChar = 'm';
        }
    }while(confirmChar == 'm');
}

void task1(const string &path)
{
    PrintLeastFuel([](int a, int b) {return abs(a - b); }, path);
}

void task2(const string &path)
{
    PrintLeastFuel([](int a, int b) {return (abs(a - b) + 1) * abs(a - b) / 2; }, path);
}

void PrintLeastFuel(const function<int(int, int)>& f, const string &path)
{
    vector<int> vd;
    string line;
    fstream stream;
    stream.open(path);

    while (getline(stream, line, ','))
    {
        vd.push_back(stoi(line));
    }

    int shortestVal = INT32_MAX;
    int shortestPos = -1;

    for (int i = *min_element(vd.begin(), vd.end()); i < *max_element(vd.begin(), vd.end()); i++)
    {
        int total = accumulate(vd.begin(), vd.end(), 0, [i, f](int cs, int v) {return cs + f(v, i); });

        if (total < shortestVal)
        {
            shortestVal = total;
            shortestPos = i;
        }
    }

    cout << shortestVal << '\n';
}