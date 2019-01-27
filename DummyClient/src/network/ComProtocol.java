package network;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

public class ComProtocol {
    private int version;
    private int headerSize;
    private int maxCapacity;
    private ByteOrder bo;

    public ComProtocol(int version) {
        this.version = version;

        switch (version) {
        case 1:
            this.headerSize = 4;
            this.maxCapacity = 8192;
            this.bo = ByteOrder.BIG_ENDIAN;
            break;

        default:
            this.headerSize = 4;
            this.maxCapacity = 2048;
            this.bo = ByteOrder.BIG_ENDIAN;
            break;
        }
    }

    /* Create a custom Exception */
    public ByteBuffer login(String name, String password) throws IllegalArgumentException {
        int requiredCapacity = name.length() + password.length() + this.headerSize;

        if (requiredCapacity > this.maxCapacity)
            throw new IllegalArgumentException("Packet size bigger than max capacity");

        ByteBuffer packet = ByteBuffer.allocate(requiredCapacity * 2);

        packet.order(this.bo);
        packet.putShort((short)1002);
        packet.putShort((short)(requiredCapacity * 2));
        
        packet.putShort((short)name.length());
        for(int i = 0; i < name.length(); i++) {
            packet.putChar(name.charAt(i));
        }

        packet.putShort((short)password.length());
        for(int i = 0; i < password.length(); i++) {
            packet.putChar(password.charAt(i));
        }

        packet.position(0);
        
        return packet;
    }

    public int version() {
        return this.version;
    }
}
