#!/bin/bash

g++ -o server server.cpp online_client.cpp msghandler.cpp message.cpp client_info.cpp cJSON.c dbconnect.cpp tools.c -I/usr/include/mysql/mysql -L/usr/lib/mysql -lmysqlclient

