#include <fstream>
#include <iostream>
#include <vector>

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
            char c = line[it];
            if( isdigit(c) ){
                // Convert the digit from a character to an int
                // Since the first digit represents the tens digit, multiply it by 10

                // In production we would check if this would overflow sum
                sum += static_cast<int>(c-'0')*10;
                break;
            }
            ++it;
        }

        it = line.size()-1;
        while( it >= 0 ){
            char c = line[it];
            if( isdigit(c) ){
                // Convert the digit from a character to an int
                // Add the digit to the sum
                sum += static_cast<int>(c-'0');
                break;
            }
            --it;
        }
    }

    // Print the result to the terminal
    std::cout<<sum<<std::endl;

    return 0;

}
