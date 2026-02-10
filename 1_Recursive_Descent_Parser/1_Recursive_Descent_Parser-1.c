// 20201590 송준규 // Calculate_Expression.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA_LEN 64 // char array

typedef enum _token { // 토큰의 종류 
	_NULL, NUMBER, PLUS, STAR, HYPHEN, SLASH, DOT, LP, RP, END
} token;

typedef enum _kind { INT, FLT } kind; // 숫자의 종류

typedef struct _number_type { // 
	kind t; // 정수(0) or 실수(1)
	union { int i; float f; }val;
} number_type;

typedef struct _number_data {
	size_t data_len;
	char data_current;
	char data[MAX_DATA_LEN];
	kind t;
	int dot;
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

char warning_Buff[BUFSIZ] = {""}; //for warning
int token_cnt=0;
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
	nData->data_current = 0;
	nData->t = INT;
	nData->dot=0;
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
	while ((ch = getchar()) == ' ' || ch == '\t') { token_cnt++; } // for warning or error
	switch (ch) {
	case '+': new_token = PLUS; break;
	case '*': new_token = STAR; break;
	case '-': new_token = HYPHEN; break;
	case '/': new_token = SLASH; break;
	case '(': new_token = LP; break;
	case ')': new_token = RP; break;
	case '.': new_token = DOT; new_number.data_current = ch; new_number.t = FLT; new_number.dot++; break;
	case '\n': new_token = END; break;
	case EOF: new_token = END; break;
	default:
		if (ch >= '0' && ch <= '9') {
			new_token = NUMBER;
			new_number.data_current = ch;
			break;
		}
		else
			error("get_token error");
	}
}
number_type expression() {
	number_type ret = term();
	while (new_token == PLUS || new_token == HYPHEN) {
		token old_token = new_token;
		get_token();
		if (old_token == PLUS)
			ret = number_add(ret, term());
		else if (old_token == HYPHEN)
			ret = number_sub(ret, term());
	}
	return (ret);
}
number_type term() {
	number_type ret = factor();
	while (new_token == STAR || new_token == SLASH) {
		token old_token = new_token;
		get_token();
		if (old_token == STAR)
			ret = number_mul(ret, factor());
		else if (old_token == SLASH)
			ret = number_div(ret, factor());
	}
	return (ret);
};
number_type factor() {
	number_type ret;
	if (new_token == NUMBER) {
		number_type num_ret = number();
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
	do {
		number_data_push(&new_number, new_number.data_current);
		get_token();
	} while (new_token == NUMBER || new_token == DOT);
	if (new_number.dot>=2)
		error("more than one Dot in one flt");
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
	for (int i = 0; i < token_cnt-1; i++) {
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
