# Nome: João Victor Labre Machado
# Data of Criation: 30/12/2024
# O objetivo do programa é calcular a área de um quadrilátero a partir da área de  dois triângulos

print('O objetivo do programa é calcular a área de um quadrilátero a partir da área de  dois triângulos!!')

from area_triangulo import area_triangulo

lista = [] 
for x in range(1,5):
    vertice = int(input(f'Digite o lado {x} do quadrilátero: '))
    lista.append(vertice)

area_tr1 = area_triangulo(lista[0],lista[1],lista[3])
area_tri2 = area_triangulo(lista[0],lista[2],lista[3])

area_quad = area_tr1 + area_tri2

print(area_quad)