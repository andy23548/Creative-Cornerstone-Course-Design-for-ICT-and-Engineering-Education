import Screen as Scr
import corner as cnr
import maze as mz
import score
import util

#from pygame.locals import *
import numpy as np
#import pygame
import pandas
import time
import sys
import os
'''
size = (800, 800)
black = (0, 0, 0)
white = (255, 255, 255)
title = "LaLaLa"

board = pygame.transform.scale(pygame.image.load('image/board.png'),(500,100))
smile = pygame.transform.scale(pygame.image.load('image/smile.jpg'),(40,40))
cross = pygame.transform.scale(pygame.image.load('image/cross.png'),(80,80))
ding = pygame.transform.scale(pygame.image.load('image/ding.png'),(80,80))
turn = pygame.transform.scale(pygame.image.load('image/corner.png'),(80,80))
straight = pygame.transform.scale(pygame.image.load('image/straight.png'),(80,80))
dead = pygame.transform.scale(pygame.image.load('image/dead.png'),(80,80))
typ = [straight,dead,turn,ding,cross]
D = np.array(['N','S','W','E'])
'''

def main():
    maze = mz.Maze("data/maze2.csv")
    #prevCor = maze.getStartPoint()
    nextCor = maze.getStartPoint()
    car_dir = cnr.Direction.SOUTH
    point = score.scoreboard("data/UID.csv")

#    I think it's better to load pictures here...
    '''
    scr = Scr.Screen("data/maze.csv",typ)
    mapp = scr.mapp
    op = scr.op
    pygame.init()
    font = pygame.font.Font(os.environ['SYSTEMROOT'] + "\\Fonts\\mingliu.ttc", 80)
    '''
    interface = util.interface()

    xt = 0
    yt = 0
    if(sys.argv[1] == '0'):
        #pygame.display.set_caption(title)
        #font = pygame.font.SysFont("ubuntu", 40)
        #screen = pygame.display.set_mode(size, 0, 32)

        while (1):
            #TODO
            '''
            screen.fill(white)
            count = 0
            for j in range(6):
                for i in range(8):
                    y = 80*j
                    x = 80*i
                    screen.blit(op[j][i],(x,y))
                    count += 1
            message = 'Score: '+str(point.get_score())
            text = font.render(message, True, black)
            screen.blit(board,(170,500))
            screen.blit(text,(170,500))

            for event in pygame.event.get():
                if event.type == QUIT:
                    exit()
            '''
            corList = maze.strategy(nextCor)
            if len(corList) == 0:
                corner = 0
                while(not corner):
                    corner = interface.wait_for_corner()
                point.add_score(corner) 
                break

            print("from ", corList[0].getIndex())
            #pygame.display.update()


            for i in range(1, len(corList)):
                corner = 0
                while(not corner):
                    corner = interface.wait_for_corner()
                point.add_score(corner)
                action, car_dir = maze.getAction(car_dir, corList[i-1], corList[i])
                interface.send_action(action)
                print(corList[i].getIndex(), action)
                '''
                message = 'Score: '+str(point.get_score())
                text = font.render(message, True, black)
                screen.blit(board,(170,500))
                screen.blit(text,(170,500))
                #print (yt,xt)
                screen.blit(smile,(80*xt+20,80*yt+20))
                p = np.where(mapp==int(corList[i].getIndex()))
                (yt,xt) = (int(p[0]),int(p[1]))
                pygame.display.update()
                '''
            print("-----------------------")
            nextCor = corList[len(corList)-1]
            
            #pygame.display.update()

    elif(sys.argv[1] == '1'):
        while (1):
            #TODO
            corner = 0
            while(not corner):
                corner = interface.wait_for_corner()
            point.add_score(corner)
            cmd,opt = interface.cmd_input()
            interface.exeCmd(cmd,opt)

    elif(sys.argv[1] == '2'):
        #pygame.display.set_caption(title)
        #font = pygame.font.SysFont("ubuntu", 40)
        #screen = pygame.display.set_mode(size, 0, 32)

        while (1):
            #TODO
            '''
            screen.fill(white)

            count = 0
            for j in range(6):
                for i in range(8):
                    y = 80*j
                    x = 80*i
                    screen.blit(op[j][i],(x,y))
                    count += 1
            message = 'Score: '+str(point.get_score())
            text = font.render(message, True, black)
            screen.blit(board,(170,500))
            screen.blit(text,(170,500))
            
            for event in pygame.event.get():
                if event.type == QUIT:
                    exit()
            pygame.display.update()
            '''
            cor = int(input("destination: "))
            if(cor == 0):
            	print("end process")
            	print('')
            	break
            corList = maze.BFS_2(nextCor,cor)
            if len(corList) == 0:
                corner = 0
                while(not corner):
                    corner = interface.wait_for_corner()
                point.add_score(corner) 
                break

            print("from ", corList[0].getIndex())
            for i in range(1, len(corList)):
                corner = 0
                while(not corner):
                    corner = interface.wait_for_corner()
                point.add_score(corner)
                action, car_dir = maze.getAction(car_dir, corList[i-1], corList[i])
                interface.send_action(action)
                print(corList[i].getIndex(), action)
                '''
                #print (yt,xt)
                screen.blit(board,(170,500))
                screen.blit(smile,(80*xt+20,80*yt+20))
                message = 'Score: '+str(point.get_score())
                text = font.render(message, True, black)
                screen.blit(text,(170,500))
                p = np.where(mapp==int(corList[i].getIndex()))
                (yt,xt) = (int(p[0]),int(p[1]))
                #time.sleep(1)
                pygame.display.update()
                '''
            print("-----------------------")
            nextCor = corList[len(corList)-1]
            #pygame.display.update()

    corner = 0
    while(not corner):
        corner = interface.wait_for_corner()
    point.add_score(corner)

    interface.end_process()
    print("complete")
    print("")
    a = point.get_score()
    print(a)



if __name__=='__main__':
    main()