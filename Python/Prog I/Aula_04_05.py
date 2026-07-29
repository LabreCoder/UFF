
dia = int(input('Por favor, digite o dia em que se deseja saber o mês:'))

if dia > 1 and dia <= 31 :
    print('O mês é Janeiro')
elif dia>31 and dia <=59:
    print('O mês é Fevereiro')
elif dia>59 and dia <=90:
    print('O mês é Março')
elif dia>90 and dia <=120:
    print('O mês é Abril')
elif dia>120 and dia <=151:
    print('O mês é Maio')
elif dia>151 and dia <=181:
    print('O mês é Junho')
elif dia>181 and dia <=212:
    print('O mês é Julho')
elif dia>212 and dia <=243:
    print('O mês é Agosto')
elif dia>243 and dia <=273:
    print('O mês é Setembro')
elif dia>273 and dia <=304:
    print('O mês é Outurbo')
elif dia>304 and dia <=334:
    print('O mês é Novembro')
elif dia>334 and dia <=365:
    print('O mês é Dezembro')
else:
    print()
