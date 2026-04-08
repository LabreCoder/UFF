# Nome: João Victor Labre Machado
# Data de criação: 03/11/2024
# Área do triângulo, sendo considerada a fórmula da àrea = (Base*Altura)/2

print('O objetivo desse programa é calcular a área do triângulo, sendo considerada a fórmula da área = (Base*Altura)/2')
print('')
a = int(input('Digite a altura do triângulo: '))
b = int(input('Digite a base do triângulo: '))
x = 1

# Esta parte não permite que um dos valores requeridos sejam 0
while x == 1:
    if a <= 0:
        a = int(input('A Altura não pode ser menor ou igual à 0, digite a altura do triângulo: '))
    elif b <= 0:
        b = int(input('A base não pode ser menor ou igual à 0, digite a base do triângulo: '))
    else:
        x = 0
area = (b*a)/2
print('A área do triângulo é',area,'metros quadrados!')