GCC:=gcc
#c++编译器
CXX:=gcc
#c编译器
CC:=gcc

#取得操作系统名称#OS_NAME="Linux:SunOS:HP-UX:AIX"
OS_NAME:= $(shell uname -s)

#######c编译选项###############
#c编译器参数,建议-W -Wall必须使用
CFLAGS:= -c -g -W -Wall
#CPP c预编译器名字,默认$(CC) -E
CPP:=
#CPPFLAGS C预编译器选项
CPPFLAGS:=
######c++编译选项#############
#c++编译选项 c++编译器参数
CXXFLAGS:= -c -g -W -Wall
#c++预编译器参数
CXXPPFLAGS:=

#c链接器选项
CLD_FLAGS:= 
#c++链接器选项
CXXLD_FLAGS:= 

############################################################
##指定源文件的路径/支持的源文件的扩展名/源文件搜索路径
##自动搜索源文件名
## 注意:
##   文件名不能含特殊字符,如空格/通配符等
#指定支持的源代码扩增名
SFIX:=.c .C .cpp .cc .CPP .c++ .cp .cxx 
#从指定的路径目录下获取源文件
#$(wildcard PATTERN) 列出当前目录下所有符合模式“PATTERN”格式的文件名
SRC_DIR:=
AUTO_SOURCES:= $(foreach x,${SRC_DIR},\
                     $(wildcard  \
                        $(addprefix  ${x}/*,${SFIX})) )
#生成依赖文件名集合) 
#AUTO_OBJS:=$(addsuffix .o ,$(basename $(notdir ${SOURCES}) ) ) #notdir拿掉路径部分; basename取出文件名中最后一个点号之前的部分
AUTO_OBJS:=$(addsuffix .o ,$(basename  ${AUTO_SOURCES})  ) #含路径信息
###########################################################
#检查源码中，除了C源码外是否有C++源码 ,并定义变量LDCXX存储检查结果
LDCXX:= $(strip $(filter-out  %.c , ${AUTO_SOURCES} ) )
ifdef LDCXX   #有C++源码时,所有源码都使用g++编译，包括C源码，将CC、CFLAGS 的值设置为对应的${CXX}、 ${CXXFLAGS}的值
  CC := ${CXX}                    #重置C编译器为C++编译器
  CFLAGS :=  ${CXXFLAGS}          #重置C编译选现为C++编译选现
  CPP :=  ${CXXPP}                #重置C预编译器为C++预编译器
  CPPFLAGS := ${CXXPPFLAGS}       #重置C预编译的选项为C++预编译的选项
endif

#宏定义
DCPPFLAGS:=-D${OS_NAME}

###############################以上是公共定义部分####################################
#头文件路径
INCLUDES:= -I./
#动态库路径
LIB_DIR:=
SO_LIBS:=-lstdc++

#常用文件
COMMON_SOURCES:=./ConfigFile.cpp
COMMON_OBJS:= $(COMMON_SOURCES:.cpp=.o)


SOURCES:=$(COMMON_SOURCES) $(AUTO_SOURCES)
OBJS:= $(AUTO_OBJS) $(COMMON_OBJS)



#汇总所有的源文件
TARGET:=unittest
#输出路径
OUTPUT_DIR:=./bin
all:$(TARGET)

unittest:$(OBJS)

#$@表示目标; $^表示所有依赖文件; $<表示第一个依赖文件
#模式规则: 
# 模式规则中，至少在规则的目标定义中要包含"%"，否则，就是一般的规则。
# 目标中的"%"定义表示对文件名的匹配，"%"表示长度任意的非空字符串。
# 例如："%.c"表示以".c"结尾的文件名（文件名的长度至少为3），而"s.%.c"则表示以"s."开头，".c"结尾的文件名（文件名的长度至少为5）
# 模式规则语法:  %.o: %.c ; COMMAND...
# 老式模式规则语法: .c.o: <=> %.o: %.c
#静态模式:
#  规则存在多个目标;
#  并且不同的目标可以根据目标文件的名字来自动构造出依赖文件
#  静态模式规则比多目标规则更通用
#静态规则:
#  静态规则语法: 
#     TARGETS ...: TARGET-PATTERN: PREREQ-PATTERNS ...
#        
$(COMMON_OBJS): %.o:%.cpp
	$(GCC) -o $@ $(DCPPFLAGS) $(CFLAGS) $(INCLUDES) $<

%.o: %.c
	$(CC) ${DCPPFLAGS}  ${CFLAGS}   ${INCLUDES} $<
%.o: %.C
	$(CXX) ${DCPPFLAGS} ${CXXFLAGS} ${INCLUDES) $<
%.o: %.cc
	${CXX} ${DCPPFLAGS} ${CXXFLAGS} ${INCLUDES}   $<
%.o: %.cpp
	${CXX}     ${DCPPFLAGS}    ${CXXFLAGS}    ${INCLUDES}   $<
%.o : %.CPP
	${CXX}     ${DCPPFLAGS}    ${CXXFLAGS}    ${INCLUDES}   $<
%.o: %.c++
	${CXX}     ${DCPPFLAGS}    ${CXXFLAGS}    ${INCLUDES}   $<
%.o: %.cp
	${CXX}     ${DCPPFLAGS}    ${CXXFLAGS}    ${INCLUDES}   $<
%.o: %.cxx
	${CXX}     ${DCPPFLAGS}    ${CXXFLAGS}    ${INCLUDES}   $<


clean:
	rm -f $(OBJS)

test:
	@echo "AutoSources=[${AUTO_SOURCES}]"
	@echo "AutoObjs=[${AUTO_OBJS}]"
	@echo "LDCXX=[${LDCXX}]"
	@echo "OBJS=[${OBJS}]"
