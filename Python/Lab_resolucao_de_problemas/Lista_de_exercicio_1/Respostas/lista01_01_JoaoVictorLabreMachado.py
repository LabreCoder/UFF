# Nome: João victor Labre Machado
# Data de criação: 26/10/2024
# Média Salarial - o objetivo desse programa é coletar os seguintes dados: quantidade de trabalhadores, idade, genero, salário de cada um dos trabalhadores e realizar a média salarial entres as classes e verificar qual o maior slárioa abaixo dos 30 anos!

qtd_trabalhadores = int(input('Olá, estamos realizando uma pesquisa de média salarial. Quantos trabalhadores irão participar da pesquisa?  '))

qtd_m = 0
qtd_f = 0
media_m = 0
media_f = 0
salario_base = 0

while qtd_trabalhadores!= 0:
    idade = int(input('Caro usuário, digite sua idade:  '))                     # idade do usuário
    print('')
    genero = str(input('Agora, digite seu genero (M) Masculino ou (F) Feminino: ')) # genero do usuário
    print('')
    salario = float(input('Por último, digite seu salário:  '))                 # salário do usuário
    print('')

    if genero == 'M' or genero == 'm':                                          # Verificador para os Masculinos
        qtd_m += 1                                                              # Irá somar a quantidade de homens
        media_m += salario                                                      # Irá somando os salários dos homens
        #print(media_m, salario)                                                # Caso queria ir acompanhando a soma dos salários

    elif genero == 'F' or genero == 'f':                                        # Verificador para os Femininos
        qtd_f += 1                                                              # Irá somar a quantidade de mulheres
        media_f += salario                                                      # Irá somando os salários dos mulheres
        #print(media_f, salario)                                                # Caso queria ir acompanhando a soma dos salários

    else:
        print('O usuário n digitou a informação requerida')                     # Caso a informção referente ao genero esteja incoerente
        qtd_trabalhadores += 1                                                  # Retorna para o mesmo trabalhador

    if idade < 30:                                                              # Verifica quem é menor de 30 anos
        if salario > salario_base:                                              # Verifica qual salário é maior
            salario_base = salario
            idade_ = idade                                                      # Verifica a idade de quem tem o maior salário

    qtd_trabalhadores -= 1

else:
    if qtd_m > 1: 
        media_m = (media_m/qtd_m)                                               # Realiza o cálculo da édia de salário entre os homens
    else:
        media_m = media_m
        
    if qtd_f > 1:
        media_f = (media_f/qtd_f)                                               # Realiza o cálculo da édia de salário entre as mulheres
    else:
        meida_f = media_f
    
    print('A média salarial dos homens é: R$',media_m,',00!')
    print('A média salarial das mulheres é: R$',media_f,',00!')
    print('O maior salário abaixo dos 3o anos é',salario_base,', com',idade_,'anos!')

