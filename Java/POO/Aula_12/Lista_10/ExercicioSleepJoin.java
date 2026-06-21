public class ExercicioSleepJoin {

    public static void main(String[] args) {

        System.out.println("EXERCÍCIO:");
        System.out.println(
            "Qual a diferença entre o método sleep() e o método join() "
            + "da classe Thread?"
        );

        System.out.println("\nRESPOSTA:");

        System.out.println(
            "O método sleep() faz a thread atual pausar sua execução "
            + "por um determinado período de tempo."
        );

        System.out.println(
            "\nExemplo: Thread.sleep(1000);"
        );

        System.out.println(
            "\nO método join() faz uma thread esperar que outra "
            + "thread termine sua execução antes de continuar."
        );

        System.out.println(
            "\nExemplo:"
        );

        System.out.println("thread1.start();");
        System.out.println("thread1.join();");

        System.out.println(
            "\nResumo:"
        );

        System.out.println(
            "sleep() -> pausa a thread atual por um tempo determinado."
        );

        System.out.println(
            "join() -> faz uma thread aguardar o término de outra thread."
        );
    }
}