# Nome: João Victor Labre Machado
# Data de criação: 02/11/2024
# Feedback: o objetivo do programa é realizar uma pesquisa simples de satisfação do produto!

print('O objetivo do programa é realizar uma pesquisa simples de satisfação do produto!')
print('')

S = 0
N = 0
Total = 0
voto_ = 1

# Aqui será feito a pesquisa
while voto_ != 0:
    voto = str(input('Se você gostou do produto, digite:'+'\n'+ '(S) sim'+ '\n'+'Se não gostou digite:'+'\n'+'(N) não'+'\n'+'Caso queira encerrar a pesquisa digite (F):'+ '\n'))
    if voto == 'S' or voto == 's':
        S += 1
        Total += 1
    if voto == 'N' or voto == 'n':
        N += 1
        Total += 1
    if voto == 'F' or voto == 'f':
        voto_ = 0

# Calcula a porcentagem dos feedbacks
Porc_S = (S*100)/Total
Porc_N = (N*100)/Total

# Mostra os resultados dos feedbacks
print('Temos um total de',S,'feedback positivo!')
print('Temos um total de',N,'feedback negativo.')   
print('Ao total de',Total,'avaliações, teremos, então:',S,'-',Porc_S,'% para Sim e',N,'-',Porc_N,'% para Não!')
print('Obrigado por participar da nossa pesquisa!')