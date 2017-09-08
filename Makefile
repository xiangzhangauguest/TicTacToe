main: main.cpp ; g++ -std=c++11 -o main $^
tic: tictactoe.cpp ; g++ -std=c++11 -o tictactoe $^
test: test.cpp ; g++ -std=c++11 -o test $^