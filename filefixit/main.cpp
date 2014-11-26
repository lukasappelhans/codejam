#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

pair<string, string> split(const std::string &input)
{
    pair<string, string> result;
    std::string delimiter = "/";
    size_t pos = 0;
    if ((pos = input.find(delimiter)) != std::string::npos) {
        result.first = input.substr(0, pos);
        result.second = input.substr(pos + 1, input.length());
    } else {
        result.first = input;
    }
    return result;
}

class CustomBinaryTree
{
public:
    CustomBinaryTree() {
    }
    CustomBinaryTree(const std::vector<string> &initializers) {
        insert(initializers);
    }
    ~CustomBinaryTree() {
        auto it = m_children.begin();
        auto end = m_children.end();
        for (; it != end; ++it)
            delete it->second;
    }
    
    int insert(const std::vector<string> &elements) {
        int added = 0;
        auto it = elements.begin();
        auto end = elements.end();
        for (; it != end; ++it) {
            added += insert(*it);
        }
        return added;
    }
    
private:
    int insert(const std::string &path) {
        if (path.empty())
            return 0;
        int added = 0;
        std::string element = path;
        if (element.at(0) == '/') //Remove first slash
            element = element.substr(1, element.length());
        pair<string, string> splitted = split(element);
        auto mapIt = m_children.find(splitted.first);
        if (mapIt == m_children.end()) {
            added += 1;
            m_children[splitted.first] = new CustomBinaryTree();
        }
        added += m_children[splitted.first]->insert(splitted.second);
        return added;
    }
    unordered_map<string, CustomBinaryTree*> m_children;
};


int main( int argc, const char* argv[] )
{
    std::ifstream infile("A-large-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream ss(line);
    int number;
    ss >> number;
    
    for (int i = 0; i != number; ++i) {
        std::getline(infile, line);
        std::stringstream iss(line);
        int n, m;
        iss >> n;
        iss >> m;
        std::vector<string> existing;
        for (int i = 0; i != n; ++i) {
            std::getline(infile, line);
            existing.push_back(line);
        }
        std::vector<string> adding;
        for (int i = 0; i != m; ++i) {
            std::getline(infile, line);
            adding.push_back(line);
        }
        CustomBinaryTree tree(existing);
        int result = tree.insert(adding);
        std::cout << "Case #" << (i + 1) << ": " << result << std::endl;
    }
}

