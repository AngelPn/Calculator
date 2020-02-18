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

int unumber(){ //Function that builts up an unsigned number
	int  i=0;

	while (ch>='0' && ch<='9'){
    	i= (ch-'0')+i*10;
      ch= getchar();
	}
	ispaces(); //Ignore the spaces
	while(ch!='+' && ch!='-' && ch!='*' && ch!='\n' && ch!=')'){ //If following character not expected
		error1++; //Increase the correct error counter
		ch= getchar();
	}
	printf("unumber= %d \n", i);
	return i; //Return the unsigned number
}

int snumber(){ //Function that builts up a signed number
	int i=0;

	if (ch=='+'){
		ch= getchar();
		//If following character not expected
		if (ch=='\n' ){
			error3++;
		}
		else if (!(ch>='0' && ch<='9')){
			error1++;
		}
		else i= unumber();
	}
	else if (ch=='-'){
		ch=getchar();
		//If following character not expected
		if (ch=='\n'){//If following character not expected
			error3++;
		}
		else if (!(ch>='0' && ch<='9')){
			error1++;
		}
		else i=(-1)*unumber();
	}
	else if (ch>='0' && ch<='9') //Not a signed number
		i= unumber();
	printf("iunumber= %d\n", i);
	return i;
}

int factor();

int term(){
	int i=0, j=0;

	i=factor();
	printf("ifactor= %d\n", i);
	while (ch=='*'){
		ch=getchar();
		ispaces();

		if (ch=='\n')
			error3++;
		if (ch!='(' && !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='\n'){
			error1++;
			ch=getchar();
		}
		j= factor();
		printf("ifactor= %d\n", i);
		i= i*j;
	}
	printf("totalifactor=%d \n", i);
	return i;
}

int expression(int *exp){
	//int i=0;
	//ch= getchar();
	ispaces();
	if ( !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='('){
		error1++;
		ch=getchar();
	}

	//*expression= i;
	//printf("iterm= %d\n", i);
	if(ch== '+'){
		ch= getchar();
		//i+= term();
		*exp+= term();
		//printf("+=expression= %d\n", i);
	}

	else if(ch== '-'){
		ch= getchar();
		//i+= (-1)*expression();
	//	*expression-= term;
		//i-= term();
		*exp-= term();
	//	printf("-=expression= %d\n", i);
	}
	else{
		*exp= term();
	}
	while(ch!= '\n')
		*exp= expression(exp);
/*
	while(ch=='+'){
		ch=getchar();
		ispaces();

		if (ch=='\n')
			error3++;
		if (ch!='(' && !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='\n'){
			error1++;
			ch=getchar();
		}
		j=term();
		i= j+i;
		while(ch=='-'){
			ch=getchar();
			ispaces();

			if (ch=='\n')
				error3++;
			if (ch!='(' && !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='\n'){
				error1++;
				ch=getchar();
			}
			j=term();
			i=i-j;
		}
	}
	while(ch=='-'){
		ch=getchar();
		ispaces();

		if (ch=='\n')
			error3++;
		if (ch!='(' && !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='\n'){
			error1++;
			ch=getchar();
		}
		j=term();
		i=i-j;
		while(ch=='+'){
			ch=getchar();
			ispaces();

			if (ch=='\n')
				error3++;
			if (ch!='(' && !(ch>='0' && ch<='9') && ch!='+' && ch!='-' && ch!='\n'){
				error1++;
				ch=getchar();
			}
			j=term();
			i= j+i;
		}
	}
*/
	return *exp;
}

int factor(){
	int i=0;

	//i= snumber();
	if (ch=='('){
		ch=getchar();
		int n= 0;
		i=expression(&n);
		printf("iexpression= %d\n", i);
		if (ch==')'){
			ch=getchar();
			ispaces();
			return i;
		}
		else if (ch=='\n'){
			error2++;
		}
	}
	else i= snumber();
	printf("isnumber= %d\n", i);
	return i;
}

int main(void){
	int  total=0, flag=0;
	while ((ch=getchar())!= EOF){
		int n= 0;
		while (ch!='\n'){
			total= expression(&n);
		}
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
