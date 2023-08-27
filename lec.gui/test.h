typedef struct Data{
	int ID;
	char* str;
	bool flag= 1;
	int ts;
} Data ;


class TEST : public Thread{	
#define MSGPCS 18

public:
	vector<Data> msgList;
	int curIdx;
	int myID;

	TEST(){
#define MSGSIZE 40
		Data* msg = new Data[MSGSIZE];
		int msgSize = MSGSIZE;
		for (int i = 0; i < msgSize; i++){
			msg[i].ID = i;
			msg[i].str = new char[64];
			msg[i].str = "abcdef";
			msg[i].flag = 1;
			msg[i].ts = 1000 + i;
		}

		msg[31].str = "�ȳ��ϼ���";
		msg[31].flag = 0;
		msg[31].ID = 333;

		msg[34].str = "�׽�Ʈ�޽���";
		msg[34].flag = 0;
		msg[34].ID = 333;

		msg[36].str = "�ָ��� ����ͳ׿�";
		msg[36].flag = 0;
		msg[36].ID = 333;

		msg[37].str = "���Ͽ��� �ϲ������ϴµ�";
		msg[37].flag = 0;
		msg[37].ID = 333;

		msg[25].str = "��";
		msg[25].flag = 0;
		msg[25].ID = 333;

		msg[20].str = "��󸮾ⷪ";
		msg[20].flag = 0;
		msg[20].ID = 333;

		msg[17].str = "�߳�����";
		msg[17].flag = 0;
		msg[17].ID = 333;

		msg[13].str = "������";
		msg[13].flag = 0;
		msg[13].ID = 333;

		for (int i = 0; i < 40; i++)
			msgList.push_back(msg[i]);

		curIdx = msgList.size() - MSGPCS;
		myID = 333;
	}
	~TEST(){
		//delete
	}
	void init(){	
	}

	void operate(int idx){
		int size = msgList.size();
		curIdx += idx;

		if (curIdx > size - MSGPCS)
			curIdx = size - MSGPCS;
		else if (curIdx < 0)
			curIdx = 0;
	}

	void pushMsg(char* txt){
		Data* msg = new Data;
		msg->ID = myID;
//		msg->flag = 1;
		msg->ts = 10000;		
		msg->str = strdup(txt);
		msgList.push_back(*msg);
	}
	
};