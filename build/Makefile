default:
	x86_64-w64-mingw32-gcc -o game.exe ../src/main.c -I../include/ -L../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

mac:
	clang -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL -I ../include/ ../lib/libraylibmac.a ../src/main.c -o game

web: 
	emcc -o game.html ../src/main.c ../lib/libraylibweb.a -I../include/ -L../lib/ -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB -static

webmac:
	emcc -o game.html ../src/main.c ../lib/libraylibwebmac.a -I../include/ -L../lib/ -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB -static

windows:
	gcc -o game.exe ../src/main.c -I../include/ -L../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	rm game*

cleanwsl:
	rm game.exe
