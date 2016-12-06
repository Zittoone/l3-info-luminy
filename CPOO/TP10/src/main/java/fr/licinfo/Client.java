package fr.licinfo;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

/**
 * Created by c16017548 on 06/12/16.
 */
public class Client implements Runnable {

    private Socket socket;

    public Client(Socket socket) {
        this.socket = socket;
    }

    public void run() {
        BufferedReader reader = null;
        try {
            reader = new BufferedReader(
                    new InputStreamReader(
                            socket.getInputStream()));


            PrintWriter writer = new PrintWriter(socket.getOutputStream(), true);

            for (; ; ) {
                String line = reader.readLine();
                if (line == null) break;
                writer.println("[" + line + "]");
            }

            socket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Socket getSocket() {
        return socket;
    }
}
