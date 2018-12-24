package models;

public class Gamelobby {
    private int maxPlayers;
    private int currPlayers;
    private String title;

    public Gamelobby() {
        this.maxPlayers = 10;
        this.currPlayers = 0;
        this.title = new String("");
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public void setMaxPlayers(int playercount) {
        this.maxPlayers = playercount;
    }

    public void setCurrentPlayers(int playercount) {
        this.currPlayers = playercount;
    }

    public String getTitle() {
        return this.title;
    }

    public int getMaxPlayers() {
        return this.maxPlayers;
    }

    public int getCurrentPlayers() {
        return this.currPlayers;
    }
}
