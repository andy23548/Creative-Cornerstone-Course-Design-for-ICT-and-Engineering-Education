import numpy as np
from enum import IntEnum

class Direction(IntEnum):
    NORTH = 1
    SOUTH = 2
    WEST  = 3
    EAST  = 4

def reverse(dir):
    if dir == Direction.NORTH: return Direction.SOUTH
    if dir == Direction.SOUTH: return Direction.NORTH
    if dir == Direction.WEST:  return Direction.EAST
    if dir == Direction.EAST:  return Direction.WEST
    print("invalid Direction")
    return 0

class Corner:
    def __init__(self, index=0):
        self.index = index
        self.Successors = []

    def getIndex(self):
        return self.index

    def setSuccessor(self, successor, direction, length=1):
        for succ in self.Successors:
            if succ[0].getIndex() == successor.getIndex():
                print("Corner(", self.index, ") setSuccessor Failed (duplicate successor).")
                return
            if succ[1] == direction:
                print("Corner(", self.index, ") setSuccessor Failed (duplicate direction).")
                return
        self.Successors.append((successor, direction, length))
        return

    def getSuccessor(self, direction):
        for succ in self.Successors:
            if succ[1] == direction:
                return succ[0]
        print("Corner(", self.index, ") Successor is not found")
        return 0

    def getSuccessors(self):
        return self.Successors

    def getDirection(self, cor):
        for succ in self.Successors:
            if succ[0] == cor: return succ[1]
        print("Error in corner.py, getDirection()")
        print("Corner(",cor.getIndex(),") is not the Successor of Corner(",self.index,")")
        return 0
        
    def getLegalDirections(self):
        directions = []
        for succ in self.Successors:
            directions.append(succ[1])
        return directions

    def isEnd(self):
        return len(self.Successors) == 1 and self.index != 1

    def isSuccessor(self, cor):
        for succ in self.Successors:
            if succ[0] == cor: return True
        return False
