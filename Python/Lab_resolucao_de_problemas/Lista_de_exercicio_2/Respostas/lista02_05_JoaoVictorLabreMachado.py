# Nome: João victor Labre Machado
# Data de criação: 01/12/2024
# O objetivo do programa é trocar os 8 primeiros valores de um vetor de 16 posições

import random 

print('O objetivo do programa é trocar os 8 primeiros valores de um vetor de 16 posições!!')

vetor = [random.randint(1, 100) for _ in range(16)]

for i in range(len(vetor)):
    aux=i
    for x in range(i+1,len(vetor)):
        if vetor[x] < vetor[aux]:
            aux=x
    aux2 = vetor[i]
    vetor[i] = vetor[aux]
    vetor[aux] = aux2

vetor_ = vetor.copy()
a = 8
for i in range(16):
    if i == 8:
        a = 0
    vetor_[i] = vetor[a]
    a += 1
print(f'O vetor original é: {vetor}')
print(f'O vetor novo é: {vetor_}')