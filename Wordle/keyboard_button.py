import pygame
import colors

pygame.init()
screen = pygame.display.set_mode((700, 500))
pygame.display.set_caption("Button!")
game_font = pygame.font.SysFont('consolas', 30)

margin = 7

class Button():
    def __init__(self, x_position, y_position, width, height, text_input):
        self.x_pos = int(x_position)
        self.y_pos = int(y_position)
        self.width = int(width)
        self.height = int(height)
        # self.rect = self.get_rect(center=(self.x_pos, self.y_pos))
        self.text_input = text_input
        self.text = game_font.render(self.text_input, True, 'black')
        # self.text_rect = self.text.get_rect(center=(self.x_pos, self.y_pos))

    def update(self, win):
        '''wyswietla przycisk'''
        screen.blit(self.text, (self.x_pos+margin, self.y_pos+6))
        pygame.draw.rect(win, colors.button_frame_color, (self.x_pos, self.y_pos, self.width, self.height), 2, 5)

    def checkForInput(self, position):
        return position[0] in range(self.x_pos, self.x_pos+self.width) and position[1] in range(self.y_pos, self.y_pos+self.height)


    def changeColor(self, position):
        '''zmienia kolor tekstu na klawiaturze po najechaniu na nia myszka'''
        if position[0] in range(self.x_pos, self.x_pos + self.width) and position[1] in range(self.y_pos, self.y_pos + self.height):
            self.text = game_font.render(self.text_input, True, colors.button_clicked_color)
        else:
            self.text = game_font.render(self.text_input, True, colors.button_color)


