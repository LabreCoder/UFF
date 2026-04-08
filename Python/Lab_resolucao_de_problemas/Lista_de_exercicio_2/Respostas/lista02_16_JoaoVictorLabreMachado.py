# Nome: João Victor Labre Machado
# Data of Criation: 23/12/2024
# O objetivo do programa é converter de decimal para hexadecimal

print('O objetivo do programa é converter de decimal para hexadecimal!!')
num = int(input('Digite um valor dentro da base 10: '))

def dec_to_hex(num):
    list = []
    num_ = num
    # Caso o valor seja o próprio 16, o resultado será um
    if num == 16:
        print('O número',num,'na base hexadecimal é 10!')
    # Caso não seja, ele irá realizar o cálculo para realizar a conversão para a base hexadecimal
    else:
        base = 1
        div = 0
        # Irá buscar quantos divisões o número fez até chegar em 0
        while base!=0:
            num = num//16
            div += 1
            if num == 0:
                base=0
        num = num_

        # Irá fazer um cálculo do último resto até chegar ao primeiro
        while div!=0:
            num = num_

            for x in range(div,0,-1):
                resto = num%16
                num = num//16  

                if resto == 10:
                    resto = 'A'
                elif resto == 11:
                    resto = 'B'
                elif resto == 12:
                    resto = 'C'
                elif resto == 13:
                    resto = 'D'
                elif resto == 14:
                    resto = 'E'
                elif resto == 15:
                    resto = 'F'
            #print(resto,end='')
            list.append(resto)
            div -=1
    return list

list = dec_to_hex(num)
a = ''
for i in list:
    i = str(i)
    a+=i

print(f'O número {num} na base hexadecimal é: {a}!')