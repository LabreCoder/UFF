# Nome: João Victor Labre Machado
# Data of Criation: 06/01/2025
# O Objetivo do programa é criar subsequência

print('O Objetivo do programa é criar subsequência!!')

from itertools import combinations

def subsequencias_nao_continuas(seq):
    subsequencias = []
    
    for tamanho in range(2, len(seq) + 1):
        for comb in combinations(seq, tamanho):
            subsequencias.append(list(comb))
    
    return subsequencias

tam_conjunto = int(input('Digite o tamanho do conjunto: '))
sequencia = []
for x in range(tam_conjunto):
    sequencia.append(input('Digite um valor para o conjunto: '))
resultado = subsequencias_nao_continuas(sequencia)
print(resultado)

# Cansei!