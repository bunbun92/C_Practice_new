template<class T>
class SyncQueue {
	Mutex m;
	deque <T> q;
public:

	void push(T){
		m.lock();
		q.push_back(T);
		m.unlock();
	}

	T pop(){
		m.lock();
		while(1){
			if (q.empty()){
				m.unlock();
				Sleep(10);
				m.lock();
				continue;
			}

			T v = q.front();

			if(v == 0){
				m.unlock();
				break;
			}
			q.pop_front();
			m.unlock();
			return v;
		}
		return 0;
	}
	

};