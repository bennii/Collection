package network;

import java.net.InetSocketAddress;
import java.nio.channels.AsynchronousSocketChannel;
import java.util.concurrent.Future;

public class Client {
    private int port;
    private String address;
    private boolean connected;
    private ComProtocol comProtocol;
    private InetSocketAddress inetaddr;
    private AsynchronousSocketChannel client;

    public Client(String address, int port) throws IllegalArgumentException {
        this.port = port;
        this.address = address;
        this.connected = false;
        this.comProtocol = new ComProtocol(1);

        try {
            this.inetaddr = new InetSocketAddress(this.address, this.port);
        } catch (IllegalArgumentException exc) {
            throw new IllegalArgumentException("Port or address invalid");
        }

        try {
            this.client = AsynchronousSocketChannel.open();
        } catch (Exception exc) {
            throw new IllegalArgumentException("There was an error creating the client");
        }
    }

    public boolean connect() {
        try {
            Future result = this.client.connect(this.inetaddr);
            result.get();
        } catch (Exception exc) {
            this.connected = false;
            return false;
        }

        return true;
    }

    public void sendRaw() {
        try {
            this.client.write(comProtocol.login("Test", "Test"));
        } catch (Exception exc) {
            exc.printStackTrace();
        }
    }

    public boolean isConnected() {
        return this.connected;
    }

    public void close() {
        try {
            this.client.close();
        } catch (Exception exc) {
            exc.printStackTrace();
        }
    }

    public static void main(String[] args) {
        Client c = new Client("localhost", 22350);

        System.out.println("" + 0x0402); 
       
        c.connect();
        c.sendRaw();
    }
}
