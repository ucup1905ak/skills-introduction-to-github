#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <stdbool.h>
typedef int infotype ;
typedef struct {
	infotype * data;
	int Col;
	int Row;
	char name[10];
}matrix;

void createMatrix(matrix * mtx,int Row, int Col);

void editValue(matrix * mtx);

void freeMatrix(matrix * mtx){
	free(mtx);
}

void printMtx(matrix * mtx, int HighlightRow, int HighlightCol);

matrix * init(char * name);

void multiplyMtx(matrix * C,matrix * mtxA, matrix * mtxB);

bool addMtx(matrix * A,matrix * B);

int main(int argc, char *argv[]) {
	int exit=0,initA=0,initB=0;
	matrix * p_A;
	matrix * p_B;
	matrix * temp;
	char menu;
	int i,j;
	do{
		system("cls");
		printf("WELCOME to MATRIX CALCULATOR!!!\n");
		printf("\n\n");
		printf("1. MtxA\n");
		printf("2. MtxB\n");
		printf("3. Multiply\n");
		printf("4. Add\n");
		printf("5. Transposisi A\n");

		menu = getch();
		switch(menu){
			case '1':
				system("cls");
				if(initA==0){
				p_A = init("Mtx A");
				initA++;
				}
				editValue(p_A);
				break;
			case '2':
				system("cls");
				if(initB==0){
				p_B = init("Mtx B");
				initB++;
				}
				editValue(p_B);
				break;
			case '3':
				if(initA!=0&&initB!=0){
					system("cls");
					printf("\nMATRIX A\n");
					printMtx(p_A,10,10);
					printf("\nMATRIX B\n");
					printMtx(p_B,10,10);
					printf("\n\nMATRIX A * MATRIX B\n");
					matrix * C = calloc(1,sizeof(matrix));
					createMatrix(C,p_A->Row,p_B->Col);
					multiplyMtx(C,p_A,p_B);
					printMtx(C,10,10);
					temp = C;
					free(C);
				}else{
					printf("\nMtx A atau Mtx B blom di isi, plis...");
				}
				menu = getch();
				if(menu=='r'){
					free(p_A->data);
					free(p_A);
					p_A = temp;
				}
				
				break;
			case '4':
				
				if(initA==0||initB==0)continue;
				if(addMtx(p_A,p_B)){
					free(p_B);
					initB=0;
					printMtx(p_A,10,10);
				}
				getch();
				break;
			case '5':
				system("cls");
				free(temp);
				temp =  calloc(1,sizeof(matrix));
				temp->Col = p_A->Row;
				temp->Row = p_A->Col;
				for(j=0;j<temp->Row;j++){
					for(i=0;i<temp->Col;i++)*(temp->data + j*temp->Col + i)=*(p_A->data + i*p_A->Col + j);
				}
				// 2 3
				// 4 5
				printf("\n\n");
				printMtx(temp,10,10);
				getch();
				break;
			default:
				break;
		}
	}while(menu!=0x1B);
	printf("bye");
	freeMatrix(p_A);
	freeMatrix(p_B);
	return 0;
}

void createMatrix(matrix * mtx,int Row, int Col){
	mtx->Col = Col;
	mtx->Row = Row;
	mtx->data = calloc(Row*Col,sizeof(infotype));
}

matrix * init(char *name){
	int inputRow,inputCol;
	printf("Matrix: %s\nNumber of Rows?\n>>",name);scanf("%d",&inputRow);
	printf("Matrix: %s\nNumber of Colums?\n>>",name);scanf("%d",&inputCol);
	matrix * mtx = calloc(1,sizeof(matrix));
	createMatrix(mtx,inputRow,inputCol);
	strcpy(mtx->name,name);
	return mtx;
}

void editValue(matrix * mtx){
	int inputCol,inputRow;
	int HighRow = 0,HighCol = 0;
	int edit;
	edit=1;
	while(edit!=0){
		system("cls");
		printf("%s\n",mtx->name);
		printMtx(mtx,HighRow,HighCol);
		printf("\n[ENTER]\tto edit");
		printf("\n[ESC]\tto exit");
		char input = getch();
		switch(input) {
	    case 72:    // key up
			if(HighRow>0)HighRow--;
	        break;
	    case 80:    // key down
			if(HighRow<(mtx->Row-1))HighRow++;
	        break;
	    case 77:    // key right
			if(HighCol<(mtx->Col-1))HighCol++;
	        break;
	    case 75:    // key left
			if(HighCol>0)HighCol--;
	        break;
		case 0x1B:
			edit = 0;
			break;
		case 13:
			printf("\nEnter New Value >>");
			scanf("%d",mtx->data+HighRow*mtx->Col+HighCol);
			break;

		}
	}
}

bool addMtx(matrix * A, matrix * B){
	int i,j,temp;
	if(A->Col!=B->Col||A->Row!=B->Row){
		system("cls");
		printf("Matrix tidak kompatibel");
		return 0;
	}
	for(j=0;j<(A->Row);j++){
		for(i=0;i<(A->Col);i++)*(A->data+j*A->Col+i)+=*(B->data+j*B->Col+i);
		return 1;
	}
}

void printMtx(matrix * mtx, int HighlightRow, int HighlightCol){
	int i,j;
	char mystr[50];
	for(j=0;j<mtx->Row;j++){
		for(i=0;i<mtx->Col;i++){
				sprintf(mystr,"%5d",*(mtx->data + j * mtx->Col + i));
				if(j==HighlightRow&&i==HighlightCol){
				printf("\e[0;30m\e[47m%s\e[0m ",mystr);
				}else printf("%s ",mystr);
			}
			printf("\n");
	}
}
void multiplyMtx(matrix * C,matrix * mtxA, matrix * mtxB){
	int a,b,i,j,temp,add;
	if(mtxA->Col==mtxB->Row){
	}; //check Rulles
	for(j=0;j<mtxA->Row;j++){
		for(i=0;i<mtxB->Col;i++){
			temp=0;
			for(add=0;add<mtxA->Col;add++){
				a = *(mtxA->data + j*mtxA->Col+add);
				b = *(mtxB->data+ add*mtxB->Col +i);
				temp+=a*b;
			}
			*(C->data+j*C->Col+i)= temp;
		}
	}
	return C;
}



// only if m.Col == m.Row
void determinantMtx(matrix * m, int * determinan){
	int i,j;
	int value, tempPlus, tempMin;
	/*


	expand matrix

	*/
	
	
	
	
	tempPlus = 0;
	for(j=0;j<m->Col;j++){ // ++
		value = 0;
		for(i=0;i<m->Col;i++){ //Kali kali
			if(i==0){//    Data awal | Row         | Col | shifter |
				value = *( m->data +   i*m->Col*2 +   i   +    j);
			}else{
				value *= *(m->data + i*m->Col*2+i + j);
			}
		}
		tempPlus += value;
	}
	tempMin = 0;
	for(j=0;j<m->Col;j++){ // --
		value = 0;
		for(i=m->Col*2;i>0;i--){ //Kali kali
			if(i==m->Col){
				value = *(m->data + i*m->Col*2+i + j);
			}else{
				value *= *(m->data + i*m->Col*2+i + j);
			}
		}
		tempMin -= value;
	}
	*determinan = tempPlus + tempMin;
}
