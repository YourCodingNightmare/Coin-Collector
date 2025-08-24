compile:
	gcc src/main.c src/Entity.c src/Text.c src/Game.c src/Timer.c -Iinc -o bin/app.exe -lSDL2 -lSDL2_ttf
run: compile
	./bin/app.exe