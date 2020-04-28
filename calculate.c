#include <stdio.h>

int ch;
int error1, error2, error3; //Counters of errors
//error1: Unexpected character
//error2: Missing closing parenthesis
//error3: Unexpected end of input

void ispaces(){ //Function that ignores the spaces and tabs at input
	while(ch==' ' || ch=='\t')
		ch= getchar();
}

int unumber(){ //<unumber>::= <digit> | <digit> <unumber>
	int  i= 0;
	while (ch>='0' && ch<='9'){
    		i= (ch-'0')+i*10;
      		ch= getchar();
	}
	ispaces(); //Ignore the spaces
	while(ch!='+' && ch!='-' && ch!='*' && ch!='\n' && ch!=')'){ //If following character not expected
		error1++; //Increase the correct error counter
		ch= getchar();
	}
	return i; //Return the unsigned number
}

int snumber(){ //<snumber>::= <unumber> | ’+’ <unumber> | ’-’ <unumber>
	int i= 0;
	if (ch=='+'){ //If the number is positive
		ch= getchar();
		//If following character not expected
		if (ch=='\n' )
			error3++;
		else if (!(ch>='0' && ch<='9'))
			error1++;
		else i= unumber();
	}
	else if (ch=='-'){ //If the number is negative
		ch=getchar();
		//If following character not expected
		if (ch=='\n')//If following character not expected
			error3++;
		else if (!(ch>='0' && ch<='9'))
			error1++;
		else i=(-1)*unumber();
	}
	else if (ch>='0' && ch<='9') //Not a signed number
		i= unumber();
	return i;
}

int factor();

int term(){ //<term>::= <factor> | <factor> ’*’ <term>
	int i= 0, j= 0;
	i= factor();

	while (ch=='*'){
		ch=getchar();
		ispaces();

		if (ch=='\n')
			error3++;
		else if (ch!='(' && !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='\n'){
			error1++;
			ch=getchar();
		}
		j= factor();
		i= i*j;
	}
	return i;
}

int expression(){ //<expression>::= <term> | <expression> ’+’ <term> | <expression> ’-’ <term>
	int i= 0, j= 0;
	ispaces();

	if (!(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='('){
		error1++;
		ch=getchar();
	}
	i= term();

	while(ch=='+' || ch=='-'){
		int operation= ch;
		ch=getchar();
		ispaces();

		if (ch=='\n')
			error3++;
		if (ch!='(' && !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='\n'){
			error1++;
			ch=getchar();
		}
		j=term();
		if(operation=='+') i= i+j;
		else i= i-j;
	}
	return i;
}

int factor(){ //factor::= <snumber> | ’(’ <expression> ’)’
	int i= 0;
	i= snumber();
	
	if (ch=='('){
		ch=getchar();
		i=expression();

		if (ch==')'){
			ch=getchar();
			ispaces();
			return i;
		}
		else if (ch=='\n')
			error2++;
	}
	return i;
}

int main(void){
	int  total=0, flag=0;
	while ((ch=getchar())!= EOF){
		while (ch!='\n')
			total= expression();
		if (error1!=0){
			flag++;
			printf("Result %d: Unexpected character\n", flag);
		}
		else if (error2!=0){
			flag++;
			printf("Result %d: Missing closing parenthesis\n", flag);
		}
		else if (error3!=0){
			flag++;
			printf("Result %d: Unexpected end of input\n", flag);
		}
		else if (error1==0 && error2==0 && error3==0){
			flag++;
			printf("Result %d: %d\n",flag,total);
		}
		error1=0;
		error2=0;
		error3=0;
	}
	return 0;
}
