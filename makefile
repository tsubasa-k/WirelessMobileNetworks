TARGET = HW1
FLAG = -std=c++11

all: $(TARGET).cpp
	g++ $(FLAG) -c $(TARGET).cpp
	g++ $(FLAG) -o $(TARGET) $(TARGET).o

clean:
	rm -f $(TARGET)
	rm -f $(TARGET).o
	
