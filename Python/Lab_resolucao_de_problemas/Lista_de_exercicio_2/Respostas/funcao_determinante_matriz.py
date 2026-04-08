def determinante_matriz(matriz):
    matriz.extend([[]]*2)
    matriz[-2] = matriz[0]
    matriz[-1] = matriz[1]
    #print(matriz)
    
    T = 0
    i = 0
    positiva = 0
    negativa = 0
    
    while T < 3:
        positiva += matriz[T][i]*matriz[T+1][i+1]*matriz[T+2][i+2]
        negativa += matriz[T+2][i]*matriz[T+1][i+1]*matriz[T][i+2]
        T += 1
    determinante = positiva - negativa
    return determinante