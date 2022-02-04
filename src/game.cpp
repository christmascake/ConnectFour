#include "game.h"

#include <iostream>

namespace connect_four {

ConnectFour::ConnectFour() : board{} { this->clear_board(); }

bool ConnectFour::make_move(const int row, const int col) {
  // if someone has already won
  if (this->side_won != Side::none) {
    return false;
  }

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

bool ConnectFour::check_side_won() {
  for (auto i = 0; i < board_rows; i++) {
    for (auto j = 0; j < board_cols; j++) {
      // is there a checker at this spot?
      if (this->board.at(i).at(j) != Side::none) {
        auto& this_checker = this->board.at(i).at(j);
        auto& this_row = this->board.at(i);

        // is there 3 slots east of this checker?
        if (j + 3 < board_cols) {
          // are there 4 of a kind?
          if (this_checker == this_row.at(j + 1) &&
              this_row.at(j + 1) == this_row.at(j + 2) &&
              this_row.at(j + 2) == this_row.at(j + 3)) {
            this->side_won = this_checker;
            return true;
          }
        }

        // is there 3 slots south of this checker?
        if (i + 3 < board_rows) {
          // are there 4 of a kind?
          if (this_checker == this->board.at(i + 1).at(j) &&
              this->board.at(i + 1).at(j) == this->board.at(i + 2).at(j) &&
              this->board.at(i + 2).at(j) == this->board.at(i + 3).at(j)) {
            this->side_won = this_checker;
            return true;
          }
        }

        // is there 3 slots south-east of this checker?
        if (i + 3 < board_rows && j + 3 < board_cols) {
          // are there 4 of a kind?
          if (this_checker == this->board.at(i + 1).at(j + 1) &&
              this->board.at(i + 1).at(j + 1) ==
                  this->board.at(i + 2).at(j + 2) &&
              this->board.at(i + 2).at(j + 2) ==
                  this->board.at(i + 3).at(j + 3)) {
            this->side_won = this_checker;
            return true;
          }
        }

        // is there 3 slots south-west of this checker?
        if (i + 3 < board_rows && j - 3 > 0) {
          // are there 4 of a kind?
          if (this_checker == this->board.at(i + 1).at(j - 1) &&
              this->board.at(i + 1).at(j - 1) ==
                  this->board.at(i + 2).at(j - 2) &&
              this->board.at(i + 2).at(j - 2) ==
                  this->board.at(i + 3).at(j - 3)) {
            this->side_won = this_checker;
            return true;
          }
        }
      }
    }
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