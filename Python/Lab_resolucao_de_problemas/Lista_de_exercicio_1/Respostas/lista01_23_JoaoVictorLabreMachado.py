# Nome: João Victor Labre Machado
# Data de criação: 16/11/2024
# Esse programa irá buscar os números primos que fazem parte da série de Fibonacci

print('Esse programa irá buscar os N (colocado pelo usuário) números primos que fazem parte da série de Fibonacci!')
print('')

# Irá coletar o N requerido
N = int(input('Digita quantos números primos você quer saber se pertencem a série de Fibonacci: '))
primos_f = 0
valor_1 = 1
valor_2 = 1
contDiv = 0

# Irá realiazr o cálculo para ver se o primo faz parte da série de Fibonacci
print('Temos os próximos',N,'números primos pertencentes a sequência de Fibonacci: ')
while primos_f!=N:
    contDiv = 0 
    soma = valor_1+valor_2
    valor_1 = valor_2
    valor_2 = soma
    for i in range(2, soma):
        if (soma%i) == 0:
            contDiv += 1
    if contDiv == 0:
        primos_f +=1
        print(soma,end=', ')
print(' e obrigado por participar!!')