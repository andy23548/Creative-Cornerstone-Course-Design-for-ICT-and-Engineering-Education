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
    maze = mz.Maze("data/maze_test.csv")
    next_nd = maze.getStartPoint()
    node_dict = maze.getNodeDict()
    car_dir = Direction.SOUTH
    point = score.Scoreboard("data/UID.csv")
    interface = student.interface()         # the part of calling student.py was commented out.

    # Do not have destination
    if (sys.argv[1] == '0'):
        print("Mode 0")
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

    # Have destination
    elif (sys.argv[1] == '1'):
        print("Mode 1")
        while (1):
            #TODO: Implement your algorithm here and return the UID for evaluation function
            nd = int(input("destination: "))
            if(nd == 0):
            	print("end process")
            	print('')
            	break
            try:
                nd = node_dict[nd]
            except:
                print("Your input is not a valid node !!")
                raise IndexError("No node!")
            # print(nd)
            # print(next_nd)
            ndList = maze.strategy_2(next_nd,nd)

            for i in range(1, len(ndList)):
                get_UID = "just a test"
                point.add_UID(get_UID)

    # Our testing mode
    elif (sys.argv[1] == '2'):
        print("Mode 2")
        while(1):
            state_cmd = input("Please enter a mode command: ")
            print(state_cmd)
            # if state_cmd == 's':
            #     print(state_cmd)
            # if state_cmd == '':
            #     print(state_cmd)
            # if state_cmd == 's':
            #     print(state_cmd)
            # if state_cmd == 's':
            #     print(state_cmd)
            # if state_cmd == 's':
            #     print(state_cmd)
            # if state_cmd == 's':
            #     print(state_cmd)

            interface.ser.SerialWrite(state_cmd)
            interface.ser.SerialReadString()
            if state_cmd == "break":
                
                break
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