#include <stdio.h>
#include <conio.h>

int conversao_binaria(int n, int *vetor_binario, int tamanho, int tamanho_fixo) // o "tamanho fixo" é usado somente na última chamada da função no vetor_binario
{
    vetor_binario[tamanho] = (n % 2); // as últimas posições do vetor receberão o resto dessa divisão
    n /= 2; // o "n" precisa ser dividido para continuar os próximos cálculos corretamente
    if(tamanho > 0) // esse "if" é usado em todas as funções recursivas exceto a última chamada quando o tamanho for igual a zero
    {
        tamanho--; // a função a ser chamada receberá um tamanho decrementado
        return conversao_binaria(n, vetor_binario, tamanho, tamanho_fixo); // chama a função recursivamente com tamanho decrementado
    }
    if(tamanho == 0) // apenas na última chamada será feito isso
    {
        int indice, binario;
        for(indice = 0; indice < tamanho_fixo; indice++)
        {
            if(indice == 0)
            {
                if(vetor_binario[indice] == 0)
                {
                    binario = 0;
                }
                else
                {
                    binario = 1;
                }
            }
            else
            {
                if(vetor_binario[indice] == 0)
                {
                    binario *= 10;
                }
                else
                {
                    binario = (binario * 10) + 1;
                }
            }
        }
        return binario;
    }
    return 0;
}

int main(void)
{
    int exemplos[3] = {5, 25, 123};
    int i;
    for(i = 0; i < 3; i++)
    {
        int n = exemplos[i];
        int indice, tamanho, tamanho_fixo, numero_binario;
        tamanho = 0; // zerando o tamanho do vetor
        for(indice = n; indice > 0; ) // usado na função recursiva
        {
            indice /= 2; // laço para especificar o tamanho do vetor
            tamanho++;
        }
        tamanho_fixo = tamanho;
        int vetor_binario[tamanho];
        tamanho -= 1; // decrementa o tamanho para ser usado nessa forma na função
        numero_binario = conversao_binaria(n, vetor_binario, tamanho, tamanho_fixo);
        // a função retornará um inteiro formatado como um "binário"
        printf("\nO numero %d em binario e': %d", n, numero_binario);
    }
    getch();
    return 0;
}
