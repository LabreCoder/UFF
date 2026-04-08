# Nome: João Victor Labre Machado
# Data of Criation: 23/12/2024
# O objetivo do programa é condensar uma lista já ordenada

print('O objetivo do programa é condensar uma lista já ordenada!!')

lista = [3, 3, 4, 3, 7, 7, 13, 13, 23]
lista.sort()
def condensar_lista(lista):
    for i in lista:
        qtd = lista.count(i)
        if qtd>1:
            for j in range(qtd):
                lista.remove(i)
            lista.insert(i,f'{i}^{qtd}')
        else:
            continue
    return lista
print(condensar_lista(lista))