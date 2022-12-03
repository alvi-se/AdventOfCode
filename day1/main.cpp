#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::string;
using std::vector;
using std::cout;
using std::endl;

vector<vector<int>> loadInput(string filename)
{
    std::ifstream stream{filename};
    vector<vector<int>> cals;
    cals.push_back(vector<int>{});
    vector<int>* current = &*(cals.end() - 1);
    int val;

    while (!stream.eof())
    {
        if (stream.peek() == '\n')
        {
            cals.push_back(vector<int>{});
            current = &*(cals.end() - 1);

            stream.get();
        }
        stream >> val;
        current->push_back(val);
        stream.get();
    }
    stream.close();
    return cals;
}

int sumVect(const vector<int>& v)
{
    int sum = 0;
    for (int val : v)
        sum += val;
    return sum;
}

int maxVect(const vector<int>& v)
{
    int max = *v.begin();
    vector<int> buff;
    
    for (size_t i = 1; i < v.size(); ++i)
    {
        if (v.at(i) > max)
        {
            max = v.at(i);
        }
    }
    return max;
}

int main()
{
    vector<vector<int>> inp = loadInput("input.txt");
    
    vector<int> sums;
    for (const vector<int>& vec : inp)
    {
        sums.push_back(sumVect(vec));
    }

    std::sort(sums.begin(), sums.end());

    int tot = 0;

    for (auto it = sums.rbegin(); it != (sums.rbegin() + 3); ++it)
    {
        cout << "Rep" << endl;
        tot += *it;
    }

    cout << "Total: " << tot << endl;

    return 0;
}
