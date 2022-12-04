#include <exception>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using std::cout;
using std::vector;
using std::pair;
using std::string;
using std::endl;
using std::ifstream;

class Range
{
public:
    pair<int, int> range;

    Range()
    {
        range.first = 0;
        range.second = 0;
    }

    Range(int begin, int end)
    {
        if (begin > end) throw std::exception{};
        range.first = begin;
        range.second = end;
    }

    bool contains(const Range& other) const
    {
        return range.first >= other.range.first &&
            range.second <= other.range.second;
    }

    bool overlaps(const Range& other) const
    {
        const Range& first = range.first <= other.range.first ? *this : other;
        const Range& second = range.first > other.range.first ? *this : other;

        return first.range.second >= second.range.first;
    }
};

using Assignement = pair<Range, Range>;

vector<Assignement> loadInput(string filename)
{
    ifstream stream{filename};
    vector<Assignement> assignments;
    while (!stream.eof())
    {
        char _;
        Assignement assignment;
        stream >> assignment.first.range.first
            >> _
            >> assignment.first.range.second
            >> _
            >> assignment.second.range.first
            >> _
            >> assignment.second.range.second;

        if (stream.good())
            assignments.push_back(assignment);
    }
    stream.close();
    return assignments;
}

int main()
{
    vector<Assignement> assignments = loadInput("input.txt");

    int count = 0;
    for (Assignement a : assignments)
    {
        if (a.first.overlaps(a.second))
            ++count;
    }

    cout << "Count: " << count << endl;
}