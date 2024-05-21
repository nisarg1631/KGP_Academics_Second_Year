#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <unordered_map>

#define MAX 10000

using namespace std;

/**********************************************************/
/************** Stack Datatype and Operations *************/
/**********************************************************/

// stack structure declaration
typedef struct stackADT {
    char opr[MAX];
    int top;
} Stack;

// initialize stack
void initStack (Stack *stack)
{
    stack->top = -1;
}

// check whether stack is empty
int isEmptyStack (Stack *stack)
{
    return (stack->top == -1);
}

// check whether stack is full
int isFullStack (Stack *stack)
{
    return (stack->top == MAX-1);
}

// push an element into stack
void push (Stack *stack, char x)
{
    if (isFullStack(stack))
        printf("Error: Stack is Full!\n");
    else
        stack->opr[++(stack->top)] = x;
}

// pop an element from stack
char pop (Stack *stack)
{
    char x;
    if (isEmptyStack(stack))
        printf("Error: Stack is Empty!\n");
    else
        x = stack->opr[(stack->top)--];
    return x;
}

/**********************************************************/


/**********************************************************/
/*********** Binary Tree Datatype and Operations **********/
/**********************************************************/

// binary tree structure declaration
typedef struct binTree {
    char element;
    struct binTree *leftChild;
    struct binTree *rightChild;
} BT;

// creating a node in binary tree
BT *createNode (char el)
{
    BT *newNode;
    if ( (newNode=(BT *)malloc(sizeof(BT))) == NULL )
        printf("Error: Malloc Error in Creating Node!\n");
    else {
        newNode->element = el;
        newNode->leftChild = NULL;
        newNode->rightChild = NULL;
    }
    return (newNode);
}

// creating an exact replica of the the binary tree
BT *duplicate(BT *orig)
{
    BT *dup = NULL;
    if(orig != NULL) {
        dup = createNode(orig->element);
        dup->leftChild = duplicate(orig->leftChild);
        dup->rightChild = duplicate(orig->rightChild);
    }
    return (dup);
}

/**********************************************************/


/**********************************************************/
/******************** Utility Functions *******************/
/**********************************************************/

// structure holding propositional values
typedef struct PropVal {
    char prop;
    int val; // '0' for False and '1' for True
} PV;

// scan every propositional values (one by one) from user as input
PV *scanPropValueInput(int *propcnt)
{
    unsigned int noProp, i;
    PV *pvarr;
    
    printf("Enter Total Number of Propositions: ");
    scanf("%u",&noProp);
    *propcnt=noProp;
    pvarr = (PV *)malloc(noProp * sizeof(PV));
    
    for (i = 0; i < noProp; i++) {
        printf("Enter Proposition [%u] (Format: Name <SPACE> Value): ", i+1);
        scanf(" %c %d", &pvarr[i].prop, &pvarr[i].val);
    }
    return pvarr;
}

// determines whether p is a proposition including 0 or 1
int isProposition (char p)
{
    return ( ((p >= 'a') && (p <= 'z')) || ((p >= 'A') && (p <= 'Z')) || (p == '0') || (p == '1') );
}

// printing the validity and satisfiability flags
void printResult (int valid, int sat)
{
    printf("\nThe Given Formula is: < ");
    valid ? printf("VALID") : printf("INVALID");
    printf(" + ");
    sat ? printf("SATISFIABLE") : printf("UNSATISFIABLE");
    printf(" >\n\n");
}

//display postfix form of propositional formula (from internally represented string)
void displayPfForm(char *pfForm)
{
    int i;
    
    printf("Postfix Representation of Formula:");
    for(i = 0; pfForm[i] != '\0'; i++){
        if ( pfForm[i] == '-' )
            printf(" ->");
        else if (pfForm[i] == '~')
            printf(" <->");
        else
            printf(" %c", pfForm[i]);
    }
    printf("\n");
}

// count number of characters in the formula representing only propositions and operators
int noOfIdsInFormula (char *formula)
{
    int i, len = strlen(formula), count = 0;
    for(i = 0; i < len; i++){
        if ( (formula[i] != '(') && (formula[i] != ')') && (formula[i] != ' ') && (formula[i] != '\t') )
            count++;
    }
    return count;
}

// pre-defined priority of in-stack element
int inStackPriority (char oper){
    switch(oper){
        case '!': return 3; break;
        
        case '&':
        case '|': return 2; break;
        
        case '~':
        case '-': return 1; break;
        
        case '(': return 0; break;
        
        default : return -1; break;
    }
}

// pre-defined priority of in-coming element
int inComingPriority (char oper){
    switch(oper){
        case '!': return 4; break;
        
        case '&':
        case '|': return 2; break;
        
        case '~':
        case '-': return 1; break;
        
        case '(': return 4; break;
        
        default : return -1; break;
    }
}

// generate postfix formula from the given input formula
char *genPostFixFormula(char *formula)
{
    int noOfIds = noOfIdsInFormula(formula), i, len = strlen(formula), k;
    char *pf = (char *)malloc((noOfIds+1) * sizeof(char));
    char out;
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    initStack(stack); push(stack,'#');
    
    for (i = 0, k = 0; i < len; i++){
        if ( (formula[i] != ' ') && (formula[i] != '\t') ){
            if ( isProposition(formula[i]) )
                pf[k++] = formula[i];
            else if (formula[i] == ')') {
                while ( (out = pop(stack)) != '(')
                    pf[k++] = out;
            }
            else {
                while ( inStackPriority(out = pop(stack)) >= inComingPriority(formula[i]) )
                    pf[k++] = out;
                push(stack, out);
                push(stack, formula[i]);
            }
        }
    }
    while( (out = pop(stack)) != '#' )
        pf[k++] = out;
    pf[k] = '\0';
    
    return pf;
}

/**********************************************************/





/**********************************************************/
/****************** YOUR CODE STARTS HERE *****************/
/**********************************************************/

// determines whether p is a binary connective
bool isBinCon (char p){
    return (p=='&' || p=='|' || p=='~' || p=='-');
}

// expression tree formation from postfix formula string
BT *ETF (char *pfForm, int start, int end)
{
    if(start==end)
        return createNode(pfForm[start]);
    
    BT *et = NULL;
    if(pfForm[end]=='!'){
        et=createNode('!');
        et->rightChild=ETF(pfForm, start, end-1);
    }
    else{
        int ind=end-1, cnt=0;
        while(cnt != -1){
            char curr=pfForm[ind];
            if(isBinCon(curr)) cnt++;
            else if(curr != '!') cnt--;
            ind--;
        }
        et=createNode(pfForm[end]);
        et->leftChild=ETF(pfForm, start, ind);
        et->rightChild=ETF(pfForm, ind+1, end-1);
    }

    return et;
}

// storing the expresion tree in a string using inorder traversal
void ETP (BT *et)
{
    if(et==NULL)
        return;

    char curr=et->element;
    
    if(isBinCon(curr))
        cout<<" (";
    ETP(et->leftChild);
    switch(curr){
        case '-': cout<<" ->"; break;
        case '~': cout<<" <->"; break;
        default: cout<<" "<<curr; break;
    }
    ETP(et->rightChild);
    if(isBinCon(curr))
        cout<<" )";
}

// recursively evaluates the formula from the expression tree from the proposition values using hash table
int evalUtil (BT *et, unordered_map<char,int> pval){
    char curr=et->element;

    if(isProposition(curr))
        return pval[curr];
    
    if(curr == '!')
        return (!evalUtil(et->rightChild, pval));
    
    int left=evalUtil(et->leftChild, pval);
    int right=evalUtil(et->rightChild, pval);
    switch(curr){
        case '&': return (left && right); break;
        case '|': return (left || right); break;
        case '-': return ((!left) || right); break;
        case '~': return ((left && right) || ((!left) && (!right))); break;
        default: return 0; break;
    }
}

// evaluate the formula from the expression tree from the proposition values provided in varr[] array
// this function first creates a hash table of propositions storing their truth values and then calls evalUtil on root of tree
int EVAL (BT *et, PV *pvarr, int propcnt)
{
    // hash table to store truth values of propositions for direct access
    unordered_map<char,int> pval;
    for(int i=0; i<propcnt; i++)
        pval[pvarr[i].prop]=pvarr[i].val;

    return evalUtil(et, pval);
}

// convert expression tree to IFF expression tree
BT *IFF (BT *et, int createDuplicate=0)
{
    if(createDuplicate){
        return IFF(duplicate(et));
    }

    if(et == NULL)
        return et;
    
    if(et->element == '-'){
        BT *left=et->leftChild;
        et->element='|';
        et->leftChild=createNode('!');
        et->leftChild->rightChild=left;
    }
    else if(et->element == '~'){
        BT *left=et->leftChild;
        BT *leftcopy=duplicate(et->leftChild);
        BT *right=et->rightChild;
        BT *rightcopy=duplicate(et->rightChild);

        et->element='&';
        et->leftChild=createNode('-');
        et->rightChild=createNode('-');

        et->leftChild->leftChild=left;
        et->leftChild->rightChild=right;

        et->rightChild->leftChild=rightcopy;
        et->rightChild->rightChild=leftcopy;
    }
    
    et->leftChild=IFF(et->leftChild);
    et->rightChild=IFF(et->rightChild);
    return et;
}

// convert IFF expression tree to NNF expression tree
BT *NNF (BT *etI, int createDuplicate=0)
{
    if(createDuplicate){
        return NNF(duplicate(etI));
    }

    if(etI == NULL)
        return etI;
    
    if(etI->element == '!'){
        if(etI->rightChild->element == '!'){
            etI=NNF(etI->rightChild->rightChild);
        }
        else if((etI->rightChild->element == '&') || (etI->rightChild->element == '|')){
            BT *left=etI->rightChild->leftChild;
            BT *right=etI->rightChild->rightChild;

            if(etI->rightChild->element == '&')
                etI->element='|';
            else
                etI->element='&';
            
            etI->leftChild=createNode('!');
            etI->rightChild=createNode('!');

            etI->leftChild->rightChild=left;
            etI->rightChild->rightChild=right;
        }
    }

    etI->leftChild=NNF(etI->leftChild);
    etI->rightChild=NNF(etI->rightChild);
    return etI;
}

// convert NNF expression tree to CNF expression tree
BT *CNF (BT *etN, int createDuplicate=0)
{
    if(createDuplicate){
        return CNF(duplicate(etN));
    }

    if(etN == NULL)
        return etN;
    
    if(etN->element == '|'){
        if(etN->leftChild->element == '&'){
            BT *ll=etN->leftChild->leftChild;
            BT *lr=etN->leftChild->rightChild;
            BT *r=etN->rightChild;
            BT *rcopy=duplicate(etN->rightChild);

            etN->element='&';
            etN->leftChild->element='|';
            etN->rightChild=createNode('|');

            etN->leftChild->leftChild=CNF(ll);
            etN->leftChild->rightChild=CNF(r);
            etN->rightChild->leftChild=CNF(lr);
            etN->rightChild->rightChild=CNF(rcopy);
        }
        else if(etN->rightChild->element == '&'){
            BT *rl=etN->rightChild->leftChild;
            BT *rr=etN->rightChild->rightChild;
            BT *l=etN->leftChild;
            BT *lcopy=duplicate(etN->leftChild);

            etN->element='&';
            etN->leftChild=createNode('|');
            etN->rightChild->element='|';

            etN->leftChild->leftChild=CNF(l);
            etN->leftChild->rightChild=CNF(rl);
            etN->rightChild->leftChild=CNF(lcopy);
            etN->rightChild->rightChild=CNF(rr);
        }
    }
    
    etN->leftChild=CNF(etN->leftChild);
    etN->rightChild=CNF(etN->rightChild);
    return etN;
}

// convert NNF expression tree to DNF expression tree
BT *DNF (BT *etN, int createDuplicate=0)
{
    if(createDuplicate){
        return DNF(duplicate(etN));
    }

    if(etN == NULL)
        return etN;
    
    if(etN->element == '&'){
        if(etN->leftChild->element == '|'){
            BT *ll=etN->leftChild->leftChild;
            BT *lr=etN->leftChild->rightChild;
            BT *r=etN->rightChild;
            BT *rcopy=duplicate(etN->rightChild);

            etN->element='|';
            etN->leftChild->element='&';
            etN->rightChild=createNode('&');

            etN->leftChild->leftChild=DNF(ll);
            etN->leftChild->rightChild=DNF(r);
            etN->rightChild->leftChild=DNF(lr);
            etN->rightChild->rightChild=DNF(rcopy);
        }
        else if(etN->rightChild->element == '|'){
            BT *rl=etN->rightChild->leftChild;
            BT *rr=etN->rightChild->rightChild;
            BT *l=etN->leftChild;
            BT *lcopy=duplicate(etN->leftChild);

            etN->element='|';
            etN->leftChild=createNode('&');
            etN->rightChild->element='&';

            etN->leftChild->leftChild=DNF(l);
            etN->leftChild->rightChild=DNF(rl);
            etN->rightChild->leftChild=DNF(lcopy);
            etN->rightChild->rightChild=DNF(rr);
        }
    }
    
    etN->leftChild=DNF(etN->leftChild);
    etN->rightChild=DNF(etN->rightChild);
    return etN;
}

// recursively evaluates the formula using evalUtil for all possible truth value combinations
void checkUtil (BT *et, char *props, unordered_map<char, int> pval, int ind, int n, int *cnt){
    if(ind==n){
        cout<<"\t{ ";
        for(int i=0; i<n; i++)
            cout<<"("<<props[i]<<" = "<<pval[props[i]]<<") ";
        cout<<"} : ";
        if(evalUtil(et, pval)){
            cout<<1<<'\n';
            (*cnt)++;
        }
        else
            cout<<0<<'\n';
        return;
    }
    pval[props[ind]]=0;
    checkUtil(et, props, pval, ind+1, n, cnt);
    pval[props[ind]]=1;
    checkUtil(et, props, pval, ind+1, n, cnt);
}

// exhaustive search for checking validity / satisfiability
void CHECK (BT *et)
{
    int valid = 0, sat = 0;
    cout<<"\nEnter Number of Propositions: ";
    int n;
    cin>>n;
    char *props=new char[n];
    unordered_map<char,int> pval;
    cout<<"Enter Proposition Names (<SPACE> Separated): ";
    for(int i=0; i<n; i++){
        cin>>props[i];
        pval[props[i]]=0;
    }
    int cnt=0;
    cout<<"Evaluations of the Formula:\n";
    checkUtil(et, props, pval, 0, n, &cnt);

    if(cnt){
        sat=1;
        if(cnt==(int)pow(2,n)){
            valid=1;
        }
    }
    printResult(valid,sat);
}

/**********************************************************/
/******************* YOUR CODE ENDS HERE ******************/
/**********************************************************/





// main routine
int main ()
{
    char formula[MAX], *pfForm;
    int len, i, propcnt;
    
    BT *et, *etI, *etN, *etDup, *etC, *etD;
    int *varr;
    PV *pvarr;
    int result;
    
    // scan propositional formula from user input
    printf("\nEnter Propositional Logic Formula: ");
    scanf("%[^\n]", formula);
    
    // internal formula string with operators as, AND (&), OR (|), NOT (!), IMPLY (-) and IFF (~)
    len = strlen(formula);
    for(i = 0; i < len; i++){
        if(formula[i] == '<'){ // denoting iff operator (<->) using ~
            formula[i] = ' ';
            formula[i+1] = '~';
        }
        if(formula[i] == '>'){ // denoting imply operator (->) using -
            formula[i] = ' ';
        }
    }
    
    // postfix form generation from represented formula string
    pfForm = genPostFixFormula(formula);
    
    // display postfix form of the internally represented formula
    displayPfForm(pfForm);
    
    // internal postfix formula string with operators as, AND (&), OR (|), NOT (!), IMPLY (-) and IFF (~)
    printf("\n++++ PostFix Format of the Propositional Formula ++++\n('-' used for '->' and '~' used for '<->')\n");
    printf("YOUR INPUT STRING: %s\n", pfForm);
    
    
    
    /**********************************************************/
    /********** YOUR CODE ENABLES THE FOLLOWING PARTS *********/
    /**********************************************************/

    
    printf("\n++++ Expression Tree Generation ++++");
    et = ETF(pfForm, 0, strlen(pfForm)-1);
    printf("\nOriginal Formula (from Expression Tree):");
    ETP(et);
    printf("\n");
    
    printf("\n++++ Expression Tree Evaluation ++++\n");
    pvarr = scanPropValueInput(&propcnt);
    result = EVAL(et, pvarr, propcnt);
    printf("\nThe Formula is Evaluated as: ");
    (result) ? printf("True\n") : printf("False\n");
    
    printf("\n++++ IFF Expression Tree Conversion ++++");
    etI = IFF(et, 1);
    printf("\nFormula in Implication Free Form (IFF from Expression Tree):");
    ETP(etI);
    printf("\n");
    
    printf("\n++++ NNF Expression Tree Conversion ++++");
    etN = NNF(etI, 1);
    printf("\nFormula in Negation Normal Form (NNF from Expression Tree):");
    ETP(etN);
    printf("\n");

    etDup = duplicate(etN); // keeping a duplicate copy for DNF conversion
    
    printf("\n++++ CNF Expression Tree Conversion ++++");
    etC = CNF(etN, 1);
    printf("\nFormula in Conjunctive Normal Form (CNF from Expression Tree):");
    ETP(etC);
    printf("\n");
    
    printf("\n++++ DNF Expression Tree Conversion ++++");
    etD = DNF(etDup, 1);
    printf("\nFormula in Disjunctive Normal Form (DNF from Expression Tree):");
    ETP(etD);
    printf("\n");
    
    printf("\n++++ Exhaustive Search from Expression Tree for Validity / Satisfiability Checking ++++");
    CHECK (et);
    
    /**********************************************************/
    
    
    
    return 0;
}
