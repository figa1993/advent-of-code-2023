#include <fstream>
#include <iostream>
#include <vector>

// @Assumpion: This function will be called on the space that proceeds the count of a cube
// which is then followed by a space and a string representing the color
bool isValidCubeCount( const std::string& s, int& idx ) {
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
            result =  cubeCount <= 14;
            break;
        case 'g': // green
            result = cubeCount <= 13;
            break;
        case 'r': // red
            result = cubeCount <= 12;
            break;
        default: 
            throw std::invalid_argument("invalid input provided");
    }

    // Process remaining characters related to this cube to properly advance the idx
    while( idx < s.size() && s[idx] != ' '){
        ++idx;
    }

    return result;

}

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
        int idx{0};
        // @Note: the input game ID is the same as the line in the file

        // @Assumption: The input has a well formed game id
        idx += 5 + std::to_string(gameId).size() + 1;
        //     |   |                               |- skip colon character
        //     |   |- skip characters required to represent gameId
        //     |-skip "Game " prefix

        // Split the remaining part of the string on the ';' character to get a vector of game_strings
        bool isGameValid{true};
        while( idx < line.size() ){
            isGameValid &= isValidCubeCount(line,idx);
        }

        if( isGameValid ){ 
            sum += gameId;
        }
        ++gameId;
    }

    // Print the result to the terminal
    std::cout<<sum<<std::endl;

    return 0;

}
