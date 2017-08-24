#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 17:45:10 2017

@author: lucasnn
"""

# Programa em paralelo que calcula uma matriz ao quadrado(AxA = C)
# Uma Thread para cada Linha x Coluna

import threading
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import time
import sys

benchmarkThreads = []
benchmarkLinear = []

class myThread(threading.Thread):
    """Sobrescrevendo o construtor de Threading"""
    row  = 0 
    def __init__(self, row):
        self.row = row;
        threading.Thread.__init__(self);
    def run(self):
        for col in range(0, ORDEM):
            result[self.row][col] += matriz_aleat[self.row][col] * matriz_aleat[col][self.row] 
                                


def dot(first, second, size, row, col):
    acc = 0
    for i in range(size):
        acc += first[row][i] * second[i][col]
    return acc

for tamanho in range (10,100):
    #Cria a Matriz Aleatória de ordem N
    ORDEM = tamanho 
    #Cria a Matriz Aleatória de ordem N
    matriz_aleat = np.random.rand(ORDEM,ORDEM)
    #Cria a Matriz que irá receber a resposta
    result = np.zeros((ORDEM, ORDEM))

    #Cria um array de Threads de forma que irão fazer a operação Linha x Coluna
    thread_list = []
    for N in range(0,ORDEM):
        thread_list.append(myThread(N))

    start = time.time()
    #Inicia cada thread e atrela sua execução do "main"
    for thr in thread_list:
        thr.start()

    for thr in thread_list:
        thr.join()
    end = time.time()

    elapsed = end - start

    print("Threads: tamanho: " +str(ORDEM) + " Tempo: "+str(elapsed))
    benchmarkThreads.append((tamanho, elapsed))

    #################################################################################
    ###########################LINEAR MULTIPLICATION#################################
    #################################################################################
    start = time.time()
    for row in range(0,ORDEM):
        for col in range(0, ORDEM):
            result[row][col] = dot(matriz_aleat, matriz_aleat, ORDEM, row, col)
    end = time.time()
    elapsed = end - start
    print("Sequencial: tamanho: " +str(ORDEM) + " Tempo: "+str(elapsed))
    benchmarkLinear.append((tamanho, elapsed))

sizeThreads, elapsedThreads = zip(*benchmarkThreads)
sizeLinear, elapsedLinear = zip(*benchmarkLinear)


plt.ylabel('Seconds')
plt.xlabel('Size')

red = mpatches.Patch(label = 'n Threads', color = 'red')
black = mpatches.Patch(label = '1 Thread', color = 'black')

legend = plt.legend(handles=[red], loc='upper right')
legend2 = plt.legend(handles=[black], loc='upper left')

plt.gca().add_artist(legend)
plt.gca().add_artist(legend2)

plt.plot(sizeThreads, elapsedThreads, color='red',label = 'n Threads') 
plt.plot(sizeLinear, elapsedLinear, color='black',label = '1 Thread')
plt.show()

