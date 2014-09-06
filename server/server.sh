#!/bin/bash

g++ -o server loadbalance.cpp server.cpp online_client.cpp msghandler.cpp message.cpp client_info.cpp cJSON.cpp dbconnect.cpp tools.cpp -I/usr/include/mysql/mysql -L/usr/lib/mysql -lmysqlclient

