#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 17:45:10 2017

@author: lucasnn
"""
import threading
import numpy as np

ORDEM = 100
matriz_aleat = np.random.rand(ORDEM,ORDEM)
result = np.zeros((ORDEM, ORDEM))


class myThread(threading.Thread):
    """Sobrescrevendo o construtor de Threading"""
    def __init__(self, threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
    def run(self):
        # iterate through columns of Y
        print(self.name)
        for j in range(len(matriz_aleat[0])):
            # iterate through rows of Y
            for k in range(len(matriz_aleat)):
                result[self.threadID][j] += matriz_aleat[self.threadID][k] * \
                                            matriz_aleat[k][j]


thread_list = [myThread(N , "LC"+ str(N)) for N in range(ORDEM)]
              

for thr in thread_list:
    thr.start()
    thr.join()

for line in result:
    print(line)
'''
resultado = np.zeros((ORDEM, ORDEM))

# iterate through rows of X
for i in range(len(matriz_aleat)):
   # iterate through columns of Y
   for j in range(len(matriz_aleat[0])):
       # iterate through rows of Y
       for k in range(len(matriz_aleat)):
           resultado[i][j] += matriz_aleat[i][k] * matriz_aleat[k][j]
           #print(i, j, k)
           
for linha in resultado:
   print(linha)

if resultado.all() == result.all():
    print("SOU FODA AAA")
'''
