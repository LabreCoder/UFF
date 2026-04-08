# Nome: João victor Labre Machado
# Data de criação: 01/12/2024
# O objetivo do programa é ler uma frase e imprimir o total de vogais, o total de brancos e o total do resto

print('O objetivo do programa é ler uma frase e imprimir o total de vogais, o total de brancos e o total do resto!','\n')

frase = input('Por favor, digite uma frase: ')

vogs = ['a','e','i','o','u','y']
total_vog = 0
total_bra = 0
total_rest = 0
frase = frase.lower()
for x in range(len(frase)):
    if frase[x] in vogs:
        total_vog += 1
    elif frase[x]==' ':
        total_bra += 1
    else:
        total_rest += 1
print(f'O total de vogais é {total_vog}, o total de brancos é {total_bra} e o total de resto é {total_rest}!')