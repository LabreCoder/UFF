# Nome: João Victor Labre Machado
# Data de criação: 02/11/2024
# Soma dos primeiros pares

print('O objetivo desse programa é calcular a soma dos 20 primeiros pares!')
print('')
soma = 0
x = 2
while x != 21:
    if x%2 == 0:
        soma += x
    x += 1
print('A soma dos 20 primeiros pares é:',soma)    