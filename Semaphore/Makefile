all: cripter

cripter: cripter.c threads.c queue.c queue.h cripter.h
	gcc threads.c cripter.c queue.c -pthread -o encrypter

install: cripter	
	mkdir -p /var/log/threads
	touch /var/log/threads/tr.log
	touch /var/log/threads/td.log
	touch /var/log/threads/tw.log
	touch /var/log/threads/te.log
	cp encrypter /bin

clean:
	rm -rf /var/log/threads
	rm -f encrypter
	rm -f /bin/encrypter
