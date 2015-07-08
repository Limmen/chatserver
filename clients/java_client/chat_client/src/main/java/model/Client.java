package model;

//
import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import view.Chat_GUI;


/**
 *
 * @author kim
 */


public class Client extends Thread
{    
    private String host;
    private int port;
    public Socket socket;
    private BufferedReader in;
    private DataOutputStream out;
    private Chat_GUI gui;
    public Client(String host, int port, Chat_GUI gui) throws Exception{

        this.host = host;
        this.port = port;
        this.gui = gui;
      
        this.socket = new Socket(host, port);
        this.in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
        this.out = new DataOutputStream(socket.getOutputStream());
    }
    @Override
    public void run(){
        try{
            while(!Thread.currentThread().isInterrupted()) {
                while(true){
                    String message = in.readLine();
                    if (message == null) {
                        System.exit(0);
                    }
                    gui.newMsg(message);
                }
            }
        }
        catch(Exception e)
            {
                System.out.println("Socket was closed");
                shutDown();
            }
    }
    
    public void sendMsg(String msg){
        try{
            out.write(msg.getBytes());
        }
        catch(Exception e){
            e.printStackTrace();
        }

    }
    public void shutDown(){
        try{
            in.close();
            out.close();
            socket.close();
            interrupt();
        }
        catch(Exception e){
            
        }

    }
}
