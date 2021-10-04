all: chat.cpp
			gcc -g -lstdc++ -Wall -o chat chat.cpp

clean:
	 	$(RM) chat
