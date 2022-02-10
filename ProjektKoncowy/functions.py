# import nltk
# nltk.download('words')
from nltk.corpus import words
import random
from game_init import *
from config import *
from keyboard_button import Button

win = initialization()

def game_init():
    '''wywoluje funckje inicjalizujace: pola, klawiature oraz funkcje losujaca haslo'''
    # inicjalizacja gry
    fields_init()
    draw_keyboard()
    # print(password)
    # print(fields_colors)


def fields_init():
    '''inicjalizuje plansze do gry oraz inicjalizuje zmienne: guesses, fields, fields_colors'''
    for i in range(0, 6):
        empty_guess = []
        line = []
        fields_colors_row = []
        for j in range(0, 5):
            empty_guess.append("")
            line.append([125 + (j * x_interspace), margin + (i * y_interspace)])
            fields_colors_row.append(colors.background_color)
        guesses.append(empty_guess)
        fields.append(line)
        fields_colors.append(fields_colors_row)

def draw_keyboard():
    '''tworzy klawiature (odowluje sie do keyboard_init)'''
    pygame.draw.rect(win, colors.keyboard_color, (0, 0, 300, 300))
    keyboard_init("QWERTYUIOP", 0, 0)
    keyboard_init("ASDFGHJKL", letter_size / 2, letter_size)
    keyboard_init("ZXCVBNM<+", letter_size, 2 * letter_size)
    pygame.display.update()



def draw_fields():
    '''rysuje pola, do ktorych beda wpisywane zgadywane hasla'''
    for i in range(0, 6):
        for j in range(0, 5):
            color = fields_colors[i][j]
            pygame.draw.rect(win, color,
                             (fields[i][j][0]+1, fields[i][j][1]+1, letter_width-2, letter_height-2))
            pygame.draw.rect(win, "black",
                             (fields[i][j][0], fields[i][j][1] , letter_width, letter_height), 3, 5)


def keyboard_init(letters, x_start, y_start):
    """inicjalizuje danyc rzad klawiatury

    Parameters:
        letters(string): litery, ktore beda wpisywane do danego rzedu kawiatury
        x_start(float): wspolrzedna x-owa rozpoczecia rzedu klawiatury
        y_start(float): wspolrzedna y-owa rozpoczecia rzedu klawiatury"""
    for i, letter in enumerate(letters):
        pygame.draw.rect(win, colors.keyboard_buttons_color, (
            1.5 * margin + (i * letter_size) + x_start, keyboard_high + 1.5 * margin + y_start, letter_size * 0.7,
            letter_size * 0.9), 2, 5)
        keyboard_buttons[letter] = Button(1.5 * margin + (i * letter_size) + x_start,
                                          keyboard_high + 1.5 * margin + y_start, letter_size * 0.7, letter_size * 0.9,
                                          letter)





# funkcje do obslugi wpisywania, usuwania i sprawdzania zgadywanych hasel
def add_letter(letter):
    '''dopisuje do zgadywanego hasla kliknieta przez gracza litere

    Parameteres:
        letter (char): litera, ktora kliknal gracz'''
    global x_offset, y_offset
    # letter_text = game_font.render(letter, True, colors.button_clicked_color)
    if x_offset < 5:
        guesses[y_offset][x_offset] = letter
        x_offset += 1


def delete_letter():
    """usuwa ostatnio wpisana litere
    (obsluguje klawisz "<")"""
    global x_offset, y_offset
    if x_offset > 0:
        # win.blit(letter_text, (fields[y_offset][x_offset].first, fields[y_offset][x_offset].second))
        x_offset -= 1
        guesses[y_offset][x_offset] = ""

def game_end(result):
    """obsluguje zakonczenie gry (wygrana/przegrana)

    Parameters:
        result (string): tekst wwyswietlany na koniec VICORY/LOSE !!!"""
    win2 = pygame.display.set_mode([500, 700])
    run2 = True
    while run2:
        win2.fill(colors.background_color)
        pygame.draw.rect(win2, colors.keyboard_color, (100, 300, width - 200, high - 600))
        victory_text = game_font.render(result, True, "white")
        win2.blit(victory_text, (190, 340))
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run2 = False
        pygame.display.update()

def is_guessed(check_guess, password):
    """funkcja pomocnicza
    (sprawdza czy wpisane haslo jest rowne temu, ktore mialo zostac odgadniete)

    Parameters:
        check_guess (list of char): haslo wpisane przez gracza
        password (string): haslo, ktore nalezy zgadnac

    Returns:
        (True/False)"""
    for i in range(0, 5):
        if check_guess[i] != password[i]:
            return False
    return True


def check_guess():
    """sprawdza czy gracz nie wygral/przegral,
    jesli nie to sprawdza ktore litery sa poprawne i koloruje odpowidnio pola"""
    global x_offset, y_offset, run
    check_guess = guesses[y_offset]
    if is_guessed(check_guess, password):
        print("VICORTY")
        run = False
        game_end("VICTORY")
    elif y_offset < 5:
        for i in range(0, 5):
            if check_guess[i] == password[i]:
                fields_colors[y_offset][i] = colors.exacly_color
            elif check_guess[i] in password:
                fields_colors[y_offset][i] = colors.mostly_color
            else:
                fields_colors[y_offset][i] = colors.wrong_color

        y_offset += 1
        x_offset = 0
    else:
        game_end("LOSE !!!")



def generate_password():
    """losuje 5-literowe haslo
    (wybiera ze slownika angielskiego wszystkie slowa 5-literowe i losuje jedno z nich)

    Returns:
        password (string): haslo"""
    words_list = words.words()
    words_5 = list(filter(lambda x: len(x) == 5, words_list))

    pass_idx = random.randint(1, len(words_5))
    password = words_5[pass_idx - 1]
    password = password.upper()
    return password



password = generate_password()
print(password)