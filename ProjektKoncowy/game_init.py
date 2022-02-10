import pygame
import colors
import config

# ZMIENNE GLOBALNE
# hasla
password = ""
guesses = []
# plansza
fields = []
fields_colors = []
# klawiatura
keyboard_buttons = {}

def initialization():
    pygame.init()
    # wyświetlenie okna gry
    pygame.display.set_caption("Guess the word -- GAME")
    win = pygame.display.set_mode([500, 700])
    win.fill(colors.background_color)
    pygame.display.flip()
    # rysowanie klawiatury
    pygame.draw.rect(win, colors.keyboard_color, (config.margin, config.keyboard_high, config.width - 2 * config.margin, 200 - config.margin))
    return win
