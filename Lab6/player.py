class Card:
    suits = {"red": ["diamonds", "hearts"],
             "black": ["clubs", "spikes"]}

    def __init__(self, suit, nominal, whos_trump):
        self.suit = suit
        self.nominal = nominal
        self.whos_trump = whos_trump

    def get_card_info(self):
        return self.suit, self.nominal, self.whos_trump

    @staticmethod
    def beat(attack, defense, who_defense):
        if attack.suit == defense.suit:
            return defense.nominal > attack.nominal
        elif defense.whos_trump == who_defense:
            return True
        else:
            return False

    def __eq__(self, other_card):
        return self.suit == other_card.suit and self.nominal == other_card.nominal \
               and self.whos_trump == other_card.whos_trump


class Player:
    def __init__(self, color, trump):
        self.color = color
        self.trump = trump
        self.cards = []
