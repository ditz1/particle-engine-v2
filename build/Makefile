default:
	x86_64-w64-mingw32-gcc -o game.exe ../src/main.c -I../include/ -L../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

mac:
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -I ../include/ ../lib/libraylibmac.a ../src/main.c -o game

windows:
	gcc -o game.exe ../src/main.c -I../include/ -L../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	del /Q game.exe

cleanwsl:
	rm game.exe
