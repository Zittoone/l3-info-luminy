package fr.licinfo;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by c16017548 on 06/12/16.
 */
public class Server {
    private ServerSocket serverSocket;
    private List<Client> clients;

    public Server(int port) throws IOException {
        serverSocket = new ServerSocket(8088);
        clients = new ArrayList<Client>();
    }

    public void run(){
        boolean loop = true;
        try {

            while (loop) {
                new Thread(new Client(serverSocket.accept())).start();
            }
            serverSocket.close();

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void subscribeToBroadcast(Client client){
        clients.add(client);
    }

    public void unsubscribeToBroadcast(Client client){
        clients.remove(client);
    }

    public void broadcastMessage(String message){

        for (Client c : clients){
            sendMessage(c, message);
        }
    }

    public void sendMessage(Client client, String message) {
        Socket socket = client.getSocket();

        PrintWriter writer = null;
        try {
            writer = new PrintWriter(socket.getOutputStream(), true);
        } catch (IOException e) {
            e.printStackTrace();
            return;
        }
        writer.println(message);
    }
}
