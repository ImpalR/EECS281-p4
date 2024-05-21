// Project Identifier: 1761414855B69983BD8035097EFBD312EB0527F0

#include "mst.hpp"

using namespace std;


void MST::run() {
  read_input();
  mst_algorithm();
  print();
}

void MST::read_input() {
  int x, y;
  cin >> x;
  location_num = x;
  loc_vector.reserve(location_num);
  vector<bool> valid = {false, false, false};
  for (int i = 0; i < location_num; ++i) {
    cin >> x >> y;
    Location temp(x, y, i, true);
    if (temp.get_loc_type() == Loc_type::Main) valid[0] = true;
    if (temp.get_loc_type() == Loc_type::Medical) valid[1] = true;
    if (temp.get_loc_type() == Loc_type::Border) valid[2] = true;
    loc_vector.push_back(temp);
  }
  if (valid[0] and valid[1] and not valid[2]) {
    cerr << "Cannot construct MST";
    exit(1);
  }
}

void MST::mst_algorithm() {
  Location l1 = loc_vector[0];
  init(l1, 0);
  int count = 1;
  while (count != location_num) {
    size_t next_loc = find_closest_loc();
    algo_updater(loc_vector[next_loc], next_loc);
    ++count;
  }
}

void MST::init(Location &l1, size_t l1_num) {
  vector<Location> temp_p(location_num, l1);
  parents.swap(temp_p);
  vector<double> temp_d(location_num);
  for (size_t i = 0; i < size_t(location_num); ++i) {temp_d[i] = get_dist(l1, loc_vector[i]);}
  dists.swap(temp_d);
  vector<bool> temp_v(location_num, false);
  temp_v[l1_num] = true;
  visited.swap(temp_v);
  return;
}

size_t MST::find_closest_loc() {
  double min_dist = numeric_limits<double>::infinity();
  size_t index = 0;

  for (size_t i = 0; i < dists.size(); ++i) {
    if (dists[i] < min_dist) {
      if (visited[i] == false) {
        min_dist = dists[i];
        index = i;
      }
    }
  }
  return index;
}

void MST::algo_updater(Location &next, size_t next_num) {
  visited[next_num] = true;
  for (int i = 0; i < location_num; ++i) {
    if (i == int(next_num)) continue;
    if (visited[i] == false) {
      double temp_d = get_dist(next, loc_vector[i]);
      if (temp_d < dists[i]) {
        parents[i] = next;
        dists[i] = temp_d;
      }
    }
  }
}

double MST::get_total_dist() {
  double total = 0;
  for (size_t i = 0; i < dists.size(); ++i) {
    total += dists[i];
  }
  return total;
}

void MST::print() {
  double total = get_total_dist();
  cout << total << '\n';

  for (int i = 0; i < location_num; ++i) {
    Location curr = loc_vector[i];
    Location parent = parents[i];
    if (curr.get_loc_num() < parent.get_loc_num()) 
      cout << curr.get_loc_num() << ' ' << parent.get_loc_num() << '\n';
    else if (curr.get_loc_num() > parent.get_loc_num())
      cout << parent.get_loc_num() << ' ' << curr.get_loc_num() << '\n';
  }
}