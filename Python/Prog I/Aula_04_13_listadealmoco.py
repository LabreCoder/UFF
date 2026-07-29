# Lista de almoço/janta



prato = int(input('Escolha o prato desejado:'+ '\n'+'(1) Vegetariano - 180 cal'+'\n'+'(2) Peixe - 230 cal'+'\n'+'(3) Frango - 250 cal'+'\n'+'(4) Carne - 350 cal'+'\n'+'(5) Nenhuma das opções'+'\n'))
sobremesa = int(input('Escolha o prato desejado:'+ '\n'+'(1) Abacaxi - 75 cal'+'\n'+'(2) Sorvete diet - 110 cal'+'\n'+'(3) Mouse diet - 170 cal'+'\n'+'(4) Mouse chocolate - 170 cal'+'\n'+'(5) Nenhuma das opções'+'\n'))
bebida = int(input('Escolha o prato desejado:'+ '\n'+'(1) Chá - 20 cal'+'\n'+'(2) Suco de Laranja - 70 cal'+'\n'+'(3) Suco de Melão - 100 cal'+'\n'+'(4) Refrigerante diet - 65 cal'+'\n'+'(5) Nenhuma das opções'+'\n'))

cal = 0
e = 0
p = 0
s = 0
b = 0

match prato:
    case 1:
        cal_p = 180
        e = 1
        p = 'Vegetariano'
    case 2:
        cal_p = 230
        e = 1
        p = 'Peixe'
    case 3:
        cal_p = 250
        e = 1
        p = 'Frango'
    case 4:
        cal_p = 350
        e = 1
        p = 'Carne'
    case _:
        cal_p = 0
        e += 0

match sobremesa:
    case 1:
        cal_s = 75
        e += 1
        s = 'Abacaxi'
    case 2:
        cal_s = 110
        e += 1
        s = 'Sorvete diet'
    case 3:
        cal_s = 170
        e += 1
        s = 'Mouse diet'
    case 4:
        cal_s = 170
        e += 1
        s = 'Mouse chocolate'
    case _:
        cal_s = 0
        e += 0

match bebida:
    case 1:
        cal_b = 20
        e += 1
        b = 'Chá'
    case 2:
        cal_b = 70
        e += 1
        b = 'Suco de Laranja'
    case 3:
        cal_b = 100
        e += 1
        b = 'Suco de Melão'
    case 4:
        cal_b = 70
        e += 1
        b = 'Refrigerante diet'
    case _:
        cal_b = 0
        e += 0

cal = cal_p + cal_s + cal_b

if e == 1:
    if p != 0:
        print(f'O prato escolhido foi {p} com {cal_p} calorias!')
    if s != 0:
        print(f'A sobremesa escolhido foi {s} com {cal_s} calorias!')
    if b != 0:
        print(f'A bebida escolhido foi {b} com {cal_b} calorias!')
        
if e == 2:
    print('Foram feitos as seguintes escolhas:', end='')
    if p != 0:
        print(f' prato:{p} com {cal_p} calorias'+'+', end='')
    if s != 0:
        print(f' sobremesa {s} com {cal_s} calorias'+'+', end='')
    if b != 0:
        print(f' bebida {b} com {cal_b} calorias', end='')
    print(f', totalizando {cal} calorias!')
if e == 3:
    print(f'Você escolheu um total de {e} tipos de comida, sendo o prato: {p}, a sobremesa: {s} e bebida: {b} com um total de {cal} calorias!')

if e == 0:
    print('N foi feito a escolha de nenhum prato, sobremesa ou bebida!')
    

    
