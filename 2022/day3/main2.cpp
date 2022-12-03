#include <exception>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

using std::cout;
using std::vector;
using std::string;
using std::endl;
using std::ifstream;

using Rucksack = string;
using RucksackGroup = vector<Rucksack>;

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
        Rucksack rucksack;
        stream >> rucksack;
        std::sort(rucksack.begin(), rucksack.end());
        
        rucksacks.push_back(rucksack);
    }

    return rucksacks;
}

char getCommonItem(const RucksackGroup& rucksackGroup)
{
    for (char c : rucksackGroup.at(0))
    {
        bool common = true;
        for (auto rucksack = rucksackGroup.begin() + 1; rucksack != rucksackGroup.end(); ++rucksack)
        {
            if (!std::binary_search(rucksack->begin(), rucksack->end(), c))
                common = false;
        }
        if (common) return c;
    }
   
    throw std::exception{};
}

vector<RucksackGroup> splitGroups(const vector<Rucksack>& rucksacks, int divider)
{
    vector<RucksackGroup> groups;
    RucksackGroup* group;
    for (int i = 0; i < rucksacks.size(); ++i)
    {
        if (i % divider == 0)
        {
            groups.push_back(RucksackGroup{});
            group = &*(groups.end() - 1);
        }

        group->push_back(rucksacks.at(i));
    }

    return groups;
}

int main()
{
    vector<Rucksack> rucksacks = loadInput("input.txt");
    vector<RucksackGroup> groups = splitGroups(rucksacks, 3);

    int sumPriorities = 0;
    for (const RucksackGroup& group : groups)
    {
        try
        {
            char common = getCommonItem(group);
            sumPriorities += getPriority(common);
        }
        catch (std::exception) {}
    }

    cout << "Sum: " << sumPriorities << endl;
}