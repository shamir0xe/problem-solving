#include <bits/stdc++.h>

class TrieTree {
public:
    TrieTree* children[26];
    bool isEndOfWord;
    TrieTree() {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }

    void insert(const std::string& word) {
        TrieTree* node = this;
        for (char c : word) {
            int index = c - 'a';
            if (node->children[index] == nullptr) {
                node->children[index] = new TrieTree();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }
};

int main() {
    return 0;
}
