import gui.MainFrame;

public class App {
    private static MainFrame mainFrame = new MainFrame("Java Client");

    public static void main(String[] args) {
        mainFrame.setSize(200, 300);
        mainFrame.setVisible(true);
    }
}
