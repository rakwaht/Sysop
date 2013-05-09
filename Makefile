all: cripter

cripter: cripter.c threads.c 
	mkdir -p /var/log/threads
	touch /var/log/threads/tr.log
	touch /var/log/threads/td.log
	touch /var/log/threads/tw.log
	touch /var/log/threads/te.log
	gcc threads.c cripter.c -pthread -o cripter
	cp cripter /bin

clean:
	rm -rf /var/log/threads
	rm cripter
	rm /bin/cripter
