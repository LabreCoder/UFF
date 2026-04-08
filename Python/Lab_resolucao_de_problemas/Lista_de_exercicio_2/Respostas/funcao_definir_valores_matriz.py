def linhas_e_colunas():
    linhas = int(input('Por favor digite a quantidade de linhas da matriz: '))
    colunas = int(input('Por favor digite a quantidade de colunas da matriz: '))
    return linhas, colunas

def definir_valores_matriz(linha,coluna):
    matriz = [[]]*linha
    for i in range(linha):
        matriz[i] = [[]]*coluna
        # Aqui será feito a subistituição de acordo com os valores do usuário
        for j in range(coluna):
            matriz[i][j] = int(input(f'Digite o valor para a linha {i} e coluna {j} da matriz: '))
    return matriz