package fr.licinfo;

import java.io.IOException;
import java.net.ServerSocket;

/**
 * Hello world!
 */
public class App {
    public static void main(String[] args) {
        ServerSocket serverSocket = null;
        boolean loop = true;
        try {

            serverSocket = new ServerSocket(8088);

            while (loop) {
                new Thread(new Client(serverSocket.accept())).start();
            }

            serverSocket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
