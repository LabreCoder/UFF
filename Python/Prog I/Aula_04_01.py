ano = int(input('Por favor, digite o ano desejado:'))

if ano%400==0 or (ano%4==0 and ano%100 !=0):
          
        print('O ano é bissexto')
else:
        print('O ano não é bissexto')
