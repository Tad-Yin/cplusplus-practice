#ifndef __VISITOR_H__
#define __VISITOR_H__

#include <stack>
#include "parse.h"
class Expr;
class ExprOp;
class ExprNum;
enum class bin_op;
class Visitor {
public:
	virtual void visit(ExprOp& _op) = 0;
	virtual void visit(ExprNum& _num) = 0;

protected:
	virtual ~Visitor() = default;
};

class CalVisitor :public Visitor {
private:
	int res;
	inline int call(Expr& node) {
		node.accept(*this);
		return res;
	}
	std::function<int(int, int)> getFunc(bin_op op);
public:
	inline void visit(ExprOp& _op) override{
		res = getFunc(_op.op)(call(*_op.left), call(*_op.right));
	}
	inline void visit(ExprNum& _num) override {
		res = _num.num;
	}
	int getRes() {
		return res;
	}
};

#endif /* ifndef __VISITOR_H__ */
