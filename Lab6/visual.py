import random
import tkinter as tk
from PIL import Image, ImageTk
import game as g
import player as p


class Menu:
    def __init__(self, root):
        self.root = root
        self.root.title("Menu")
        self.root.geometry("1280x720")
        self.root.resizable(width=False, height=False)
        self.welcome_label = tk.Label(root, text="Let's play Challenge aka Svoyi Koziri",
                                      font=("Times New Roman", 30))
        self.welcome_label.place(x=260, y=50)
        self.play_button = tk.Button(self.root, text="Play", font=("Times New Roman", 14),
                                     command=lambda: self.switch_to_suit_choice(),
                                     height=3, width=20)
        self.play_button.place(x=530, y=500)
        self.radio_boxes_var = tk.IntVar()
        self.radio_boxes_var.set(1)
        self.dif_label = tk.Label(root, text="Choose difficulty", font=("Times New Roman", 18))
        self.dif_label.place(x=550, y=200)
        self.radio_box1 = tk.Radiobutton(self.root, text="Easy", font=("Times New Roman", 14),
                                         variable=self.radio_boxes_var, value=1)
        self.radio_box1.place(x=600, y=250)
        self.radio_box2 = tk.Radiobutton(self.root, text="Medium", font=("Times New Roman", 14),
                                         variable=self.radio_boxes_var, value=2)
        self.radio_box2.place(x=600, y=300)
        self.radio_box3 = tk.Radiobutton(self.root, text="Hard", font=("Times New Roman", 14),
                                         variable=self.radio_boxes_var, value=3)
        self.radio_box3.place(x=600, y=350)

    def switch_to_suit_choice(self):
        for widget in self.root.winfo_children():
            widget.destroy()
        app = Suit_choice(self.root, self.radio_boxes_var.get())


class Suit_choice:
    def __init__(self, root, difficulty):
        self.difficulty = difficulty
        self.root = root
        self.root.title("Choose suit")
        self.dif_label = tk.Label(root, text="Choose suit", font=("Times New Roman", 18))
        self.dif_label.place(x=570, y=25)
        self.suits_image = Image.open("src/suits.png")
        self.diamonds_image = ImageTk.PhotoImage(self.suits_image.crop([0, 0, 200, 229]))
        self.diamonds_button = tk.Button(self.root,
                                         image=self.diamonds_image,
                                         command=lambda: self.switch_to_game_state("diamonds"))
        self.diamonds_button.place(x=390, y=100)
        self.hearts_image = ImageTk.PhotoImage(self.suits_image.crop([200, 0, 400, 229]))
        self.hearts_button = tk.Button(self.root,
                                       image=self.hearts_image,
                                       command=lambda: self.switch_to_game_state("hearts"))
        self.hearts_button.place(x=690, y=100)
        self.clubs_image = ImageTk.PhotoImage(self.suits_image.crop([400, 0, 600, 229]))
        self.clubs_button = tk.Button(self.root,
                                      image=self.clubs_image,
                                      command=lambda: self.switch_to_game_state("clubs"))
        self.clubs_button.place(x=390, y=400)
        self.spikes_image = ImageTk.PhotoImage(self.suits_image.crop([600, 0, 800, 229]))
        self.spikes_button = tk.Button(self.root,
                                       image=self.spikes_image,
                                       command=lambda: self.switch_to_game_state("spikes"))
        self.spikes_button.place(x=690, y=400)

    def switch_to_game_state(self, player_suit):
        for widget in self.root.winfo_children():
            widget.destroy()
        player_color = list(p.Card.suits.keys())[0] if player_suit in p.Card.suits[list(p.Card.suits.keys())[0]] \
            else list(p.Card.suits.keys())[1]
        computer_color = list(p.Card.suits.keys())[0] if player_color == list(p.Card.suits.keys())[1] \
            else list(p.Card.suits.keys())[1]
        computer_suit = p.Card.suits[computer_color][random.randint(0, 1)]
        player_suit_image, computer_suit_image = self.take_suit_images(player_suit, computer_suit)
        who_bot = random.randint(0, 1)
        player = p.Player(player_color, player_suit)
        bot = p.Player(computer_color, computer_suit)
        if who_bot:
            app = Game_vis(self.root, player, bot, who_bot, self.difficulty, player_suit_image, computer_suit_image)
        else:
            app = Game_vis(self.root, bot, player, who_bot, self.difficulty, player_suit_image, computer_suit_image)

    def take_suit_images(self, player_suit, computer_suit):
        player_suit_image = None
        computer_suit_image = None
        if player_suit == "hearts":
            player_suit_image = self.hearts_image
        if computer_suit == "hearts":
            computer_suit_image = self.hearts_image
        if player_suit == "diamonds":
            player_suit_image = self.diamonds_image
        if computer_suit == "diamonds":
            computer_suit_image = self.diamonds_image
        if player_suit == "clubs":
            player_suit_image = self.clubs_image
        if computer_suit == "clubs":
            computer_suit_image = self.clubs_image
        if player_suit == "spikes":
            player_suit_image = self.spikes_image
        if computer_suit == "spikes":
            computer_suit_image = self.spikes_image
        return player_suit_image, computer_suit_image


class Game_vis:
    def __init__(self, root, player0, player1, who_bot, difficulty, player_suit_image, computer_suit_image):
        self.game = g.Game(player0, player1, who_bot, difficulty)
        self.root = root
        self.root.title("Game")
        self.player_suit_image = player_suit_image
        self.computer_suit_image = computer_suit_image
        self.player_suit_lbl = tk.Label(self.root, image=self.player_suit_image)
        self.player_suit_lbl.place(x=10, y=350)
        self.computer_suit_lbl = tk.Label(self.root, image=self.computer_suit_image)
        self.computer_suit_lbl.place(x=10, y=135)
        self.desk_cards_images = []
        self.user_cards_images = []
        self.user_cards = []
        self.bot_cards = []
        self.desk_cards = []
        self.fold_button = tk.Button(self.root, text="End attack/Fold", font=("Times New Roman", 14),
                                     command=lambda: self.render_new_state(-1),
                                     height=3, width=20)
        self.fold_button.place(x=1000, y=300)
        self.move_lbl = tk.Label(root, text="User attacks" if who_bot else "User defenses",
                                 font=("Times New Roman", 18))
        self.move_lbl.place(x=560, y=2)
        self.back_image = ImageTk.PhotoImage(Image.open("src/back.png"))
        self.cards_image = Image.open("src/cards.png")
        if not who_bot:
            self.game.computer_move()
        self.render_cards()

    def render_cards(self):
        self.render_bot_backs()
        self.render_player_cards()
        self.render_desk_cards()

    def render_bot_backs(self):
        amount_of_cards = len(self.game.current_state.players[self.game.who_bot].cards)
        for bot_card in self.bot_cards:
            bot_card.destroy()
        self.bot_cards.clear()
        for i in range(0, amount_of_cards):
            self.bot_cards.append(tk.Label(self.root, image=self.back_image))
            self.bot_cards[i].place(x=15 + (i % 16) * 78, y=40 + (i // 16) * 108)

    def render_player_cards(self):
        for player_card in self.user_cards:
            player_card.destroy()
        self.user_cards.clear()
        self.user_cards_images.clear()
        for i, card in enumerate(self.game.current_state.players[self.game.who_player].cards):
            user_card_image = self.cut_card_from_image(card.suit, card.nominal)
            self.user_cards_images.append(user_card_image)
            temp_button = tk.Button(self.root,
                                    image=self.user_cards_images[i],
                                    command=lambda index=i: self.render_new_state(index), borderwidth=0)
            self.user_cards.append(temp_button)
            self.user_cards[i].place(x=15 + (i % 16) * 78, y=575 - (i // 16) * 108)

    def render_desk_cards(self):
        for desk_card in self.desk_cards:
            desk_card.destroy()
        self.desk_cards.clear()
        self.desk_cards_images.clear()
        for i, card in enumerate(self.game.current_state.played_cards):
            desk_card_image = self.cut_card_from_image(card.suit, card.nominal)
            self.desk_cards_images.append(desk_card_image)
            temp_lbl = tk.Label(self.root, image=self.desk_cards_images[i])
            self.desk_cards.append(temp_lbl)
            if i % 2 == 0:
                self.desk_cards[i].place(x=320 + (i // 2) * 78, y=300)
            else:
                self.desk_cards[i].place(x=320 + (i // 2) * 78, y=330)

    def cut_card_from_image(self, suit, nominal):
        card_width = 75
        card_height = 105
        if suit == "diamonds":
            y_mult = 0
        elif suit == "hearts":
            y_mult = 1
        elif suit == "clubs":
            y_mult = 2
        elif suit == "spikes":
            y_mult = 3
        else:
            y_mult = -1
        x_mult = nominal - 7
        card_temp = self.cards_image.crop([x_mult * card_width, y_mult * card_height,
                                           (x_mult + 1) * card_width, (y_mult + 1) * card_height])
        card = ImageTk.PhotoImage(card_temp)
        return card

    def render_new_state(self, card_ind):
        if self.game.end_game:
            self.render_win_state()
        else:
            if not self.game.user_move(card_ind):
                return
        if self.game.end_game:
            self.render_win_state()
        else:
            self.game.computer_move()
        if self.game.end_game:
            self.render_win_state()
        else:
            self.move_lbl.config(text="User attacks"
            if self.game.current_state.who_attack == self.game.who_player else "User defenses")
            self.render_cards()

    def render_win_state(self):
        for widget in self.root.winfo_children():
            widget.destroy()
        self.win_label = tk.Label(self.root, text="", font=("Times New Roman", 30))
        self.win_label.config(text="User win!" if self.game.who_win() else "Computer win!")
        self.win_label.place(x=510, y=200)
        self.new_game_button = tk.Button(self.root, text="New game?", font=("Times New Roman", 14),
                                         command=lambda: self.return_to_menu(),
                                         height=3, width=20)
        self.new_game_button.place(x=520, y=400)

    def return_to_menu(self):
        self.win_label.destroy()
        self.new_game_button.destroy()
        app = Menu(self.root)
