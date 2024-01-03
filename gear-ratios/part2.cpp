#include <fstream>
#include <iostream>
#include <vector>

class Game{
public:
    Game() = delete;
    Game( long long int gameId, const std::string& gameString): gameId_{gameId}{
        int idx{0};
        // @Note: the input game ID is the same as the line in the file

        // @Assumption: The input has a well formed game id
        idx += 5 + std::to_string(gameId_).size() + 1;
        //     |   |                               |- skip colon character
        //     |   |- skip characters required to represent gameId
        //     |-skip "Game " prefix

        // Split the remaining part of the string on the ';' character to get a vector of game_strings
        while( idx < gameString.size() ){
           processCubeCount(gameString,idx);
        }
    }

    long long int getPower(){
        return redCount*blueCount*greenCount;
    }
private:
    long long int redCount{0};
    long long int blueCount{0};
    long long int greenCount{0};
    long long int gameId_;

    void processCubeCount( const std::string& s, int& idx ){
        bool result;
        idx += 1; // skip space which is assumed to be at the beginning of the string
        long long int cubeCount{0};

        while( std::isdigit(s[idx]) ){
            cubeCount *= 10;
            cubeCount += s[idx]-'0';
            ++idx;
        }

        idx += 1; // skip space after the number

        switch(s[idx]){
            case 'b': // blue
                blueCount = std::max(cubeCount, blueCount);
                break;
            case 'g': // green
                greenCount = std::max(cubeCount, greenCount);
                break;
            case 'r': // red
                redCount = std::max(cubeCount, redCount);
                break;
            default: 
                throw std::invalid_argument("invalid input provided");
        }

        // Process remaining characters related to this cube to properly advance the idx
        while( idx < s.size() && s[idx] != ' '){
            ++idx;
        }
    }
};
int main(int argc, char** argv){
    // Validate the input
   if (argc < 2) {
       std::cout << "Please provide a file path as a command line argument." << std::endl;
       return 1;
   }

    // Read in the input into a vector
    std::string filename(argv[1]);
    std::ifstream source;
    source.open(filename);

    std::string line;

    long long int sum{0};

    long long int gameId{1};

    while (std::getline(source, line))
    {
        Game game(gameId, line);
        sum += game.getPower();
        ++gameId;
    }

    // Print the result to the terminal
    std::cout<<sum<<std::endl;

    return 0;

}
