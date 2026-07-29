#verificador de palidromo

num = int(input('Digite um número:'))

a = num%10
b = num%100//10
c = num%1000//100
d = num%10000//1000
e = num//10000

# print(f'{a, b, c, d, e}!') Verificar os números

if a==e and b==d:
    print(f'O número {num} é um palídromo!')

else:
    print('Este número não é um palídromo!')

    
    
      
