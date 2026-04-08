# Nome: João Victor Labre Machado
# Data de criação: 15/11/2024
# Esse programa irá ler um número N e calcular a fórmula requerida no exercício

print('Esse programa irá ler um número N e aplicá-lo na fórmula!')
print('')

N = int(input('Digite um número: '))
for i in range(1,N+1):
    N += (1/i)
print('O resultado do somário da fórmula é',N)