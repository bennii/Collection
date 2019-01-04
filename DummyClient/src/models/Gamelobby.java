package models;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.SimpleIntegerProperty;

enum GameType {
    DEATHMATCH, TEAMDEATHMATCH, SEARCH_AND_DESTROY;
}

/*
 * Data class for TableView.
 */
public class Gamelobby {
    private final SimpleStringProperty map;
    private final SimpleStringProperty title;
    private final SimpleStringProperty players;
    private final SimpleIntegerProperty maxPlayers;
    private final SimpleIntegerProperty currPlayers;

    public Gamelobby() {
        this.map = new SimpleStringProperty("undefined");
        this.title = new SimpleStringProperty("undefined");
        this.maxPlayers = new SimpleIntegerProperty(10);
        this.currPlayers = new SimpleIntegerProperty(0);

        this.players = new SimpleStringProperty("" + this.getCurrentPlayers() + "/" + this.getMaxPlayers());
    }

    public void setMap(String map) {
        this.map.set(map);
    }

    public void setTitle(String title) {
        this.title.set(title);
    }

    public void setMaxPlayers(int playercount) {
        this.maxPlayers.set(playercount);

        this.players.set("" + this.getCurrentPlayers() + "/" + this.getMaxPlayers());
    }

    public void setCurrentPlayers(int playercount) {
        this.currPlayers.set(playercount);

        this.players.set("" + this.getCurrentPlayers() + "/" + this.getMaxPlayers());
    }

    public String getMap() {
        return this.map.get();
    }

    public String getTitle() {
        return this.title.get();
    }

    public String getPlayers() {
        return this.players.get();
    }

    public int getMaxPlayers() {
        return this.maxPlayers.get();
    }

    public int getCurrentPlayers() {
        return this.currPlayers.get();
    }

    @Override
    public String toString() {
        return "Lobby: " + this.title + " " + this.map + " " + this.currPlayers + "/" + this.maxPlayers;
    }
}
