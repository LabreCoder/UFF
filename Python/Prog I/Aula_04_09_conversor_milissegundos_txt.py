miliseg = int(input('Por favor, digite a quantidade de milissegundos:'))

miliseg = miliseg // 1000
horas = miliseg // 3600
resto = miliseg % 3600
minutos = resto // 60
segs = resto % 60

if (horas and minutos and segs) == 1:
    print(f'Teremos {horas} hora,', end='')
    print(f' {minutos} minuto,', end='')
    print(f' {segs} segundo', end='')

if (horas and minutos and segs) > 1:
    print(f'Teremos {horas} horas, ', end='')
    print(f'{minutos} minutos, ', end='')
    print(f'{segs} segundos', end='')

else:
    if miliseg >= 1:
        print('Teremos:', end='')
        if horas != 0 and horas != 1:
            print(f'{horas} horas ', end='')
        if minutos != 0 and minutos != 1:
            print(f'{minutos} minutos ', end='')
        if segs != 0 and segs != 1:
            print(f'{segs} segundos ', end='')
        if horas == 1:
            print(f'{horas} hora ', end='')
        if minutos == 1:
            print(f'{minutos} minuto ', end='')
        if segs == 1:
            print(f'{segs} segundo ', end='')
    else:
        print('O valor digitado não é suficiente para completar nem 1 segundo!')
