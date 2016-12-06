package fr.licinfo;

/**
 * Created by c16017548 on 06/12/16.
 */
public class MyRunnable implements Runnable {
    private String name;

    public MyRunnable(String name) {
        this.name = name;
    }

    public void run() {
        for (int i = 1; i <= 5; i++) {
            if(Thread.interrupted()) break;
            System.out.println(name+":"+i);
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                break;
            }
        }
    }
}
