def escrever_matriz(matriz):
    linhas = len(matriz)
    colunas = len(matriz[0])

    print(f'A matriz gerada pelo usuário tem {linhas} linha(s) e {colunas} coluna(s). Conforme segue abaixo:')
    for linha in matriz:
        print('[',end='')
        for valor in linha:
            print(f'{valor}',end=' ')
            continue
        print(']')
    return matriz