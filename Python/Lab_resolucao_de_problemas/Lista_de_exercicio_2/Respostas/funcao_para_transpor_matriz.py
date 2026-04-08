def transpor_matriz(matriz):
    # Aqui o valor das linhas da matriz 2 tem que ser o número de colunas da matriz 1
    matriz2 = [[]]*len(matriz[0])
    for x in range(len(matriz2)):
        # Aqui o programa já ira colocar o valor para o primeiro termo da matriz 2 na posição X (0 até -1)
        for j in range(1):
            matriz2[x] = ([matriz[j][x]])
            # Aqui o programa irá extender o valor da linha da matriz 2 com os valores da coluna da matriz 1
            k = 1
            while k != len(matriz):
                matriz2[x].extend([matriz[j+k][x]])
                k+=1
    return matriz2