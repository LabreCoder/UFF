# Nome: João Victor Labre Machado
# Data de criação: 18/11/2024
# Esse programa irá coletar N números inteiros e positivos e irá verificar se ele pode formar um polígono

print('Esse programa irá coletar N números inteiros e positivos e irá verificar se ele pode formar um polígono')
print('')

D1 = int(input('Digite o dia da primeira data: '))
M1 = int(input('Digite o mês da primeira data: '))
A1 = int(input('Digite o ano da primeira data: '))

D2 = int(input('Digite o dia da segunda data: '))
M2 = int(input('Digite o mês da segunda data: '))
A2 = int(input('Digite o ano da segunda data: '))

# Salva o valor base das variáveis
dia1 = D1
mes1 = M1
ano1 = A1

qtd_dia = 0
ano_bissexto = False

# Irá verificar se é ano bissexto
if (A1 % 4 == 0 and A1 % 100 != 0) or (A1 % 400 == 0):
    ano_bissexto = True
    
# Aqui o programa irá contar os dias
while A1 < A2 or (A1 == A2 and M1 < M2) or (A1 == A2 and M1 == M2 and D1 < D2):
    
    # Valores para os meses em ordem numérica
    if M1 == 1 or M1 == 3 or M1 == 5 or M1 == 7 or M1 == 8 or M1 == 10 or M1 == 12:        
        dias_no_mes = 31
    elif M1 == 4 or M1 == 6 or M1 == 9 or M1 == 11:
        dias_no_mes = 30         
    elif M1 == 2:
        if ano_bissexto == True:      
            dias_no_mes = 29      
        else:
            dias_no_mes = 28      
    
    # Caso o dia escolhido seja o último dia do mês
    if D1 == dias_no_mes:
        D1 = 1 
        M1 += 1 
        if M1 > 12: 
            M1 = 1 
            A1 += 1
            
            # Irá verificar se esse novo ano é ou não bissexto
            if (A1 % 4 == 0 and A1 % 100 != 0) or (A1 % 400 == 0):
                ano_bissexto = True
            else:
                ano_bissexto = False
    else:
        D1 += 1
    qtd_dia += 1

print('O total de dias entre a data',dia1,'/',mes1,'/',ano1,'para o',D2,'/',M2,'/',A2,'é',qtd_dia)