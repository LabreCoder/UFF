valor = int(input("Pfv, digite um valor:"))

'''valor_50 = valor_desejado//50

valor_10 = valor_desejado//10

valor_5 = valor_desejado//5

valor_1 = valor_desejado%5

if valor_50 >= 1:
    valor_10 = valor_10 - (valor_desejado//50)*5

    valor_5 = valor_5 - (valor_desejado//10)*2

    print(f" O cliente receberá {valor_50} notas de B$50,00, {valor_10} notas de B$10,00, {valor_5} notas de B$5,00, {valor_1} notas de B$1,00!")

elif valor_desejado == 0:
    print()
    
else:
    valor_10 = (valor_desejado//10)

    valor_5 = valor_5 - (valor_desejado//10)*2

    print(f" O cliente receberá {valor_50} notas de B$50,00, {valor_10} notas de B$10,00, {valor_5} notas de B$5,00, {valor_1} notas de B$1,00!")'''

valor_50 = valor//50
valor -= valor//50*50
valor_10 = valor//10
valor -= valor//10*10
valor_5 = valor//5
valor -= valor//5*5

print('Teremos, então:', end='')

if valor_50 > 0:
    print(f' {valor_50} notas de B$50', end='')

if valor_10 > 0:
    print(f' {valor_10} notas de B$10', end='')

if valor_5 > 0:
    print(f' {valor_5} notas de B$5', end='')

if valor > 0:
    print(f' {valor} notas de B$1')




