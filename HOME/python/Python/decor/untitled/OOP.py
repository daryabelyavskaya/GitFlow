from copy import deepcopy
import numpy as np


class LifeGame(object):
    EMPTY = 0
    ROCK = 1
    FISH = 2
    SHRIMP = 3

    def __init__(self, field):
        self.field = field

    def get_next_generation(self):
        field2 = deepcopy(self.field)
        for i in range(len(self.field)):
            for j in range(len(self.field[i])):
                self._process_cell(field2, i, j)
        self.field = field2
        return np.array(self.field).reshape(len(self.field), len(self.field[0]))

    def _process_cell(self, field2, i, j):
        count = self._get_neighbours(i, j)
        if self.field[i][j] == 0:
            field2[i][j] = self._process_empty(count)
        if self.field[i][j] == 2:
            field2[i][j] = self._process_fish(count)
        if self.field[i][j] == 3:
            field2[i][j] = self._process_shrimp(count)

    @staticmethod
    def _process_empty(neighbours):
        if neighbours[0] == 3:
            return 2
        elif neighbours[1] == 3:
            return 3
        return 0

    @staticmethod
    def _process_fish(neighbours):
        if neighbours[0] >= 4 or neighbours[0] <= 1:
            return 0
        else:
            return 2

    @staticmethod
    def _process_shrimp(neighbours):
        if neighbours[1] >= 4 or neighbours[1] <= 1:
            return 0
        else:
            return 3

    def isCorrect(self, i, j):
        if i > -1 and j > -1 and i < len(self.field) and j < len(self.field[0]):
            return True
        else:
            return False

    def _get_neighbours(self, i, j):
        fish = 0
        shrimp = 0
        for k in range(-1, 2):
            for l in range(-1, 2):
                if not k == l == 0 and self.isCorrect(i + k, l + j):
                    if self.field[k + i][l + j] == 2:
                        fish += 1
                    if self.field[k + i][l + j] == 3:
                        shrimp += 1
        return [fish, shrimp]


life_game = LifeGame([[1, 2, 3, 0],
                      [2, 0, 0, 2],
                      [1, 2, 0, 3],
                      [3, 3, 2, 0]])
life_game1 = LifeGame([
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 2, 0, 0, 0, 0],
    [0, 0, 0, 2, 2, 2, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0]
])

print(life_game.get_next_generation())
print(life_game1.get_next_generation())
board = LifeGame([
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 2, 0, 0, 0, 0],
    [0, 0, 0, 2, 2, 2, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0]
])
for i in range(8):
    board.get_next_generation()
print(board.get_next_generation())
