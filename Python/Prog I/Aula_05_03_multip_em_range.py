a = int(input('digite um numero menor ou igual ao próximo:'))
b = int(input('digite um numero :'))

qtd = 0
soma = 0

for x in range(a, b+1):
    
    if x%3 == 0:
        qtd += 1
        soma += x

    elif x%5 == 0:
        qtd += 1
        soma += x

    elif x%7 == 0:
        qtd +=1
        soma += x

else:
    print(f'A quantidade total de números é: {qtd} e a soma deles é: {soma}')
