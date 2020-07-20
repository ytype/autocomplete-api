#include "lib/httplib.h"
#include "lib/trie.hpp" 
#include "lib/json.hpp"
#include <iostream>
#include <vector>
#include <string>

// g++ -o main src/main.cpp -pthread
using namespace std;
using json = nlohmann::json;

int main(){
    Trie T;
  using namespace httplib;


  Server svr;

  svr.Get("/hi", [](const Request& req, Response& res) {
   json array = {};
   array.push_back("first");
   array.push_back("second");
   res.set_content(array.dump(),"text/plain");
  });

  svr.Get(R"(/numbers/(\s+))", [&](const Request& req, Response& res) {
    string str = req.matches[1];

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

    res.set_content(str, "text/plain");
  });

  svr.Get("/body-header-param", [](const Request& req, Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
    }
    res.set_content(req.body, "text/plain");
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
  });

  svr.listen("localhost", 1234);
}