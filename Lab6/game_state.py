import random as r
import player as p
import copy as c


class Game_state:
    def __init__(self, first, second):
        self.players = [first, second]
        self.on_desk = None
        self.played_cards = list()
        self.folded_cards = list()
        self.who_attack = 0
        self.side = 1
        self.attack_count = 0
        self.move_num = 0
        self.evaluation = 0

    def create_init_state(self):
        player_color_amount = r.randint(4, 9)
        player_trump_amount = r.randint(2, player_color_amount - 2)
        first_player_second_suit = \
            p.Card.suits[self.players[0].color][p.Card.suits[self.players[0].color].index(self.players[0].trump) - 1]
        second_player_second_suit = \
            p.Card.suits[self.players[1].color][p.Card.suits[self.players[1].color].index(self.players[1].trump) - 1]
        player_not_trump_amount = player_color_amount - player_trump_amount
        not_trump_nominals = [i for i in range(7, 15)]
        r.shuffle(not_trump_nominals)
        first_player_not_trumps = not_trump_nominals[:player_not_trump_amount]
        opposite_not_trumps = not_trump_nominals[player_not_trump_amount:]
        trump_nominals = [i for i in range(7, 15)]
        r.shuffle(trump_nominals)
        first_player_trumps = trump_nominals[:player_trump_amount]
        opposite_trumps = trump_nominals[player_trump_amount:]
        first_player_deck = list()
        second_player_deck = list()
        for trump_nominal in first_player_trumps:
            first_player_deck.append(p.Card(self.players[0].trump, trump_nominal, 0))
            second_player_deck.append(p.Card(self.players[1].trump, trump_nominal, 1))
        for not_trump_nominal in first_player_not_trumps:
            first_player_deck.append(p.Card(first_player_second_suit, not_trump_nominal, -1))
            second_player_deck.append(p.Card(second_player_second_suit, not_trump_nominal, -1))
        for not_trump_nominal in opposite_not_trumps:
            first_player_deck.append(p.Card(second_player_second_suit, not_trump_nominal, -1))
            second_player_deck.append(p.Card(first_player_second_suit, not_trump_nominal, -1))
        for trump_nominal in opposite_trumps:
            first_player_deck.append(p.Card(self.players[1].trump, trump_nominal, 1))
            second_player_deck.append(p.Card(self.players[0].trump, trump_nominal, 0))
        self.players[0].cards = first_player_deck
        self.players[1].cards = second_player_deck

    def create_child_states(self):
        child_states = list()
        if self.who_attack != self.side:
            self.create_attack_child_states(child_states)
        else:
            self.create_defense_child_states(child_states)
        return child_states

    def evaluate_state(self):
        if len(self.players[0].cards) == 0:
            return 1000000
        elif len(self.players[1].cards) == 0:
            return -1000000
        how_many_beat = 0
        for max_card in self.players[0].cards:
            for need_to_bit in self.players[1].cards:
                if p.Card.beat(need_to_bit, max_card, 0):
                    how_many_beat += 1
        max_hand = how_many_beat * 10
        max_hand = max_hand * (16 / (len(self.players[0].cards)))
        how_many_beat = 0
        for min_card in self.players[1].cards:
            for need_to_bit in self.players[0].cards:
                if p.Card.beat(need_to_bit, min_card, 1):
                    how_many_beat += 1
        min_hand = how_many_beat * 10
        min_hand = min_hand * (16 / (len(self.players[1].cards)))
        evaluation = max_hand - min_hand
        self.evaluation = evaluation

    def create_attack_child_states(self, child_states):
        if self.attack_count < 6:
            if self.on_desk is None:
                attack_cards = self.players[self.who_attack].cards
                for attack in attack_cards:
                    temp = c.deepcopy(self)
                    temp.side = 1 if temp.side == 0 else 0
                    temp.attack_count += 1
                    temp.on_desk = c.deepcopy(attack)
                    temp.played_cards.append(c.deepcopy(attack))
                    temp.players[temp.side].cards.remove(attack)
                    temp.move_num += 1
                    child_states.append(temp)
            else:
                played_nominals = set()
                for played_card in self.played_cards:
                    played_nominals.add(played_card.nominal)
                attack_cards = self.players[self.who_attack].cards
                for attack in attack_cards:
                    temp = c.deepcopy(self)
                    temp.side = 1 if temp.side == 0 else 0
                    temp.attack_count += 1
                    if attack.nominal in played_nominals:
                        temp.on_desk = c.deepcopy(attack)
                        temp.played_cards.append(c.deepcopy(attack))
                        temp.players[temp.side].cards.remove(attack)
                        temp.move_num += 1
                        child_states.append(temp)
        if self.on_desk is not None:
            temp = c.deepcopy(self)
            temp.side = 1 if temp.side == 0 else 0
            temp.attack_count = 0
            temp.on_desk = None
            temp.folded_cards = temp.folded_cards + c.deepcopy(temp.played_cards)
            temp.played_cards = list()
            temp.who_attack = 1 if temp.who_attack == 0 else 0
            temp.move_num += 1
            child_states.append(temp)

    def create_defense_child_states(self, child_states):
        who_defense = 1 if self.side == 0 else 0
        defense_cards = self.players[who_defense].cards
        for defense in defense_cards:
            if p.Card.beat(self.on_desk, defense, who_defense):
                temp = c.deepcopy(self)
                temp.on_desk = c.copy(defense)
                temp.side = who_defense
                temp.players[temp.side].cards.remove(defense)
                temp.played_cards.append(c.copy(defense))
                temp.move_num += 1
                child_states.append(temp)
        temp = c.deepcopy(self)
        temp.on_desk = None
        temp.side = who_defense
        temp.players[temp.side].cards = temp.players[temp.side].cards + temp.played_cards
        temp.played_cards = list()
        temp.attack_count = 0
        temp.move_num += 1
        child_states.append(temp)
