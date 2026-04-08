# Nome: João Victor Labre Machado
# Data of Criation: 19/12/2024
# O objetivo do programa é transpor uma matriz

from funcao_definir_valores_matriz import linhas_e_colunas, definir_valores_matriz
from funcao_para_transpor_matriz import transpor_matriz
from funcao_para_escrever_matriz import escrever_matriz

print('O objetivo do programa é transpor uma matriz!!')

linhas, colunas = linhas_e_colunas()

matriz1 = definir_valores_matriz(linhas,colunas)

matriz2 = transpor_matriz(matriz1)

escrever_matriz(matriz1)
print('')
escrever_matriz(matriz2)