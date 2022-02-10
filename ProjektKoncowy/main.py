from functions import *

game_init()

# petla glowna
run = True
while run:
    win.fill(colors.background_color)
    draw_fields()
    # draw_keyboard()
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
        if event.type == pygame.MOUSEBUTTONDOWN:
            for letter, button in keyboard_buttons.items():
                if button.checkForInput(pygame.mouse.get_pos()):
                    if letter == "<":
                        delete_letter()
                    elif letter == "+":
                        check_guess()
                    else:
                        add_letter(letter)

    for button in keyboard_buttons.values():
        button.update(win)
        button.changeColor(pygame.mouse.get_pos())
    for y, guess in enumerate(guesses):
        for x, letter in enumerate(guess):
            letter_text = game_font.render(letter, True, colors.button_color)
            win.blit(letter_text, (fields[y][x][0] + letter_width/4, fields[y][x][1] + letter_height/4))
    pygame.display.update()

