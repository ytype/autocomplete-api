#include "lib/httplib.h"
#include "lib/trie.hpp" 
#include "lib/json.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;
using json = nlohmann::json;
using namespace httplib;

Trie T;

void insert(){
  std::ifstream in("src/data/words.txt");

  if (!in.is_open()) {
    std::cout << "src/data/words.txt not found\n";
    exit(0);
  }

  std::string s;
  while (in) {
    getline(in, s);
    T.Insert(s);
  }
}

int main(){
  insert();
  cout << "Server running at http://localhost:1234\n";
  Server svr;

  svr.Get("/auto", [](const Request& req, Response& res) {
    if (!req.has_param("key")) {
      res.set_content("input prefix", "text/plain");
    }
    string prefix = req.get_param_value("key");
    TrieNode * current = T.Search(prefix);

    if (current == NULL or current == &T.root) {
        res.set_content("No words with matching prefix found", "text/plain");
    } else {
        bool haschildren = false;
        for (int c=0; c<26; c++) {
            if (current->children[c] != NULL) {
                 haschildren = true; break;
            }
        }
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