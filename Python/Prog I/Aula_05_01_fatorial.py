# Realizador de fatorial

num = int(input('Digite um número:'))

base = 1
for x in range(1, num+1):
    base *= x

print(f'O fatorial do {num} é {base}!')
