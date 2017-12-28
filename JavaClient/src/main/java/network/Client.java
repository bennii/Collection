package network;

import java.lang.Exception;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.channels.SocketChannel;

public class Client {
    private SocketChannel client;

    public Client() {
        try {
            client = SocketChannel.open();
        }
        catch (Exception exc) {
            exc.printStackTrace();
        }
    }

    public boolean connect(String _ip, int _port) {
        boolean connected = false;

        try {
            connected = client.connect(new InetSocketAddress(_ip, _port));
        } 
        catch (Exception exc) {
            exc.printStackTrace();
        }
        finally {
            return connected;
        }
    }

    public void close() {
        try {
            client.close();
        } 
        catch (IOException exc) {
            exc.printStackTrace();
        }
    }
}
