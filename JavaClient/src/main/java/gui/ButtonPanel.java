package gui;

import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JTable;
import javax.swing.JPanel;
import javax.swing.JButton;

import network.Client;

public class ButtonPanel extends JPanel implements ActionListener {
    private Client  client = null;
    private JTable  table = null;
    private JButton joinButton = new JButton("Join");
    private JButton closeButton = new JButton("Close");
    private JButton detailsButton = new JButton("Details");

    public ButtonPanel() {
        super(new FlowLayout());

        joinButton.addActionListener(this);
        closeButton.addActionListener(this);
        detailsButton.addActionListener(this);

        add(joinButton);
        add(closeButton);
        add(detailsButton);
    }

    public void setTableReference(JTable _table) {
        table = _table;
    }

    public void setClientReference(Client _client) {
        client = _client;
    }
    
    public void actionPerformed(ActionEvent event) {
        if (event.getSource() == joinButton) {
            if (table == null && client == null) return;
        }

        if (event.getSource() == closeButton) {
            System.exit(0); // Better to use a loop to find a JFrame and call its closing method for a clean exit?
        }

        if (event.getSource() == detailsButton) {
            if (table == null && client == null) return;

            System.out.println(table.getSelectedRow());
        }
    }
}
