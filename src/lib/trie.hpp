#ifndef TRIE
#define TRIE

#include "json.hpp"
#include <iostream>
#include <string>

using json = nlohmann::json;
using namespace std;

class TrieNode {

    public:
        TrieNode * children[26];
        bool end_of_word;
        char letter;
        TrieNode() {
            end_of_word = false;
            for (int i=0; i<26; i++) {
                children[i] = NULL;
            }
            letter = '\0';
        }
};

class Trie {
    private:
        json array = {};

    public:
    TrieNode root;

    // Insert the word in the trie
    void Insert (string str) {
        TrieNode * current = &root;
        for (size_t i=0; i<str.size(); i++) {
            if (current->children[str.at(i)-'a'] == NULL) {
                current->children[str.at(i)-'a'] = new TrieNode;
                current->children[str.at(i)-'a']->letter = str.at(i);
            }
            current = current->children[str.at(i)-'a'];
        }
        current->end_of_word = true;
    }

    // Search the word in trie
    TrieNode * Search (string str) {
        TrieNode * current = &root;
        for (size_t i=0; i<str.size(); i++) {
            if (current->children[str.at(i)-'a']) {
                current = current->children[str.at(i)-'a'];
             } else {
                current = NULL;
                break;
             }
        }
        return current;
    }

    // Print the words with the specified prefix in lexical order
    json PrintLexical (TrieNode * current, string prefix, string suffix) {
        if (current->end_of_word and suffix.size() != 0) {
            array.push_back(prefix+suffix);
        }
        for (int i=0; i<26; i++) {
            string temp = suffix;
            if (current->children[i]) {
                temp += current->children[i]->letter;
                PrintLexical(current->children[i], prefix, temp);
            }
        }
        return array;
    }
};

#endif