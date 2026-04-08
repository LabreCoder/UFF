# Nome: João Victor Labre Machado
# Data de criação: 04/11/2024
# Esse programa irá calcular a idade média das pessoas e a porcentagem das que estão entre 21 e 65 anos!

print('Esse programa irá calcular a idade média das pessoas e a porcentagem das que estão entre 21 e 65 anos!')
print('')
print('Para terminar o programa basta digitar: "-1"')
total = 0
soma_1 = 0
soma_2 = 0
porcentagem = 0

# Irá coletar as idades e realizar os cálculos
idade_ = False
while not idade_: 
    idade = int(input('Digite a idade:'))
    if idade == -1:
        idade_ = True
    else:
        total += 1
        soma_1 += idade
        media = soma_1/total
        if idade > 20 and idade < 66:
            soma_2 += 1
            porcentagem = (soma_2*100)/total
    
else:
    if porcentagem > 0:
        print('A quantidade total de participantes é: ',total,', a média é: ',media,', e a porcentagem das idades entre 21 e 65 é: ',porcentagem,'%', end='!')
    else:
        print('A quantidade total de participantes é: ',total,', a média é: ',media,', e não tivemos participantes entre 21 e 65 anos!')