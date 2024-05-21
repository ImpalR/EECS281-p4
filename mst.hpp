// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef MST_HPP
#define MST_HPP

#pragma once
#include "path.hpp"


class MST : public Path {
 public:
  void read_input() override;
  void run() override;
  void print() override;  
  void mst_algorithm();
  void init(Location &l1, size_t l1_num);
  size_t find_closest_loc();
  void algo_updater(Location &next, size_t next_num);
  double get_total_dist();

 private:
  std::vector<Location> parents;
  std::vector<double> dists;
  std::vector<bool> visited;
};

#endif // MST_HPP