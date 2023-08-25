#ifndef flist_h__
#define flist_h__

class FileList {
	vector<char*> F;
	bool bSub;
public:
	FileList() : bSub(1) {}
	FileList(char* path, char* ext=0, bool sub=1) { bSub=sub; search(path, ext); }
	~FileList() { clear(); }

	bool search(char* path, char* ext) {
		WIN32_FIND_DATA fd ={0};
		char tmp[512];
		sprintf(tmp, "%s\\*", path);
		HANDLE h = FindFirstFile(tmp, &fd);
		if (h==INVALID_HANDLE_VALUE)
			return 0;
		do {
			if (!strcmp(fd.cFileName, "..") || !strcmp(fd.cFileName, "."))
				continue;
			char buf[512];
			sprintf(buf, "%s/%s", path, fd.cFileName);
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				if (bSub)
					search(buf, ext);
			}
			else if (!ext || !strcmp(getExtension(buf), ext))
				F.push_back(strdup(buf));
		} while (FindNextFile(h, &fd));
		FindClose(h);
		return 1;
	}
	int size() { return F.size(); }
	char* at(int i) { return F[i]; }
	void clear() {
		for (char* f : F)
			_Delete(f);
		F.clear();
	}
	static void clear_dir(char* dir) {
		FileList fl(dir);
		for (int i=0; i<fl.size(); i++)
			::remove(fl.at(i));
	}
};

#endif // flist_h__


