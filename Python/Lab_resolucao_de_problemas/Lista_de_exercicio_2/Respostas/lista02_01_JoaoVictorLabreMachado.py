# Nome: João victor Labre Machado
# Data de criação: 01/12/2024
# O objetivo desse programa é coletar um valor de temperatura em Celsius e transformar em Farenheit, além disso ele irá calcular a média em cada uma das temperaturas

print('O objetivo desse programa é coletar um valor de temperatura em \'Celsius\' e transformar em Farenheit, além disso ele irá calcular a média em cada uma das temperaturas!','\n')

celsius = []
farenheit = []
qtd = 3
for q in range(qtd):
    valor_temp = float(input('Digite o valor da temperatura: '))
    celsius.append(valor_temp)
    farenheit.append((valor_temp*(9/5)) + 32)
media_c = 0
media_f = 0
for x in range(qtd):
    media_c += celsius[x]
    media_f += farenheit[x]
media_c = media_c/qtd
media_f = media_f/qtd
i = True
acima_m_f = []
while i==True:
    for a in range(len(farenheit)):
        if farenheit[a]>media_f:
            acima_m_f.append(farenheit[a])
    i = False
print(f'Os valores em Farenheit que ficaram acima da média foram: {acima_m_f[0:]}')
print(farenheit)
print(f'A quantidade média de temperatura em Celsius é {media_c:.2f}!')