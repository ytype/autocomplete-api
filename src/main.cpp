#include "lib/httplib.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <sstream> 
#include <iterator> 

// g++ -o main src/main.cpp -pthread
using namespace std;
int main(void)
{
  using namespace httplib;

  Server svr;

  svr.Get("/hi", [](const Request& req, Response& res) {
    vector <string> sv;
    sv.push_back("hello world");
    sv.push_back("hello shin");
    res.set_content(sv);
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