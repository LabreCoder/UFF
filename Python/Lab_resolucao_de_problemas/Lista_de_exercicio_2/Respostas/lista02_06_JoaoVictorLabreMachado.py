# Nome: João Victor Labre Machado
# Data of Criation: 08/12/2024
# O objetivo do programa é verificar se uma string é um palídromo

print('O objetivo do programa é verificar se uma string é um palídromo!!','\n')

string = input('Por favor, digite uma string: ')

def adicionar_lista(texto):
    qtd_carateres = len(texto)
    lista = []
    for i in range(qtd_carateres):
        lista.append(texto[i])
    return lista

lista = adicionar_lista(string)

def verificar_palindromo(lista_):
    i = True
    quantidade = len(lista_)
    contador = 0
    while i==True:
        for valor in range(quantidade//2):
            if lista_[valor] == lista_[(-1*valor)-1]:
                contador += 1
                print(contador)
        if contador == quantidade//2:
            resposta = 'É um palíndromo!'
        else:
            resposta = 'Não é um palíndromo'
        i = False
    return resposta
print(verificar_palindromo(lista))