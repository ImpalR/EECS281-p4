// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

#include "mst.hpp"
#include "fasttsp.hpp"
#include "opttsp.hpp"
#include <getopt.h>
#include <string.h>

using namespace std;

char getopt (int argc, char** argv) {
  opterr = false;
  char choice = '0';
  int index = 0, option = 0;

  struct option long_options[] = {
    {"help", no_argument, nullptr, 'h'},
    {"mode", required_argument, nullptr, 'm'},
    {nullptr, 0, nullptr, '\0'}
  };

  while ((option = getopt_long(argc, argv, "m:h", long_options, &index)) != -1) {
    switch (option)
    {
      case 'm':
        if (strcmp(optarg, "MST") == 0) {choice = 'M';}
        else if (strcmp(optarg, "FASTTSP") == 0) {choice = 'F';}
        else if (strcmp(optarg, "OPTTSP") == 0) {choice = 'O';}
        else {
          cerr << "Error: Invalid mode";
          exit(1);
        }
        break;

      case 'h':
        cout << "Usage: \'./drones\n\t[--help | -h]\n"
              <<                   "\t[--mode | -m]\n"
              << "EECS 281 Drones program\n";
        exit(0);

      default:
        cerr << "Error: Invalid command line option";
        exit(1);
    }
  }
  if (choice == '0') {
    cout << "Error: No mode specified";
    exit(1);
  }
  return choice;
}

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
	cout << setprecision(2);
	cout << fixed;
  char mode = getopt(argc, argv);

  if (mode == 'M') {
    MST drone; 
    drone.run();
  } else if (mode == 'F') {
    FastTSP drone; 
    drone.run();
  } else {
    OptTSP drone; 
    drone.run();
  }
}