# Nome: João Victor Labre Machado
# Data de criação: 16/11/2024
# Esse programa irá coletar N números inteiros e positivos e irá verificar se ele pode formar um polígono

print('Esse programa irá coletar N números inteiros e positivos e irá verificar se ele pode formar um polígono!')
print('')

i = False
lados = 0
maior = 0
soma = 0

# O programa irá executar  conforme a vontade do usuário

while i == False:
    n = int(input('Digite um número: '))
    lados += 1
    soma += n
    if n > maior:
        maior = n
    
    # Irá verificar se pode ou não ser um polígono
    if lados >= 3:
        soma = soma - maior
        if maior < soma:
            print('Esse é um polígono com',lados,'lados.')
        else:
            print('Não pode ser formado um polígono.')
            
        # Irá perguntar se desejsa continuar adicionando os lados
        var = input('Se deseja continuar digite "s", se não, digite qualquer tecla: ')
        if var == 's' or var == 'S':
            i = not True
        else:
            i = True
            
print('Obrigado por participar!')