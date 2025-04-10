CC = gcc

LIBS :=-lgdi32 -lm 
EXT = .exe
STATIC =

WARNINGS = -Wall -Werror -Wextra
OS_DIR = \\

SRC = rgfw_example.c

ifneq (,$(filter $(CC),winegcc x86_64-w64-mingw32-gcc i686-w64-mingw32-gcc))
	STATIC = --static
    detected_OS := WindowsCross
	OS_DIR = /
	ifeq ($(CC),x86_64-w64-mingw32-gcc)
		CC = x86_64-w64-mingw32-gcc
	else
		CC = i686-w64-mingw32-gcc
	endif
else
	ifeq '$(findstring ;,$(PATH))' ';'
		detected_OS := Windows
	else
		detected_OS := $(shell uname 2>/dev/null || echo Unknown)
		detected_OS := $(patsubst CYGWIN%,Cygwin,$(detected_OS))
		detected_OS := $(patsubst MSYS%,MSYS,$(detected_OS))
		detected_OS := $(patsubst MINGW%,MSYS,$(detected_OS))
	endif
endif

ifeq ($(detected_OS),Darwin)        # Mac OS X
	LIBS := -lm -framework Cocoa -framework IOKit $(STATIC) -framework CoreVideo
	EXT = 
	WARNINGS = 
	OS_DIR = /
endif
ifeq ($(detected_OS),Linux)
    LIBS := -lXrandr -lX11 -lm $(STATIC)
	EXT =
	OS_DIR = /
endif

ifneq (,$(filter $(CC),cl))
	OS_DIR = \\

endif

ifneq (,$(filter $(CC),/opt/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	OS_DIR = /
endif

ifneq (,$(filter $(CC),cl /op/msvc/bin/x64/cl.exe /opt/msvc/bin/x86/cl.exe))
	WARNINGS =
	STATIC = /static
	LIBS = $(STATIC)
	EXT = .exe
endif

all: main.c
	$(CC) $^ $(LIBS) -o rgfw_example$(EXT)

clean:
	rm -f *.exe rgfw_example 
