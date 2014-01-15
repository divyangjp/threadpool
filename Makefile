########################################################
# command		output
# -------   	-----------------------------------
# make			Makes executable without debug info
# make debug	Makes executable with debug info
# make clean	Cleans executable, object files and core
#######################################################

#------------------------------------------------------------------------------

SOURCEDIR=.

SOURCE=\
	$(SOURCEDIR)/Utils.cpp\
	$(SOURCEDIR)/Thread.cpp\
	$(SOURCEDIR)/Mutex.cpp\
	$(SOURCEDIR)/Condition.cpp\
	$(SOURCEDIR)/ThrReqHandler.cpp\
	$(SOURCEDIR)/Request.cpp\
	$(SOURCEDIR)/TCPRequest.cpp\
	$(SOURCEDIR)/ThreadPool.cpp\
	$(SOURCEDIR)/Thread_App.cpp

OBJECTS=\
	Thread.o\
	Mutex.o\
	Condition.o\
	ThrReqHandler.o\
	Request.o\
	TCPRequest.o\
	ThreadPool.o\
	Thread_App.o

MYPROGRAM=a.out
MYINCLUDES=\
	-I./ 

MYLIBRARIES=

CFLAGS= -Wall -pthread
CDEBUGFLAGS= -g -DDEBUG

CC=g++

#------------------------------------------------------------------------------


all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)
	$(CC) $(CFLAGS) $(MYINCLUDES) $(SOURCE) -o $(MYPROGRAM) 

debug: $(SOURCE)
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(MYINCLUDES) $(SOURCE) -o $(MYPROGRAM)


.cpp.o:
	$(CC) $(CFLAGS) $(CDEBUGFLAGS) $(MYINCLUDES) -c $<

clean:
	rm -f $(MYPROGRAM) *.o core a.out.stackdump
