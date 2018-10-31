from node import *
import maze as mz
import score
import student

import numpy as np
import pandas
import time
import sys
import os

def main():
    maze = mz.Maze("data/maze.csv")
    next_nd = maze.getStartPoint()
    car_dir = Direction.SOUTH
    point = score.Scoreboard("data/UID.csv")
    interface = student.interface()         # the part of calling student.py was commented out.


    if(sys.argv[1] == '0'):

        while (1):

            #TODO: Impliment your algorithm here and return the UID for evaluation function
            ndList = maze.strategy(next_nd)
            

            # ================================================
            # Basically, you will get a list of nodes and corresponding UID strings after the end of algorithm.
			# The function add_UID() would convert the UID string score and add it to the total score.
			# In the sample code, we call this function after getting the returned list. 
            # You may place it to other places, just make sure that all the UID strings you get would be converted.
            # ================================================

            for i in range(1, len(ndList)):
                node = 0
                get_UID = "just a test"
                point.add_UID(get_UID)

            break

    elif(sys.argv[1] == '1'):

        while (1):

            #TODO: Implement your algorithm here and return the UID for evaluation function
            nd = int(input("destination: "))
            
            if(nd == 0):
            	print("end process")
            	print('')
            	break
            ndList = maze.stategy_2(next_nd,nd)

            for i in range(1, len(ndList)):
                get_UID = "just a test"
                point.add_UID(get_UID)

    """
    node = 0
    while(not node):
        node = interface.wait_for_node()

    interface.end_process()
    """
    print("complete")
    print("")
    a = point.getCurrentScore()
    print("The total score: ", a)

if __name__=='__main__':
    main()