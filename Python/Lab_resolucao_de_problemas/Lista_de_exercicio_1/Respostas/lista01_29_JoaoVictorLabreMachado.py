# Nome: João Victor Labre Machado
# Data de criação: 17/11/2024
# Esse programa irá coletar duas variáveis A e B, e irá buscar o MDC delas

print('Esse programa irá coletar duas variáveis A e B, e irá buscar o MDC delas!')
print('')

A = int(input('Digite um valor: '))
B = int(input('Digite outro valor: '))
A_ = A
B_ = B
div_a = 0
div_b = 0
div_ab = 0
a = 2
b = 1
c = 1
while A!=1 and B!=1:
    if A%a == 0 and B%a == 0:
        div_ab += 1
        b *= a
    if A%a ==0:
        A/=a
        div_a+=1
    if B%a ==0:
        B/=a
        div_b+=1
    if A%a!=0 and B%a!=0:
        a+=1
print('O máximo divisor comum entre',A_,'e',B_,'é',b,'tendo um total de',div_ab,'divisores em comum!')