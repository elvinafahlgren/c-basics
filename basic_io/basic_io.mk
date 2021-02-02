##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=basic_io
ConfigurationName      :=Debug
<<<<<<< HEAD
WorkspacePath          :=/home/elvina/Dokument/MOP/myWorkspace
ProjectPath            :=/home/elvina/Dokument/MOP/myWorkspace/basic_io
IntermediateDirectory  :=./Debug
=======
WorkspacePath          :=D:/mop/myWorkspace
ProjectPath            :=D:/mop/myWorkspace/basic_io
IntermediateDirectory  :=$(ConfigurationName)
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
<<<<<<< HEAD
User                   :=Elvina
Date                   :=29/01/21
CodeLitePath           :=/home/elvina/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
=======
User                   :=elvin
Date                   :=30/01/2021
CodeLitePath           :=D:/Nedladdningar/CodeLite
LinkerName             :=$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
SharedObjectLinkerName :=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi-g++.exe -shared -fPIC
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
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
ObjectsFileList        :="basic_io.txt"
PCHCompileFlags        :=
<<<<<<< HEAD
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
=======
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=
LinkOptions            :=  -T$(ProjectPath)/md407-ram.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostartfiles
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gcc $(LibrarySwitch)c_nano 
ArLibs                 :=  "gcc" "c_nano" 
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
<<<<<<< HEAD
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as
=======
AR       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-ar.exe rcu
CXX      := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
CC       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-gcc.exe
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-as.exe
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78


##
## User defined environment variables
##
<<<<<<< HEAD
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) 
=======
CodeLiteDir:=D:\Nedladdningar\CodeLite
ARM_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp
ARM_GCC_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp
ARM_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/softfp
ARM_GCC_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/softfp
ARM_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/hard
ARM_GCC_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/hard
Objects0=$(IntermediateDirectory)/myStartup.c$(ObjectSuffix) 
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78



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

<<<<<<< HEAD
MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug
=======
PostBuild:
	@echo Executing Post Build commands ...
	D:\Nedladdningar\CodeLite/tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  Debug/basic_io Debug/basic_io.s19
	D:\Nedladdningar\CodeLite/tools/gcc-arm/bin/arm-none-eabi-objdump -D -S Debug/basic_io > Debug/basic_io.dass
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(ConfigurationName)"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "$(ConfigurationName)"
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78

PreBuild:


##
## Objects
##
<<<<<<< HEAD
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c $(IntermediateDirectory)/main.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/elvina/Dokument/MOP/myWorkspace/basic_io/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(DependSuffix): main.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.c$(ObjectSuffix) -MF$(IntermediateDirectory)/main.c$(DependSuffix) -MM main.c

$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c
=======
$(IntermediateDirectory)/myStartup.c$(ObjectSuffix): myStartup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/myStartup.c$(ObjectSuffix) -MF$(IntermediateDirectory)/myStartup.c$(DependSuffix) -MM myStartup.c
	$(CC) $(SourceSwitch) "D:/mop/myWorkspace/basic_io/myStartup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/myStartup.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/myStartup.c$(PreprocessSuffix): myStartup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/myStartup.c$(PreprocessSuffix) myStartup.c
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
<<<<<<< HEAD
	$(RM) -r ./Debug/
=======
	$(RM) -r $(ConfigurationName)/
>>>>>>> dc0f5182086ffeff8f1a2a914b9878b9ebf76c78


