class ImgThread: public Thread{
	vector<char*> q;	
	char** argv;

	int thr(){
		printf("thr start \n");
		for (int i= 0; i < q.size(); i++){
			GrayImg g(q.at(i));
			g.operate(argv);
			char* fn= fileName(q.at(i));
			char dst[64];
			sprintf(dst, "%s/%s", argv[2], fn);
			CIF(g.save(dst));
			g.free();
		}
		printf("thr done \n");
		Thread::thr();
		return 0;
	}

public:

	void init(char** argv){
		this->q = q;
		this->argv = argv;
	}
	void add(char* src) {
		q.push_back(src);
	}
};