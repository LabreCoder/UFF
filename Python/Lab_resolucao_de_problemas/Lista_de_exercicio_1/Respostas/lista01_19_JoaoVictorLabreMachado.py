# Nome: João Victor Labre Machado
# Data de criação: 15/11/2024
# Esse programa irá imprimir se um número é perfeito ou não

print('Esse programa irá imprimir se um número é perfeito ou não!')
print('')

num = int(input('Por favor, digite um número: '))
soma_div = 0
print('Seus divisores são:',end=' ')

# Irá realizar um verificação se é número perfeito ou não
for x in range(1,num):
    if num%x==0:
        soma_div+=x
        print(x,end=', ')
if soma_div==num:
    print('a soma deles é o próprio',num,', então,',end=' ')
    print(num,'é um número perfeito!')
else:
    print('a soma deles é',soma_div,', então,',end=' ')
    print(num,'não é um número perfeito!')