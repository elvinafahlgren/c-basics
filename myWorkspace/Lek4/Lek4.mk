##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Lek4
ConfigurationName      :=Debug
WorkspacePath          :=D:/mop/myWorkspace
ProjectPath            :=D:/mop/myWorkspace/Lek4
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=elvin
Date                   :=26/01/2021
CodeLitePath           :=D:/Nedladdningar/CodeLite
LinkerName             :=$(CodeLiteDir)/tools/gcc/bin/g++
SharedObjectLinkerName :=$(CodeLiteDir)/tools/gcc/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
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
ObjectsFileList        :="Lek4.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=$(CodeLiteDir)/tools/gcc/bin/windres
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := $(CodeLiteDir)/tools/gcc/bin/ar rcus
CXX      := $(CodeLiteDir)/tools/gcc/bin/g++
CC       := $(CodeLiteDir)/tools/gcc/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := $(CodeLiteDir)/tools/gcc/bin/as


##
## User defined environment variables
##
CodeLiteDir:=D:\Nedladdningar\CodeLite
Objects0=$(IntermediateDirectory)/VariousTextString.c$(ObjectSuffix) $(IntermediateDirectory)/PrintIntegerArray.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(ConfigurationName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(ConfigurationName)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/VariousTextString.c$(ObjectSuffix): VariousTextString.c
	$(CC) $(SourceSwitch) "D:/mop/myWorkspace/Lek4/VariousTextString.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VariousTextString.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/VariousTextString.c$(PreprocessSuffix): VariousTextString.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/VariousTextString.c$(PreprocessSuffix) VariousTextString.c

$(IntermediateDirectory)/PrintIntegerArray.c$(ObjectSuffix): PrintIntegerArray.c
	$(CC) $(SourceSwitch) "D:/mop/myWorkspace/Lek4/PrintIntegerArray.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PrintIntegerArray.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/PrintIntegerArray.c$(PreprocessSuffix): PrintIntegerArray.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/PrintIntegerArray.c$(PreprocessSuffix) PrintIntegerArray.c

##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/

