import java.util.Random;

public class Q7Main {
    public static void main(String[] args) {
        QueueBuffer buffer = new QueueBuffer();
        Producer p = new Producer(buffer);
        Consumer c = new Consumer(buffer);
        Thread prod = new Thread(p, "producer_thread");
        Thread consm = new Thread(c, "consumer_thread");

        prod.start();
        consm.start();

        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            System.out.println("Error during sleep of main");
        } finally {
            System.exit(0);
        }
    }
}

class QueueBuffer {
    long data;
    boolean isFull;

    QueueBuffer() {
        isFull = false;
    }

    synchronized long get() {
        while (!isFull) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println(e + "\t Buffer.GET()");
            }
        }

        notify();
        isFull = false;
        return data;
    }

    synchronized void put(long n) {
        while (isFull) {
            try {
                wait();
            } catch (InterruptedException e) {
                System.out.println(e + "\t Buffer.PUT()");
            }
        }

        this.data = n;
        isFull = true;
        notify();
    }
}

class Producer implements Runnable {
    QueueBuffer buf;

    Producer(QueueBuffer b) {
        buf = b;
    }

    @Override
    public void run() {
        Random rand = new Random(System.currentTimeMillis());
        while (true) {
            try {
                Thread.sleep(100);
            } catch (Exception e) {
                System.out.println("producer error");
            }
            
            long l = rand.nextLong();
            System.out.println("Produced:  " + l);
            buf.put(l);
        }
    }
}

class Consumer implements Runnable {
    QueueBuffer buf;

    Consumer(QueueBuffer b) {
        buf = b;
    }

    @Override
    public void run() {
        while (true) {
            try {
                Thread.sleep(100);
            } catch (Exception e) {
                System.out.println("consumer error");
            }

            long l = buf.get();
            System.out.println("Recieved:  " + l);
        }
    }
}
