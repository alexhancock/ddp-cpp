#include "ddpClient.hpp"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

int msgCount = 0;

// Top level websocket message handler
// TODO - Parse messages and call appropriate Document Event Handler
void on_message(client* webSocketClient, DDPClient* ddpClient, websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << msg->get_payload();
    if (msgCount == 0){
      std::string connectMessage = "{ \"msg\": \"connect\", \"version\": \"pre1\" }";
      webSocketClient->send(hdl, connectMessage, msg->get_opcode());
    } else if (msgCount == 1){
      std::string subMessage = "{ \"msg\": \"sub\", \"id\": \"cppClient\", \"name\": \"feedItems\" }";
      webSocketClient->send(hdl, subMessage, msg->get_opcode());
    }
    msgCount++;
}

// Callback Setup
void DDPClient::onAdded(int (*addedCallback)(string)) {
   this->addedCallback = addedCallback;
}
void DDPClient::onRemoved(int (*removedCallback)(string)){
   this->removedCallback = removedCallback;
}
void DDPClient::onChanged(int (*changedCallback)(string)){
   this->changedCallback = changedCallback;
}

// Document Event Handlers
void DDPClient::addedDocument(string doc){
  this->addedCallback(doc);
}
void DDPClient::removedDocument(string doc){
  this->removedCallback(doc);
}
void DDPClient::changedDocument(string doc){
  this->changedCallback(doc);
}

// connect to a meteor server
int DDPClient::connect(string uri){
  client ws_client;

  ws_client.init_asio();
  ws_client.set_message_handler(bind(&on_message,&ws_client, this, ::_1,::_2));

  websocketpp::lib::error_code ec;
  client::connection_ptr con = ws_client.get_connection(uri, ec);
  
  ws_client.connect(con);
  ws_client.run();
  return 1;
}
