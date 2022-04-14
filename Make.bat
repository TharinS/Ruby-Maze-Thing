g++ -I src/include -c Projects/RubyMazeThing.cpp -o Main.o
g++ Main.o -o RubyMazeThing -L src/lib -lsfml-graphics -lsfml-window -lsfml-system
RubyMazeThing.exe