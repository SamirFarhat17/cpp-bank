#!/bin/python3

import math
import os
import random
import re
import sys

#
# Complete the 'countSort' function below.
#
# The function accepts 2D_STRING_ARRAY arr as parameter.
#

def countSort(arr: list[list[str]]) -> None:
    for i in range(len(arr) // 2):
        arr[i][1] = "-"
    arr.sort(key=lambda x: int(x[0]))
    print(*(x[1] for x in arr))

if __name__ == '__main__':
    n = int(input().strip())

    arr = []

    for _ in range(n):
        arr.append(input().rstrip().split())

    countSort(arr)
