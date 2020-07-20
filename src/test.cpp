#include <iostream>
#include "lib/trie.hpp" 
#include "lib/json.hpp"

using json = nlohmann::json;

int main() {

    Trie T;

    // Insert word(s) in the trie
    T.Insert("we");
    T.Insert("walk");
    T.Insert("want");
    T.Insert("wish");
    T.Insert("wit");
    T.Insert("am");
    T.Insert("yo");
    T.Insert("will");
    T.Insert("wee");
    T.Insert("war");
    T.Insert("warp");
    T.Insert("win");

    // Search for the prefix in the trie
    string prefix("wa");

    TrieNode * current = T.Search(prefix);

    if (current == NULL or current == &T.root) {
        cout << "No words with matching prefix found" << endl;
    } else {
        // Prefix has been found in the tree, look for children
        bool haschildren = false;
        for (int c=0; c<26; c++) {
            if (current->children[c] != NULL) {
                 haschildren = true; break;
            }
        }
        // No words found with the prefix (only the prefix was found)
        if (haschildren == false) {
            cout << "No words with matching prefix found" << endl;
        } else {
            cout << "Word(s) with prefix: " << prefix << endl;
            json temp = T.PrintLexical(current, prefix, "");
            cout << temp.dump() ;
        }
    }
    return 0;
}