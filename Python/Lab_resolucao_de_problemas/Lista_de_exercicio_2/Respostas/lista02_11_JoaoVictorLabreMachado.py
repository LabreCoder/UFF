# Nome: João Victor Labre Machado
# Data of Criation: 23/12/2024
# O objetivo do programa é achar o valor para pi

print('O objetivo do programa é achar o valor para pi!!')

n = int(input('Por favor, digite quantos termos deseja na série: '))

sinal = 1
base = 1
for i in range(2,n+1):
    sinal *= -1
    base += (1/i**2)*(sinal)

def definir_pi(base):
    pi = ((12*base))**(1/2)
    return pi

pi = definir_pi(base)
print(f'O valor par pi com a soma dos {n} primeiros termos é: {pi}!')