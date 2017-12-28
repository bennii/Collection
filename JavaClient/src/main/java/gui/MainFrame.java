package gui;

import gui.ButtonPanel;
import gui.GameBrowser;
import network.Client;
import javax.swing.JFrame;

public class MainFrame extends JFrame {
    private Client client = new Client();
    private GameBrowser gameBrowser = new GameBrowser();
    private ButtonPanel buttonPanel = new ButtonPanel();

    public MainFrame(String _title) {
        super(_title);

        add(gameBrowser, java.awt.BorderLayout.CENTER);
        add(buttonPanel, java.awt.BorderLayout.PAGE_END);
        
        pack();
        setSize(1200, 675);
        setVisible(true);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);

        if (!client.connect("127.0.0.1", 22350))
            System.out.println("Connection to the server could not be established");

        buttonPanel.setClientReference(client);
        buttonPanel.setTableReference(gameBrowser.getTableReference());
    }
}
