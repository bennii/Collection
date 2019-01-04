package dummyclient;

import models.Gamelobby;

import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.control.Button;
import javafx.scene.control.TableView;
import javafx.scene.control.TableColumn;
import javafx.geometry.Pos;
import javafx.geometry.Insets;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class App extends Application {
    private Stage window;

    private Scene lobbieScene;
    private Scene detailsScene;

    private double width;
    private double height;
    private double padding;
    private double spacing;

    private Button joinButton;
    private Button detailsButton;
    private Button lobbyExitButton;
    private Button detailsExitButton;

    private TableView lobbyView;
    private TableColumn mapColumn;
    private TableColumn titleColumn;
    private TableColumn playersColumn;

    private ObservableList<Gamelobby> lobbies;

    @Override
    public void init() {
        this.width = 1200d;
        this.height = 600d;
        this.padding = 8d;
        this.spacing = 12d;

        this.lobbies = FXCollections.observableArrayList();
        this.lobbies.add(new Gamelobby());
        this.lobbies.add(new Gamelobby());

        this.lobbyView = new TableView<>();
        this.lobbyView.setEditable(false);
        this.lobbyView.setItems(this.lobbies);

        this.titleColumn = new TableColumn<>("Title");
        this.titleColumn.setMinWidth(this.width / 2 - 50);
        this.titleColumn.setCellValueFactory(new PropertyValueFactory<Gamelobby, String>("title"));

        this.playersColumn = new TableColumn<>("Players");
        this.playersColumn.setMinWidth(125);
        this.playersColumn.setMaxWidth(125);
        this.playersColumn.setCellValueFactory(new PropertyValueFactory<Gamelobby, String>("players"));

        this.mapColumn = new TableColumn<>("Map");
        this.mapColumn.setMinWidth(this.width / 5);
        this.mapColumn.setCellValueFactory(new PropertyValueFactory<Gamelobby, String>("map"));

        this.lobbyView.getColumns().addAll(this.titleColumn, this.playersColumn, this.mapColumn);
        this.lobbyView.setEditable(false);
        this.lobbyView.setMinHeight(this.height - (this.height / 10));

        this.joinButton = new Button("Join");
        this.detailsButton = new Button("Details");
        this.lobbyExitButton = new Button("Exit");
        this.detailsExitButton = new Button("Exit");

        this.lobbyExitButton.setOnAction(event -> this.window.close());
        this.detailsExitButton.setOnAction(event -> this.window.close());
        this.joinButton.setOnAction(event -> { });
        this.detailsButton.setOnAction(event -> this.window.setScene(this.detailsScene));
    }

    @Override
    public void start(Stage primaryStage) {
        HBox buttonPanel = new HBox(this.spacing);
        VBox lobbieLayout = new VBox(this.spacing);
        VBox detailsLayout = new VBox(this.spacing);

        this.lobbieScene = new Scene(lobbieLayout, this.width, this.height);
        this.detailsScene = new Scene(detailsLayout, this.width, this.height);

        buttonPanel.setPadding(new Insets(this.padding, this.padding, this.padding, this.padding));
        buttonPanel.getChildren().add(this.joinButton);
        buttonPanel.getChildren().add(this.detailsButton);
        buttonPanel.getChildren().add(this.lobbyExitButton);
        buttonPanel.setAlignment(Pos.BASELINE_RIGHT);

        lobbieLayout.getChildren().add(this.lobbyView);
        lobbieLayout.getChildren().add(buttonPanel);

        detailsLayout.getChildren().add(this.detailsExitButton);

        this.window = primaryStage;
        this.window.setScene(this.lobbieScene);
        this.window.setTitle("Gamelobby Test Client");
        this.window.setAlwaysOnTop(true);
        this.window.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
