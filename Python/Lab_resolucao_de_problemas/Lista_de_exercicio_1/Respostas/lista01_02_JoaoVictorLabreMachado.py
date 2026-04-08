# Nome: João victor Labre Machado
# Data de criação: 26/10/2024
# PA - o objetivo desse programa é coletar os seguintes dados: primeiro termo de uma PA, a razão dessa PA, e calcular os N primeiros termos!

primeiro_termo = float(input('Por favor, digite o primeiro termo da PA: '))             # Pede ao usuário o primeiro termo da PA
print('')
razao = float(input('Por favor, digite a razão da PA: '))                               # Pede ao usuário a razão da PA
print('')
N = int(input('Digite quantos termos você quer que apareça: '))                         # Pede ao usuário a quantidade de termos qu e da PA
print('')

#N = int(input('Por favor, digite a quantidade de termos desejada para a PA: '))        # Caso o usuário queira saber sobre mais termos da PA

termo_N = primeiro_termo                                                                # Irá reprensentar o valor dos demais termos
print(primeiro_termo)

while N != 1:
    termo_N += razao
    print(termo_N)
    N -= 1