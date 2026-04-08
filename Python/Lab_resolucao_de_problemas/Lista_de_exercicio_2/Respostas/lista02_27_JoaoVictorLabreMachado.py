# Nome: João victor Labre Machado
# Data de criação: 01/12/2024
# O objetivo do programa é escrever o fatorial de decomposto em números primos

print('O objetivo do programa é escrever o fatorial de decomposto em números primos!!')

def fat_primo(num):
    fatores = []
    divisor = 2
    while divisor * divisor <= num:
        contagem = 0
        while num % divisor == 0:
            num //= divisor
            contagem += 1
        if contagem > 0:
            fatores.append(f"{divisor}^{contagem}")
        divisor += 1
    if num > 1:
        fatores.append(f"{num}^1")

    return fatores

numero = int(input('Por favor, digite o número que quer decompor: '))
resultado = fat_primo(numero)
print(resultado)
