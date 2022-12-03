#include <exception>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using std::cout;
using std::vector;
using std::pair;
using std::string;
using std::endl;
using std::ifstream;

using Rucksack = pair<string, string>;

int getPriority(char c)
{
    // Checking if it's a letter
    if (
        (c < 'a' || c > 'z') &&
        (c < 'A' || c > 'Z')
    )
        throw std::exception{};
    
    if (c >= 'a')
        return c - 'a' + 1;
    else return c - 'A' + 27;
}

vector<Rucksack> loadInput(string filename)
{
    ifstream stream{filename};
    vector<Rucksack> rucksacks;
    while (!stream.eof())
    {
        pair<string, string> p;
        string row;
        stream >> row;
        p.first = row.substr(0, row.size() / 2);
        // Works only if the string has even characters,
        // otherwise the last character is excluded
        p.second = row.substr(row.size() / 2, row.size() / 2);
        std::sort(p.first.begin(), p.first.end());
        std::sort(p.second.begin(), p.second.end());
        rucksacks.push_back(p);
    }

    return rucksacks;
}

char getCommonItem(const Rucksack& rucksack)
{    
    for (char item : rucksack.first)
    {
        if (std::binary_search(rucksack.second.begin(), rucksack.second.end(), item))
            return item;
    }
    throw std::exception{};
}

int main()
{
    vector<Rucksack> rucksacks = loadInput("input.txt");
    int sumPriorities = 0;
    for (const Rucksack& r : rucksacks)
    {
        try
        {
            char common = getCommonItem(r);
            sumPriorities += getPriority(common);
        }
        catch (std::exception) {}
    }

    cout << "Sum: " << sumPriorities << endl;
}