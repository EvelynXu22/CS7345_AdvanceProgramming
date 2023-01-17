#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <ctime>
#include <sstream>

#include "../../../../../../../../evelynxu/emsdk/upstream/emscripten/system/include/emscripten/websocket.h"

#include <assert.h>
#include <thread>

#include "json.hpp"
using namespace nlohmann;

std::string myName;

EMSCRIPTEN_WEBSOCKET_T socket;


static double data = 0;
void work(){
    while (data < 10000){
        data += 0.001;
    }
    std::string message = "Done";
    emscripten_websocket_send_utf8_text(socket, message.c_str());
    data = 0;

}


EM_BOOL WebSocketOpen(int eventType, const EmscriptenWebSocketOpenEvent *e, void *userData){

    emscripten_websocket_send_utf8_text(e->socket, "Start Working");
    std::cout << "Work?" << std::endl;
    work();
    
    return 0;

}



EM_BOOL WebSocketClose(int eventType, const EmscriptenWebSocketCloseEvent *e, void *userData){

	time_t t = time(nullptr);
	struct tm* now = localtime(&t);

    std::stringstream time;

    time << now->tm_hour << ":";
	time << now->tm_min << ":";
	time << now->tm_sec;

    std::cout << myName << " : " << "Disconnected" << " || " << time.str() << std::endl;
    return 0;
}

EM_BOOL WebSocketError(int eventType, const EmscriptenWebSocketErrorEvent *e, void *userData){

    return 0;
}

EM_BOOL WebSocketMessage(int eventType, const EmscriptenWebSocketMessageEvent *e, void *userData){

    if(e->isText){
        auto msg = json::parse(e->data);

        if(msg["type"] == "color"){
            myName = to_string(msg["data"]["author"]);
            std::cout << myName << " Connected." << std::endl;
        }
        else if (msg["type"] == "message"){
            std::cout << msg["data"]["author"] << " : " << msg["data"]["text"] << std::endl;
            if(msg["data"]["text"] == "Keep Working"){
                work();
            }
        }
        else{
            std::cout << "Something Wrong" << std::endl;
        }

    }

    return 0;

}



int main(){
    if(!emscripten_websocket_is_supported()){
        printf("Websocket are not supported, cannot continue\n");
        exit(1);
    }
    
    printf("Websockets are supported\n");
    EmscriptenWebSocketCreateAttributes attr;
    emscripten_websocket_init_create_attributes(&attr);

    const char *url = "ws://localhost:3000";
    attr.url = url;
    attr.protocols = "protocol1,protocol2";
    attr.createOnMainThread = false;

    socket = emscripten_websocket_new(&attr);

    if(socket <= 0){
        printf("WebSocket creation failed, error code %d\n", (EMSCRIPTEN_RESULT)socket);
        exit(1);
    }

    printf("Websockets are supported\n");
    emscripten_websocket_set_onopen_callback(socket, (void*)42, WebSocketOpen);
    emscripten_websocket_set_onclose_callback(socket, (void*)43, WebSocketClose);
    emscripten_websocket_set_onerror_callback(socket, (void*)44, WebSocketError);
    emscripten_websocket_set_onmessage_callback(socket, (void*)45, WebSocketMessage);


}