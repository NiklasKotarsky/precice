#include <cassert>
#include <iostream>
#include <precice/SolverInterface.hpp>
#include <precice/Tooling.hpp>
#include <stdexcept>
#include <string>

void printUsage()
{
  std::cerr << "Usage:\n\n";
  std::cerr << "Print XML reference      :  binprecice xml\n";
  std::cerr << "Print DTD for XML config :  binprecice dtd\n";
  std::cerr << "Print Markdown reference :  binprecice md\n";
  std::cerr << "Print preCICE version    :  binprecice version\n";
  std::cerr << "                            binprecice --version\n";
  std::cerr << "Check configuration file :  binprecice check FILE [ PARTICIPANT [ COMMSIZE ] ]\n";
}

int main(int argc, char **argv)
{
  if (argc < 2) {
    printUsage();
    return 1;
  }

  const std::string action(argv[1]);
  const int         args = argc - 2;

  using namespace precice::tooling;

  if (action == "dtd" && args == 0) {
    printConfigReference(std::cout, ConfigReferenceType::DTD);
    return 0;
  }
  if (action == "md" && args == 0) {
    printConfigReference(std::cout, ConfigReferenceType::MD);
    return 0;
  }
  if (action == "xml" && args == 0) {
    printConfigReference(std::cout, ConfigReferenceType::XML);
    return 0;
  }
  if ((action == "version" || action == "--version") && args == 0) {
    std::cout << precice::getVersionInformation() << '\n';
    return 0;
  }
  if (action == "check" && args >= 1 && args <= 3) {
    std::string file(argv[2]);
    std::string participant = (args > 1) ? std::string(argv[3]) : "";

    int size = 1;
    if (args == 3) {
      try {
        size = std::stoi(argv[4]);
      } catch (std::invalid_argument &e) {
        std::cerr << "ERROR: passed COMMSIZE is not a valid number\n";
        printUsage();
        return 1;
      }
    }
    precice::tooling::checkConfiguration(file, participant, size);
    return 0;
  }

  printUsage();
  return 1;
}
