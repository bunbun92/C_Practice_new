#define HEADER1 1; //1 폴링
#define HEADER2 2; //2 현재 연결된 클라 고유 ID
#define HEADER3 3; //3 ID와 메세지
#define HEADER4 4; //4 참가자 ID 배열
/*#define IP "125.132.166.81"*/
#define IP "172.30.1.38"
#define PORT 3333
#include <stddef.h>

class SocketThread : public Thread{
	Sock sock;	
	Mutex m;
	SyncQueue<Data*>* q; // 멤버변수에서 뺴기

	int thr(){
		printf("connecting..\n");
		if (sock.open(IP, PORT))
			printf("connected\n");
		else{
			printf("connecting failed\n");
			return thr();			
		}

		int myID;
		sock.read(&myID, 4);
		WriteThread(&sock, q, &m, myID);
		
		
		while(1){			
			run();					
			Sleep(100);
		}

		sock.close();
	}



	bool run(){
		polling();
		uint8 h;		
		sock.read(&h, 1);		
		switch (h)
		{
		case 0:
			return 0;
// 		case 1:
// 			polling();
// 			break;
// 		case 2:
// 			setMyID();
// 			break;
		case 3:
			printMsg();
			break;
// 		case 4:
// 			printMembers();
// 			break;
		}
		return 1;
	}

// 	void polling(){
// 		bool h = HEADER1;
// 		sock.write(&h, 1);		
// 	}


// 	void setMyID(){
// 		sock.read(&myID, 4);
// 	}

	bool printMsg(){
		int myID;		
		sock.read(&myID, 4);	
		int ID;
		sock.read(&ID, 4);
		char msg[1024];		
		sock.readStr(msg);
		if (this->myID == myID)
			printf("%d님의 말 (본인) : %s\n", ID, msg);
		else
			printf("%d님의 말 : %s\n", ID, msg);		
		return 1;
	}

	void printMembers(){
		int l;
		sock.read(&l, 4);
		int arrLen = (int)(l *0.25);
		int* arr = new int[arrLen];
		sock.read(arr, l);
		printf("내 ID = %d\n", myID);
		printf("참여자 ID 목록 \n");
		for (int i= 0; i < arrLen; i++)
			printf("%d ", arr[i]);
		puts("");
	}

public:
	SocketThread(SyncQueue<Data*>* q){		
		this->q = q;
		start();
	}
};