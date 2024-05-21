// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef PATH_HPP
#define PATH_HPP

#include <getopt.h>
#include <cmath>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string>


enum class Loc_type { Medical, Border, Main, Empty};

class Location {
 public:
  Location(int x_in, int y_in, int loc_in, bool mst) {
    loc_num = loc_in;
    x = x_in;
    y = y_in;
    if (mst) {
      if (x < 0 and y < 0) loc_type = Loc_type::Medical;
      else if ((x <= 0 and y == 0) or (y <= 0 and x == 0)) loc_type = Loc_type::Border;
      else loc_type = Loc_type::Main;
    }
  }

  int get_x() { return x; }
  int get_y() { return y; }
  Loc_type get_loc_type() { return loc_type; }
  int get_loc_num() { return loc_num; }

 private:
  int x = 0;
  int y = 0;
  int loc_num = -1;
  Loc_type loc_type = Loc_type::Empty;
}; 

class Path {
 public:
  virtual double get_dist(Location &l1, Location &l2) {
    Loc_type t1 = l1.get_loc_type();
    Loc_type t2 = l2.get_loc_type();
    if ((t1 == Loc_type::Medical and t2 == Loc_type::Main) or 
        (t1 == Loc_type::Main and t2 == Loc_type::Medical)) {
      return std::numeric_limits<double>::infinity();
    }
    double x1 = double(l1.get_x());
    double x2 = double(l2.get_x());
    double y1 = double(l1.get_y());
    double y2 = double(l2.get_y());
    double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return dist;
  }

  virtual void read_input() = 0;
  virtual void run() = 0;
  virtual void print() = 0;

 protected:
  int location_num;
  std::vector<Location> loc_vector;
};

#endif // PATH_HPP