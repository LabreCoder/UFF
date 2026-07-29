a = float(input('Digite um número:'))
b = float(input('Digite outro número:'))
c = float(input('Digite outro número:'))

if a<b:
    if c<a:
        maior = b
        meio = a
        menor = c
    if c>a and c<b:
        maior = b
        meio = c
        menor = a
    if c>b:
        maior = c
        meio = b
        menor = a
if a>b:
    if c<b:
        maior = a
        meio = b
        menor = c
    if c>b and c<a:
        maior = a
        meio = c
        menor = b
    if c>a:
        maior = c
        meio = a
        menor = b

v1 = menor/maior
v6 = maior/menor

if menor/meio<meio/maior:
    v2 = menor/meio
    v3 = meio/maior
    v4 = maior/meio
    v5 = meio/menor
else:
    v2 = meio/maior
    v3 = menor/meio
    v4 = meio/menor
    v5 = maior/meio

print(f'Os valores ficaram {v1, v2, v3, v4, v5, v6}!')
