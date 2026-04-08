# Nome: João Victor Labre Machado
# Data of Criation: 30/12/2024
# O objetivo do programa é trocar maiúsculas por minúsculas

print('O objetivo do programa é trocar as letras maiúsculas por minúsculas!!')

import random as r

alfabeto = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']

texto = open('D:\\Lista_02\\entrada.txt','w',encoding='utf-8')

# Aqui será decidido as letras e se elas serão maiúsculas ou minúsculas
for caracteres in range(100):
    tamanho = r.randint(0,1)
    pos_letra = r.randint(0,25)        
    if tamanho == 1:
        texto.write(alfabeto[pos_letra].upper())
        texto.write('\n')
    else:
        texto.write(alfabeto[pos_letra].lower())
        texto.write('\n')
        
# Aqui irá ser feito as trocas
texto = open('D:\\Lista_02\\entrada.txt','r',encoding='utf-8')
texto_ = texto.readlines()
lista = []
for pos in range(len(texto_)):
    print(texto_[pos].strip(), end=' ')
    if texto_[pos].isupper() == True:
        lista.append(texto_[pos].strip().lower())
    else:
        lista.append(texto_[pos].strip().upper())
else:
    print('\n')
for alteraçao in lista:
    print(alteraçao,end=' ')
    
texto.close()