a = int(input('Digite um número:'))
b = int(input('Digite outro número:'))

if a<b:
    for x in range(a, b+1):

        if x==2 or x==3 or x==5 or x==7:
            print(f'{x}, ',end='')
        if x%(x**(1/2)) == 0:
            #print(x)
            continue
        if (x%2)!= 0 and (x%3)!= 0 and (x%5)!= 0 and (x%7)!= 0:
            print(f'{x}, ', end ='')

else:
    for x in range(b, a+1):

        if x==2 or x==3 or x==5 or x==7:
            print(f'{x}, ',end='')
        if x%(x**(1/2)) == 0:
            #print(x)
            continue
        if (x%2)!= 0 and (x%3)!= 0 and (x%5)!= 0 and (x%7)!= 0:
            print(f'{x}, ', end ='')
    else:
        print(' e terminamos aqui kkk', end='.')

