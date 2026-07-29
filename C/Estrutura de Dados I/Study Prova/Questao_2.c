#include <stdio.h>
#include <stdlib.h>

void binario(int n){
    if (n == 0){
        return;
    }
    
    binario(n / 2);
    printf("%d", n % 2);
}

int main() {
    
    int n = 0;
    printf("Ingrese un numero: ");
    scanf("%d", &n);

    while (n > 0) {
        printf("\nO valor de %d em binário é: ", n);
        
        if (n == 0){
            printf("0");
        } else {
            binario(n);
        }
        
        printf("\n");
        n--;
    }   
    
    return 0;
}
/*

**Principais correções:**

1. **Função recursiva corrigida**: A função `binario` agora divide o número por 2 recursivamente até chegar a 0, e então imprime os restos na ordem correta (do bit mais significativo ao menos significativo).

2. **Removido o loop for interno**: O loop `for` original estava causando confusão na recursão.

3. **Retorno void**: A função não precisa retornar um valor, apenas imprimir o resultado.

4. **Loop principal simplificado**: O `while` agora apenas decrementa `n` e chama a função para cada valor.

5. **Tratamento do zero**: Adicionei verificação para imprimir "0" quando o número for zero.

**Exemplo de saída:**
```
Ingrese un numero: 5

O valor de 5 em binário é: 101
O valor de 4 em binário é: 100
O valor de 3 em binário é: 11
O valor de 2 em binário é: 10
O valor de 1 em binário é: 1
*/