import pygame

# ktore haslo i ktora litera aktualnie zgadywana
x_offset = 0
y_offset = 0

# czcionka
pygame.font.init()
game_font = pygame.font.SysFont('consolas', 30)

# wymiary
width = 500
high = 700
keyboard_high = 500
margin = 15
letter_size = (width - 2 * margin) / 10

# TWORZENIE PÓL DO ZGADYWANIA
letter_height = letter_size
letter_width = letter_size * 0.7
x_interspace = (500 - 250) / 5
y_interspace = 500 / 6

