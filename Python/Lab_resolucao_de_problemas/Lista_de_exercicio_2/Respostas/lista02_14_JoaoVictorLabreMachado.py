# Nome: João Victor Labre Machado
# Data of Criation: 23/12/2024
# O objetivo do programa é simular um caixa eletrônico

print('O objetivo do programa é simular um caixa eletrônico!!')

valor = int(input("Pfv, digite um valor:"))

def simulador(valor):
    valor_50 = valor//50
    valor -= valor//50*50
    valor_20 = valor//20
    valor -= valor//20*20
    valor_10 = valor//10
    valor -= valor//10*10
    valor_5 = valor//5
    valor -= valor//5*5
    
    return valor_50, valor_20, valor_10, valor_5, valor

valor_50, valor_20, valor_10, valor_5, valor_1 = simulador(valor) 

if valor_50 > 0:
    print(valor_50,'notas de R$50', end=' - ')
if valor_20 > 0:
    print(valor_20,'notas de R$20', end=' - ')
if valor_10 > 0:
    print(valor_10,'notas de R$10', end=' - ')
if valor_5 > 0:
    print(valor_5,'notas de R$5', end=' - ')
if valor_1 > 0:
    print(valor_1,'notas de R$1')