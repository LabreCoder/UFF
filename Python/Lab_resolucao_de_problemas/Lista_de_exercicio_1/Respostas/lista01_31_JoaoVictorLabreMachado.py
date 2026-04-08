# Nome: João Victor Labre Machado
# Data de criação: 16/11/2024
# Esse programa irá realizar o cálculo de um número X para buscar sua raiz inteira

print('Esse programa irá realizar o cálculo de um número X para buscar sua raiz inteira!')
print('')

X = int(input('Digite um número: '))

# Irá guardar o valor base de X
guardador = X

# Irá ver a raiz quadrada de X
X = (X**0.5)
i = 1

# Irá buscar o valor de i quando X divisão inteira por i for igual a 0
while (X//i) != 0:
    i += 1

# Ele irá imprimir o valor base de X e a sua raiz inteira
print('A raiz inteira de',guardador,'é',i-1)