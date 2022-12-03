#include <ostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>

using std::cout;
using std::vector;
using std::pair;
using std::string;
using std::endl;

enum Hand : int
{
    Rock = 1,
    Paper = 2,
    Scissors = 3
};

int outcomePoints(Hand h1, Hand h2)
{
    switch (h1)
    {
    case Rock:
        switch (h2)
        {
        case Rock: return 3;
        case Paper: return 0;
        case Scissors: return 6;
        }
    
    case Paper:
        switch (h2)
        {
        case Rock: return 6;
        case Paper: return 3;
        case Scissors: return 0;
        }
    case Scissors:
        switch (h2)
        {
        case Rock: return 0;
        case Paper: return 6;
        case Scissors: return 3;
        }
    }

    throw std::exception{};
}

Hand charToHand(char c)
{
    switch (c)
    {
    case 'A':
    case 'X':
        return Rock;
    
    case 'B':
    case 'Y':
        return Paper;
    
    case 'C':
    case 'Z':
        return Scissors;
    }

    throw std::exception{};
}

class Game
{
public:
    Hand player;
    Hand opponent;

    Game(Hand player1, Hand player2)
        : player{player1}, opponent{player2} {}

    Game(pair<char, char> p)
    {
        player = charToHand(p.second);
        opponent = charToHand(p.first);
    }

    operator string() const
    {
        string str;
        std::ostringstream stream{str};
        // NOT WORKING
        stream << opponent << ' ' << player;
        return str;
    }

    int getPoints() const
    {
        return static_cast<int>(player) + outcomePoints(player, opponent);
    }    
};

vector<Game> loadGames(string filename)
{
    std::ifstream stream{filename};
    vector<Game> games;
    int a = 0;
    while (!stream.eof())
    {
        cout << a++ << endl;
        if (stream.peek() == -1) break;
        pair<char, char> p;
        stream >> p.first >> p.second;
        cout << p.first << ' ' << p.second << endl;
        games.push_back(Game{p});
    }
    return games;
}

int main()
{
    vector<Game> games = loadGames("input.txt");
    int sum = 0;
    for (const Game& g : games)
    {
        cout << "Points: " << g.getPoints() << endl;
        sum += g.getPoints();
    }
    
    cout << "Sum: " << sum << endl;


    return 0;
}