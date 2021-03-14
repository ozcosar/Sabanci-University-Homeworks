
/*Begin : taken from DynIntStack.h and updated*/
struct StackNode
{
	int row, col;
	StackNode *next;
};

class DynStack
{
private:
	StackNode *top;

public:
	DynStack(void);
	void push(int,int);
	void pop(int &, int &);
	bool isEmpty(void);
};
/*End : taken from DynIntStack.h and updated*/