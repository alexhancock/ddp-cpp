#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

int msgCount = 0;

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << msg->get_payload();

    if (msgCount == 0){
      std::string connectMessage = "{ \"msg\": \"connect\", \"version\": \"pre1\" }";
      c->send(hdl, connectMessage, msg->get_opcode());
    } else if (msgCount == 1){
      std::string subMessage = "{ \"msg\": \"sub\", \"id\": \"cppClient\", \"name\": \"feedItems\" }";
      c->send(hdl, subMessage, msg->get_opcode());
    }

    msgCount++;
}

int main(int argc, char* argv[]) {
  client ws_client;
  std::string uri = "ws://0.0.0.0:3000/websocket";

  if (argc == 2) {
    uri = argv[1];
  }

  ws_client.init_asio();
  ws_client.set_message_handler(bind(&on_message,&ws_client,::_1,::_2));

  websocketpp::lib::error_code ec;
  client::connection_ptr con = ws_client.get_connection(uri, ec);
  
  ws_client.connect(con);
  ws_client.run();
}
