import java.util.Scanner;

public class ConversaoDeTempo { // conversor de segundos para hora, minutos e segundos
    public static void main(String[] args){ 
        int segundos;
        Scanner teclado = new Scanner(System.in);
        System.out.printf("Por favor, digite uma quantidade de segundo(s): ");
        segundos = teclado.nextInt();

        int horas = (segundos / 3600);
        segundos = (horas != 0) ? (segundos%3600) : segundos;
        int minutos = (segundos / 60);
        segundos = (minutos != 0) ? (segundos % 60) : segundos;

        System.out.printf("Nós teremos então: %d horas(s), %d minutos(s) e %d segundo(s)!\n", horas, minutos, segundos);

        teclado.close();
    }

}
