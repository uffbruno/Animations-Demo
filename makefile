#the compiler
CC=g++

#compiler flags, for extra error-and-warning intolerance
CPPFLAGS=-Wall -Wextra -pedantic -Weffc++ -Werror -g

#all these link flags is for linking Allegro 5 statically with my application
#so there is no need to send dlls along with executable and resources to distribution
A5LINKFLAGS=-lallegro-static -lallegro_font-static -lallegro_ttf-static -lallegro_image-static
WIN32LINKFLAGS=-lopengl32 -lwinmm -luuid -lgdiplus -lfreetype -lole32 -lgdi32 -lkernel32 -lpsapi -lshlwapi -static-libgcc -static-libstdc++

#some DOS commands
RM=rm
RMDIR=rmdir
MKDIR=mkdir
CP=cp

#directory where all source code is located
SRCDIR=src

#directory where all objects are located
#TODO: adapt this makefile to generate *.o -> build/*.o
OBJDIR=.

#directory where our final executable will be located
BINDIR=.

#directory for the distribution
DISTDIR=dist

#directory with the app's resources
RESOURCESDIR=resources

# 'make' looks for objects in the directories specified by VPATH
VPATH=$(SRCDIR);$(OBJDIR);$(BINDIR)

OBJECTS=main.o game.o animation.o sprite.o character.o rpg_char.o char_2d.o
EXECUTABLE=animdemo.exe

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(BINDIR)\$(EXECUTABLE) $(OBJECTS) $(A5LINKFLAGS) $(WIN32LINKFLAGS)

main.o: game.hpp
game.o: game.hpp character.hpp rpg_char.hpp
animation.o: animation.hpp
sprite.o: animation.hpp
character.o: sprite.hpp
rpg_char.o: character.hpp
char_2d.o: character.hpp

dist: $(EXECUTABLE)
	$(MKDIR) $(DISTDIR)
	$(CP) $(BINDIR)\$(EXECUTABLE) $(DISTDIR)
	$(CP) -r $(RESOURCESDIR) $(DISTDIR)
	strip $(DISTDIR)\$(EXECUTABLE)
    
dist-zip: dist
	7z a $(DISTDIR).zip $(DISTDIR)\* -r
    
.PHONY: clean
clean:
	$(RM) $(OBJECTS) $(BINDIR)\$(EXECUTABLE)

.PHONY: clean-dist
clean-dist:
	$(RM) -rf $(DISTDIR)
	$(RM) $(DISTDIR).zip
