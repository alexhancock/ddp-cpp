# ddp-cpp

A C++ utility for speaking [DDP](https://github.com/meteor/meteor/blob/master/packages/livedata/DDP.md) to `Meteor` servers over a websocket.

## status
* Connects to a meteor server over a websocket and sets up initial collection subscription
* Very much a work in progress - not ready for any kind of public usage yet

## deps
* [boost](http://www.boost.org/) (`system` and `random` libs)
* [websocketcpp](https://github.com/zaphoyd/websocketpp)

## goals
My motivation for writing this is to make a utility for talking to Meteor servers, and expose data sourced from [Meteor.Collections](http://docs.meteor.com/#collections) in an easy to consume way on the C++ side.

As an initial application, I will be using this as a way to provide realtime data to OpenGL/C++ based visualizations. I don't know a lot of C++ yet, so I am learning as I go.

## todos
* Decide on a good C++ utility for serializing and deserializing JSON.
* Package this as a library, and expose a useful API