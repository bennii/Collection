/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dummyclient;

import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.geometry.Insets;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.scene.control.Button;
import javafx.scene.control.TableView;
import javafx.scene.control.TableColumn;
import javafx.application.Application;

import network.Client;

/**
 *
 * @author Benjamin
 */
public class App extends Application {
    private Stage window;

    private Scene lobbieScene;
    private Scene detailsScene;

    private Client client;

    private Button joinButton;
    private Button detailsButton;
    private Button lobbieExitButton;
    private Button detailsExitButton;

    private TableView lobbies;
    private TableColumn lobbieTitleColumn;
    private TableColumn lobbiePlayersColumn;

    @Override
    public void init() {
        this.lobbies = new TableView<>();
        this.lobbies.setEditable(false);
        this.lobbieTitleColumn = new TableColumn<>("Title");
        this.lobbiePlayersColumn = new TableColumn<>("Players");

        this.lobbies.getColumns().addAll(this.lobbieTitleColumn, this.lobbiePlayersColumn);

        this.joinButton = new Button("Join");
        this.detailsButton = new Button("Details");
        this.lobbieExitButton = new Button("Exit");
        this.detailsExitButton = new Button("Exit");

        this.lobbieExitButton.setOnAction(event -> this.window.close());
        this.detailsExitButton.setOnAction(event -> this.window.close());
        this.joinButton.setOnAction(event -> System.out.println("Selecting a lobby"));
        this.detailsButton.setOnAction(event -> this.window.setScene(this.detailsScene));

        try {
            this.client = new Client("localhost", 22350);
            this.client.connect();
            this.client.sendRaw();
        } catch (Exception exc) {
        }
    }

    @Override
    public void start(Stage primaryStage) {
        HBox buttonPanel = new HBox(10);
        VBox lobbieLayout = new VBox(10);
        VBox detailsLayout = new VBox(10);

        this.lobbieScene = new Scene(lobbieLayout, 1200, 600);
        this.detailsScene = new Scene(detailsLayout, 1200, 600);

        buttonPanel.setPadding(new Insets(12, 12, 12, 12));
        buttonPanel.getChildren().add(this.joinButton);
        buttonPanel.getChildren().add(this.detailsButton);
        buttonPanel.getChildren().add(this.lobbieExitButton);

        lobbieLayout.getChildren().add(this.lobbies);
        lobbieLayout.getChildren().add(buttonPanel);

        detailsLayout.getChildren().add(this.detailsExitButton);

        this.window = primaryStage;
        this.window.setScene(this.lobbieScene);
        this.window.setTitle("Gamelobby Test Client");
        this.window.show();
    }

    /**
     * @param args The command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
}
