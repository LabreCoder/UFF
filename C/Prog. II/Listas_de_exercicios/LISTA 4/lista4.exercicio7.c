#include <stdio.h>
#include <string.h>
#include <locale.h>

void CamelCase(char *s);

int main() {
    setlocale(LC_ALL, "Portuguese");

    int n;
    printf("Qual é o tamanho máximo da string que você deseja escrever? R: ");
    scanf("%d", &n);
    getchar(); // Limpa o '\n' do buffer

    char s[n]; // Array de tamanho definido em tempo de execução

    printf("Digite a sua frase para transformarmos em CamelCase: ");
    fgets(s, n, stdin);

    // Remover '\n' final, se houver
    size_t len = strlen(s);
    if (len > 0 && s[len - 1] == '\n') {
        s[len - 1] = '\0';
        len--;
    }

    if (len >= n - 1) {
        printf("Você digitou mais caracteres do que o permitido (%d).\n", n - 1);
    }

    CamelCase(s);

    return 0;
}

void CamelCase(char *s){

    int i;
    s[0] = to_upper(s[0]);
    for (i=0; i<strlen(s); i++){
        if (s[i]==' '){
            toupper(s[i+1]);
        }
    }

}
