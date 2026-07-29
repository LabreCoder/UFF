a = int(input('Por favor, digite um número:'))
b = int(input('Por favor, digite outro número:'))

if a>b:
    if a%b==0:
        print('A é multiplo e maior que B!')
    else:
        print('A não é multiplo, porém é maior que B!')
elif a<b:
    if b%a==0:
        print('B é multiplo e maior que A!')
    else:
        print('B não é multiplo, porém é maior que A!')
else:
    print('A e B são o mesmo número!')
