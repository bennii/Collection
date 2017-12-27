JCC = javac
JFLAGS = -g

default: App.class MainFrame.class Client.class

App.class: App.java
	$(JCC) $(JFLAGS) App.java

MainFrame.class: gui/MainFrame.java
	$(JCC) $(JFLAGS) gui/MainFrame.java

Client.class: network/Client.java
	$(JCC) $(JFLAGS) network/Client.java

clean: $(RM) *.class<Paste>
