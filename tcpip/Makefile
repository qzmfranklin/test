exe:= showip.exe server.exe client.exe

all: ${exe}

%.exe: %.cpp
	icpc -o $@ $^

clean:
	rm -f ${exe}
