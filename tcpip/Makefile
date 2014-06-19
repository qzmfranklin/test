exe:= showip.exe server.exe client.exe chat_server.exe chat_client.exe

all: ${exe}

%.exe: %.cpp
	icpc -o $@ $^

clean:
	rm -f ${exe}
