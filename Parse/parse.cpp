#include "parse.h"
#include "visitor.h"
#include "exception.h"
#include <cassert>
#include <cstdio>
#include <cstring>
void ExprNum::accept(Visitor& vi) {
	vi.visit(*this);
}

void ExprOp::accept(Visitor& vi) {
	vi.visit(*this);
}

bool ParseTree::is(const char*& _stream, const char* _text) {
	auto len = strlen(_text);
	const char* read = _stream;
	while (*read == ' ') read++;
	if (strncmp(read, _text, len) == 0) {
		_stream = read + len;
		return true;
	}
	return false;
}

Expr::Ptr ParseTree::getNumber(const char*& _stream) {
	const char* read = _stream;
	while (*read == ' ') read++;
	int num = 0;
	bool got = false;
	while (true) {
		char ch = *read;
		if (ch >= '0'&&ch <= '9') {
			num = num * 10 + ch - '0';
			got = true;
			read++;
		}
		else break;
	}
	if (got) {
		_stream = read;
		return std::make_unique<ExprNum>(num);
	}
	throw StrException(_stream, "need expression");
}

Expr::Ptr ParseTree::getTerm(const char*& _stream) {
	try {
		return getNumber(_stream);
	}
	catch (StrException& e) {
		const char* read = _stream;
		if (is(read, "(")) {
			auto tmpExpr = getExpress(read);
			if (is(read, ")")) {
				_stream = read;
				return tmpExpr;
			}
			else throw StrException(_stream, "need right bracket");
		}
		else throw e;
	}
}

Expr::Ptr ParseTree::getFactor(const char*& _stream) {
	const char* read = _stream;
	auto factor = getTerm(read);
	while (true) {
		bin_op op;
		if (is(read, "*")) op = bin_op::Multiplication;
		else if (is(read, "/")) op = bin_op::Division;
		else break;
		factor = std::make_unique<ExprOp>(op, std::move(factor), getTerm(read));
	}
	_stream = read;
	return factor;
}

Expr::Ptr ParseTree::getExpress(const char*& _stream) {
	const char* read = _stream;
	auto expression = getFactor(read);
	while (true) {
		bin_op op;
		if (is(read, "+")) op = bin_op::Plus;
		else if (is(read, "-")) op = bin_op::Minus;
		else break;
		expression = std::make_unique<ExprOp>(op, std::move(expression), getFactor(read));
	}
	_stream = read;
	return expression;
}

int ParseTree::getEval() {
	assert(root != nullptr);
	CalVisitor visitor;
	root->accept(visitor);
	return visitor.getRes();
}

void ParseTree::parse(const char* expr) {
	root = getExpress(expr);
}
