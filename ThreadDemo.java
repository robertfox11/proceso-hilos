// Press Shift twice to open the Search Everywhere dialog and type `show whitespaces`,
// then press Enter. You can now see whitespace characters in your code.
//class NewThread implements Runnable {
class NewThread extends Thread {
    Thread t;
    NewThread() {
// Crea un nuevo hilo
        t = new Thread(this,"Hilo Hijo");
        System.out.println("Hilo Hijo: " + t);
        t.start();
    }
    // este es el punto de entrada del hilo
    public void run() {
        try {
            for (int i=5;i>0;i--) {
                System.out.println("Hilo hijo: " + i);
                Thread.sleep(500);
            }
        } catch (InterruptedException e){
            System.out.println("Interrupcion del hilo hijo");
        }
        System.out.println("Sale de hilo hijo.");
    }
}
public class ThreadDemo {
    public static void main(String[] args) {
        NewThread hilo;
        hilo = new NewThread(); // crea un nuevo hilo
        try {
            for (int i=5;i>0;i--) {
                System.out.println("Hilo principal: "+i);
                Thread.sleep(1000);
            }
        } catch (InterruptedException e) {
            System.out.println("Interrupcion del hilo principal");
        }System.out.println("Sale de hilo principal.");

    }
}
