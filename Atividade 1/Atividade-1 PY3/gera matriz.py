#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 22 17:45:10 2017

@author: lucasnn
"""

import numpy as np

ORDEM = 3

matriz_aleat = np.random.rand(ORDEM,ORDEM)
nome_arquivo = "Matrizes Aleatórias/Matriz " + str(ORDEM)
matriz_aleat = list(matriz_aleat)

with open(nome_arquivo, "w") as file:
    for line in matriz_aleat:
        file.write(str(line))