# Verificador de crédito

saldo = float(input('Digite o seu saldo:'))

if 0 < saldo <= 200:
    print(f'De acordo com seu saldo R${saldo}, você não terá crédito!')
if 201 <= saldo <= 400:
    credito = (saldo*120)/100 - saldo
    print(f'O seu saldo é R${saldo} + {credito} de crédito!')
if 401 <= saldo <= 600:
    credito = (saldo*130)/100 - saldo
    print(f'O seu saldo é R${saldo} + {credito} de crédito!')
if saldo > 600:
    credito = (saldo*140)/100 - saldo
    print(f'O seu saldo é R${saldo} + {credito} de crédito!')
else:
    print('Você não tem saldo no banco!')
