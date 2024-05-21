// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

# include "opttsp.hpp"

using namespace std;


void OptTSP::read_input() {
  FastTSP::read_input();
  dist_mat.resize(loc_vector.size());
  dists.resize(loc_vector.size(), numeric_limits<double>::infinity());
  opt_path.resize(loc_vector.size());
  path.reserve(loc_vector.size());
  visited.resize(loc_vector.size());

  for (size_t i = 0; i < loc_vector.size(); ++i) {
    dist_mat[i].resize(loc_vector.size());
    for (size_t j = 0; j < loc_vector.size(); ++j) {
      dist_mat[i][j] = get_dist(loc_vector[i], loc_vector[j]);
    }
  }
}

void OptTSP::run() {
  read_input();
  init(0, 1, 2, total_dist);
  insert_algo(total_dist);
  loc_vector.clear();
  path.pop_back();
  opt_path = path;
  best_path = path;
  path.clear();
  best_total = total_dist;
  gen_perms(1, 0);
  print();
}

void OptTSP::print() {
  cout << best_total << '\n';
  for (size_t i = 0; i < best_path.size(); ++i) {
    cout << best_path[i] << ' ';
  }
}

void OptTSP::gen_perms(size_t perm_len, double curr_total) {
  if (perm_len == opt_path.size()) {
    if (curr_total + dist_mat[0][opt_path[perm_len - 1]] < best_total) {
      best_total = curr_total + dist_mat[0][opt_path[perm_len - 1]];
      best_path = opt_path;
    }
  }
  if (!promising(perm_len, curr_total)) return;
  for (size_t i = perm_len; i < opt_path.size(); ++i) {
    swap(opt_path[perm_len], opt_path[i]);
    gen_perms(perm_len + 1, curr_total + dist_mat[opt_path[perm_len - 1]][opt_path[perm_len]]);
    swap(opt_path[perm_len], opt_path[i]);
  }
}

bool OptTSP::promising(size_t perm_len, double curr_total) {
  if (opt_path.size() - perm_len < 5) return true;
  
  fill(dists.begin(), dists.end(), numeric_limits<double>::infinity());
  fill(visited.begin(), visited.end(), false);
  size_t curr_min = perm_len;
  double total = 0;
  
  for (size_t i = perm_len; i < opt_path.size(); ++i) {
    int next_min = -1;
    for (size_t j = perm_len; j < opt_path.size(); ++j) {
      if (not visited[j]) {
        if (next_min == -1) next_min = int(j);
        double dist = dist_mat[opt_path[curr_min]][opt_path[j]];
        if (dist < dists[j]) dists[j] = dist;
        if (dists[j] < dists[next_min]) next_min = int(j);
      }
    }
    visited[next_min] = true;
    curr_min = next_min;
    total += dists[curr_min];
  }
  double best_begin = numeric_limits<double>::infinity();
  double best_end = numeric_limits<double>::infinity();
  int begin = 0, end = int(opt_path[perm_len - 1]);

  for (size_t i = perm_len; i < opt_path.size(); ++i) {
    if (dist_mat[begin][opt_path[i]] < best_begin) best_begin = dist_mat[begin][opt_path[i]];
    if (dist_mat[end][opt_path[i]] < best_end) best_end = dist_mat[end][opt_path[i]];
  }
  if (best_total < best_end + best_begin + curr_total + total) return false;
  return true;
}

