# Nome: João Victor Labre Machado
# Data of Criation: 22/12/2024
# O objetivo do programa é verificar quais são os valores dentro de uma matriz maiores que 10

print('O objetivo do programa é verificar quais são os valores dentro de uma matriz maiores que 10!!')
from funcao_para_escrever_matriz import escrever_matriz
from funcao_gerar_matriz_aleatoria import gerar_matriz

tamanho_maximo_linhas = int(input('Por favor, digite o tamanho máximo para as linhas: '))
tamanho_maximo_colunas = int(input('Por favor, digite o tamanho máximo para as colunas: '))
tamanho_maximo_do_vetor = int(input('Por favor, digite o tamanho máximo para as vetor: '))

matriz, linhas, colunas = gerar_matriz(tamanho_maximo_linhas,tamanho_maximo_colunas,tamanho_maximo_do_vetor)
escrever_matriz(matriz, linhas, colunas)

def mat_maior_10(matriz):
    qtd_maior_10 = 0
    num_maior_10 = []
    for linha in matriz:
        for num in linha:
            if num>10:
                qtd_maior_10 += 1
                num_maior_10.append(num)
    return qtd_maior_10, num_maior_10

qtd_maior_10, lista_maior_10 = mat_maior_10(matriz)

if qtd_maior_10 != 0:
    print(f'{qtd_maior_10} foi a quantidade de números maiores que 10!')
    print(f'Segue a lista dos números que foram maior que 10: {lista_maior_10}!')
else:
    print('Não teve nenhum valor maior que 10!')