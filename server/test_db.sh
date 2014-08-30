#!/bin/bash

g++ -I/usr/include/mysql/mysql -L/usr/lib/mysql test_db.cpp dbconnect.cpp tools.c cJSON.c message.cpp -lmysqlclient -o test_db -g 
