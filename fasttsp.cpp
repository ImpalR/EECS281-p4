// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

#include "fasttsp.hpp"

using namespace std;


void FastTSP::read_input() {
  int x, y;
  cin >> x;
  location_num = x;
  loc_vector.reserve(size_t(location_num));
  for (int i = 0; i < location_num; ++i) {
    cin >> x >> y;
    Location temp(x, y, i, false);
    loc_vector.push_back(temp);
  }
}

double FastTSP::get_dist(Location &l1, Location &l2) {
  double x1 = double(l1.get_x());
  double x2 = double(l2.get_x());
  double y1 = double(l1.get_y());
  double y2 = double(l2.get_y());
  double dist = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
  return dist;
}

void FastTSP::run() {
  read_input();
  init(0, 1, 2, total_dist);
  insert_algo(total_dist);
  print();
}

void FastTSP::init(size_t idx1, size_t idx2, size_t idx3, double& dist) {
  path.reserve(location_num + 1);
  path.push_back(idx1);
  path.push_back(idx2);
  path.push_back(idx3);
  path.push_back(idx1);
  dist += get_dist(loc_vector[idx1], loc_vector[idx2]) + 
          get_dist(loc_vector[idx2], loc_vector[idx3]) + 
          get_dist(loc_vector[idx3], loc_vector[idx1]);
}

void FastTSP::insert_algo(double &dist) {
  for (int i = 3; i < location_num; ++i) {
    double min_dist_diff = numeric_limits<double>::infinity();
    auto it = path.begin();
    auto insert_it = it;
    for (size_t j = 0; j < path.size() - 1; ++j) {
      double dist_diff = dist_difference(j, (j + 1), i);
      if (dist_diff < min_dist_diff) {
        min_dist_diff = dist_diff;
        insert_it = it;
        ++insert_it;
      }
      ++it;
    }
    dist += min_dist_diff;
    path.insert(insert_it, i);
  }
}

double FastTSP::dist_difference(size_t idx1, size_t idx2, int in) {
  Location l1 = loc_vector[path[idx1]];
  Location l2 = loc_vector[path[idx2]];
  Location lin = loc_vector[in];
  double dist_diff = get_dist(l1, lin) + get_dist(lin, l2) - get_dist(l1, l2);
  return dist_diff;
}

void FastTSP::print() {
  path.pop_back();
  cout << total_dist << '\n';
  for (size_t i = 0; i < path.size(); ++i) {
    cout << path[i] << ' ';
  }
}