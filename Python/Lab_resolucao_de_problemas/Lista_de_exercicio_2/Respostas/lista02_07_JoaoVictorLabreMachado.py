# Nome: João Victor Labre Machado
# Data of Criation: 18/12/2024
# O objetivo do programa é verificar se duas strings são anagramas uma da outra

print('O objetivo do programa é verificar se duas strings são anagramas uma da outra!!','\n')

string1 = input('Por favor, digite um texto: ')
string2 = input('Por favor, digite outro texto: ')

def retirar_brancos(frase1,frase2):
    frase1 = frase1.strip()
    frase2 = frase2.strip()
    return frase1, frase2

frases = retirar_brancos(string1,string2)

def anagrama(palavra1, palavra2):
    # Variável para verificação
    verificado = True
    # Irá percorrer as palavras para realizar o teste
    for i in palavra1:
        # Irá contar se todas são iguais
        cont = palavra1.count(i)
        if palavra1.count(i)==palavra2.count(i):
            verificador = True
        # Caso não sejam iguais, será indicado
        else:
            verificado = False
    if verificado == False:
        print('Não é um anagrama!')
    else:
        print('É um anagrama!!')
    return verificado
anagrama(frases[0],frases[1])