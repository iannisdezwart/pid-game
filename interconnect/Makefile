.PHONY: test
test:
	$(CXX) -o test_client test_client.cpp `pkg-config --libs libsodium`
	$(CXX) -o test_server test_server.cpp `pkg-config --libs libsodium`