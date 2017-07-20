#ifndef __PARSE_H__
#define __PARSE_H__

#include <memory>
#include <functional>
class CalVisitor;
class Visitor;
enum class bin_op
{
	Plus = '+',
	Minus = '-',
	Multiplication = '*',
	Division = '/',
};

class Expr {
public:
	using Ptr = std::unique_ptr<Expr>;
	Expr() = default;

	virtual void accept(Visitor&) = 0;
	virtual ~Expr() = default;

};

class ExprOp : public Expr {
public:
	bin_op op;
	Expr::Ptr left;
	Expr::Ptr right;
	void accept(Visitor& vp) override;
	explicit ExprOp(bin_op _op, Expr::Ptr _left, Expr::Ptr _right)
		:op(_op), left(std::move(_left)), right(std::move(_right)) {}
};

class ExprNum : public Expr {
public:
	int num;
	void accept(Visitor& vp) override;
	explicit ExprNum(int _num) :num(_num) {};
};

class ParseTree {
	Expr::Ptr getNumber(const char*& _stream);
	Expr::Ptr getTerm(const char*& _stream);
	Expr::Ptr getFactor(const char*& _stream);
	Expr::Ptr getExpress(const char*& _stream);
	bool is(const char*& _stream, const char* _text);

	Expr::Ptr root;
public:
	explicit ParseTree()
		:root(nullptr) {}
	explicit ParseTree(const char* _stream)
		:root(getExpress(_stream)) {}

	void parse(const char* _stream);
	int getEval();
};

#endif /* ifndef __PARSE_H__ */
