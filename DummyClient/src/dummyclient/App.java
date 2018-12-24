/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dummyclient;

import models.Gamelobby;
import network.Client;

import javafx.stage.Stage;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.TableView;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.TableColumn;
import javafx.application.Application;

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
    private Button lobbyExitButton;
    private Button detailsExitButton;

    private TableView lobbyView;
    private TableColumn lobbyTitleColumn;
    private TableColumn lobbyPlayersColumn;

    @Override
    public void init() {
        this.lobbyView = new TableView<>();
        this.lobbyView.setEditable(false);
        this.lobbyTitleColumn = new TableColumn<>("Title");
        this.lobbyPlayersColumn = new TableColumn<>("Players");

        this.lobbyView.getColumns().addAll(this.lobbyTitleColumn, this.lobbyPlayersColumn);
        this.lobbyView.setEditable(false);

        this.joinButton = new Button("Join");
        this.detailsButton = new Button("Details");
        this.lobbyExitButton = new Button("Exit");
        this.detailsExitButton = new Button("Exit");

        this.lobbyExitButton.setOnAction(event -> this.window.close());
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
        buttonPanel.getChildren().add(this.lobbyExitButton);

        lobbieLayout.getChildren().add(this.lobbyView);
        lobbieLayout.getChildren().add(buttonPanel);

        detailsLayout.getChildren().add(this.detailsExitButton);

        this.window = primaryStage;
        this.window.setScene(this.lobbieScene);
        this.window.setTitle("Gamelobby Test Client");
        this.window.show();
        this.window.setAlwaysOnTop(true);
    }

    /**
     * @param args The command line arguments
     */
    public static void main(String[] args) {
        launch(args);
    }
}
