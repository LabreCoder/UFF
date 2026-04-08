# Nome: João Victor Labre Machado
# Data de criação: 02/11/2024
# Eleição: o objetivo desse programa é realizar a contagem de votos em uma eleição simulada!

print('O objetivo desse programa é realizar a contagem de votos em uma eleição simulada!')
print('')
JS = 0
JR = 0
MM = 0
PA = 0
N = 0

print('Estameros começando a eleição desse ano!')
print('Candidato João da Silva (1)')
print('Candidato José Ramalho (2)')
print('Candidata Maria Mattos (3)')
print('Candidato Pedro Américo (4)')
print('Nulo (0)')

x = 0
voto = 0

# Caso queira mudar a quantidade de votos totais, basta alterar o 'eleitores'
eleitores = 20000                                              
while x != eleitores:                                       
    # Aqui é onde os votos serão computados
    voto = int(input('Por favor, digite seu voto: '))
    print('')
    if voto == 1:
        JS += 1
    elif voto == 2:
        JR += 1
    elif voto == 3:
        MM += 1
    elif voto == 4:
        PA += 1
    else:
        N += 1
    voto -= 3
    x += 1

print('O resultado das eleições foi: ')
print('João da Silva com',JS,'votos -',(JS*100/eleitores),'% ')
print('José Ramalho com',JR,'votos -',(JR*100/eleitores),'% ')
print('MAria Mattos com',MM,'votos -',(MM*100/eleitores),'% ')
print('Pedro Américo com',PA,'votos -',(PA*100/eleitores),'% ')
print('Nulo com',N,'votos -',(N*100/eleitores),'% ')