# Nome: João Victor Labre Machado
# Data of Criation: 24/12/2024
# O objetivo do programa é calcular três raizes a partir da Regra de Cramer

print('O objetivo do programa é calcular três raizes a partir da Regra de Cramer!!')

from funcao_gerar_matriz_aleatoria import gerar_matriz_3x3
from funcao_para_escrever_matriz import escrever_matriz
from funcao_determinante_matriz import determinante_matriz
from regra_cramer import regra_cramer
import random as r


matriz = gerar_matriz_3x3()
escrever_matriz(matriz)
determinante_matriz(matriz)

resultado_equacoes = []

for i in range(3):
    resultado_equacoes.append(r.randint(0,10))
print(f'O resultado de cada equação, respectivamente, é: {resultado_equacoes}.')
raizes = regra_cramer(matriz,resultado_equacoes)

x = [x for x in raizes]
print(f'Os valores das raízes são: {x}') 
