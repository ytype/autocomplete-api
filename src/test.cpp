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

    return 0;
}