# verificador de divisível

num = int(input('Por favor, digite um número:'))

if ((num%10) or (num%5) or (num%2)) == 0:
    print('Teremos, então:', end='')
    if num%10 == 0:
        print(' que este número é divisel por 10', end='')
    if num%5 == 0:
        print(' que este número é divisel por 5', end='')
    if num%2 == 0:
        print(' que este número é divisel por 2', end='')

else:
    print('O número não é dividido nem por 10, nem por 5, nem por 2!')
