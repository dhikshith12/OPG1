##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=OpenGl
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/dhiks/dev/dev
ProjectPath            :=/home/dhiks/dev/OpenGl/OpenGl
IntermediateDirectory  :=../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl
OutDir                 :=../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=03/11/22
CodeLitePath           :=/home/dhiks/.codelite
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
OutputFile             :=../../dev/build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)GL $(LibrarySwitch)GLEW $(LibrarySwitch)SDL2 $(LibrarySwitch)glfw 
ArLibs                 :=  "GL" "GLEW" "SDL2" "glfw" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/.d $(Objects) 
	@mkdir -p "../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl"
	@mkdir -p ""../../dev/build-$(ConfigurationName)/bin""

../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/.d:
	@mkdir -p "../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl"

PreBuild:


##
## Objects
##
../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(ObjectSuffix): main.cpp ../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/dhiks/dev/OpenGl/OpenGl/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(ObjectSuffix) -MF../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(DependSuffix) -MM main.cpp

../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl/main.cpp$(PreprocessSuffix) main.cpp


-include ../../dev/build-$(ConfigurationName)/__/OpenGl/OpenGl//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


