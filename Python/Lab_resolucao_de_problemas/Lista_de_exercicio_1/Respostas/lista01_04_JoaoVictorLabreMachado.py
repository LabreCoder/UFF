# Nome: João victor Labre Machado
# Data de criação: 26/10/2024
# Maior Valor - o objetivo desse programa é verificar qual o produto tem o maior preço e se tem algum com preço repetido!


print('Olá, iremos começar pedindo o nome de 3 produtos e logo em sequência o valor para cada um deles. É importante que não tenha nenhum valor repetido!')
print('')

produto1 = str(input('Por favor, digite o nome do produto: '))
valor1 = float(input('Agora digite o valor para',produto1,': '))

print('')

produto2 = str(input('Por favor, digite o nome do outro produto: '))
valor2 = float(input('Agora digite outro valor para',produto2,': '))

print('')

produto3 = str(input('Por favor, digite o nome do outro produto: '))
valor3 = float(input('Agora digite outro valor para',produto3,': '))

print('')

x = 1

while x != 0:

    if produto1 == produto2:
        print('Os produtos não podem ter o mesmo nome!')
        produto2 = str(input('Por favor, digite o nome do produto 2: '))
        x += 1

    elif valor1 == 0:
        print(f'Por favor, não existe produto  de 0 reais!')
        valor1 = float(input('Insira um novo valor para esse produto: '))
        x += 1
    
    elif valor1 == valor2 or valor2 == 0:
        print('Por favor, o valor do produto "',produto2,'" não pode ser igual ao do "',produto1,'"!')
        valor2 = float(input('Insira um novo valor para',produto2,': '))
        x += 1

    elif produto1 == produto3:
        print('Os produtos não podem ter o mesmo nome!')
        produto3 = str(input('Por favor, digite o nome do',produto3,': '))
        x += 1

    elif valor1 == valor3 or valor3 == 0:
        print('Por favor, o valor do produto "',produto3,'" não pode ser igual ao do "',produto1,'"!')
        valor3 = float(input('Insira um novo valor para esse',produto3,': '))
        x += 1

    elif produto2 == produto3:
        print('Os produtos não podem ter o mesmo nome!')
        produto3 = str(input('Por favor, digite o nome do',produto3,': '))
        x += 1

    elif valor2 == valor3:
        print('Por favor, o valor do produto "',produto3,'" não pode ser igual ao do "',produto2,'"!')
        valor3 = float(input('Insira um novo valor para',produto3,':'))
        x += 1        

    x -= 1

if valor1 > valor2 and valor1 > valor3:
    print('O produto mais caro é',produto1,', com R$',valor1,'!')

elif valor2 > valor3 and valor2 > valor3:
    print('O produto mais caro é',produto2,', com R$',valor2,'!')

elif valor3 > valor2 and valor3 > valor1:
    print('O produto mais caro é',produto3,', com R$',valor3,'!')
