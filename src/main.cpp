#include "lib/httplib.h"
#include "lib/json.hpp"
#include <iostream>
#include <vector>
#include <string>

// g++ -o main src/main.cpp -pthread
using namespace std;
using json = nlohmann::json;
int main(void){
  using namespace httplib;

  Server svr;

  svr.Get("/hi", [](const Request& req, Response& res) {
   json array = {};
   array.push_back("first");
   array.push_back("second");
   res.set_content(array.dump(),"text/plain");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
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