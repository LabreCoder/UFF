def gerar_matriz(max_linha,max_coluna,max_vetor):
    # Caso queria gerar uma matriz de tamanho aleatória
    import random as r
    '''linha = r.randint(max_linha)
    coluna = r.randint(1,max_coluna)'''
    #--Apague daqui até--
    linha = max_linha
    coluna = max_coluna
    #--------Aqui--------
    matriz = [[]]*linha
    for i in range(linha):
        matriz[i] = [[]]*coluna
        # Aqui será feito a subistituição de acordo com os valores do usuário
        for j in range(coluna):
            matriz[i][j] = r.randint(0,max_vetor)
    return matriz, linha, coluna

def gerar_matriz_3x3():
    import random as r
    linha = 3
    coluna = 3
    matriz = [[]]*linha
    for i in range(linha):
        matriz[i] = [[]]*coluna
        # Aqui será feito a subistituição de acordo com os valores do usuário
        for j in range(coluna):
            matriz[i][j] = r.randint(0,9)
    return matriz