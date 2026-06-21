import java.util.Random;

abstract class Animal {
    public abstract void fala();
}

class Homem extends Animal {
    public void fala() {
        System.out.println("Oi");
    }
}

class Cao extends Animal {
    public void fala() {
        System.out.println("Au au");
    }
}

class Gato extends Animal {
    public void fala() {
        System.out.println("Miau");
    }
}

public class AnimalFala {
    public static void main(String[] args) {
        Animal[] vetor = new Animal[10];
        Random rand = new Random();

        // Preenche o vetor aleatoriamente
        for (int i = 0; i < vetor.length; i++) {
            int sorteio = rand.nextInt(3); // 0, 1 ou 2
            if (sorteio == 0) {
                vetor[i] = new Homem();
            } else if (sorteio == 1) {
                vetor[i] = new Cao();
            } else {
                vetor[i] = new Gato();
            }
        }

        // Faz todos os animais falarem
        for (Animal animal : vetor) {
            animal.fala();
        }
    }
}