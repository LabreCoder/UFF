# Nome: João Victor Labre Machado
# Data of Criation: 30/12/2024
# O objetivo do programa é calcular a área de um triângulo a partir de uma matriz

print('O objetivo do programa é calcular a área de um triângulo a partir de uma matriz!!')

from funcao_para_escrever_matriz import escrever_matriz
from area_triangulo import area_triangulo_pelo_usuario

matriz, area  = area_triangulo_pelo_usuario()
escrever_matriz(matriz)
print(f'Nós teremos então uma área de: {area}.')