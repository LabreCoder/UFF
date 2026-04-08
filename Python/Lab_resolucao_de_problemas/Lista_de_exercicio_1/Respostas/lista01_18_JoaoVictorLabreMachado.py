# Nome: João Victor Labre Machado
# Data de criação: 09/11/2024
# Esse programa irá imprimir Os N primeiros números primos

print('Esse programa irá imprimir os N primeiros números primos!')
print('')

x = int(input('Digite um número:'))
primos = 0
div = 0
base = 2
while primos<x:
    contDiv = 0
    for i in range(2, base):
        if base % i == 0:
            contDiv += 1
    if contDiv == 0:
        print('O número',base,'é um primo')
        primos += 1
    base += 1
print('Ao total tivemos',x,'primos!!!')