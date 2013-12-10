CC = g++

app:
	${CC} -I ~/work/websocketpp/ -I rapidjson -lboost_system -lboost_random ddpClient.cpp main.cpp -o app
clean:
	rm -f app
br:
	make clean && make && ./app
