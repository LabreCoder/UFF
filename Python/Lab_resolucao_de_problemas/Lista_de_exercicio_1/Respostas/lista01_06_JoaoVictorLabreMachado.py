# Nome: João victor Labre Machado
# Data de criação: 02/11/2024
# Somatório: o objetivo desse programa é realizar o somatório do intervalo entre A e B se B for maior que A!
print('O objetivo desse programa é realizar o somatório do intervalo entre A e B se B for maior que A!')
print('')
A = int(input('Por favor, digite A:' ))
B = int(input('Por favor, digite B:' ))

if A>B:
    print('O soma não será executada, pois A é maior que B!!')
if A==B-1:
    print('Não é possivel realizar o somatório dos números, pois eles são consecutivos!')

i = A + 1
soma = 0

while i!=B:
    if A==B:
        print('A e B não podem ser iguais')
        A = int(input('Por favor, digite A:' ))
        B = int(input('Por favor, digite B:' ))
    soma += i
    i += 1
print('A soma dos números entre A:',A,'e B:',B,'é',soma,'!')