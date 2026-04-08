# Nome: João Victor Labre Machado
# Data de criação: 03/11/2024
# Soma dos primeiros ímpares, segundo requerido pelo usuário!

print('O objetivo desse programa é calcular a soma dos N primeiros ímpares colocados pelo usuário!')
print('')

# Calcula a soma dos N primeiros ímpares!
N = int(input('Por favor, digite até o que número deseja saber a soma dos ímpares: '))
soma = 0
num = 0
qtd = 0
while qtd != N:
    if num%2 != 0:
        soma += num
        qtd += 1
    num += 1
print('A soma dos',N,'primeiros ímpares foi:',soma)

# Calcula a soma dos primeiros números ímpares até o N!
soma_ = 0
num_ = 0
while num_ != N+1:
    if num_%2 != 0:
        soma_ += num_
    num_ += 1
print('A soma dos primeiros primos até',N,'é:',soma_)