import node
import numpy as np
import csv
import pandas
from enum import IntEnum

class Action(IntEnum):
    ADVANCE    = 1
    U_TURN     = 2
    TURN_RIGHT = 3
    TURN_LEFT  = 4
    HALT       = 5

class Maze:
    def __init__(self, filepath):
        self.raw_data = pandas.read_csv(filepath).values
        self.nodes = []
        self.nd_dict = dict() # key: index, value: the correspond node
        self.explored = set()

        for dt in self.raw_data:
            continue
            #TODO: Update the nodes with the information from raw_data


        for i in range(len(self.nodes)):
            for j in range(1,5):
                continue
                #TODO: Update the successors for each node

    def getStartPoint(self):

        if (len(self.nd_dict) < 2):
            print ("Error: the start point is not included.")
            return 0
        return self.nd_dict[1]
    
    def BFS(self, nd):
        """ return a sequence of nodes from the node to the nearest unexplored deadend"""
        #TODO: design your data structure here for your algorithm
        queue = [nd]
        # explored set
        ndList = []
        while (True):
            #TODO: Apply your algorithm here. Make sure your algorithm can update values and stop under some conditions.

            break
        #TODO: update the information of your data structure

        ndList.reverse()

        return ndList

    def BFS_2(self, nd_from, nd_to):
        """ return a sequence of nodes of the shortest path"""
        #TODO: similar to BFS but fixed start point and end point
        ndList = []

        return ndList

    def getAction(self, car_dir, nd_from, nd_to):
        """ return an action and the next direction of the car """
        if nd_from.isSuccessor(nd_to):
            nd_dir = nd_from.getDirection(nd_to)
            #TODO: Return the action based on the current car direction and the direction to next node
            print("Error: Failed to get the action")
            return 0
        else:
            print("Error: Node(",nd_to.getIndex(),") is not the Successor of Node(",nd_from.getIndex(),")")
            return 0

    def strategy(self, nd):
        return self.BFS(nd)

    def strategy_2(self, nd_from, nd_to):
        return self.BFS_2(nd_from, nd_to)