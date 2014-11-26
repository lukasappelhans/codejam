#include <unordered_map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Trie
{
public:
    Trie() {}
    Trie(const std::vector<string> &words) {
        auto it = words.begin();
        auto end = words.end();
        for (; it != end; ++it) {
            insert(*it);
        }
    }
    ~Trie() {
        auto it = m_children.begin();
        auto end = m_children.end();
        for (; it != end; ++it)
            delete it->second;
    }
    
    int options(const std::string &word) {
        if (word.empty())
            return 1;
        if (word.at(0) != '(') {
            unordered_map<char, Trie*>::iterator it;
            if ((it = m_children.find(word.at(0))) == m_children.end()) {
                return 0;
            } else {
                return it->second->options(word.substr(1, word.length()));
            }
        }
        
        size_t pos = 0;
        if ((pos = word.find(')')) == std::string::npos)
            return 0;
        
        std::string choices = word.substr(1, pos - 1);
        std::string rest = word.substr(pos + 1, word.length());
        
        int options = 0;
        for (int i = 0; i != choices.length(); ++i) {
            char c = choices.at(i);
            unordered_map<char, Trie*>::iterator it;
            if ((it = m_children.find(c)) == m_children.end()) {
                continue;
            } else {
                options += it->second->options(rest);
            }
        }
        return options;
    }
    
private:
    void insert(const std::string &word) {
        if (word.empty())
            return;
        char c = word.at(0);
        if (m_children.find(c) == m_children.end()) {
            m_children[c] = new Trie();
        }
        m_children[c]->insert(word.substr(1, word.length()));
    }
    unordered_map<char, Trie*> m_children;
};

int main( int argc, const char* argv[] )
{
    std::ifstream infile("A-large-practice.in");
    string line;
    std::getline(infile, line);
    std::stringstream iss(line);
    int l, d, n;
    iss >> l;
    iss >> d;
    iss >> n;
    
    std::vector<string> words;
    for (int i = 0; i != d; ++i) {
        std::getline(infile, line);
        words.push_back(line);
    }
    
    Trie trie(words);
    
    for (int i = 0; i != n; ++i) {
        std::getline(infile, line);
        int result = trie.options(line);
        std::cout << "Case #" << (i + 1) << ": " << result << std::endl;
    }
}