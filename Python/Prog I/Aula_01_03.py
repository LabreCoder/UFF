import math

larg = float(input('Por favor, informe a largura:'))
comp = float(input('Por favor, informe a comprimento:'))
alt = float(input('Por favor, informe a altura:'))

area = larg*alt*2 + comp*alt*2 + larg*comp
litros = area/3
latas = math.ceil(litros/18)
Valor_latas = latas*215
horas = area/8
Valor_horas = horas*60
rolo = math.ceil(horas*2)
Valor_rolo = rolo*12

print(f'O total de horas de serviço é {horas}h, com um valor de mão de obra de R${Valor_horas:.2f} + R${(Valor_rolo+Valor_latas):.2f} de material!')
