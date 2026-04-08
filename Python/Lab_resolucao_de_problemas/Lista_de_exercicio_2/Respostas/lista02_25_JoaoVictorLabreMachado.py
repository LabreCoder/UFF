# Nome: João Victor Labre Machado
# Data of Criation: 30/12/2024
# O objetivo do programa é converter números inteiros para romanos

print('O objetivo do programa é converter números inteiros para romanos!!')

def arabico_para_romano(numero):
    if numero <= 0 or numero >= 4000:
        return "Número fora do intervalo permitido (1 a 3999)"

    # Dicionário de números romanos e seus respectivos valores
    valores_romanos = [
        (1000, "M"),
        (900, "CM"),
        (500, "D"),
        (400, "CD"),
        (100, "C"),
        (90, "XC"),
        (50, "L"),
        (40, "XL"),
        (10, "X"),
        (9, "IX"),
        (5, "V"),
        (4, "IV"),
        (1, "I")
    ]

    resultado = ""
    
    # Percorre os valores romanos e constrói o número romano
    for valor, romano in valores_romanos:
        while numero >= valor:
            resultado += romano
            numero -= valor

    return resultado

# Exemplo de uso
numero = int(input("Digite um número inteiro menor que 4000: "))
print(f"Em romano, o número é: {arabico_para_romano(numero)}")