//WAP to understand expression evaluation
// lab 4
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
int top1 = -1, top2 = -1;
int operand[100];
char operator[100];
int precedence(char opr)
{
    //Checking the precedence order of operators (highest operator precedence is assigned highest number)
    switch (opr)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    //For precedence of brackets 
    default:
        return 0;
    }
}
void doProcess()
{
    //Poping out two operands from operand stack
    int x = operand[top1--];
    int y = operand[top1--];
    //Poping out operator from operator stack
    char opr = operator[top2--];
    int z; //Variable to store result 
    switch (opr) //Performing arithmatic operation based on operator poped form the opeartor stack
    {
    case '+':
        z = y + x;
        break;
    case '-':
        z = y - x;
        break;
    case '*':
        z = y * x;
        break;
    case '/':
        z = y / x;
        break;
    case '^':
        z = pow(y,x);
        break;
    }
    operand[++top1] = z; //Pushing the result in the operand stack
}
int evalInfixExpression(char *exp)
{
    //Getting the length of expression for performing iteration  
    int size = strlen(exp);
    for (int i = 0; i < size; i++) //Performing Iteration
    {
        char ch = exp[i]; //Storing the characters of expression one by one in 'ch' variable
        if (isdigit(ch))  //[isdigit] is a function available in ctype.h header file that returns true if a character is a digit otherwise returns false
        {
            int num = 0;
            while (isdigit(exp[i]))
            {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;
            operand[++top1] = num;  //Pushing the digits in the operand stack
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') //Checking if the current character is an operator or not
        {
            if(top2 == -1) //Checking if the operator stack is empty or not if empty then pushing the operator in it
            {
                operator[++top2] = ch;
            }
            else //If operator stack is not empty checking precendece;if precedence of current operator is more than that of operator stack top then pushing it 
            //If precedence of current operator is less than or equal to that of operator stack top then do the process until the current operator's precedence is more than operator stack top or the stack is empty
            {
                while (top2 != -1 && precedence(ch) <= precedence(operator[top2]))
                {
                    doProcess();
                }
                operator[++top2] = ch;
            }
        }
        else if (ch == '(') //If current character is opening bracket then pushing it in the operator stack
        {
            operator[++top2] = ch;
        }
        else if (ch == ')') //If current character is closing bracket then checking if operator stack top is opening bracket or not if opening bracket then poping the opening bracket
        {   //If operator stack top is not opening bracket then do the process until you find the opening bracket in the operator stack
            while (operator[top2] != '(')
            {
                doProcess();
            }
            top2--;
        }
    } //End of iteration
    while (top2 != -1)  //After iteration checking if the operator stack is empty or not;if not empty then do the process until it is empty
    {
        doProcess();
    }
    return operand[top1--]; //Returning the result of the entered expression to the main function
}
int evalPostfixExpression(char *exp)
{
    //Getting the length of expression for performing iteration  
    int size = strlen(exp);
    for (int i = 0; i < size; i++) //Performing Iteration
    {
        char ch = exp[i]; //Storing the characters of expression one by one in 'ch' variable
        if (isdigit(ch))  //[isdigit] is a function available in ctype.h header file that returns true if a character is a digit otherwise returns false
        {
            int num = 0;
            while (isdigit(exp[i]))
            {
                num = num * 10 + exp[i] - '0';
                i++;
            }
            i--;
            operand[++top1] = num;  //Pushing the digits in the operand stack
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') //Checking if the current character is an operator or not
        {
            //Poping out two operands from operand stack
            int x = operand[top1--];
            int y = operand[top1--];
            int z; //Variable to store result 
            switch (ch) //Performing arithmatic operation based on operator
            {
            case '+':
                z = y + x;
                break;
            case '-':
                z = y - x;
                break;
            case '*':
                z = y * x;
                break;
            case '/':
                z = y / x;
                break;
            case '^':
                z = pow(y,x);
                break;
            }
        operand[++top1] = z; //Pushing the result in the operand stack
        }
    } //End of iteration
    return operand[top1--]; //Poping and returning the result
}
int evalPrefixExpression(char *exp)
{
    //Getting the length of expression for performing iteration  
    int size = strlen(exp);
    for (int i = size-1; i >= 0; i--) //Performing Iteration
    {
        char ch = exp[i]; //Storing the characters of expression one by one in 'ch' variable
        if (isdigit(ch))  //[isdigit] is a function available in ctype.h header file that returns true if a character is a digit otherwise returns false
        {
            int num = 0,place=1;
            while (isdigit(exp[i]))
            {
                num = num + (exp[i] - '0') * place;
                place = place * 10;
                i--;
            }
            i++;
            operand[++top1] = num;  //Pushing the digits in the operand stack
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') //Checking if the current character is an operator or not
        {
            //Poping out two operands from operand stack
            int x = operand[top1--];
            int y = operand[top1--];
            int z; //Variable to store result 
            switch (ch) //Performing arithmatic operation based on operator
            {
            case '+':
                z = x + y;
                break;
            case '-':
                z = x - y;
                break;
            case '*':
                z = x * y;
                break;
            case '/':
                z = x / y;
                break;
            case '^':
                z = pow(x,y);
                break;
            }
        operand[++top1] = z; //Pushing the result in the operand stack
        }
    } //End of iteration
    return operand[top1--]; //Poping and returning the result
}
int main(){
    char str[100];
    printf("Enter Infix expression = ");
    gets(str);
    int result = evalInfixExpression(str);
    printf("Result = %d\n",result);
    printf("Enter Postfix expression = ");
    gets(str);
    result = evalPostfixExpression(str);
    printf("Result = %d\n",result);
    printf("Enter Prefix expression = ");
    gets(str);
    result = evalPrefixExpression(str);
    printf("Result = %d\n",result);
    return 0;
}