CC = g++
FLAGS = -std=c++17 -pedantic -Wall -Werror -Wextra -lm --coverage

SOURCE = Buffer.cpp

TARGET = Buffer

$(TARGET):
	$(CC) $(FLAGS) -c *.cpp
	ar rcs $(TARGET) *.o
	ranlib $(TARGET)
	rm -rf *.o

run: 
	$(CC) $(FLAGS) $(SOURCE) -o $(TARGET)
	./$(TARGET) 

clean:
	rm -rf *.gcno *.gcda Buffer