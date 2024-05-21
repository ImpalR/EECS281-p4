// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef FASTTSP_HPP
#define FASTTSP_HPP

#pragma once
#include "path.hpp"



class FastTSP : public Path {
 public:
  void read_input() override;
  double get_dist(Location &l1, Location &l2) override;
  void run() override;
  void print() override;
  void init(size_t idx1, size_t idx2, size_t idx3, double& dist);
  void insert_algo(double &dist);
  double dist_difference(size_t idx1, size_t idx2, int in);

 protected:
  double total_dist = 0;
  std::vector<size_t> path;
};

#endif // FASTTSP_HPP
