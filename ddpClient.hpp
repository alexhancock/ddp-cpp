#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <iostream>

typedef websocketpp::client<websocketpp::config::asio_client> client;
typedef websocketpp::config::asio_client::message_type::ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using namespace std;

class DDPClient {
    public:

      // storage for callback function pointers
      function<int(string)> addedCallback;
      function<int(string)> removedCallback;
      function<int(string)> changedCallback;

      // Callback Setup
      // take function pointers to be used as callbacks when data changes
      void onAdded(int (*addedCallback)(string));
      void onRemoved(int (*removedCallback)(string));
      void onChanged(int (*changedCallback)(string));

      // Document Event Handlers
      // entry point for data changing in various ways -call the appropriate callbacks when things happen
      void addedDocument(string doc);
      void removedDocument(string doc);
      void changedDocument(string doc);

      // Connection Management
      // connect to a meteor server
      int connect(string uri);
};
