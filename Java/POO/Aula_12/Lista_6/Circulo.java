import java.util.Scanner;

public class Circulo {
    private int x;
    private int y;
    private double raio;

    public Circulo(int x, int y, double raio) {
        this.x = x;
        this.y = y;
        this.raio = raio;
    }

    // Getters e Setters
    public int getX() { return x; }
    public int getY() { return y; }
    public double getRaio() { return raio; }

    public void setX(int x) { this.x = x; }
    public void setY(int y) { this.y = y; }
    public void setRaio(double raio) { this.raio = raio; }

    // Mesmos métodos do Retangulo
    public void mover(int novoX, int novoY) {
        x = novoX;
        y = novoY;
    }

    public void desenhar() {
        System.out.printf("Circulo(%d, %d, %.2f)%n", x, y, raio);
    }

    public void redimensionar(float escala) {
        if (escala > 0) {
            raio = escala / 100 * raio;
        }
    }

    // Métodos extras que fazem sentido para um círculo
    public double area() {
        return Math.PI * raio * raio;
    }

    public double perimetro() {
        return 2 * Math.PI * raio;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Digite o valor de x: ");
        int x = scanner.nextInt();

        System.out.print("Digite o valor de y: ");
        int y = scanner.nextInt();

        System.out.print("Digite o raio: ");
        double raio = scanner.nextDouble();

        Circulo c = new Circulo(x, y, raio);
        c.desenhar();
        System.out.printf("Área: %.2f%n", c.area());
        System.out.printf("Perímetro: %.2f%n", c.perimetro());

        scanner.close();
    }
}