# Nome: João Victor Labre Machado
# Data de criação: 16/11/2024
# Esse programa irá coletar as variáveis r (juros), pmt(valores das parcelas) e n (número das parcelas) e realizará o cálculo da fórmula apresentada no exercício

print('Esse programa irá coletar as variáveis r (juros), pmt(valores das parcelas) e n (número das parcelas) e realizará o cálculo da fórmula apresentada no exercício!')
print('')

# Valor dos juros
r = float(input('Digite o valor dos juros em porcentagem: '))

# Valor das Parcelas
pmt = float(input('Digite o valor das parcelas: '))

# Quantidade das parcelas
n = int(input('Digite o número das parcelas: '))
r = r/100
i=1
somatorio = 0
while i!=n:
    somatorio += (pmt/((1+r)**i))
    print('R$',somatorio,'para',n,'parcela(s)!')
    i+=1