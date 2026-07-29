# Verificador de qual é o segundo maior

num = float(input('Digite qualquer valor:'))

a = num
b = num
p = 1

for x in range(2,11):
    num = float(input('Digite qualquer valor:'))

    if num > a:
        b = a
        a = num
        p = x - 1
        #print(f'Teremos então na 2ª posição: P{x}',' - ',b)

    elif num < a:
        

print(f'Teremos então na 2ª posição: P{p}',' - ',b)

            
