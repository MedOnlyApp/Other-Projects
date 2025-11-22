import pygame as py
import sys
from pygame.locals import *
import random


FPS = 30 # speed of the programe (frames per second)
WINDOW_WIDTH = 500
WINDOW_HEIGHT = 500
#REVEALSPEED = 8 # Speed of revealing the boxes
CADRE_SIZE = 305
BOX_SIZE = 70 # Size of the boxes
GAP_SIZE = 5 # Gap between the boxes
BOARD_WIDTH = 4 # Number of columns in the board
BOARD_HEIGHT = 4 # Number of rows in the board

XMARGIN = int((WINDOW_WIDTH - (BOARD_WIDTH * (BOX_SIZE + GAP_SIZE))) / 2)
YMARGIN = int((WINDOW_HEIGHT - (BOARD_HEIGHT * (BOX_SIZE + GAP_SIZE))) / 2)


# Set the colors
WHIGHT = (255, 255, 255)
BLACK = (0, 0, 0)
BGCOLOR = (220, 219, 226)
BOX_COLOR = (255, 255, 255)
BOX_COLOR_2 = (11, 131, 243)
BOX_COLOR_4 = (247, 65, 50)
BOX_COLOR_8 = (247, 211, 50 )
BOX_COLOR_16 = (78, 56, 244)
BOX_COLOR_32 = (202, 183, 173)
BOX_COLOR_64 = (67, 227, 240)
BOX_COLOR_128 = (240, 138, 67)
BOX_COLOR_256 = (242, 96, 160)
BOX_COLOR_512 = (222, 242, 96)
BOX_COLOR_1024 = (147, 244, 189)
color_list = [BOX_COLOR, BOX_COLOR_2, BOX_COLOR_4, BOX_COLOR_8, BOX_COLOR_16, BOX_COLOR_32, BOX_COLOR_64, BOX_COLOR_128, BOX_COLOR_256, BOX_COLOR_512, BOX_COLOR_1024]
SCORE = 0  
BOXS_dict = {       ## Box's indexs and their value
    (0,0) : None,
    (0,1) : None,
    (0,2) : None,
    (0,3) : None,
    (1,0) : None,
    (1,1) : None,
    (1,2) : None,
    (1,3) : None,
    (2,0) : None,
    (2,1) : None,
    (2,2) : None,
    (2,3) : None,
    (3,0) : None,
    (3,1) : None,
    (3,2) : None,
    (3,3) : None
}

swipe_var = 0

def check_dict(empty_boxs_list):   ## returns a list of the empty box's indexs and a list of the full box's indexs
    for i in range(4):
        for j in range(4):
            if BOXS_dict[(i,j)] == None:
                empty_boxs_list.append((i,j))

    return empty_boxs_list

def set_dict(move, Y_N):   ## Move the boxs up, down, left and right and add the numbers 
    global SCORE, swipe_var
    if move == 'up':
        ## Move the boxes up
        for i in range(4):
            k = 0
            for j in range(4):
                if BOXS_dict[(i,j)] == None:
                    k += 1
                elif k != 0 and BOXS_dict[(i,j)] != None: 
                    BOXS_dict[(i,j-k)] = BOXS_dict[(i,j)] 
                    BOXS_dict[(i,j)] = None
                    swipe_var = 1

        ## Add the boxes together
        if Y_N == 'yes':
            for j in range(3):
                for i in range(4):
                    if BOXS_dict[(i,j)] == BOXS_dict[(i,j+1)] and BOXS_dict[(i,j)] != None:
                        BOXS_dict[(i,j)] += BOXS_dict[(i,j+1)]
                        BOXS_dict[(i,j+1)] = None
                        SCORE += BOXS_dict[(i,j)]
                        swipe_var = 1

            set_dict('up', 'no')

    elif move == 'down':
        ## Move the boxes up
        for i in range(4):
            k = 0
            for j in range(3,-1,-1):
                if BOXS_dict[(i,j)] == None:
                    k += 1
                elif k != 0 and BOXS_dict[(i,j)] != None: 
                    BOXS_dict[(i,j+k)] = BOXS_dict[(i,j)] 
                    BOXS_dict[(i,j)] = None
                    swipe_var = 1

        ## Add the boxes togeter
        if Y_N == 'yes':
            for j in range(3,0,-1):
                for i in range(4):
                    if BOXS_dict[(i,j)] == BOXS_dict[(i,j-1)] and BOXS_dict[(i,j)] != None:
                        BOXS_dict[(i,j)] += BOXS_dict[(i,j-1)]
                        BOXS_dict[(i,j-1)] = None
                        SCORE += BOXS_dict[(i,j)]
                        swipe_var = 1

            set_dict('down', 'no')

    elif move == 'left':
        ## Move the boxes up
        for j in range(4):
            k = 0
            for i in range(4):
                if BOXS_dict[(i,j)] == None:
                    k += 1
                elif k != 0 and BOXS_dict[(i,j)] != None: 
                    BOXS_dict[(i-k,j)] = BOXS_dict[(i,j)] 
                    BOXS_dict[(i,j)] = None
                    swipe_var = 1

        ## Add the boxes togeter
        if Y_N == 'yes':
            for i in range(3):
                for j in range(4):
                    if BOXS_dict[(i,j)] == BOXS_dict[(i+1,j)] and BOXS_dict[(i,j)] != None:
                        BOXS_dict[(i,j)] += BOXS_dict[(i+1,j)]
                        BOXS_dict[(i+1,j)] = None
                        SCORE += BOXS_dict[(i,j)]
                        swipe_var = 1

            set_dict('left', 'no')

    elif move == 'right':
        ## Move the boxes up
        for j in range(4):
            k = 0
            for i in range(3,-1,-1):
                if BOXS_dict[(i,j)] == None:
                    k += 1
                elif k != 0 and BOXS_dict[(i,j)] != None: 
                    BOXS_dict[(i+k,j)] = BOXS_dict[(i,j)] 
                    BOXS_dict[(i,j)] = None   
                    swipe_var = 1 

        ## Add the boxes togeter
        if Y_N == 'yes':
            for i in range(3,0,-1):
                for j in range(4):
                    if BOXS_dict[(i,j)] == BOXS_dict[(i-1,j)] and BOXS_dict[(i,j)] != None:
                        BOXS_dict[(i,j)] += BOXS_dict[(i-1,j)]
                        BOXS_dict[(i-1,j)] = None
                        SCORE += BOXS_dict[(i,j)]
                        swipe_var = 1

            set_dict('right', 'no')
    print(SCORE)

    return

def Game_over_panel():
    py.draw.rect(root, "#626264", (100, 100, CADRE_SIZE, CADRE_SIZE), border_top_left_radius=10, border_bottom_right_radius=10, border_top_right_radius=10, border_bottom_left_radius=10)
    font = py.font.SysFont('Arial bold', 50)
    font = font.render("Game Over", True, WHIGHT, "#626264")
    font_rect = font.get_rect()
    font_rect.center = (250, 250)
    root.blit(font, font_rect)

    return

def add_score():  ## Display text in the game
    global SCORE
    py.draw.rect(root, "#626264", (190, 30, 210, 50), border_top_left_radius=10, border_bottom_right_radius=10, border_top_right_radius=10, border_bottom_left_radius=10)
    font = py.font.SysFont('Arial', 40)
    font = font.render("Score: " + str(SCORE), True, WHIGHT, "#626264")
    font_rect = font.get_rect()
    font_rect.center = (300, 55)
    root.blit(font, font_rect)

    return

def add_text(text, x, y):  ## Display text in the game
    N = 2
    index = 1
    while N != text :
        N *= 2
        index += 1
    font = py.font.SysFont('Arial', 40)
    font = font.render(str(text), True, WHIGHT, color_list[index])
    font_rect = font.get_rect()
    font_rect.center = (140+75*x, 140+75*y)
    root.blit(font, font_rect)

    return

def drawBoxes(number, empty_boxs_list):   ## Draw the shapes in the game
    global swipe_var
    occ = 0 
    value = True

    for i in range(BOARD_HEIGHT):
        for j in range(BOARD_WIDTH):
            if BOXS_dict[(i,j)] != None:
                # Get the index of the color_list from the number in the box_dict
                box_num = BOXS_dict[(i,j)]
                index = 1
                while box_num != 2 :
                    box_num /= 2
                    index += 1
                # Draw the box with the right color then add the number on top
                py.draw.rect(root, color_list[index], (105+75*i, 105+75*j, BOX_SIZE, BOX_SIZE), border_top_left_radius=10, border_bottom_right_radius=10, border_top_right_radius=10, border_bottom_left_radius=10)
                add_text(BOXS_dict[(i,j)], i, j)

            else:
                py.draw.rect(root, color_list[0], (105+75*i, 105+75*j, BOX_SIZE, BOX_SIZE), border_top_left_radius=10, border_bottom_right_radius=10, border_top_right_radius=10, border_bottom_left_radius=10)

    if swipe_var != 0:
        # choose where the next 2 is gonna pop up
        while value:
            try:
                rand_tuple = random.choice(empty_boxs_list)
            except IndexError:
                py.draw.rect(root, "#626264", (100, 100, CADRE_SIZE, CADRE_SIZE), border_top_left_radius=10, border_bottom_right_radius=10, border_top_right_radius=10, border_bottom_left_radius=10)
                Game_over_panel()
                continue
            x = rand_tuple[0]
            y = rand_tuple[1]
            occ += 1

            BOXS_dict[(x, y)] = 2
            py.draw.rect(root, BOX_COLOR_2, (105+75*x, 105+75*y, BOX_SIZE, BOX_SIZE), border_top_left_radius=10, border_bottom_right_radius=10, border_top_right_radius=10, border_bottom_left_radius=10)
            add_text(2, x, y)
            if number == occ:
                value = False
            
    swipe_var = 0
    return

def main():
    global root, swipe_var
    swipe_var = 1
    py.init()
    FPSCLOCK = py.time.Clock()
    root = py.display.set_mode((WINDOW_WIDTH,WINDOW_HEIGHT))
    py.display.set_caption('2048 Game')

    root.fill(BGCOLOR)
    py.draw.rect(root, "#626264", (100, 100, CADRE_SIZE, CADRE_SIZE), border_top_left_radius=10, border_bottom_right_radius=10, border_top_right_radius=10, border_bottom_left_radius=10)
    empty_boxs_list = []
    empty_boxs_list = check_dict(empty_boxs_list)
    drawBoxes(2, empty_boxs_list)
    add_score()
    index = 1
    running = True

    py.mixer.music.load("song1.mp3")

    py.mixer.music.play()
    while running:
        
        for event in py.event.get(): # event handling loop
            empty_boxs_list = []
            if event.type == QUIT or (event.type == KEYUP and event.key == K_ESCAPE):
                py.quit()
                sys.exit()
            elif (event.type == KEYUP and event.key == K_UP):
                set_dict('up', 'yes')
                empty_boxs_list = check_dict(empty_boxs_list)
                drawBoxes(1, empty_boxs_list)
                add_score()
            elif (event.type == KEYUP and event.key == K_DOWN):
                set_dict('down', 'yes')
                empty_boxs_list = check_dict(empty_boxs_list)
                drawBoxes(1, empty_boxs_list)
                add_score()
            elif (event.type == KEYUP and event.key == K_LEFT):
                set_dict('left', 'yes')
                empty_boxs_list = check_dict(empty_boxs_list)
                drawBoxes(1, empty_boxs_list)
                add_score()
            elif (event.type == KEYUP and event.key == K_RIGHT):
                set_dict('right', 'yes')
                empty_boxs_list = check_dict(empty_boxs_list)
                drawBoxes(1, empty_boxs_list)
                add_score()

        py.display.flip()
        FPSCLOCK.tick(FPS)
        index += 1


if __name__ == '__main__':
    main()