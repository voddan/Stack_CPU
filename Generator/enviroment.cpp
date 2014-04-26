#include <cstdio>
//-----------------------------------------------------
class Obj {
	public:
		Obj(int x): value(x) {}
		static int state;
		
		void dump();
		
		static void execute();
	private:
		int value;
};

int Obj::state = 0;

Obj* obj;
Obj head(0);
//-----------------------------------------------------
extern "C"
void Obj::dump() {
	printf("tdump_obj\n");
	printf("state: %d\n", Obj::state);
	printf("value: %d\n", obj->value);
}

extern "C"
void init_obj() {
	printf("init_obj\n");
	obj = new Obj(239);
	Obj::state = 45;
}

extern "C"
void del_obj() {
	printf("del_obj\n");
	delete obj;
	Obj::state = -13;
}

extern "C"
void Obj::execute() {
	printf("execute\n");
}



