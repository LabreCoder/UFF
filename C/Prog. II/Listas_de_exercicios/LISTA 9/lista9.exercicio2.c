typedef struct data {
int dia;
int mes;
char nomeMes[12];
} Data;

main(){
    Data aniversarios[3] = 
    { {5,1,"JANEIRO"},
    {4,2,"FEVEREIRO"},
    {10,3,"MAIO"} };
    
    int a;
    Data *p_dt;
    p_dt=&aniversarios[2];
    printf("Nome do mês %d é: %s.", p_dt->mes, p_dt->nomeMes);
    strcpy(p_dt->nomeMes, "MARÇO");
    printf("\nNúmero de letras : %d=", strlen(p_dt->nomeMes));
    Data p_dt2 = (Data *)malloc(sizeof(Data));
    p_dt2 = &aniversarios[0];
    
    
    printf("Respostas: \na) O programa não irá funcionar mais na parte do p_dt2, pois ele não é um ponteiro e estamos tentando fazer um malloc nele. Além disso, nós sobrepomos o valor do malloc e não liberamos ele.\nb) O print deveria ser '5'!");
    
