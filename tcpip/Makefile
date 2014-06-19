CXX:= g++
exe:= showip.exe server.exe client.exe chat_server.exe chat_client.exe

all: ${exe}

%.exe: %.o
	${CXX} -o $@ $^

%.o: %.cpp
	${CXX} -c -o $@ $< -MMD -MP 

clean:
	rm -f *.d *.o *.exe

-include inet_utils.d
-include chat_client.d
-include chat_server.d

chat_client.exe: chat_client.o inet_utils.o
chat_server.exe: chat_server.o inet_utils.o
