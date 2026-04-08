# Nome: João Victor Labre Machado
# Data of Criation: 24/12/2024
# O objetivo do programa é criar um vetor com 100 elementos aleatórios e ordenar eles

print('O objetivo do programa é criar um vetor com 100 elementos aleatórios e ordenar eles!!')

import random as r
vetor = []

for i in range(100):
    vetor.append(r.randrange(100))
    
for i in range(len(vetor)):
    aux = i
    for x in range(i+1,len(vetor)):
        if vetor[x] < vetor[aux]:
            aux = x
    aux2 = vetor[i]
    vetor[i] = vetor[aux]
    vetor[aux] = aux2
print(f'O vetor ordenado é: {vetor}','\n')
