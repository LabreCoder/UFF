# Nome: João Victor Labre Machado
# Data of Criation: 30/12/2024
# O objetivo do programa é contar quantas vezes cada palavra ocorre no texto

print('O objetivo do programa é contar quantas vezes cada palavra ocorre no texto!!')

import random as r

alfabeto = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

# Caso queira colocar um texto automático
'''texto = open('D:\\Lista_02\\texto.txt','w',encoding='utf-8')

# Aqui o programa irá gerar os caracteres
for caracteres in range(100):
    a = r.randint(50,100)
    valor = str(chr(a))
    texto.write(valor.lower())
    texto.write('\n')

texto.close()'''

# Aqui o programa irá ler cada um dos caracteres
caracter = open('D:\\Lista_02\\texto.txt','r',encoding='utf-8')
caracter_ = caracter.readline()
lista = []
dic = {}

# Aqui o programa irá passar esses caracteres para uma lista
for i in range(len(caracter_)):
    lista.append(caracter_[i])

# Aqui o programa irá verificar os caracteres e as quantidaes
print('OS valores dos caracteres são: ',end='" ')
for valores in lista:
    qtd = lista.count(valores)
    print(valores,end='')
    if qtd>1:
        for j in range(qtd-1):
            lista.remove(valores)
        if valores in alfabeto: 
            dic[f'{valores}'] = qtd
        else:
            continue
    else:
        if valores in alfabeto: 
            dic[f'{valores}'] = 1
        else:
            continue

print(' "','\n')
print(f'Os valores e suas respectivas quantidades que são letras é: {dic}')