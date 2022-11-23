CC = gcc
CFLAGS = -Wall 
DEPS = linked_list_hospital.h patient.h 
OBJ = emergencyRoomMain.o linked_list_hospital.o patient.o

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o

emergencyRoomMain.o : emergencyRoomMain.c linked_list_hospital.h patient.h
linked_list_hospital.o: linked_list_hospital.h patient.h
patient.o: patient.h