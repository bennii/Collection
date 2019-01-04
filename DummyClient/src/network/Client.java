package network;

import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.AsynchronousSocketChannel;
import java.util.concurrent.Future;

public class Client {
    private int port;
    private String address;
    private boolean connected;
    private InetSocketAddress inetaddr;
    private AsynchronousSocketChannel client;

    public Client(String address, int port) throws IllegalArgumentException {
        this.port = port;
        this.address = address;
        this.connected = false;

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
            ByteBuffer buffer = ByteBuffer.allocate(100);


            buffer.put((byte) 10);
            buffer.putChar((char) 1);
            buffer.position(0);

            this.client.write(buffer);
        } catch (Exception exc) {
            exc.printStackTrace();
        }
    }

    public boolean isConnected() {
        return this.connected;
    }

    public void close() {
        this.client.close();
    }

    public static void main(String[] args) {
        Client c = new Client("localhost", 22350);

        c.connect();
        c.sendRaw();
    }
}
