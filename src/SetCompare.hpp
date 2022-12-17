#include <iostream>
#include <map>
#include <set>

bool SetCompare(const std::set<string>& lhs, const std::set<string>& rhs) {
  // Compare the sizes of the sets first
  if (lhs.size() != rhs.size()) {
    return lhs.size() < rhs.size();
  }

  // If the sizes are equal, compare the elements of the sets
  auto it1 = lhs.begin();
  auto it2 = rhs.begin();
  while (it1 != lhs.end()) {
    if (*it1 != *it2) {
      return *it1 < *it2;
    }
    ++it1;
    ++it2;
  }

  // The sets are equal
  return false;
}