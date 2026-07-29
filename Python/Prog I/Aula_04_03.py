P1 = float(input('Por favor, digite a nota da P1:'))
P2 = float(input('Por favor, digite a nota da P2:'))

Media = (P1 + P2)/2

if Media>=6:
    print('O aluno não precisa realizar a P3, pois sua média foi maior que 6!')
else:
    if P1>P2:
        P3 = (12 - P1)
        print(f'O aluno precisará realizar  P3 e obter nota igual ou superior a {P3:.2f}')
    elif P1<P2:
        P3 = (12 - P2)
        print(f'O aluno precisará realizar  P3 e obter nota igual ou superior a {P3:.2f}')
    else:
        P3 = (12 - P1 or P2)
        print(f'O aluno precisará realizar  P3 e obter nota igual ou superior a {P3:.2f}')
