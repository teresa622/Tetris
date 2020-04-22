//
// Created by Teresa Dong on 4/17/20.
//

#ifndef FINALPROJECT_SRC_LOCATION_H_
#define FINALPROJECT_SRC_LOCATION_H_

#include <ostream>

namespace mylibrary {
// Represents a location on the board.
class Location {
 public:
  Location(int row, int col);

  // Comparison operators.
  bool operator()(const Location& lhs, const Location& rhs) const;
  bool operator==(const Location& rhs) const;
  bool operator!=(const Location& rhs) const;
  bool operator<(const Location& rhs) const;
  bool operator<=(const Location& rhs) const;
  bool operator>(const Location& rhs) const;
  bool operator>=(const Location& rhs) const;

  // Vector operators.
  Location operator+(const Location& rhs) const;
  // Note: Always returns positive coordinates.
  Location operator%(const Location& rhs) const;
  Location operator-(const Location& rhs) const;
  Location& operator+=(const Location& rhs);
  Location operator-() const;

  // Accessors.
  int Row() const;
  int Col() const;

 private:
  int row_;
  int col_;
};

std::ostream& operator<<(std::ostream& os, const Location& location);

}  // namespace mylibrary
#endif  // FINALPROJECT_SRC_LOCATION_H_
