# Nome: João Victor Labre Machado
# Data de criação: 17/11/2024
# Esse programa irá coletar a base numérica desejada e um número dentro das regras dela, e irá passar tudo para a base decimal

print('Esse programa irá coletar a base numérica desejada e um número dentro das regras dela, e irá passar tudo para a base decimal!')
print('')

# Usuário irá digitar a base que ele deseja colocar o número
base = int(input('Digite qual deve ser a base númérica desejada menor que 10: '))
base_ = False

# Irá informar que a base < 2 e base > 10 não são válidas
while base_ == False:
    if base == 1:
        print('Não é possível realizar com Base 1!')
        base = int(input('Digite qual deve ser a base númérica desejada menor que 10: ')) 
    elif base >= 10:
        print('Escolha uma base menor que 10!')
        base = int(input('Digite qual deve ser a base númérica desejada menor que 10: '))
    else:
        base_ = True
        print('A base escolhida foi',base)

# Irá mostrar apenas os números que pode ser digitados dentro da base escolhida
print('Só podem ser digitados os seguintes números: ', end='')

for num_base in range(0,base):
    print(num_base,',',end='')
num = int(input(' então, digite o valor: '))

# Irá verificar quantods digítos tem o número
str_num = str(num)
qtd_digitos = 0

for qtd in str_num:
    qtd_digitos += 1

numero_por_casa = 0
valor_final = 0

# Irá realizar a conversão para a base decimal
for i in range(1,qtd_digitos+1):
    numero_por_casa = num%(10**i)//10**(i-1)
    valor_final += base**(i-1)*numero_por_casa
print('O valor',num,'da base numérica',base,'irá se tornar',valor_final,'na base decimal!')