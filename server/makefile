test_db: dbconnect.o test_db.o
	g++ -o test_db dbconnect.o test_db.o -I/usr/include/mysql -L/usr/lib/mysql
dbconnect.o: dbconnect.cpp
	g++ -c dbconnect.cpp
test_db: test_db.cpp
	g++ -c test_db.cpp
