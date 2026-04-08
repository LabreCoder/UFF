# Nome: João victor Labre Machado
# Data de criação: 01/12/2024
# O objetivo do programa é ler um vetor de 30 posições e impimir quantas vezes X aparece

import random 

print('O objetivo do programa é ler um vetor de 30 posições e impimir quantas vezes X aparece!!')

vetor = [random.randint(1, 100) for _ in range(30)]

for i in range(len(vetor)):
    aux=i
    for x in range(i+1,len(vetor)):
        if vetor[x] < vetor[aux]:
            aux=x
    aux2 = vetor[i]
    vetor[i] = vetor[aux]
    vetor[aux] = aux2

print(f'O vetor é: {vetor}')
x = float(input('Digite qual número deseja saber quantas vezes apareceu no vetor:'))
cont = 0
for x_ in vetor:
     if x_ == x:
        cont += 1
print(f'O vetor ordenado é: {vetor} com {cont} vezes que o número {x} apareceu!')