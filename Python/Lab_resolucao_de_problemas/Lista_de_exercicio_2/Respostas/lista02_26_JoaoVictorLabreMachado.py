# Nome: João victor Labre Machado
# Data de criação: 01/12/2024
# O objetivo do programa é converter escritos para romanos

print('O objetivo do programa é converter escritos para romanos!!')
def romano_para_arabico(romano):
    valores_romanos = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}

    arabico = 0
    for i in range(len(romano) - 1, -1, -1):
        if i == len(romano) - 1 or valores_romanos[romano[i]] >= valores_romanos[romano[i + 1]]:
            arabico += valores_romanos[romano[i]]
        else:
            arabico -= valores_romanos[romano[i]]

    return arabico

numero_romano = input("Digite um número romano: ")
resultado = romano_para_arabico(numero_romano.upper())
print(f"O número arábico correspondente é: {resultado}")