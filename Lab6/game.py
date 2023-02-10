import game_state as gs
import minimax as alg


class Game:
    def __init__(self, player0, player1, who_bot, difficulty):
        self.current_state = gs.Game_state(player0, player1)
        self.current_state.create_init_state()
        self.who_bot = who_bot
        self.who_player = 1 if who_bot == 0 else 0
        self.end_game = False
        self.difficulty = difficulty

    def user_move(self, card_ind):
        available_moves = self.current_state.create_child_states()
        if card_ind != -1:
            for move in available_moves:
                if move.on_desk is not None and \
                        self.current_state.players[self.who_player].cards[card_ind] == move.on_desk:
                    if not move.players[0].cards or not move.players[1].cards:
                        self.end_game = True
                    self.current_state = move
                    return True
        else:
            for move in available_moves:
                if move.on_desk is None:
                    if not move.players[0].cards or not move.players[1].cards:
                        self.end_game = True
                    self.current_state = move
                    return True
        return False

    def computer_move(self):
        move = alg.alpha_beta(self.current_state, self.difficulty, -float('inf'), float('inf'), not self.who_bot)
        if not move.create_child_states():
            self.end_game = True
        self.current_state = move

    def who_win(self):
        if self.end_game:
            if not self.current_state.players[self.who_bot].cards:
                return 0
            elif not self.current_state.players[self.who_player].cards:
                return 1
        else:
            return -1
