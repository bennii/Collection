RM = rm
JCC = javac
JFLAGS =

default: App.class MainFrame.class ButtonPanel.class GameBrowser.class GameLobby.class Opcodes.class Client.class 

App.class: App.java
	$(JCC) $(JFLAGS) App.java

MainFrame.class: gui/MainFrame.java
	$(JCC) $(JFLAGS) gui/MainFrame.java

ButtonPanel.class: gui/ButtonPanel.java
	$(JCC) $(JFLAGS) gui/ButtonPanel.java

GameBrowser.class: gui/GameBrowser.java
	$(JCC) $(JFLAGS) gui/GameBrowser.java

Client.class: network/Client.java
	$(JCC) $(JFLAGS) network/Client.java

GameLobby.class: lib/GameLobby.java
	$(JCC) $(JFLAGS) lib/GameLobby.java

Opcodes.class: lib/Opcodes.java
	$(JCC) $(JFLAGS) lib/Opcodes.java

clean:
	$(RM) *.class gui/*.class lib/*.class network/*.class
