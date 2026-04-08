# Nome: João Victor Labre Machado
# Data de criação: 04/11/2024
# Esse programa irá calcular a quantidade de pessoas que gostaram de um produto ou não, além de calcular a porcentagem dos sexo masculino que disseram não

print('Esse programa irá calcular a quantidade de pessoas que gostaram de um produto ou não, além de calcular a porcentagem dos sexo masculino que disseram não!')
print('')

s = 0
n = 0
# Total de Homens que deram um feedback 
total_M = 0
# Total de Homens que deram um feedback negativo
total_M_n = 0 
# Total de Mulheres que deram um feedback                                                            
total_F = 0

for x in range(1,5):
    sexo = str(input('Qual seu sexo? (M)Masculino ou (F)Feminino  ->  '))
    print('Se você gostou do produto, digite:', end='')
    feedback = input('(S) Sim ou (N) Não  ->  ')
    if feedback == 'S' or feedback == 's':
        s += 1
        if sexo == 'M' or sexo == 'm':
            total_M += 1
        if sexo == 'F' or sexo == 'f':
            total_F += 1
    elif feedback == 'N' or feedback == 'n':
        n += 1
        if sexo == 'M' or sexo == 'm':
            total_M += 1
            total_M_n += 1
        if sexo == 'F' or sexo == 'f':
            total_F += 1      
    else:
        print('Por favor, preencha os dados conforme requeridos!!')
        x -= 1
print('Tivemos um total de ',s,' feedbacks positivos!')
print('Tivemos um total de ',n,' feedbacks negativos!')

# Irá calcular automaticamente a procentagem de feedbacks negativos dos homens
print((total_M_n*100)/total_M,'% dos',total_M,'participantes,',total_M_n,'homens deram um feedback negativo!')