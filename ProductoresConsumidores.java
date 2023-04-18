
class Q {
    int n;
    boolean valueSet=false;
    synchronized int get () {
        if (!valueSet)
            try {
                wait();
            } catch (InterruptedException e ) {
                System.out.println("captura la excepcion");
            }
        System.out.println("Consume: "+n);
        valueSet=false;
        notify();
        return n;
    }
    synchronized void put (int n) {
        if (valueSet)
            try {
                wait();
            } catch (InterruptedException e ) {
                System.out.println("captura la excepcion");
            }
        this.n=n;
        valueSet=true;
        System.out.println("Produce: "+n);
        notify();}
}
class Producer implements Runnable {
    Q q;
    Producer(Q q) {
        this.q=q;
        new Thread(this,"Productor").start();
    }
    public void run() {
        int i;
        for (i = 0; i < 10; i++) q.put(i);
    }
}
class Consumer implements Runnable {
    Q q;
    Consumer(Q q) {
        this.q=q;
        new Thread(this,"Consumidor").start();
    }
    public void run() {
        int i;
        for (i = 0; i < 10; i++) q.get();
    }
}
public class PCFijo {
    public static void main(String args[]) {
        Q q = new Q();
        new Producer(q);
        new Consumer(q);
    }
}
