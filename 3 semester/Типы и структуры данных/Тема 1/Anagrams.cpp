#include <iostream>
#include <string>
#include <map>

bool IsAnnagramm(const std::string& str, const std::string& str1) {
    std::map<char, int> chars;
    std::map<char, int> chars1;
    for (char chr : str) {
        ++chars[chr];
    }
    for (char chr1 : str1) {
        ++chars1[chr1];
    }

    if (chars == chars1) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    std::string word;
    std::string word1;

    std::cin >> word >> word1;

    if (IsAnnagramm(word, word1)) {
        std::cout << "YES";
    }
    else {
        std::cout << "NO";
    }
}
