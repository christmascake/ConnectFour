#ifndef CONNECTFOUR_INCLUDE_GAME_H_
#define CONNECTFOUR_INCLUDE_GAME_H_

#include <array>

namespace connect_four {

class ConnectFour {
 public:
  static constexpr auto board_cols = 7;
  static constexpr auto board_rows = 6;

  class AI;

  enum class Side { red, yellow, none };

  using board_t = std::array<std::array<Side, board_cols>, board_rows>;

  ConnectFour();

  bool make_move(const int row, const int col);

  Side getSideAt(const int row, const int col) const noexcept;

 private:
  enum class AI_Difficulty { easy, medium, hard };

  void clear_board();

  board_t board;

  bool is_red_turn = true;

  AI_Difficulty ai_d;
};

}  // namespace connect_four

#endif  // !CONNECTFOUR_INCLUDE_GAME_H_