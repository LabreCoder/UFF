#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");
    int capacidade[21][2]; // [idade, opinião]
    int idade, opiniao;
    char terminar = 'n';
    int i = 0;

    while ((i < 20) && (terminar != 's' && terminar != 'S')) {
        printf("\nDigite a sua idade: ");
        scanf("%d", &idade);
        printf("Digite o que achou do filme - (1)Ótimo (2)Bom (3)Regular (4)Ruim (5)Péssimo: ");
        scanf("%d", &opiniao);

        capacidade[i][0] = idade;
        capacidade[i][1] = opiniao;
        i++;

        if (i<20){
        // Limpa o buffer antes de ler o char
        while ((getchar()) != '\n'); // descarta o ENTER
        printf("\nDeseja encerrar a pesquisa?\n(s) Sim (n) Não -> ");
        scanf("%c", &terminar);
        }
    }

    // Contadores
    int qtd_otimo = 0, qtd_bom = 0, qtd_regular = 0, qtd_ruim = 0, qtd_pessimo = 0;
    int maior_otimo = 0, maior_ruim = 0, maior_pessimo = 0;
    float soma_idade_ruim = 0.0;
    int cont_ruim = 0;

    for (int j = 0; j < i; j++) {
        idade = capacidade[j][0];
        opiniao = capacidade[j][1];

        switch (opiniao) {
            case 1:
                qtd_otimo++;
                if (idade > maior_otimo) maior_otimo = idade;
                break;
            case 2:
                qtd_bom++;
                break;
            case 3:
                qtd_regular++;
                break;
            case 4:
                qtd_ruim++;
                soma_idade_ruim += idade;
                cont_ruim++;
                if (idade > maior_ruim) maior_ruim = idade;
                break;
            case 5:
                qtd_pessimo++;
                if (idade > maior_pessimo) maior_pessimo = idade;
                break;
        }
    }

    // Cálculos finais
    float media_idade_ruim = (cont_ruim > 0) ? soma_idade_ruim / cont_ruim : 0.0;
    float diferenca_percentual = abs(qtd_bom - qtd_regular) * 100.0 / i;
    float porcentagem_pessimo = qtd_pessimo * 100.0 / i;
    int diferenca_idade = abs(maior_otimo - maior_ruim);

    // Impressões finais
    printf("\nA quantidade de respostas 'Otimo' e: %d", qtd_otimo);
    printf("\nA diferença percentual entre respostas 'Bom' e 'Regular' e: %.2f%%", diferenca_percentual);
    printf("\nA media de idade das pessoas que responderam 'Ruim' e: %.2f", media_idade_ruim);
    printf("\nA porcentagem de respostas 'Pessimo' e: %.2f%% e a maior idade que utilizou esta opcao e: %d", porcentagem_pessimo, maior_pessimo);
    printf("\nA diferença de idade entre quem respondeu 'Otimo' e 'Ruim' e: %d\n", diferenca_idade);

    return 0;
}
