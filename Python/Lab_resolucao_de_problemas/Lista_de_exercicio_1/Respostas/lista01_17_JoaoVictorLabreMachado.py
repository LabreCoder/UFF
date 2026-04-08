# Nome: João Victor Labre Machado
# Data de criação: 09/11/2024
# Esse programa irá verificar se um número é primo ou não

print('Esse programa irá verificar se um número é primo ou não!')
print('')

# Digitar um valor
num = int(input('Digite um número:  '))

# Aqui ele irá verificar se é primo ou não
if num==2 or num==3 or num==5 or num==7:
    print('O número',num,'é primo!')
else:
    i = 0
    for x in range(2, num):
        if num%x==0:
            i += 1
    if i>0:
        print(num,'não é primo!')
    if i==0:
        print(num,'é primo!')