client.c -> Proces1
<<<<<<< HEAD
app_client -> Proces2
app_server -> Proces3

Kompilacja:
make
gcc -O2 -Wall -c client.c
gcc -s client.c -o client

Uruchomienie:
Na trzech osobnych terminalach:
Terminal 1:
./app_server 127.0.0.1
Terminal 2:
./app_client 127.0.0.1
Terminal 3:
./client
=======
app_client.c -> Proces2
app_server.c -> Proces3
>>>>>>> 6aa215f7aa6d727b317ee4ea919c8a4553746553
