// 20201590 송준규 // Assignment-1A.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_DATA_LEN 64 // char array
typedef enum _token { // 토큰의 종류 
	_NULL, NUMBER, PLUS, STAR, HYPHEN, SLASH, LP, RP, END
} token;
typedef enum _kind { INT, FLT } kind; // 숫자의 종류
typedef struct _number_type {
	kind t; // 정수(0) or 실수(1)
	union { int i; float f; }val;
} number_type;
typedef struct _number_data {
	size_t data_len;
	char data[MAX_DATA_LEN];
	kind t;
} number_data;
// Declaration
number_type number_add(number_type n1, number_type n2);
number_type number_sub(number_type n1, number_type n2);
number_type number_mul(number_type n1, number_type n2);
number_type number_div(number_type n1, number_type n2);
number_type number_eval(number_data* nData);
void number_data_init(number_data* nData);
void number_data_push(number_data* nData, char ch);
void number_print(number_type* ret);
void get_token();
number_type expression();
number_type term();
number_type factor();
number_type number();
void error(char* message);
void warning(char* code);
char warning_Buff[BUFSIZ] = { "" }; //for warning
int token_cnt = 0;
token new_token; // 매번 사용할 token 변수
number_data new_number; // 매번 사용할 number 변수
// Definition
number_type number_add(number_type n1, number_type n2) {
	number_type ret;
	if (n1.t == INT && n2.t == INT) {
		ret.t = INT;
		ret.val.i = n1.val.i + n2.val.i;
	}
	else {
		ret.t = FLT;
		if (n1.t == FLT) {
			if (n2.t == FLT)
				ret.val.f = n1.val.f + n2.val.f;
			else if (n2.t == INT) {
				warning("C4244");
				ret.val.f = n1.val.f + (float)n2.val.i;
			}
		}
		else if (n1.t == INT && n2.t == FLT) {
			warning("C4244");
			ret.val.f = (float)n1.val.i + n2.val.f;
		}
		else
			error("number_add error");
	}
	return ret;
}
number_type number_sub(number_type n1, number_type n2) {
	number_type ret;
	if (n1.t == INT && n2.t == INT) {
		ret.t = INT;
		ret.val.i = n1.val.i - n2.val.i;
	}
	else {
		ret.t = FLT;
		if (n1.t == FLT) {
			if (n2.t == FLT)
				ret.val.f = n1.val.f - n2.val.f;
			else if (n2.t == INT) {
				warning("C4244");
				ret.val.f = n1.val.f - (float)n2.val.i;
			}
		}
		else if (n1.t == INT && n2.t == FLT) {
			warning("C4244");
			ret.val.f = (float)n1.val.i - n2.val.f;
		}
		else
			error("number_sub error");
	}
	return ret;
}
number_type number_mul(number_type n1, number_type n2) {
	number_type ret;
	if (n1.t == INT && n2.t == INT) {
		ret.t = INT;
		ret.val.i = n1.val.i * n2.val.i;
	}
	else {
		ret.t = FLT;
		if (n1.t == FLT) {

			if (n2.t == FLT)
				ret.val.f = n1.val.f * n2.val.f;
			else if (n2.t == INT) {
				warning("C4244");
				ret.val.f = n1.val.f * (float)n2.val.i;
			}
		}
		else if (n1.t == INT && n2.t == FLT) {
			warning("C4244");
			ret.val.f = (float)n1.val.i * n2.val.f;
		}
		else
			error("number_mul error");
	}
	return ret;
}
number_type number_div(number_type n1, number_type n2) {
	number_type ret;
	if (n2.val.i == 0 && n2.val.f == 0) error("number_div error; divide by 0");
	if (n1.t == INT && n2.t == INT) {
		ret.t = INT;
		ret.val.i = n1.val.i / n2.val.i;
	}
	else {
		ret.t = FLT;
		if (n1.t == FLT) {

			if (n2.t == FLT)
				ret.val.f = n1.val.f / n2.val.f;
			else if (n2.t == INT) {
				warning("C4244");
				ret.val.f = n1.val.f / (float)n2.val.i;
			}
		}
		else if (n1.t == INT && n2.t == FLT) {
			warning("C4244");
			ret.val.f = (float)n1.val.i / n2.val.f;
		}
		else
			error("number_div error");
	}
	return ret;
}
number_type number_eval(number_data* nData) {
	number_type ret;
	if (nData->t == INT) {
		ret.t = INT;
		ret.val.i = atoi(nData->data);
		return ret;
	}
	else if (nData->t == FLT) {
		ret.t = FLT;
		ret.val.f = atof(nData->data);
		return ret;
	}
	else
		error("number eval error");
}
void number_data_init(number_data* nData) {
	nData->data_len = 0;
	nData->t = INT;
	memset(nData->data, 0, MAX_DATA_LEN);
};
void number_data_push(number_data* nData, char ch) {
	nData->data[nData->data_len++] = ch;
};
void number_print(number_type* ret) {
	if (ret->t == INT) {
		printf("%d", ret->val.i);
		return;
	}
	else if (ret->t == FLT) {
		printf("%f", ret->val.f);
		return;
	}
	else
		error("number print error");
};
void get_token() {
	token_cnt++; // for warning or error
	static char ch = ' ';
	while (ch == ' ' || ch == '\t') { ch = getchar(); token_cnt++; }
	int dot = 0;
	if (isdigit(ch) || ch == '.') {
		while (isdigit(ch) || ch == '.') {
			if (ch == '.') {
				dot++;
				if (dot >= 2)
					error("more than one . in one flt");
				new_number.t = FLT;
			}
			number_data_push(&new_number, ch);
			ch = getchar();
		}
		new_token = NUMBER;
	}
	else if (ch == '+') { ch = getchar(); new_token = PLUS; }
	else if (ch == '*') { ch = getchar(); new_token = STAR; }
	else if (ch == '-') { ch = getchar(); new_token = HYPHEN; }
	else if (ch == '/') { ch = getchar(); new_token = SLASH; }
	else if (ch == '(') { ch = getchar(); new_token = LP; }
	else if (ch == ')') { ch = getchar(); new_token = RP; }
	else if (ch == '\n' || ch == EOF) { new_token = END; }
	else
		error("get_token error");
}
number_type expression() {
	number_type ret = term();
	while (new_token == PLUS || new_token == HYPHEN) {
		if (new_token == PLUS) {
			get_token();
			ret = number_add(ret, term());
		}
		else if (new_token == HYPHEN) {
			get_token();
			ret = number_sub(ret, term());
		}
		else error("expression error");
	}
	return (ret);
}
number_type term() {
	number_type ret = factor();
	while (new_token == STAR || new_token == SLASH) {
		if (new_token == STAR) {
			get_token();
			ret = number_mul(ret, factor());
		}
		else if (new_token == SLASH) {
			get_token();
			ret = number_div(ret, factor());
		}
		else error("term error");
	}
	return (ret);
};
number_type factor() {
	number_type ret;
	if (new_token == NUMBER) {
		number_type num_ret = number();
		get_token();
		return num_ret;
	}
	else if (new_token == LP) {
		get_token();
		ret = expression();
		if (new_token == RP) {
			get_token();
			return ret;
		}
		else
			error("factor error");
	}
	else
		error("factor error; Syntax error");
};
number_type number() {
	number_type ret = number_eval(&new_number);
	number_data_init(&new_number);
	return ret;
}
void main() {
	printf("[Calcualte_Expression_20201590]\n");
	number_data_init(&new_number);
	get_token();
	number_type result = expression();
	if (new_token != END)
		error("expression end wrong");
	else {
		printf("%s", warning_Buff);
		printf("Result: ");
		number_print(&result);
	}
	return;
}
void error(char* message) {
	for (int i = 0; i < token_cnt - 1; i++) {
		printf(" ");
	}
	printf("^\n");
	fprintf(stderr, "%d: %s", token_cnt, message);
	exit(1);
}
void warning(char* code) {
	if (code == "C4244")
		strcat(warning_Buff, "warning C4244 : conversion, possible loss of data\n");
}
