def regra_cramer(matriz, resultado):
    matriz_copy = matriz.copy()
    matriz_copy.extend([[]]*2)
    
    Dk = []
    
    for k in range(len(matriz[0])):   
        matriz_copy[k] = resultado 
        matriz_copy[-2] = matriz_copy[0]
        matriz_copy[-1] = matriz_copy[1]
        
        T = 0
        i = 0
        positiva = 0
        negativa = 0
        while T < 3:
            positiva += matriz_copy[T][i]*matriz_copy[T+1][i+1]*matriz_copy[T+2][i+2]
            negativa += matriz_copy[T+2][i]*matriz_copy[T+1][i+1]*matriz_copy[T][i+2]
            T += 1
        
        Dk.extend([positiva - negativa])
        matriz_copy = matriz.copy()
        matriz_copy.extend([[]]*2)
    
    from funcao_determinante_matriz import determinante_matriz
    D = determinante_matriz(matriz)

    for d in range(len(Dk)):
        Dk[d] = (Dk[d]/D)
    return Dk