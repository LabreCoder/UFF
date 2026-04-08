# Nome: João victor Labre Machado
# Data de criação: 01/12/2024
# O objetivo do programa é ordenar um vetor e ver quantos pares ele tem

print('O objetivo do programa é ordenar um vetor e ver quantos pares ele tem!!')
import random

# Creating a list with 40 random values
vetor_desordenado = [random.randint(1, 100) for _ in range(40)]

for i in range(len(vetor_desordenado)):
    aux=i
    for x in range(i+1,len(vetor_desordenado)):
        if vetor_desordenado[x]<vetor_desordenado[aux]:
            aux=x
    aux2=vetor_desordenado[i]
    vetor_desordenado[i]=vetor_desordenado[aux]
    vetor_desordenado[aux]=aux2
vetor = vetor_desordenado.copy()
cont = 0
for x in vetor:
     if x%2 == 0:
        cont += 1
print(f'O vetor ordenado é: {vetor} com {cont} números pares!')