##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=test
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/elvina/Dokument/MOP/laborationer
ProjectPath            :=/home/elvina/Dokument/MOP/laborationer/test
IntermediateDirectory  :=../build-$(ConfigurationName)/test
OutDir                 :=../build-$(ConfigurationName)/test
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Elvina
Date                   :=04/02/21
CodeLitePath           :=/home/elvina/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
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
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  -T$(ProjectPath)/md407-ram.x -L$(ARM_V6LIB) -L$(ARM_GCC_V6LIB) -nostartfiles
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)gcc $(LibrarySwitch)c_nano 
ArLibs                 :=  "gcc" "c_nano" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
ARM_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp
ARM_GCC_V6LIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v6-m/nofp
ARM_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/softfp
ARM_GCC_M4SFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/softfp
ARM_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi/lib/thumb/v7e-m+fp/hard
ARM_GCC_M4HFPLIB:=$(CodeLiteDir)/tools/gcc-arm/lib/gcc/arm-none-eabi/9.2.1/thumb/v7e-m+fp/hard
Objects0=../build-$(ConfigurationName)/test/startup.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/test/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/test"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-objcopy -S -O srec  $(IntermediateDirectory)/$(ProjectName).elf $(IntermediateDirectory)/$(ProjectName).s19
	$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-objdump -D -S $(IntermediateDirectory)/$(ProjectName).elf > $(IntermediateDirectory)/$(ProjectName).dass
	@echo Done

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/test"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/test/.d:
	@mkdir -p "../build-$(ConfigurationName)/test"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/test/startup.c$(ObjectSuffix): startup.c ../build-$(ConfigurationName)/test/startup.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/elvina/Dokument/MOP/laborationer/test/startup.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/test/startup.c$(DependSuffix): startup.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/test/startup.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/test/startup.c$(DependSuffix) -MM startup.c

../build-$(ConfigurationName)/test/startup.c$(PreprocessSuffix): startup.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/test/startup.c$(PreprocessSuffix) startup.c


-include ../build-$(ConfigurationName)/test//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


