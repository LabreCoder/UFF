# Nome: João Victor Labre Machado
# Data de criação: 26/10/2024
# Valor de mercado: o objetivo do programa é recolher a descrição, o preço dos produtos comprados por uma empresa, e ao final dizer qual é o mais caro e sua descrição!

print('O objetivo do programa é recolher a descrição, o preço dos produtos comprados por uma empresa, e ao final dizer qual é o mais caro e sua descrição!')
print('')
total_gasto = 0
produto_mais_caro = ''
preco_mais_caro = 0

i = 0
while i != 10:
    
    print('\nProduto',i + 1,':')
    descricao = str(input('Descrição do produto: '))
    preco_unitario = float(input('Preço unitário: '))
    
    # Calcula o total gasto com o produto
    total_gasto_produto = preco_unitario
    total_gasto += total_gasto_produto
    
    # Verifica se este produto é o mais caro
    if preco_unitario > preco_mais_caro:
        preco_mais_caro = preco_unitario
        produto_mais_caro = descricao
    i += 1
# Resultado final
print('Total gasto pela empresa: R$',total_gasto,'.')
print('Produto mais caro:',produto_mais_caro,' (Preço unitário: R$',preco_mais_caro,')')
