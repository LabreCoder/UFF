public class ExercicioSynchronized {

    public static void main(String[] args) {

        System.out.println("EXERCÍCIO:");
        System.out.println("Para que serve o modificador synchronized?");
        System.out.println("Em que situações ele deve ser usado?");
        System.out.println("Por que não usar em todos os métodos do programa?");

        System.out.println("\nRESPOSTA:");
        System.out.println(
            "O modificador synchronized é utilizado para controlar o acesso "
            + "de múltiplas threads a um recurso compartilhado. Ele garante "
            + "que apenas uma thread por vez execute um método ou bloco "
            + "sincronizado."
        );

        System.out.println(
            "\nEle deve ser usado quando várias threads acessam ou "
            + "modificam dados compartilhados, evitando problemas de "
            + "concorrência e inconsistência de dados."
        );

        System.out.println(
            "\nNão deve ser usado em todos os métodos porque reduz o "
            + "paralelismo da aplicação e pode impactar o desempenho, "
            + "fazendo as threads aguardarem umas pelas outras "
            + "desnecessariamente."
        );
    }
}