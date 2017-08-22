#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 17:45:10 2017

@author: lucasnn
"""

# Program to multiply two matrices using nested loops

import numpy as np

ORDEM = 100

matriz_aleat = np.random.rand(ORDEM,ORDEM)

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
