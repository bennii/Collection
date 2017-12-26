##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Server
ConfigurationName      :=Debug
WorkspacePath          := "E:\Server"
ProjectPath            := "E:\Server\Server"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Benjamin
Date                   :=18.08.2013
CodeLitePath           :="C:\Programming\CodeLite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Server.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)ws2_32 
ArLibs                 :=  "libws2_32.a" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O3 -Wall  $(Preprocessors)
CFLAGS   :=  -g -O3 -Wall  $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=C:\Programming\CodeLite
WXWIN:=C:\Programming\CodeLite\wxWidgets-2.9.4
PATH:=$(WXWIN)\lib\gcc_dll;$(PATH)
WXCFG:=gcc_dll\mswu
UNIT_TEST_PP_SRC_DIR:=C:\Programming\CodeLite\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/GameLobby$(ObjectSuffix) $(IntermediateDirectory)/Gamemanager$(ObjectSuffix) $(IntermediateDirectory)/main$(ObjectSuffix) $(IntermediateDirectory)/Packetbuilder$(ObjectSuffix) $(IntermediateDirectory)/Packetreader$(ObjectSuffix) $(IntermediateDirectory)/Packets$(ObjectSuffix) $(IntermediateDirectory)/Player$(ObjectSuffix) $(IntermediateDirectory)/Playermanager$(ObjectSuffix) $(IntermediateDirectory)/Server$(ObjectSuffix) $(IntermediateDirectory)/SimpleServer$(ObjectSuffix) \
	$(IntermediateDirectory)/MD5Hash$(ObjectSuffix) $(IntermediateDirectory)/hashmanager$(ObjectSuffix) $(IntermediateDirectory)/Matchmaking$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/GameLobby$(ObjectSuffix): GameLobby.cpp $(IntermediateDirectory)/GameLobby$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/GameLobby.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GameLobby$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/GameLobby$(DependSuffix): GameLobby.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/GameLobby$(ObjectSuffix) -MF$(IntermediateDirectory)/GameLobby$(DependSuffix) -MM "GameLobby.cpp"

$(IntermediateDirectory)/GameLobby$(PreprocessSuffix): GameLobby.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/GameLobby$(PreprocessSuffix) "GameLobby.cpp"

$(IntermediateDirectory)/Gamemanager$(ObjectSuffix): Gamemanager.cpp $(IntermediateDirectory)/Gamemanager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Gamemanager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Gamemanager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Gamemanager$(DependSuffix): Gamemanager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Gamemanager$(ObjectSuffix) -MF$(IntermediateDirectory)/Gamemanager$(DependSuffix) -MM "Gamemanager.cpp"

$(IntermediateDirectory)/Gamemanager$(PreprocessSuffix): Gamemanager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Gamemanager$(PreprocessSuffix) "Gamemanager.cpp"

$(IntermediateDirectory)/main$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main$(ObjectSuffix) -MF$(IntermediateDirectory)/main$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/Packetbuilder$(ObjectSuffix): Packetbuilder.cpp $(IntermediateDirectory)/Packetbuilder$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Packetbuilder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Packetbuilder$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Packetbuilder$(DependSuffix): Packetbuilder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Packetbuilder$(ObjectSuffix) -MF$(IntermediateDirectory)/Packetbuilder$(DependSuffix) -MM "Packetbuilder.cpp"

$(IntermediateDirectory)/Packetbuilder$(PreprocessSuffix): Packetbuilder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Packetbuilder$(PreprocessSuffix) "Packetbuilder.cpp"

$(IntermediateDirectory)/Packetreader$(ObjectSuffix): Packetreader.cpp $(IntermediateDirectory)/Packetreader$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Packetreader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Packetreader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Packetreader$(DependSuffix): Packetreader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Packetreader$(ObjectSuffix) -MF$(IntermediateDirectory)/Packetreader$(DependSuffix) -MM "Packetreader.cpp"

$(IntermediateDirectory)/Packetreader$(PreprocessSuffix): Packetreader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Packetreader$(PreprocessSuffix) "Packetreader.cpp"

$(IntermediateDirectory)/Packets$(ObjectSuffix): Packets.cpp $(IntermediateDirectory)/Packets$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Packets.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Packets$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Packets$(DependSuffix): Packets.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Packets$(ObjectSuffix) -MF$(IntermediateDirectory)/Packets$(DependSuffix) -MM "Packets.cpp"

$(IntermediateDirectory)/Packets$(PreprocessSuffix): Packets.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Packets$(PreprocessSuffix) "Packets.cpp"

$(IntermediateDirectory)/Player$(ObjectSuffix): Player.cpp $(IntermediateDirectory)/Player$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Player.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Player$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Player$(DependSuffix): Player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Player$(ObjectSuffix) -MF$(IntermediateDirectory)/Player$(DependSuffix) -MM "Player.cpp"

$(IntermediateDirectory)/Player$(PreprocessSuffix): Player.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Player$(PreprocessSuffix) "Player.cpp"

$(IntermediateDirectory)/Playermanager$(ObjectSuffix): Playermanager.cpp $(IntermediateDirectory)/Playermanager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Playermanager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Playermanager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Playermanager$(DependSuffix): Playermanager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Playermanager$(ObjectSuffix) -MF$(IntermediateDirectory)/Playermanager$(DependSuffix) -MM "Playermanager.cpp"

$(IntermediateDirectory)/Playermanager$(PreprocessSuffix): Playermanager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Playermanager$(PreprocessSuffix) "Playermanager.cpp"

$(IntermediateDirectory)/Server$(ObjectSuffix): Server.cpp $(IntermediateDirectory)/Server$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Server$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Server$(DependSuffix): Server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Server$(ObjectSuffix) -MF$(IntermediateDirectory)/Server$(DependSuffix) -MM "Server.cpp"

$(IntermediateDirectory)/Server$(PreprocessSuffix): Server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Server$(PreprocessSuffix) "Server.cpp"

$(IntermediateDirectory)/SimpleServer$(ObjectSuffix): SimpleServer.cpp $(IntermediateDirectory)/SimpleServer$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/SimpleServer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SimpleServer$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SimpleServer$(DependSuffix): SimpleServer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SimpleServer$(ObjectSuffix) -MF$(IntermediateDirectory)/SimpleServer$(DependSuffix) -MM "SimpleServer.cpp"

$(IntermediateDirectory)/SimpleServer$(PreprocessSuffix): SimpleServer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SimpleServer$(PreprocessSuffix) "SimpleServer.cpp"

$(IntermediateDirectory)/MD5Hash$(ObjectSuffix): MD5Hash.cpp $(IntermediateDirectory)/MD5Hash$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/MD5Hash.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MD5Hash$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/MD5Hash$(DependSuffix): MD5Hash.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/MD5Hash$(ObjectSuffix) -MF$(IntermediateDirectory)/MD5Hash$(DependSuffix) -MM "MD5Hash.cpp"

$(IntermediateDirectory)/MD5Hash$(PreprocessSuffix): MD5Hash.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/MD5Hash$(PreprocessSuffix) "MD5Hash.cpp"

$(IntermediateDirectory)/hashmanager$(ObjectSuffix): hashmanager.cpp $(IntermediateDirectory)/hashmanager$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/hashmanager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/hashmanager$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hashmanager$(DependSuffix): hashmanager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/hashmanager$(ObjectSuffix) -MF$(IntermediateDirectory)/hashmanager$(DependSuffix) -MM "hashmanager.cpp"

$(IntermediateDirectory)/hashmanager$(PreprocessSuffix): hashmanager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hashmanager$(PreprocessSuffix) "hashmanager.cpp"

$(IntermediateDirectory)/Matchmaking$(ObjectSuffix): Matchmaking.cpp $(IntermediateDirectory)/Matchmaking$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "E:/Server/Server/Matchmaking.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matchmaking$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Matchmaking$(DependSuffix): Matchmaking.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Matchmaking$(ObjectSuffix) -MF$(IntermediateDirectory)/Matchmaking$(DependSuffix) -MM "Matchmaking.cpp"

$(IntermediateDirectory)/Matchmaking$(PreprocessSuffix): Matchmaking.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Matchmaking$(PreprocessSuffix) "Matchmaking.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/GameLobby$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/GameLobby$(DependSuffix)
	$(RM) $(IntermediateDirectory)/GameLobby$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Gamemanager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Gamemanager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Gamemanager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Packetbuilder$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Packetbuilder$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Packetbuilder$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Packetreader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Packetreader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Packetreader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Packets$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Packets$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Packets$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Player$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Player$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Player$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Playermanager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Playermanager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Playermanager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Server$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Server$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Server$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/SimpleServer$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/SimpleServer$(DependSuffix)
	$(RM) $(IntermediateDirectory)/SimpleServer$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/MD5Hash$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/MD5Hash$(DependSuffix)
	$(RM) $(IntermediateDirectory)/MD5Hash$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/hashmanager$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/hashmanager$(DependSuffix)
	$(RM) $(IntermediateDirectory)/hashmanager$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/Matchmaking$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/Matchmaking$(DependSuffix)
	$(RM) $(IntermediateDirectory)/Matchmaking$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) "../.build-debug/Server"


