#############################################################################
# Makefile for building: KFiltre
# Generated by qmake (2.01a) (Qt 4.6.2) on: lun. janv. 17 00:52:28 2011
# Project:  KFiltre.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile KFiltre.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		kimage.cpp \
		tab.cpp \
		histogram.cpp \
		kgraphicsview.cpp \
		kresizedialog.cpp \
		kmatrixdialog.cpp \
		kfusion.cpp \
		kfiltre.cpp moc_mainwindow.cpp \
		moc_kresizedialog.cpp \
		moc_kmatrixdialog.cpp \
		moc_kfusion.cpp
OBJECTS       = main.o \
		mainwindow.o \
		kimage.o \
		tab.o \
		histogram.o \
		kgraphicsview.o \
		kresizedialog.o \
		kmatrixdialog.o \
		kfusion.o \
		kfiltre.o \
		moc_mainwindow.o \
		moc_kresizedialog.o \
		moc_kmatrixdialog.o \
		moc_kfusion.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		KFiltre.pro
QMAKE_TARGET  = KFiltre
DESTDIR       = 
TARGET        = KFiltre

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_kresizedialog.h ui_kmatrixdialog.h ui_kfusion.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: KFiltre.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile KFiltre.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile KFiltre.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/KFiltre1.0.0 || $(MKDIR) .tmp/KFiltre1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/KFiltre1.0.0/ && $(COPY_FILE) --parents mainwindow.h kimage.h tab.h histogram.h kgraphicsview.h kresizedialog.h kmatrixdialog.h kfusion.h kfiltre.h kimage_fwd.h .tmp/KFiltre1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp kimage.cpp tab.cpp histogram.cpp kgraphicsview.cpp kresizedialog.cpp kmatrixdialog.cpp kfusion.cpp kfiltre.cpp .tmp/KFiltre1.0.0/ && $(COPY_FILE) --parents mainwindow.ui kresizedialog.ui kmatrixdialog.ui kfusion.ui .tmp/KFiltre1.0.0/ && (cd `dirname .tmp/KFiltre1.0.0` && $(TAR) KFiltre1.0.0.tar KFiltre1.0.0 && $(COMPRESS) KFiltre1.0.0.tar) && $(MOVE) `dirname .tmp/KFiltre1.0.0`/KFiltre1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/KFiltre1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_kresizedialog.cpp moc_kmatrixdialog.cpp moc_kfusion.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_kresizedialog.cpp moc_kmatrixdialog.cpp moc_kfusion.cpp
moc_mainwindow.cpp: histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h \
		mainwindow.h \
		mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_kresizedialog.cpp: mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h \
		kresizedialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) kresizedialog.h -o moc_kresizedialog.cpp

moc_kmatrixdialog.cpp: mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h \
		kmatrixdialog.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) kmatrixdialog.h -o moc_kmatrixdialog.cpp

moc_kfusion.cpp: mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h \
		kfusion.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) kfusion.h -o moc_kfusion.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_kresizedialog.h ui_kmatrixdialog.h ui_kfusion.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_kresizedialog.h ui_kmatrixdialog.h ui_kfusion.h
ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

ui_kresizedialog.h: kresizedialog.ui
	/usr/bin/uic-qt4 kresizedialog.ui -o ui_kresizedialog.h

ui_kmatrixdialog.h: kmatrixdialog.ui
	/usr/bin/uic-qt4 kmatrixdialog.ui -o ui_kmatrixdialog.h

ui_kfusion.h: kfusion.ui
	/usr/bin/uic-qt4 kfusion.ui -o ui_kfusion.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h \
		ui_mainwindow.h \
		tab.h \
		kgraphicsview.h \
		kfiltre.h \
		ui_fusion.h \
		kresizedialog.h \
		kmatrixdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

kimage.o: kimage.cpp kfusion.h \
		mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kimage.o kimage.cpp

tab.o: tab.cpp tab.h \
		kgraphicsview.h \
		mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o tab.o tab.cpp

histogram.o: histogram.cpp histogram.h \
		kimage.h \
		kimage_fwd.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o histogram.o histogram.cpp

kgraphicsview.o: kgraphicsview.cpp kgraphicsview.h \
		mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kgraphicsview.o kgraphicsview.cpp

kresizedialog.o: kresizedialog.cpp kresizedialog.h \
		mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h \
		ui_kresizedialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kresizedialog.o kresizedialog.cpp

kmatrixdialog.o: kmatrixdialog.cpp kmatrixdialog.h \
		mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		kfusion.h \
		ui_kmatrixdialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kmatrixdialog.o kmatrixdialog.cpp

kfusion.o: kfusion.cpp kfusion.h \
		mainwindow.h \
		histogram.h \
		kimage.h \
		kimage_fwd.h \
		ui_kfusion.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kfusion.o kfusion.cpp

kfiltre.o: kfiltre.cpp kfiltre.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o kfiltre.o kfiltre.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_kresizedialog.o: moc_kresizedialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_kresizedialog.o moc_kresizedialog.cpp

moc_kmatrixdialog.o: moc_kmatrixdialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_kmatrixdialog.o moc_kmatrixdialog.cpp

moc_kfusion.o: moc_kfusion.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_kfusion.o moc_kfusion.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

