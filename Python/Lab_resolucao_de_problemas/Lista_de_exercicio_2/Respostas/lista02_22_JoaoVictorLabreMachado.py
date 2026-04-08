# Nome: João Victor Labre Machado
# Data of Criation: 30/12/2024
# O objetivo do programa é contar quantas vezes cada palavra ocorre no texto

print('O objetivo do programa é contar quantas vezes cada palavra ocorre no texto!!')

import random as r

alfabeto = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

entrada = open('D:\\Lista_02\\entrada.txt','r',encoding='utf-8')
saida = open('D:\\Lista_02\\saida.txt','w',encoding='utf-8')

# Aqui o programa irá ler cada um dos caracteres
caracter_ = entrada.readlines()
lista = []

# Aqui o programa irá passar esses caracteres para uma lista
for i in range(len(caracter_)):
    lista.append(caracter_[i].strip())

# Aqui o programa irá verificar os caracteres e as quantidaes
print('OS valores dos caracteres são: ',end='" ')
soma = 0
for valores in lista:
    qtd = lista.count(valores)
    print(valores,end='')
    if qtd>1:
        for j in range(qtd-1):
            lista.remove(valores)
        if valores.lower() in alfabeto: 
            saida.write(f'{valores} {qtd}')
            saida.write('\n')
            soma += qtd
        else:
            continue
    else:
        if valores.lower() in alfabeto: 
            saida.write(f'{valores} 1')
            saida.write('\n')
            soma+=1
        else:
            continue

print(' "','\n')

saida = open('D:\\Lista_02\\saida.txt','r',encoding='utf-8')
saida_ = saida.readlines()

for valor in saida_:
    print(valor.strip())
print(soma)