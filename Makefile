all:main

main:
	g++ .\main.cpp .\station.cpp -o main.exe
clean:
	rm -f .\main.exe .\process_info.ini