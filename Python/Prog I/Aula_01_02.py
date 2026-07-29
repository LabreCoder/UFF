a = input('Por favor, digite o A da equação:')
b = input('Por favor, digite o B da equação:')
c = input('Por favor, digite o C da equação:')

delta = b**2 - 4*a*c
raiz1 = (-b + delta**0.5)/2*a
raiz2 = (-b - delta**0.5)/2*a

print(f'A raiz 1 é {raiz1:.2f} e a raiz 2 é {raiz2:.2f}')
