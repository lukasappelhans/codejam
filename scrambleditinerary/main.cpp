#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <list>

using namespace std;

int main( int argc, const char* argv[] )
{
    std::ifstream infile("C-large-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream ss(line);
    int number;
    ss >> number;
    
    const std::string searchTerm = "welcome to code jam";
    for (int i = 0; i != number; ++i) {
        std::getline(infile, line);
        std::stringstream mss(line);
        int m;
        mss >> m;
            
        list<std::string> flights;
        
        unordered_map<std::string, std::string> correct;
        unordered_map<std::string, std::string> reverse;

        std::string firstFlightSource;
        getline(infile, firstFlightSource);
        std::string firstFlightDestination;
        getline(infile, firstFlightDestination);
            
        flights.push_back(firstFlightSource);
        flights.push_back(firstFlightDestination);

        for (int i = 1; i != m; ++i) {
            std::string source;
            getline(infile, source);
            std::string destination;
            getline(infile, destination);

            correct.insert(pair<std::string, std::string>(source, destination));
            reverse.insert(pair<std::string, std::string>(destination, source));
        }
        
        while (correct.size() > 0) {
            std::string newSource = flights.back();
            unordered_map<std::string, std::string>::iterator it;
            if ((it = correct.find(newSource)) != correct.end()) {
                flights.push_back(it->second);
                auto reverseIt = reverse.find(it->second);
                correct.erase(it);
                reverse.erase(reverseIt);
            }
            std::string newDestination = flights.front();
            if ((it = reverse.find(newDestination)) != reverse.end()) {
                flights.push_front(it->second);
                auto correctIt = correct.find(it->second);
                correct.erase(correctIt);
                reverse.erase(it);
            }
        }

        std::string output;
        auto firstIt = flights.begin();
        auto secondIt = flights.begin();
        ++secondIt;
        auto end = flights.end();
        for (; secondIt != end; ++secondIt, ++firstIt) {
            output = output + (*firstIt) + "-" + (*secondIt) + " ";
        }
        std::cout << "Case #" << (i + 1) << ": " << output << std::endl;
    }
}
