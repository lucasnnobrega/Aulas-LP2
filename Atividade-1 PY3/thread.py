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

#Cria a Matriz Aleatória de ordem N
ORDEM = 2
#Cria a Matriz Aleatória de ordem N
matriz_aleat = np.random.rand(ORDEM,ORDEM)
#Cria a Matriz que irá receber a resposta
result = np.zeros((ORDEM, ORDEM))


class myThread(threading.Thread):
    """Sobrescrevendo o construtor de Threading"""
    def __init__(self, threadID, name):
        threading.Thread.__init__(self)
        self.threadID = threadID
        self.name = name
    def run(self):
        # itera sobre as colunas de Y
        #print(self.name)
        for j in range(len(matriz_aleat[0])):
            # itera sobre as linhas de Y
            for k in range(len(matriz_aleat)):
                result[self.threadID][j] += matriz_aleat[self.threadID][k] * \
                                            matriz_aleat[k][j]

#Cria um array de Threads de forma que irão fazer a operação Linha x Coluna
thread_list = [myThread(N , "LC"+ str(N)) for N in range(ORDEM)]
    
#Inicia cada thread e atrela sua execução do "main"
for thr in thread_list:
    thr.start()
    thr.join()

#imprime o array resultante
for line in result:
    print(line)

