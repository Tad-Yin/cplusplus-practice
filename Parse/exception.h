#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__

struct StrException {
	StrException(const char* _aText, const char* _aError)
		:aText(_aText),aError(_aError) {}
	const char* aText;
    const char* aError;
};

#endif /* ifndef __EXCEPTION_H__ */
