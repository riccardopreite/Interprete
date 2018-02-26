//ARCH1718.riccardo.preite.0000839635

#include <stdio.h>
#include <stdlib.h>


//Prototipi funzioni

int length(char *);
void set(char *, char *);
void setN(char *, char *, int);
_Bool equals(char *, char* );
char* indexOf(char *, char );
char* indexOfReverse(char *, char ) ;
_Bool contains(char *, char );
void concat(char *, char *);
void removeChar(char *, char );
char intToChr(int );
int chrToInt(char );
char* intToStr(int , char *);
int strToInt(char *);
int stringSpan(char *, char *, _Bool );
void stringSplit(char *, char *, char *);
_Bool strEndsWith(char *, char *);
_Bool retFlag(_Bool* );
_Bool flag(char *) ;
void getAsmFileName(char *, char *);
void setVmFileName(char *);
void split(char *, char *);
void getSp();
void incSp();
void decSp();
int pointerPos(char *);
int tempPos(char *);
void popWrite(char );
void pushWrite(char );
void evaluateCondition(char* );
char* getAsmLabel(char *, char *);
void staticLabel(_Bool , char *);
void getPos(char *, char *, char );
void swapAD() ;
void standardPos(_Bool , int );
void calculatePos(_Bool , char *, char *);
void stack(_Bool , char *);
void pop1Operation(char ) ;
void pop2Operation(char );
void arithmeticCondition(char* );
void writeArithmetic(char* );
void computeArithmetic(char* );
void label(char *);
void gotoInst(char *);
void ifgoto(char *);
void function(char *);
void restoreValue(char *);
void rtrn();
void pushValue(char *);
void calcArg(int );
void call(char *);
void initVm();
void computeInstructions(FILE *, char *);
_Bool 	add = 0, sub = 0,
and = 0, or = 0,
not = 0, neg = 0,
eq = 0, gt = 0, lt = 0,
retrn = 0;

const int pnt = 3;
const int tmp = 5;

FILE* vm;
FILE* asmFile;

char inputArgument[300];
char vmName[300];
char asmFileName[300];

int c = 0;

#if 0

Main

#endif


int main(int argc, char *argv[]) {
	#if 0
	controllo argomenti in input
	#endif
	if (argc < 2) {
		printf("Non hai inserito il vile VM!\n");
		return 1;
	}

	if (argc > 2) {
		printf("Hai inserito troppi argomenti!\n");
		return 1;
	}

	set(inputArgument, argv[1]);

	char  fileName[1000];
	set(fileName, inputArgument);
	getAsmFileName(asmFileName, fileName);
	vm=fopen(inputArgument,"r");
	asmFile=fopen(asmFileName,"w");
	initVm();
	computeInstructions(vm, fileName);

	#if 0
	fine programma e chiusura file
	#endif
	if (vm != NULL) fclose(vm);
	if (asmFile != NULL) fclose(asmFile);

	return 0;
}

#if 0

End Main

#endif

//Corpo funzioni
int length(char *s) {
	int l = 0;

	if (s == NULL) return 0;

	while (s[l++] != '\0');

	return l-1;
}

void set(char *dest, char *from) {
	if (from == NULL) {
		dest = NULL;
		return;
	}

	int i;
	for (i = 0; i < length(from); ++i) {
		dest[i] = from[i];
	}
	dest[i] = '\0';
}

void setN(char *dest, char *from, int l) {
	set(dest, from);
	dest[l] = '\0';
}

_Bool equals(char *s1, char* s2) {
	if (s1 == NULL && s2 == NULL) return 1;

	if (length(s1) != length(s2)) return 0;

	int i;
	for (i = 0; i <= length(s1); ++i) {
		if (s1[i] != s2[i]) {
			return 0;
		}
	}

	return 1;
}

char* indexOf(char *s, char c) {
	if (s == NULL) return NULL;

	char *cpS = s;
	while (*cpS != '\0') {
		if (*cpS == c) {
			return cpS;
		}
		++cpS;
	}

	return NULL;
}

char* indexOfReverse(char *s, char c) {
	if (s == NULL) return NULL;

	int i = length(s) - 1;
	char *cpS = s + i;

	while (i >= 0) {
		if (*cpS == c) {
			return cpS;
		}
		--cpS;
		--i;
	}

	return s;
}

_Bool contains(char *s, char c) {
	return (indexOf(s, c) != NULL);
}

void concat(char *s1, char *s2) {
	if (s2 == NULL) {
		return;
	}

	char sCp[300];
	set(sCp, s2);

	set(s1 + length(s1), sCp);
}

void removeChar(char *s, char c) {
	char *i = s;
	char *j = s;

	while(*j != '\0') {
		*i = *j++;
		if(*i != c) {
			i++;
		}
	}

	*i = '\0';
}

char intToChr(int value) {
	return '0' + value;
}

int chrToInt(char value) {
	return value - '0';
}

char* intToStr(int value, char *s) {
	char buf[300];
	char* dest = buf + 300;

	if (value == 0) {
		set(s, "0");
		return s;
	}

	*--dest = '\0';

	while (value != 0) {
		*--dest = intToChr(value % 10);
		value /= 10;
	}

	set(s, dest);
	return s;
}

int strToInt(char *s) {
	int n = 0;

	int i;
	for (i = 0; s[i] != '\0'; ++i) {
		n *= 10;
		n += chrToInt(s[i]);
	}

	return n;
}

int stringSpan(char *s, char *del, _Bool in) {
	if (s == NULL || del == NULL) {
		return -1;
	}

	int i = 0;

	while (s[i] != '\0') {
		int j;
		_Bool found = 0;
		for (j = 0; j < length(del); ++j) {
			if (s[i] == del[j]) {
				found = 1;
				break;
			}
		}

		if (in ? !found : found) {
			break;
		}

		++i;
	}

	return i;
}

void stringSplit(char *s, char *del, char *split) {
	if (s == NULL) {
		set(split, "");
		return;
	}

	set(s, s + stringSpan(s, del, 1));
	set(split, s);

	int l = stringSpan(split, del, 0);
	set(s, s + l);

	if (*(split+l) != '\0') {
		set(s, ++s);
		*(split+l) = '\0';
	}
}

_Bool strEndsWith(char *s, char *end) {
	if (s == NULL) return 0;
	if (end == NULL) return 1;
	if (length(s) < length(end)) return 0;

	char sCp[300];
	set(sCp, s+length(s)-length(end));

	return equals(sCp, end);
}
_Bool retFlag(_Bool* flag) {
	return *flag == 0 ? (*flag)++ : *flag;
}

_Bool flag(char *f) {
	if (equals(f, "add")) return retFlag(&add);
	if (equals(f, "sub")) return retFlag(&sub);

	if (equals(f, "and")) return retFlag(&and);
	if (equals(f, "or"))  return retFlag(&or);

	if (equals(f, "not")) return retFlag(&not);
	if (equals(f, "neg")) return retFlag(&neg);

	if (equals(f, "eq")) return retFlag(&eq);
	if (equals(f, "gt")) return retFlag(&gt);
	if (equals(f, "lt")) return retFlag(&lt);

	if (equals(f, "rtrn")) return retFlag(&retrn);
}

void getAsmFileName(char *asmFileName, char *inputArgument) {
	int l = length(inputArgument);

	set(asmFileName, inputArgument);
	setN(asmFileName, inputArgument, l-3);
	concat(asmFileName , ".asm");
}

void setVmFileName(char *name) {
	set(vmName, indexOfReverse(name, '/'));
	set(vmName, indexOfReverse(name, '\\'));

	if (vmName[0] == '/' || vmName[0] == '\\') {
		set(vmName, vmName+1);
	}
	vmName[length(vmName)-3] = '\0';
}

void split(char *inst, char *split) {
	stringSplit(inst, " \t", split);
}

void getSp() {
	fprintf(asmFile, "@SP\n");
	fprintf(asmFile, "A=M\n");
}

void incSp() {
	fprintf(asmFile, "@SP\n");
	fprintf(asmFile, "M=M+1\n");
}

void decSp() {
	fprintf(asmFile, "@SP\n");
	fprintf(asmFile, "M=M-1\n");
}


int pointerPos(char *pos) {
	return pnt + strToInt(pos);
}
int tempPos(char *pos) {
	return tmp + strToInt(pos);
}


void popWrite(char dest) {
	fprintf(asmFile, "@SP\n");
	fprintf(asmFile, "AM=M-1\n");

	if (dest != 'M') {
		fprintf(asmFile, "%c=M\n", dest);
	}
}

void pushWrite(char from) {
	getSp();
	fprintf(asmFile, "M=%c\n", from);
	incSp();
}

void evaluateCondition(char* cond) {
	fprintf(asmFile, "D=M\n");

	fprintf(asmFile, "@$%s.true\n", cond);
	fprintf(asmFile, "D;%s\n", cond);

	getSp();
	fprintf(asmFile, "M=0\n");
	fprintf(asmFile, "@$%s.end\n", cond);
	fprintf(asmFile, "0;JMP\n");

	fprintf(asmFile, "($%s.true)\n", cond);
	getSp();
	fprintf(asmFile, "M=-1\n");

	fprintf(asmFile, "($%s.end)\n", cond);
}


char* getAsmLabel(char *vm, char *label) {
	set(label, vmName);
	concat(label,".");
	concat(label, vm);

	return label;
}
void staticLabel(_Bool push, char *num) {
	if (!push) popWrite('D');

	char label[1000];
	getAsmLabel(num, label);
	fprintf(asmFile, "@%s\n", label);
}

void getPos(char *type, char *pos, char to) {
	fprintf(asmFile, "@%s\n", type);
	fprintf(asmFile, "D=M\n");
	fprintf(asmFile, "@%s\n", pos);
	fprintf(asmFile, "%c=D+A\n", to);
}

void swapAD() {
	fprintf(asmFile, "A=D+A\n");
	fprintf(asmFile, "D=A-D\n");
	fprintf(asmFile, "A=A-D\n");
}

void standardPos(_Bool push, int num) {
	if (!push) popWrite('D');
	fprintf(asmFile, "@%d\n", num);
}

void calculatePos(_Bool push, char *type, char *num) {
	if (push) {
		getPos(type, num, 'A');
	} else {
		getPos(type, num, 'D');
		popWrite('A');
		swapAD();
	}
}

#if 0
Push & Pop
#endif
void stack(_Bool push, char *inst) {
	char type[300], num[300];
	split(inst, type);
	split(inst, num);
	if (equals(type, "constant")) {
		fprintf(asmFile, "@%s\n", num);
		fprintf(asmFile, "D=A\n");
	} else {
		if (equals(type, "static"))		staticLabel(push, num);
		if (equals(type, "temp")) 	 	standardPos(push, tempPos(num));
		if (equals(type, "pointer"))  	standardPos(push, pointerPos(num));
		if (equals(type, "local")) 	 	calculatePos(push, "LCL", num);
		if (equals(type, "argument")) 	calculatePos(push, "ARG", num);
		if (equals(type, "this")) 	 	calculatePos(push, "THIS", num);
		if (equals(type, "that")) 	 	calculatePos(push, "THAT", num);

		fprintf(asmFile, push ? "D=M\n" : "M=D\n");
	}

	if (push) pushWrite('D');
}
#if 0
Push & Pop END
#endif

#if 0
Arithmetic Operations
#endif
void pop1Operation(char op) {
	popWrite('M');
	fprintf(asmFile, "M=%cM\n", op);
}

void pop2Operation(char op) {
	popWrite('D');
	popWrite('M');
	fprintf(asmFile, "M=M%cD\n", op);
}

void arithmeticCondition(char* cond) {
	pop2Operation('-');
	evaluateCondition(cond);
}

void writeArithmetic(char* op) {
	if (equals(op, "add")) pop2Operation('+');
	if (equals(op, "sub")) pop2Operation('-');

	if (equals(op, "and")) pop2Operation('&');
	if (equals(op, "or"))  pop2Operation('|');

	if (equals(op, "not")) pop1Operation('!');
	if (equals(op, "neg")) pop1Operation('-');

	if (equals(op, "eq"))  arithmeticCondition("JEQ");
	if (equals(op, "gt"))  arithmeticCondition("JGT");
	if (equals(op, "lt"))  arithmeticCondition("JLT");

	incSp();
}

void computeArithmetic(char* op) {
	fprintf(asmFile, "@$ret%d\n", c);
	fprintf(asmFile, "D=A\n");
	fprintf(asmFile, "@$%s$\n", op);
	fprintf(asmFile, "0;JMP\n");

	if (flag(op) == 0) {
		fprintf(asmFile, "($%s$)\n", op);

		fprintf(asmFile, "@R13\n");
		fprintf(asmFile, "M=D\n");

		writeArithmetic(op);

		fprintf(asmFile, "@R13\n");
		fprintf(asmFile, "A=M\n");
		fprintf(asmFile, "0;JMP\n");
	}

	fprintf(asmFile, "($ret%d)\n", c);

	++c;
}
#if 0
operazioni aritmetiche
#endif
void label(char *inst) {
	char vm[300];
	split(inst, vm);

	char label[300];
	getAsmLabel(vm, label);

	fprintf(asmFile, "(%s)\n", label);
}

void gotoInst(char *inst) {
	char vm[300];
	split(inst, vm);

	char label[300];
	getAsmLabel(vm, label);

	fprintf(asmFile, "@%s\n", label);
	fprintf(asmFile, "0;JMP\n");
}

void ifgoto(char *inst) {
	popWrite('D');

	int c2 = c++;

	fprintf(asmFile, "@END%d\n", c2);
	fprintf(asmFile, "D;JEQ\n");

	gotoInst(inst);

	fprintf(asmFile, "(END%d)\n", c2);
}

void function(char *inst) {
	char f[300], nStr[300];
	split(inst, f);
	split(inst, nStr);
	int n = strToInt(nStr);

	fprintf(asmFile, "(%s)\n", f);

	int i;
	for (i = 0; i < n; ++i) {
		pushWrite('0');
	}
}

// RETURN
void restoreValue(char *value) {
	fprintf(asmFile, "@R13\n");
	fprintf(asmFile, "AM=M-1\n");
	fprintf(asmFile, "D=M\n");
	fprintf(asmFile, "@%s\n", value);
	fprintf(asmFile, "M=D\n");
}

void rtrn() {
	if (flag("rtrn") == 1) {
		fprintf(asmFile, "@$RETURN$\n");
		fprintf(asmFile, "0;JMP\n");

		return;
	}

	fprintf(asmFile, "($RETURN$)\n");

	// FRAME=LCL
	fprintf(asmFile, "@LCL\n");
	fprintf(asmFile, "D=M\n");
	fprintf(asmFile, "@R13\n");
	fprintf(asmFile, "M=D\n");

	// RET=*(FRAME-5)
	fprintf(asmFile, "@5\n");
	fprintf(asmFile, "A=D-A\n");
	fprintf(asmFile, "D=M\n");
	fprintf(asmFile, "@R14\n");
	fprintf(asmFile, "M=D\n");

	// *ARG=pop()
	popWrite('D');
	fprintf(asmFile, "@ARG\n");
	fprintf(asmFile, "A=M\n");
	fprintf(asmFile, "M=D\n");

	// SP=ARG+1
	fprintf(asmFile, "@ARG\n");
	fprintf(asmFile, "D=M+1\n");
	fprintf(asmFile, "@SP\n");
	fprintf(asmFile, "M=D\n");

	restoreValue("THAT");
	restoreValue("THIS");
	restoreValue("ARG");
	restoreValue("LCL");

	// goto RET
	fprintf(asmFile, "@R14\n");
	fprintf(asmFile, "A=M\n");
	fprintf(asmFile, "0;JMP\n");
}

void pushValue(char *value) {
	fprintf(asmFile, "@%s\n", value);
	fprintf(asmFile, "D=M\n");
	pushWrite('D');

}

void calcArg(int nArg) {
	getSp();
	fprintf(asmFile, "D=A\n");

	fprintf(asmFile, "@%d\n", nArg+5);
	fprintf(asmFile, "D=D-A\n");

	fprintf(asmFile, "@ARG\n");
	fprintf(asmFile, "M=D\n");
}

void call(char *inst) {
	char f[300], nArgStr[300];
	split(inst, f);
	split(inst, nArgStr);
	int nArg = strToInt(nArgStr);

	int c2 = c++;

	fprintf(asmFile, "@RETURN%d\n", c2);
	fprintf(asmFile, "D=A\n");
	pushWrite('D');

	pushValue("LCL");
	pushValue("ARG");
	pushValue("THIS");
	pushValue("THAT");

	calcArg(nArg);

	fprintf(asmFile, "@SP\n");
	fprintf(asmFile, "D=M\n");
	fprintf(asmFile, "@LCL\n");
	fprintf(asmFile, "M=D\n");

	fprintf(asmFile, "@%s\n", f);
	fprintf(asmFile, "0;JMP\n");

	fprintf(asmFile, "(RETURN%d)\n", c2);
}

void initVm() {
	fprintf(asmFile, "@256\n");
	fprintf(asmFile, "D=A\n");
	fprintf(asmFile, "@SP\n");
	fprintf(asmFile, "M=D\n");

	return;

}

void computeInstructions(FILE *vm, char *fileName) {
	setVmFileName(fileName);

	char inst[300];

	while(fscanf(vm,"%[^\n]\n", inst) != EOF) {

		#ifdef DEBUG
		fprintf(asmFile, "\t// %s\n", inst);
		#endif

		removeChar(inst, '\n');
		removeChar(inst, '\r');

		if (length(inst) <= 1 || inst[0] == '/') {
			continue;
		}

		char frs[300];
		split(inst, frs);
		if (frs == NULL || length(frs) == 0 || frs[0] == '/') continue;

		if (equals(frs, "add") || equals(frs, "sub")
		|| equals(frs, "and") || equals(frs, "or") || equals(frs, "not")
		|| equals(frs, "neg") || equals(frs,"eq")  || equals(frs, "gt")
		|| equals(frs, "lt")) {
			computeArithmetic(frs);
		}
		if (equals(frs, "push")) stack(1, inst);
		if (equals(frs, "pop"))  stack(0, inst);

		if (equals(frs, "label")) label(inst);
		if (equals(frs, "goto")) gotoInst(inst);
		if (equals(frs, "if-goto")) ifgoto(inst);

		if (equals(frs, "function")) function(inst);
		if (equals(frs, "return")) rtrn();
		if (equals(frs, "call")) call(inst);
	}
}
