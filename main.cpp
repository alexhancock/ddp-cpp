#include "ddpClient.hpp"

int main(int argc, char* argv[]) {
  DDPClient* ddpClient = new DDPClient();
  ddpClient->connect("ws://0.0.0.0:3000/websocket");
}
