class ImgProcThread : public Thread{	
	
	FileList* f;	

	int thr(){
		printf("start\n");

		GdiPlusInit();

		char* src;
		char* dst;

		while(true){

			if (is_img(src)) {
				GrayImg g(src);
				CIF(g.is_open());
				/*ImgProc::process(g, args);*/
				CIF(g.save(dst));
				g.free();
			}

		}
		

		printf("done\n");
		Thread::thr();

		return 0;
	}

	bool is_img(char* path) {
		char* ext= getExtension(path);
		return !_stricmp(ext, "bmp") || !_stricmp(ext, "jpg") || !_stricmp(ext, "png");
	}

public:	

	void init(FileList* f){
		this->f = f;
	}


};