
IDIR=INC/
SDIR=SRC/
ODIR=OBJ/
CC:=gcc
NAME:=
CFLAGS:= -lGL -lGLU -lglut -lpthread -lm
CCIN= -c $(SDIR)*.c -I$(IDIR) 

.PHONY:usage
usage :
	@echo "USAGE : test : to create and start a computer vs computer 2 player game"
	@echo "USAGE : test2 : to create and start a computer vs computer 4 player game"
	@echo "USAGE : game : to create a game code"

.PHONY : game
game:
	make compile
	$(CC) -o carrom *.o $(CFLAGS)
	rm -f *.o 
	@echo "GAME USAGE : ./carrom (PLAYERNO) (PORTNO) (GAMETYPE) (AI1) (AI2) (AI3) (AI4)"
	@echo "AI ==0 -noai  1-easy 2-medium 3-hard 4-extreme"
	@echo "PLAYERNO AS PER U WANT TO JOIN"	

.PHONY:test
test :
	make compile
	$(CC) -o test *.o $(CFLAGS)
	rm -f *.o 
	./test 0 10000 1 4 4 4 4

.PHONY:test2
test2 :
	make compile
	$(CC) -o test *.o $(CFLAGS)
	rm -f *.o 
	./test 0 10000 2 4 4 4 4

.PHONY :compile
compile :
	$(CC) $(CCIN)
	rm -f gamequeue.o
	rm -f opengltest4.o
	rm -f physicthread.o
	
