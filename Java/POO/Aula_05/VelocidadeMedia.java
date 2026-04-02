import java.util.Scanner;

public class VelocidadeMedia { // calcular a velocidade média e consumo de combustível
    public static void main(String[] args){ 
        Scanner teclado = new Scanner(System.in);
        int distancia_percorrida, tempo_gasto, gasolina_consumida;
        float velocidade_media, consumo_combustivel;

        System.out.printf("Digite a distância percorrida (em KM): ");
        distancia_percorrida = teclado.nextInt();
        System.out.printf("Digite o tempo gasto (em Horas): ");
        tempo_gasto = teclado.nextInt();
        System.out.printf("Digite a quantidade de gasolina consumida (em Litros): ");
        gasolina_consumida = teclado.nextInt();


        velocidade_media = (float) (distancia_percorrida / tempo_gasto);
        consumo_combustivel = (float) (distancia_percorrida / gasolina_consumida);

        System.out.printf("A velocidade média foi de: %.2f (KM/h) e o consumo de combustível foi de: %.2f (KM/L).\n", velocidade_media, consumo_combustivel);

        teclado.close();
    }

}
