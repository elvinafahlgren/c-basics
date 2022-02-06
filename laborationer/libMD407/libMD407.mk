##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=libMD407
ConfigurationName      :=Debug
WorkspacePath          :=D:/mop/laborationer
ProjectPath            :=D:/mop/laborationer/libMD407
IntermediateDirectory  :=$(ConfigurationName)
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=elvin
Date                   :=09/03/2021
CodeLitePath           :=D:/Nedladdningar/CodeLite
LinkerName             :=$(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
SharedObjectLinkerName :=$(CodeLiteDir)/tools/gcc-arm/arm-none-eabi-g++.exe -shared -fPIC
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
OutputFile             :=$(IntermediateDirectory)/$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="libMD407.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=
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
AR       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-ar.exe rcu
CXX      := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-g++.exe
CC       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-gcc.exe
CXXFLAGS :=  -g -O0 -W $(Preprocessors)
CFLAGS   :=  -Wa,-adhln=test.s -g -O0 -w -mthumb -march=armv6-m  -mfloat-abi=soft -std=c99 -mthumb -march=armv6-m $(Preprocessors)
ASFLAGS  := 
AS       := $(CodeLiteDir)/tools/gcc-arm/bin/arm-none-eabi-as.exe


##
## User defined environment variables
##
CodeLiteDir:=D:\Nedladdningar\CodeLite
Objects0=$(IntermediateDirectory)/general.c$(ObjectSuffix) $(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) $(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) $(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList)
	@$(MakeDirCommand) "D:\mop\laborationer/.build-debug"
	@echo rebuilt > "D:\mop\laborationer/.build-debug/libMD407"

PostBuild:
	@echo Executing Post Build commands ...
	
	cp Debug/libMD407.a \
D:\Nedladdningar\CodeLite/tools/gcc-arm/arm-none-eabi/lib/thumb/v6-m/nofp/libmd407.a
	cp ./libMD407.h \
D:\Nedladdningar\CodeLite/tools/gcc-arm/arm-none-eabi/include/libmd407.h
	@echo Done

MakeIntermediateDirs:
	@$(MakeDirCommand) "$(ConfigurationName)"


$(ConfigurationName):
	@$(MakeDirCommand) "$(ConfigurationName)"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/general.c$(ObjectSuffix): general.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/general.c$(ObjectSuffix) -MF$(IntermediateDirectory)/general.c$(DependSuffix) -MM general.c
	$(CC) $(SourceSwitch) "D:/mop/laborationer/libMD407/general.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/general.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/general.c$(PreprocessSuffix): general.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/general.c$(PreprocessSuffix) general.c

$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix): usart_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/usart_driver.c$(DependSuffix) -MM usart_driver.c
	$(CC) $(SourceSwitch) "D:/mop/laborationer/libMD407/usart_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usart_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usart_driver.c$(PreprocessSuffix): usart_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usart_driver.c$(PreprocessSuffix) usart_driver.c

$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix): asciidisplay_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/asciidisplay_driver.c$(DependSuffix) -MM asciidisplay_driver.c
	$(CC) $(SourceSwitch) "D:/mop/laborationer/libMD407/asciidisplay_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/asciidisplay_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/asciidisplay_driver.c$(PreprocessSuffix): asciidisplay_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/asciidisplay_driver.c$(PreprocessSuffix) asciidisplay_driver.c

$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix): keypad_driver.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) -MF$(IntermediateDirectory)/keypad_driver.c$(DependSuffix) -MM keypad_driver.c
	$(CC) $(SourceSwitch) "D:/mop/laborationer/libMD407/keypad_driver.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/keypad_driver.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/keypad_driver.c$(PreprocessSuffix): keypad_driver.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/keypad_driver.c$(PreprocessSuffix) keypad_driver.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(ConfigurationName)/


