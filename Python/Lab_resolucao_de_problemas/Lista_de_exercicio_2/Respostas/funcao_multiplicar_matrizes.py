def mult_matrizes(matriz1, matriz2):
    linha_m1 = len(matriz1)
    coluna_m2 = len(matriz2[0])
    v_linha_m1 = len(matriz1[0])
    nova_matriz = [[]]*linha_m1

    # Aqui o programa irá começar o cálculo pela linha i
    i=0
    while i != linha_m1:
        j = 0
        # Aqui o programa irá definir quantas colunas a nova matriz terá
        nova_matriz[i] = [[]]*coluna_m2
        # Aqui o programa irá realizar o cálculo para cada valor da nova matriz conforme a coluna
        while j != coluna_m2:
            matriz3 = 0
            # Para cada valor dentro da linha da matriz 1 multiplicado com os valores da coluna da matriz 2
            for valor_linha in range(v_linha_m1):
                matriz3 += matriz1[i][valor_linha]*matriz2[valor_linha][j]
            nova_matriz[i][j] = matriz3
            j+=1
        i += 1
    return nova_matriz