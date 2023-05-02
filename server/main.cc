#include <cstdlib>
#include <drogon/drogon.h>
#include "requestHandler.h"
using namespace drogon;

int main() {
  app().registerController(std::make_shared<requestHandler>());
  app().addListener("0.0.0.0", 80);
  app().run();

  return EXIT_SUCCESS;
}