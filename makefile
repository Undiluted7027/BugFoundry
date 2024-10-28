SYSTEM: Main.o, Change.o Complaint.o Customer.o Exception.o Global.o Product.o ScenarioControl.o UI.o
	g++ -Wall Main.o, Change.o Complaint.o Customer.o Exception.o Global.o Product.o ScenarioControl.o UI.o -o SYSTEM

TEST: Test.o Change.o Complaint.o Customer.o Exception.o Global.o Product.o
	g++ -Wall Test.o Change.o Complaint.o Customer.o Exception.o Global.o Product.o -o TEST

Test.o: Test.cpp
	g++ -Wall -c Test.cpp

Main.o: Main.cpp
	g++ -Wall -c Main.cpp

Change.o: Change.hpp Change.cpp
	g++ -Wall -c Change.cpp

Complaint.o: Complaint.hpp Complaint.cpp
	g++ -Wall -c Complaint.cpp

Customer.o: Customer.hpp Customer.cpp
	g++ -Wall -c Customer.cpp

Exception.o: Exception.hpp
	g++ -Wall -c Exception.hpp

Global.o: Global.hpp Global.cpp
	g++ -Wall -c Global.cpp

Product.o: Product.hpp Product.cpp
	g++ -Wall -c Product.cpp

ScenarioControl.o: ScenarioControl.hpp ScenarioControl.cpp
	g++ -Wall -c ScenarioControl.cpp

UI.o: UI.hpp UI.cpp
	g++ -Wall -c UI.cpp