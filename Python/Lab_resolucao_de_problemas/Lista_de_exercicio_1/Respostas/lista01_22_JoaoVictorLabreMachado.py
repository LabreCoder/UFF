# Nome: João Victor Labre Machado
# Data de criação: 15/11/2024
# Esse programa irá ler um valor e imprimir também a quantidade que cada nota deve ser dada ao usuário. 

print('Esse programa irá ler um valor e imprimir também a quantidade que cada nota deve ser dada ao usuário. ')
print('')

valor = int(input("Pfv, digite um valor:"))

# Aqui o programa irá buscar a quantidade de notas para cada categoria, 50, 20, 10, 5
valor_50 = valor//50
valor -= valor//50*50
valor_20 = valor//20
valor -= valor//20*20
valor_10 = valor//10
valor -= valor//10*10
valor_5 = valor//5
valor -= valor//5*5

print('Teremos, então:', end=' ')

if valor_50 > 0:
    print(valor_50,'notas de R$50', end=' - ')
if valor_20 > 0:
    print(valor_20,'notas de R$20', end=' - ')
if valor_10 > 0:
    print(valor_10,'notas de R$10', end=' - ')
if valor_5 > 0:
    print(valor_5,'notas de R$5', end=' - ')
if valor > 0:
    print(valor,'notas de R$1')