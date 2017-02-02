CC=g++
MOC=moc
DEFINES= -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED -DQT_WIDGETS_LIB
CFLAGS= -pipe -g -O2 -Wall -W -std=gnu++0x -D_REENTRANT $(DEFINES)
EXECUTABLE=eAPI-DM-GUI

ifeq (,$(PREFIX))
	PREFIX=/usr/local/lib
endif
$(info Library Directory is $(PREFIX). For changing please set PREFIX variable)

INCDIRS=-I. -I$(PREFIX)/../include -I/usr/include/x86_64-linux-gnu/qt5 -I/usr/include/x86_64-linux-gnu/qt5/QtGui -I/usr/include/x86_64-linux-gnu/qt5/QtCore -I/usr/include/x86_64-linux-gnu/qt5/QtWidgets -I. -I.
LIBS=-L/usr/lib/x86_64-linux-gnu -lQt5Gui -lQt5Core -lQt5Widgets -lpthread -L$(PREFIX) -lEApi

SOURCES=main.cpp \
	boardinfo.cpp \
	circlewidget.cpp \
	gpio.cpp \
	i2c.cpp \
	mainwindow.cpp \
	mytabwidget.cpp \
	realtimeinfo.cpp \
	storage.cpp \
	watchdog.cpp \
	qrc_resource.cpp

MOC_HEADERS=boardinfo.h \
	    circlewidget.h \
	    gpio.h \
	    i2c.h \
	    mainwindow.h \
	    mytabwidget.h \
	    realtimeinfo.h \
	    storage.h \
	    watchdog.h


# Change postfixes
MOC_SOURCES=$(MOC_HEADERS:.h=.moc.cpp)
OBJECTS=$(SOURCES:.cpp=.o) $(MOC_SOURCES:.cpp=.o)

all: $(EXECUTABLE)
	@echo Done!

$(EXECUTABLE): $(OBJECTS)
	$(CC) $^ $(LIBS) -o $@

# Generate object files, rule to change postfix
qrc_resource.o: qrc_resource.cpp
	$(CC) -c $(CFLAGS) $(INCDIRS) -o qrc_resource.o qrc_resource.cpp


%.o: %.cpp
	$(CC) $(CFLAGS) $(INCDIRS) -c $< -o $@

# Generate cpp from h via Qt's Meta Object Compiler, rule to change postfix
%.moc.cpp: %.h
	$(MOC) $(INCDIRS) $< -o $@

.PHONY: tags clean

clean:
	rm *.o

# Generate ctags file for all included files (autocomplete and jump to source)
tags:
	gcc -M $(INCDIRS) $(SOURCES) | \
	sed -e 's/[\\ ]/\n/g' | \
	sed -e '/^$$/d' -e '/\.o:[ \t]*$$/d' | \
	ctags -L - --c++-kinds=+p --field -L/usr/lib/x86_64-linux-gnu -lQtGui -lQtCore -lpthreadq
