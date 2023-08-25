class ServerThread : public Thread{
	Sock s;
	char** argv;

	int thr(){				

		RIF(s.open(3333));
		while (1){
			Sock con = s.listen();
			if (con.isSock()){
				/*new Session(con);*/				
				SessionThread0* sThr = new SessionThread0;
				sThr->init(&con, argv);
				sThr->start();
			}
		}
	}
public:

	void init(char** argv){
		this->argv = argv;
	}

};