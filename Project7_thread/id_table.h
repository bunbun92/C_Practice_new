#ifndef id_table_h__
#define id_table_h__

class IdTable {
	vector<char*> _tbl[0x1000];
	int _key(char* id) {
		int s=0;
		for (char* p=id; *p; p++)
			s= s*10+ *p;
		return s&0xfff;
	}
public:
	~IdTable() {
		for (int i=0; i<0x1000; i++) {
			vector<char*>& T= _tbl[i];
			for (char* t : T)
				_Delete(t);
			T.clear();
		}
	}
	void add(char* id) {		
		
		_tbl[_key(id)].push_back(strdup(id));		
		
	}
	bool has(char* id) {
		vector<char*>& T= _tbl[_key(id)];
		for (char* t : T) {
			if (!strcmp(t, id))
				return 1;
		}
		return 0;
	}
	void cout() {
		for (int i=0; i<0x1000; i++)
			COUT("%d", _tbl[i].size());
	}

	int size(){
		int totalSize = 0;
		for (int i = 0; i < 0x1000; i++) {
			totalSize += _tbl[i].size();
		}

		return totalSize;
	}

};

#endif // id_table_h__
