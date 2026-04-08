# Nome: João Victor Labre Machado
# Data of Criation: 23/12/2024
# O objetivo do programa é fazer uma função que calcule os N primeiros primos

print('O objetivo do programa é fazer uma função que calcule os N primeiros primos!!')

N = int(input('Digite a quantidade de N primeiros números primos desejar saber: '))

def N_primeiros_primos(N):
    lista_n_primos = []
    primos = 0
    base = 2
    while primos<N:
        contDiv = 0
        for i in range(2, base):
            if base % i == 0:
                contDiv += 1
        if contDiv == 0:
            primos += 1
            lista_n_primos.extend([base])
        base += 1
    return lista_n_primos

print(f'{N_primeiros_primos(N)} são os {N} primeiros primos!')