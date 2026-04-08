# Nome: João Victor Labre Machado
# Data de criação: 04/11/2024
# Esse programa irá calcular o peso do boi mais gordo e do mais magro, além de coletar um número de identificação para ele, sendo todos os dados informados pelo usuário

print('Esse programa irá calcular o peso do boi mais gordo e do mais magro, além de coletar um número de identificação para ele, sendo todos os dados informados pelo usuário!')
print('')

# Se quiser alterar a quantidade de bis para esse programa
qtd_boi = 90

p_menor = int(input('Digite o número de identificação: '))
print('Digite o peso do boi ',p_menor,':', end='')
menor = float(input(' '))
maior = 0
p_maior = 0

# Irá fazer um range para coletar as informações requeridas
for x in range(1, qtd_boi):
    num = int(input('Digite o número de identificação: '))
    print('Digite o peso do boi ',num,':', end='')
    peso = float(input(' '))
    if menor > maior:
        maior = menor
        p_maior = p_menor
    if peso > maior:
        maior = peso
        p_maior = num
    
    # Caso você queria saber entre qual deles será escolhido para ser o maior, mesmo tendo o mesmo peso
    elif peso == maior:
        p_maior_2 = num
        peso_2 = maior
        print('Temos dois bois com o mesmo peso de ',maior,'nas posições ',p_maior,' e',p_maior_2,' e não teve nenhum outro mais pesado que eles até agora!')
    elif peso < menor:
        menor = peso
        p_menor = num
print('O boi que teve o menor peso foi ',p_menor,' com ',menor,'Kg !')
print('O boi que teve o maior peso foi ',p_maior,' com ',maior, end='Kg !') # Caso tenham dois bois com o mesmo peso, basta trocar o p_maior pelo p_maior_2, para visualizar a posição dele