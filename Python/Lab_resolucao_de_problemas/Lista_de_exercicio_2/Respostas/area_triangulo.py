def area_triangulo_pelo_usuario():
    from funcao_definir_valores_matriz import definir_valores_matriz
    matriz = definir_valores_matriz(3,2)
    i = True
    while i == True:
        lado1 = ((matriz[0][0]-matriz[1][0])**2 + (matriz[0][1]-matriz[1][1])**2)**0.5
        lado2 = ((matriz[1][0]-matriz[2][0])**2 + (matriz[1][1]-matriz[2][1])**2)**0.5
        lado3 = ((matriz[0][0]-matriz[2][0])**2 + (matriz[0][1]-matriz[2][1])**2)**0.5
        if (lado1+lado2)>lado3 and (lado1+lado3)>lado2 and (lado2+lado3)>lado1:
            print(f'Nós teremos então o lado 1 como: {lado1}.')
            print(f'Nós teremos então o lado 2 como: {lado2}.')
            print(f'Nós teremos então o lado 3 como: {lado3}.')
            i = False
        else:
            print('É necessário formar um triângulo, por favor coloque as coordenadas de forma coerente!')
            matriz = definir_valores_matriz(3,2)
    s = (lado1 + lado2 + lado3)/2
    area = (s*(s-lado1)*(s-lado1)*(s-lado3))**0.5
    return matriz, area

def area_triangulo(a,b,c):
    s = (a + b + c)/2
    area = (s*(s-a)*(s-b)*(s-c))**0.5
    return area