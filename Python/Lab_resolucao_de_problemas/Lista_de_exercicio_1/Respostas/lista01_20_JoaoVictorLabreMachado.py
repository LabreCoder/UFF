# Nome: João Victor Labre Machado
# Data de criação: 15/11/2024
# Esse programa irá imprimir os 4 primeiros números perfeitos

print('Esse programa irá imprimir os 4 primeiros números perfeitos!')
print('')

soma_div = 0
num_perfeito = 0
n = 2

# Ele irá pegar o número, ver se a soma dos seus divisores é igual a ele próprio, até chegar em 4 números nessa condição
print('Os 4 primeiros números perfeitos são:',end=' ')

while num_perfeito < 4:     # Não aumente a quantidade, pois o programa irá demorar muito para rodar!!
    for x in range(1,n):
        if (n%x) == 0:
            soma_div += x
    if soma_div == n:
        num_perfeito += 1
        print(n,end=', ')   
    soma_div = 0
    n += 1
print('e só!')