import corner
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
        self.corners = []
        self.cor_dict = dict() # key: index, value: the correspond corner
        self.explored = set()

        for dt in self.raw_data:
            tmp = corner.Corner(dt[0])
            self.corners.append(tmp)
            self.cor_dict[dt[0]] = tmp

        for i in range(len(self.corners)):
            for j in range(1,5):
                if not np.isnan(self.raw_data[i][j]) : 
                    if not np.isnan(self.raw_data[i][j+4]):
                        self.corners[i].setSuccessor(self.cor_dict[self.raw_data[i][j]], corner.Direction(j),int(self.raw_data[i][j+4]))
                    else:
                        self.corners[i].setSuccessor(self.cor_dict[self.raw_data[i][j]], corner.Direction(j))

        self.explored.add(self.cor_dict[1])

    def getStartPoint(self):
        return self.cor_dict[1]
    
    def BFS(self, cor):
        """ return a sequence of corner from the corner to the nearest unexplored deadend"""
        frontier = [cor]
        transitionTable = dict()
        corList = []
        explored = set()
        while (True):
            if len(frontier) == 0:
                return []
            node = frontier.pop()
            if node.isEnd() and node not in self.explored:
                break
            expand = node.getSuccessors()
            for leaf in expand:
                if leaf[0] not in explored:
                    frontier.insert(0,leaf[0])
                    transitionTable[leaf[0]] = node
                explored.add(leaf[0])
        corList.append(node)
        self.explored.add(node)
        while node != cor:
            prev = transitionTable[node]
            corList.append(prev)
            node = prev
        corList.reverse()
        return corList

    def BFS_2(self, cor_from, cor_to):
        """ return a sequence of corner of the shortest path"""
        frontier = [cor_from]
        transitionTable = dict()
        corList = []
        explored = set()
        while (True):
            if len(frontier) == 0:
                return []
            node = frontier.pop()
            if node.getIndex() == cor_to:
                break
            expand = node.getSuccessors()
            for leaf in expand:
                if leaf[0] not in explored:
                    frontier.insert(0,leaf[0])
                    transitionTable[leaf[0]] = node
                explored.add(leaf[0])
        corList.append(node)
        self.explored.add(node)
        while node != cor_from:
            prev = transitionTable[node]
            corList.append(prev)
            node = prev
        corList.reverse()
        return corList

    def getAction(self, car_dir, cor_from, cor_to):
        """ return an action and the next direction of the car """
        if cor_from.isSuccessor(cor_to):
            cor_dir = cor_from.getDirection(cor_to)
            tmpsum = int(car_dir) + int(cor_dir)
            tmpminus = int(car_dir) - int(cor_dir)
            if car_dir == cor_dir: return Action.ADVANCE, cor_dir
            if tmpsum == 3 or tmpsum == 7: return Action.U_TURN, cor_dir
            if tmpminus == 2 or tmpminus == -1 or tmpminus == -3: return Action.TURN_RIGHT, cor_dir
            if tmpminus == -2 or tmpminus == 1 or tmpminus == 3: return Action.TURN_LEFT, cor_dir
            print("Error in maze.py, getAction()")
            return 0
        else:
            print("Error in maze.py, getAction()")
            print("Corner(",cor_to.getIndex(),") is not the Successor of Corner(",cor_from.getIndex(),")")
            return 0

    def strategy(self, cor):
        return self.BFS(cor)

