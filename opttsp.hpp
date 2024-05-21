// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

#ifndef OPTTSP_HPP
#define OPTTSP_HPP

#pragma once
# include "fasttsp.hpp"


class OptTSP : public FastTSP {
 public:
  OptTSP() {}
  void read_input() override;
  void run() override;
  void print() override;
  void gen_perms(size_t perm_len, double curr_total);
  bool promising(size_t perm_len, double curr_total);

 private:
  std::vector<std::vector<double>> dist_mat;
  std::vector<double> dists;
  std::vector<size_t> opt_path;
  std::vector<size_t> best_path;
  std::vector<bool> visited;
  double best_total = std::numeric_limits<double>::infinity();
};

#endif // OPTTSP_HPP
