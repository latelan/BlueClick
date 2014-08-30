#!/bin/bash

g++ -o server server.cpp message.cpp client_info.cpp cJSON.c dbconnect.cpp -I/usr/include/mysql/mysql -L/usr/lib/mysql -lmysqlclient
