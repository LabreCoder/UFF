# Nome: João victor Labre Machado
# Data de criação: 26/10/2024
# Par ou Ímpar - o objetivo desse programa é coletar os seguintes dados: numero, para verificar quais são pares ou ímpares e calcular a média das classes!


# Uma pequena observção sobre o que deve ser feito
print('Olá seja bem vindo para o nosso Par ou Ímpar!!')
print('Para jogar é bem simlpes, basta que você digite um número e nós faremos o resto!')
print('')
print('Quando quiser para, é só digitar 0 (zero) e dar Enter!!')
print('')

numero = int(input('Por favor, digite um número: '))                                            # Variável requerida
        
qtd_par = 0                                                                                     # Valor inicial para a quantidade de números pares
qtd_impar = 0                                                                                   # Valor inicial para a quantidade de números ímpares
media_par = 0                                                                                   # Valor inicial para a média de números pares

while numero != 0:
    if numero%2 == 0:
        qtd_par += 1                                                                            # adiciona a quantidade de pares
        media_par += numero                                                                     # soma os pares
        print('')
        print('Este número é par:',numero,', totalizando',qtd_par,'de números pares!')
        print('')

    else:
        qtd_impar +=1                                                                           # adiciona a quantidade de ímpares
        print('')
        print('Este número é ímpar:',numero,', totalizando',qtd_impar,'de números ímpares!')
        print('')
        
    numero = int(input('Por favor, digite um número: '))

else:
    media_par = (media_par/qtd_par)                                                             # realiza a média aritimética dos números pares
    print('Temos então uma média de',media_par,', de um total de',qtd_par,'números pares!')     #  Mostra o resultado da média e quantidade total dos números pares