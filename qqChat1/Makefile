all: test_server.cpp server.cpp server.h test_client.cpp client.cpp client.h global.h
	g++ -o test_client test_client.cpp client.cpp -lpthread
	g++ -o test_server test_server.cpp server.cpp -lpthread -lmysqlclient -lhiredis
test_client: test_client.cpp client.cpp client.h global.h
	g++ -o test_client test_client.cpp client.cpp -lpthread
test_server: test_server.cpp server.cpp server.h global.h
	g++ -o test_server test_server.cpp server.cpp -lpthread -lmysqlclient -lhiredis

clean:
	rm test_server
	rm test_client