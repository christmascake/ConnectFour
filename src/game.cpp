#include "game.h"

#include <iostream>

namespace connect_four {

ConnectFour::ConnectFour() : board{} { this->clear_board(); }

bool ConnectFour::make_move(const int row, const int col) {
  // if not placing checker at top
  if (row != 0) {
    return false;
  }

  // if not clicking empty slot
  if (this->board.at(row).at(col) != Side::none) {
    return false;
  }

  // drop checker
  for (auto i = 0; i < board_rows; i++) {
    if (this->board.at(i).at(col) != Side::none) {
      this->board.at(i - 1).at(col) =
          (this->is_red_turn) ? Side::red : Side::yellow;
      this->is_red_turn = !this->is_red_turn;
      return true;
    }
  }

  // put checker on bottom
  if (this->board.at(5).at(col) == Side::none) {
    this->board.at(5).at(col) = (this->is_red_turn) ? Side::red : Side::yellow;
    this->is_red_turn = !this->is_red_turn;
    return true;
  }

  return false;
}

bool ConnectFour::get_is_red_turn() const noexcept { return this->is_red_turn; }

ConnectFour::Side ConnectFour::getSideAt(const int row,
                                         const int col) const noexcept {
  return this->board.at(row).at(col);
}

void ConnectFour::clear_board() {
  for (auto&& i : board) {
    i.fill(Side::none);
  }
}

}  // namespace connect_four