# Nome: João Victor Labre Machado
# Data de criação: 17/11/2024
# Esse programa irá realizar a fatoração de um número X

print('Esse programa irá realizar a fatoração de um número X!')
print('')

X = int(input('Digite um número: '))
soma = 0
a = 2

# Irá ralizar a fatorção, se possível
while X>1:
    if(X%a)==0:
        X/=a
        soma+=1
    else:
        if soma == 0:
            a+=1
        else:

            # e irá escrever aqui o número e a quantidade de vezes que ele apareceu no processo
            print(a,'^',soma)
            a+=1
            soma=0
print(a,'^',soma)