# verificador de peso em outros planetas

peso = float(input('Por favor, digite seu peso:'))
planeta = int(input('Escolha o planeta desejado:'+ '\n'+'(1) Mercúrio'+'\n'+'(2) Vênus'+'\n'+'(3) Marte'+'\n'+'(4) Júpiter'+'\n'+'(5) Saturno'+'\n'+'(6) Urano'+'\n'))

match planeta:
    case 1: print(f'Você escolheu o planeta Mercúrio, onde seu peso é {peso*0.37} Kg!')
    case 2: print(f'Você escolheu o planeta Vênus, onde seu peso é {peso*0.88} Kg!')
    case 3: print(f'Você escolheu o planeta Marte, onde seu peso é {peso*0.38} Kg!')
    case 4: print(f'Você escolheu o planeta Júpiter, onde seu peso é {peso*2.64} Kg!')
    case 5: print(f'Você escolheu o planeta Saturno, onde seu peso é {peso*1.15} Kg!')
    case 6: print(f'Você escolheu o planeta Urano, onde seu peso é {peso*1.17} Kg!')
    case _: print(f'Infelizmente, você não escolheu nenhuma das opções, mas seu peso é {peso} Kg!')
