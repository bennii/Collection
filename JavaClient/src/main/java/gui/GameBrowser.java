package gui;

import java.awt.Dimension;
import javax.swing.JPanel;
import javax.swing.JTable;
import javax.swing.JScrollPane;

public class GameBrowser extends JPanel {
    private JTable gameTable = new JTable(new String [][] {{"1", "3/4", "de_dust2", "dust2 only"}}, new String[] {"ID", "Players", "Map", "Title"});

    public GameBrowser() {
        super();

        gameTable.setFillsViewportHeight(true);
        gameTable.setPreferredScrollableViewportSize(new Dimension(1000, 575));

        add(new JScrollPane(gameTable));
    }

    public JTable getTableReference() {
        return gameTable;
    }
}
