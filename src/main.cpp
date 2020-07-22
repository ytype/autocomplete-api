#include "lib/httplib.h"
#include "lib/trie.hpp" 
#include "lib/json.hpp"
#include <iostream>
#include <vector>
#include <string>

// g++ -o main src/main.cpp -pthread
using namespace std;
using json = nlohmann::json;
using namespace httplib;
int main(){

  Server svr;

  svr.Get("/hi", [](const Request& req, Response& res) {
   json array = {};
   array.push_back("first");
   array.push_back("second");
   res.set_content(array.dump(),"text/plain");
  });

  svr.Get("/auto", [](const Request& req, Response& res) {

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

    if (!req.has_param("key")) {
      res.set_content("input prefix", "text/plain");
    }
    string prefix = req.get_param_value("key");
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
            res.set_content(temp.dump() , "text/plain");
        }
    }

    
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("localhost", 1234);
}