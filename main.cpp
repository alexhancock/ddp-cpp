#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;

typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

void on_message(client* c, websocketpp::connection_hdl hdl, message_ptr msg) {
}


int main(int argc, char* argv[]) {
  client ws_client;
  std::string uri = "ws://0.0.0.0:3000/websocket";

  ws_client.init_asio();
  ws_client.set_message_handler(bind(&on_message,&ws_client,::_1,::_2));

  websocketpp::lib::error_code ec;
  
  client::connection_ptr con = ws_client.get_connection(uri, ec);
  
  ws_client.connect(con);
  ws_client.run();
}
