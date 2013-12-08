CC = g++

app:
	${CC} -I ~/work/websocketpp/ -lboost_system -lboost_random main.cpp -o app
clean:
	rm -f app
br:
	make clean && make && ./app
