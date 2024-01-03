#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <optional>

static std::array<std::string,9> DIGIT_STRINGS = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

// Return an optional int if the substring starting at idx can be converted to a digit
std::optional<int> substring_to_digit( const std::string& s, int idx ){
    char c = s[idx];

    if( isdigit(c) ){
        return std::optional<int>(c-'0');
    } else {
        for( int digitIdx{0};  digitIdx < DIGIT_STRINGS.size(); ++digitIdx ){
            auto& digit_string = DIGIT_STRINGS[digitIdx];
            // Check necessary condition that the digit string can fit into the remaining characters in the string
            if( idx + digit_string.size() > s.size() ){ continue;}

            int cnt = 0;
            while( cnt < digit_string.size() ){
                if(s[idx+cnt] != digit_string[cnt] ){ break; }
                ++cnt;
            }

            if (cnt == digit_string.size()) { return std::optional<int>(digitIdx+1); }
        }
    }
    return std::optional<int>();
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

    while (std::getline(source, line))
    {
        // Process each line and add it to an accumulator
        int it{0};

        while( it < line.size()  ){
            auto optionalDigit = substring_to_digit(line,it);
            if( optionalDigit.has_value() ){
                // Convert the digit from a character to an int
                // Since the first digit represents the tens digit, multiply it by 10

                // In production we would check if this would overflow sum
                sum += optionalDigit.value()*10;
                break;
            }
            ++it;
        }

        it = line.size()-1;
        while( it >= 0 ){
            auto optionalDigit = substring_to_digit(line,it);
            if( optionalDigit.has_value() ){
                // Convert the digit from a character to an int
                // Add the digit to the sum
                sum += optionalDigit.value();
                break;
            }
            --it;
        }
    }

    // Print the result to the terminal
    std::cout<<sum<<std::endl;

    return 0;

}
