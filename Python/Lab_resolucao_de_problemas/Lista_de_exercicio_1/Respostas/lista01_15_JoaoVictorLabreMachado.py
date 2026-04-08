# Nome: João Victor Labre Machado
# Data de criação: 04/11/2024
# Esse programa irá calcular o nome e altura de participantes de um concurso de beleza até ser digitado Maria!

print('Esse programa irá calcular o nome e altura de participantes de um concurso de beleza até ser digitado Maria!')
print('')

print('Para finalizar o programa, basta escrever MARIA!!')

maior = 0
seg_maior = 0 
name_maior = ''
name_seg = ''
name = ''
total = 0

# Irá executar o programa até ser digitado Maria
while name != 'MARIA':
        name = input('Digite o nome: ')
        alt = float(input('Digite a altura: '))
        
        # Faz as trocas de maior altura
        if alt > maior:
            seg_maior = maior
            name_seg = name_maior
            name_maior = name
            maior = alt
        
        # Irá manter o nome da segunda maior
        elif seg_maior > alt:
             name_seg = name_seg
        else:
            name_seg = name
            seg_maior = alt
        total += 1

print('O maior foi ',name_maior,' com ',maior,'m de altura!')
print('A segunda maior foi ',name_seg,' com ',seg_maior,'m de altura!')
print('Tivemos um total de ',total,' moças no concurso!')