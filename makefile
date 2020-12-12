#
#	makefile
#

CXX		=	g++
CXXFLAGS	=	$(CXXINCLUDE) $(DEBUG)
CXXINCLUDE	=
LINK.o		=	$(LINK.cc)
LDLIBS		=
## LDLIBS		=	-lncurses
LOADLIBS	=
DEBUG		=
DEBUG		=	-g
ZIPCMD	=	zip


TARGET	=	ai2 ai3 gen_sentence morpheme parse

WEXECS	=	ai2.exe ai3.exe gen_sentence.exe morpheme.exe parse.exe

OBJS	=	ai2.o ai3.o gen_sentence.o morpheme.o parse.o

ZIP_SRC =	ai2.cc ai3.cc gen_sentence.cc morpheme.cc parse.cc \
		noun.txt verb.txt adj.txt adjv.txt

ARCHIVE =	class11.zip

default:
	@echo make XXX となるようにターゲットを指定してください

all:	$(TARGET)

zip:
	-$(ZIPCMD) $(ARCHIVE) $(ZIP_SRC)

clean:	
	-$(RM) $(TARGET) $(WEXECS) $(OBJS) $(ARCHIVE)

ai2:		ai2.o
ai3:		ai3.o
gen_sentence:	gen_sentence.o
morpheme:	morpheme.o
parse:		parse.o

##
##      extra rules for cygwin
##
.SUFFIXES:      .cc .exe

.cc.exe:
		$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

