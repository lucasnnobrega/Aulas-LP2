#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 17:45:10 2017

@author: lucasnn
"""
# Programa sequencial que calcula uma matriz ao quadrado(AxA = C)

import numpy as np

ORDEM = 2

matriz_aleat = np.random.rand(ORDEM,ORDEM)

resultado = np.zeros((ORDEM, ORDEM))

# itera sobre as linhas X
for i in range(len(matriz_aleat)):
   # itera sobre as colunas de Y
   for j in range(len(matriz_aleat[0])):
       # itera sobre as linhas de Y
       for k in range(len(matriz_aleat)):
           resultado[i][j] += matriz_aleat[i][k] * matriz_aleat[k][j]
           #print(i, j, k)
           
for linha in resultado:
   print(linha)
