# Nome: João Victor Labre Machado
# Data of Criation: 22/12/2024
# O objetivo do programa é fazer a multiplicação de matrizes

from funcao_gerar_matriz_aleatoria import gerar_matriz
from funcao_para_escrever_matriz import escrever_matriz
from funcao_multiplicar_matrizes import mult_matrizes

matriz1, linha_matriz1, coluna_matriz1 = gerar_matriz(3,3,9)
matriz2, linha_matriz2, coluna_matriz2 = gerar_matriz(3,5,9)

escrever_matriz(matriz1)
escrever_matriz(matriz2)

if coluna_matriz1 == linha_matriz2:
    matriz_nova = mult_matrizes(matriz1,matriz2)
    escrever_matriz(matriz_nova)
else:
    print('Não é possível realizar a multiplicação dessas matrizes!')
    print('[]')