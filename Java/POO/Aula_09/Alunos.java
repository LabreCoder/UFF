import java.util.Scanner;

public class Alunos{
    public static void main(String[] args) {
        Scanner teclado = new Scanner(System.in);

        int num_alunos = 0;
        float[] notas_alunos;
        float media = 0;

        while (true){ // while para ele se ele colocar um valor igual a 0, ele irá ter que colocar o valor novamente

            System.out.println("Digite a quantidade de alunos dentro da turma: ");
            num_alunos = teclado.nextInt();
            
            if (num_alunos <= 0){
                System.out.println("Por favor, coloque um valor maior que 0!!");
            }
            else { // Irá receber as notas para cada aluno e registrar dentro do Vetor
                notas_alunos = new float[num_alunos];
                for (int i = 0; i < notas_alunos.length; i++){
                    System.out.printf("Digite a nota para o aluno [%d]: ", i+1);
                    notas_alunos[i] = teclado.nextInt();
                    media = ((media + notas_alunos[i])); // Irá fazer o cálculo da média
                }
                System.out.printf("A média da turma é: %.2f\n", media/notas_alunos.length);
                
                int maiores_que_a_media = 0;
                for (int j = 0; j < notas_alunos.length; j++){ // Irá verificar as notas acima da média
                    if (notas_alunos[j] > media/notas_alunos.length){maiores_que_a_media++;}
                }
                System.out.printf("A quantidade de notas maiores que a média foi: %d\n",maiores_que_a_media);

                break;
            }
        }
        teclado.close();

    }
}