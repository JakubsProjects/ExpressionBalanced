#include <stdio.h>
#include <stdlib.h>

//Initializing Stack
typedef struct stack {
	char *arr;
	int CurrSize;
	int TopStack;

}stack;

//setting 1 to true and 0 to false
#define TRUE 1
#define FALSE 0

int DEBUG = FALSE;

//Function to grow the array
char *growArray(stack *stack1) {
	//creating temporary char pointer
	char *temp;		//Temp pointer
	temp = (char *)malloc((stack1->CurrSize + 2) * sizeof(char));   //allocating memory(doubling stack)
	int i;
	for (i = 0; i < stack1->CurrSize; i++) { //Copying over the elements
		temp[i] = stack1->arr[i];
	}
	free(stack1->arr); //freeing old array
	stack1->arr = temp;	//Setting pointer to new BIGGER array
	stack1->CurrSize = stack1->CurrSize + 2; //Update the size

	if (DEBUG == TRUE) {		//When debugging is on, print this information
		printf("Growing Array...\n");
		printf("OldSize: %d \nNewSize: %d\n", stack1->CurrSize - 2, stack1->CurrSize);
	}
	//return the stack array pointer
	return stack1->arr;
}

//INitializing stack
stack* InitializeStruct(stack *stack1) {

	stack1->arr = (char*)malloc(2 * sizeof(char)); //Allocating memory
	stack1->TopStack = -1; //Setting stack to -1
	stack1->CurrSize = 2; //Setting currentSize to 2

	return stack1;  //return stack1
}

//Function to check if stack is empty
int isempty(stack *stack1) {

	if (stack1->TopStack == -1) { //If topstack is -1, means its empty
		return 1;
	}
	else {
		return 0;    //If returns this, not empty
	}
}

//Check whats on top of the stack
char checkOnTop(stack *stack1) {
	char topSymbol = stack1->arr[stack1->TopStack];
	return topSymbol;    //Return that symbol
}

//Function to return the opposite symbol(used in main)
char whatSymbolShouldBe(stack* stack1) {
	char ElementonTop = checkOnTop(stack1); //Storig the top element

	switch (ElementonTop) { //Returning the opoposite of on top of the stack
	case '{':
		return '}';
		break;
	case '[':
		return']';
		break;
	case '(':
		return ')';
		break;
	case '<':
		return '>';
		break;
	}
	return 0;
}

//Pushing onto the stack
void push(stack *stack1, char item)
{
	stack1->TopStack++;  //Incrementing stack 

	if (stack1->TopStack == (stack1->CurrSize)) {  //Grow the array if curr size matches size of topstack
		stack1->arr = growArray(stack1);
	}
	if (DEBUG == TRUE) {  //When debugging is on, print this information
		printf("Pushing item: %c\n", item);
	}
	stack1->arr[stack1->TopStack] = item;
}

//Function to pop off the stack
int pop(stack *stack1, char item)
{
	char correspondingsymbol = whatSymbolShouldBe(stack1); //Storing what the symbol should be

	if (item == correspondingsymbol) { //If what it reutrns matches whats on top of the stack
		if (DEBUG == TRUE) { //When debugging is on, print this information
			printf("Popping item: %c\n", item);
		}
		stack1->TopStack--; //Decrement stock
		return 1;   //Return 1
	}
	return 0;// return 0 if it doesnt pop
}

//Finding the second error
char seconderror(char inputline) {

	switch (inputline) {
	case '}':
		return '{';
		break;
	case ']':
		return'[';
		break;
	case ')':
		return '(';
		break;
	case '>':
		return '<';
		break;
	}
	return 0;
}


//main
int main(int argc, const char **argv) {
	int value = 0;
	char inputline[300];
	stack *stack1 = (stack*)malloc(sizeof(stack));			/* Declaring all variables*/
	int linesize = sizeof(inputline) / sizeof(inputline[0]);
	int counter = 0;
	int j, k, l, x = 0;

	//Calling fucntion to initialize stack
	stack1 = InitializeStruct(stack1);
	printf(" Name: Jakub Glebocki\n");
	printf(" Welcome to the program IsBalanced. Here you input {, [, (, < and then }, ], ), > and the\n");
	printf("program checks if they are balanced. You may enter them in any order you like. It also tells\n");
	printf("if you are missing a bracket, and before which character missing bracket belongs. Try: ( { < > )\n");
	printf("\nEnter input: ");
	//Checking for user input incase to use debugger
	for (x = 0; x < argc; x++) {
		if (strcmp(argv[x], "-d") == 0) {  //If arguemnt is -d
			printf("Debugging Mode activated ");
			DEBUG = TRUE;  //Activate debugging mode(aka set it to true)
		}
	}
	fgets(inputline, linesize, stdin);  //Get the first line of input


	while (1) {   //Infinite while loop so user can keeep putting in input
		
		while (inputline[counter] != '\0') {
			if (strcmp(inputline, "q\n") == 0) {    //If person inputs q, quit program
				printf("Exiting...\n");
				exit(0);
			}

			if (isempty == 1) { //print stack is empty, if its empty
				printf(" stack is empty");
				break;
			}
			//If input is an opening symbol push it
			if (inputline[counter] == '{' || inputline[counter] == '[' || inputline[counter] == '(' || inputline[counter] == '<') {
				push(stack1, inputline[counter]);
			}
			//If input is an closing symbol push it
			if (inputline[counter] == '}' || inputline[counter] == ']' || inputline[counter] == ')' || inputline[counter] == '>') {
				value = pop(stack1, inputline[counter]);

				//printf("%s  <- reprinting input", inputline);
				//If nothing was popped and stack is not empty, display error
				if (value == 0 && isempty(stack1) == 0) {
					printf("%s", inputline);
					for (j = 0; j <= counter; j++) {
						printf(" ");
						if (j == counter - 1) {
							printf("^ Expecting %c", whatSymbolShouldBe(stack1));
						}
					}
					break;
				}
				//If nothing was popped and stack is empty, display error
				else if (isempty(stack1) == 1 && value == 0) {
					printf("%s", inputline);
					for (k = 0; k <= counter; k++) {
						printf(" ");
						if (k == counter - 1) {
							printf("^missing %c", seconderror(inputline[counter]));
						}
					}
					break;
				}
			}
			counter++;
		}
		//If stack is empty and inputline is at end of line, print error
		if (isempty(stack1) == 0 && inputline[counter] == '\0') {
			printf("%s", inputline);
			for (l = 0; l <= counter - 1; l++) {
				printf(" ");
				if (l == counter - 1) {
					printf("^Missing %c", whatSymbolShouldBe(stack1));
					break;
				}
			}
		}
		//Otherwise the expression is balacned
		else if (isempty(stack1) == 1 && inputline[counter] == '\0') {
			printf("expression is balanced\n");
		}
		counter = 0;   //Resetting counter to 0
		stack1->TopStack = -1;   //Resetting the stack
		printf("\nPlease enter new line of characters: \n\n");  //Enter new line input
		fgets(inputline, linesize, stdin);
	}
	printf("\n");
}
