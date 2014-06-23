CXX:= g++
exe:= showip.exe server.exe client.exe chat_server.exe chat_client.exe

all: ${exe}

%.exe: %.o
	${CXX} -o $@ $^

%.o: %.cpp
	${CXX} -o $@ $< -c -MMD -MP 

clean:
	rm -f *.d *.o *.exe

-include inet_utils.d

-include showip.d
showip.exe: showip.o inet_utils.o

-include chat_client.d
chat_client.exe: chat_client.o inet_utils.o

-include chat_server.d
chat_server.exe: chat_server.o inet_utils.o

#-include chat.d
#chat.exe: chat.o inet_utils.o

-include server.d
server.exe: server.o

-include client.d
client.exe: client.o
