# Nome: João Victor Labre Machado
# Data of Criation: 23/12/2024
# O objetivo do programa é calcular a determinante de uma matriz

from funcao_gerar_matriz_aleatoria import gerar_matriz_3x3
from funcao_para_escrever_matriz import escrever_matriz
from funcao_determinante_matriz import determinante_matriz

print('O objetivo do programa é calcular a determinante de uma matriz!!')

matriz = gerar_matriz_3x3()
escrever_matriz(matriz)

print(f'A determinante da matriz acime é: {determinante_matriz(matriz)}!')