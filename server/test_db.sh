#!/bin/bash

g++ -I/usr/include/mysql/mysql -L/usr/lib/mysql test_db.cpp dbconnect.cpp -lmysqlclient -o test_db
