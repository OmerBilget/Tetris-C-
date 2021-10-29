#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
int collision(int *px ,int *py,int a[22][12],int m[4][4],int *wx,int *wy);
void equaliser(int x[4][4],int y[4][4]);
void screen(int a[22][12],int n[4][4],int *px,int *py,int score);
void emptying(int n[4][4]);
int rotateright(int a[4][4]);
int rotateleft(int a[4][4]);
void placing(int a[22][12],int n[4][4],int *px,int *py,int *r);
void full(int a[22][12],int *s,int x,int y,int empty[4][4],int score);
int main(){
	srand(time(0));
	int a[22][12];
	int dimx=22;
	int dimy=12;
	int i,j,k;
	int score=0;
	for(i=0;i<dimx;i++){
		for(j=0;j<dimy;j++){
			if(i==dimx-1 || j==0 || j==dimy-1){
				a[i][j]=-1;
			}else{
				a[i][j]=0;
			}
		}
	}
	int b[4][4]={ {0,0,0,0},
	              {0,1,1,0},
	              {0,0,1,1},
			      {0,0,0,0}};
			      		      
	int c[4][4]={ {0,0,0,0},
                  {0,0,2,0},
			      {0,2,2,2},
			      {0,0,0,0}};
				  		      
	int d[4][4]={ {0,0,0,0},
	              {0,3,3,3},
	              {0,0,0,3},
			      {0,0,0,0}};
			      
	int e[4][4]={ {0,0,0,0},
	              {4,4,4,4},
	              {0,0,0,0},
			      {0,0,0,0}};
			
	int f[4][4]={ {0,0,0,0},
	              {0,5,5,0},
			      {0,5,5,0},
			      {0,0,0,0}};
			      
	int g[4][4]={ {0,0,0,0},
	              {0,6,6,0},
	              {6,6,0,0},
			      {0,0,0,0}};
			      
	int h[4][4]={ {0,0,0,0},
	              {7,7,7,0},
	              {7,0,0,0},
			      {0,0,0,0}};
			      
	int empty[4][4]={ {0,0,0,0},
	                  {0,0,0,0},
			          {0,0,0,0},
			          {0,0,0,0}};
	int x=0,y=4;
	///////////////////////////////////////////
	///////////////////////////////////////////
	//STEP EVENTS
	int end=0;
	int rand_num;
	int dirx=1;
	int diry=0;
	int timer;
	int endtimer;
	int r=1;
	char way;
	while(end==0){
		endtimer=20;
		timer=15;
		///////////////////////////////////////////
		//CHOOSE TETRAMINO
		rand_num=(rand() % 7)+1;
		if(rand_num==1){
			equaliser(empty,b);
		}else if(rand_num==2){
			equaliser(empty,c);
		}else if(rand_num==3){
			equaliser(empty,d);
		}else if(rand_num==4){
			equaliser(empty,e);
		}else if(rand_num==5){
			equaliser(empty,f);
		}else if(rand_num==6){
			equaliser(empty,g);
		}else if(rand_num==7){
			equaliser(empty,h);
		}
		while(collision(&x,&y,a,empty,&dirx,&diry)==1 || endtimer>0){
			screen(a,empty,&x,&y,score);
			if(kbhit()){
				way=getch();
				if(way=='w'){
					dirx=0;
					diry=0;
					rotateright(empty);
					if(collision(&x,&y,a,empty,&dirx,&diry)==0){
						rotateleft(empty);
					}
					dirx=1;
					diry=0;
				}
				if(way=='a'){
					dirx=0;
					diry=-1;
					if(collision(&x,&y,a,empty,&dirx,&diry)==1){
						y-=1;
					}
					dirx=1;
					diry=0;
				}
				if(way=='s'){
					timer=0;
					if(collision(&x,&y,a,empty,&dirx,&diry)==0){
				        endtimer-=5;
		        	}
				}
				if(way=='d'){
					dirx=0;
					diry=1;
					if(collision(&x,&y,a,empty,&dirx,&diry)==1){
						y+=1;
					}
					dirx=1;
					diry=0;
				}
				
			}
			if(timer>0){
				timer-=1;
			}
			if(timer<=0){
				if(collision(&x,&y,a,empty,&dirx,&diry)==1){
				    x+=1;
			    }
				timer=10;
			}
			if(x<3){
				timer=0;
			}
			if(collision(&x,&y,a,empty,&dirx,&diry)==0){
				endtimer-=1;
			}
		}
		placing(a,empty,&x,&y,&r);
		r+=1;
		if(r>3){
			r=1;
		}
		score+=((rand() % 4)+3)*4;
		full(a,&score,x,y,empty,score);
		screen(a,empty,&x,&y,score);
		emptying(empty);
		x=0;
		y=4;
		for(j=1;j<11;j++){
			if(a[3][j]!=0){
				end=1;
			}
		}
	}
	printf("DO YOU WANT TO PLAY AGAIN?\n");
	printf("y    n\n");
	int check=0;
	char replay;
	while(check==0){
		replay=getch();
		if(replay=='y' || replay=='n'){
			check=1;
		}
	}
	if(replay=='y'){
	   main();
	}else{
		return 0;
	}
}








int collision(int *px ,int *py,int a[22][12],int m[4][4],int *wx,int *wy){
	int i,j;
	*px+=*wx;
	*py+=*wy;
	for(i=*px;i<=*px+3;i++){
		for(j=*py;j<=*py+3;j++){
			if(m[i-*px][j-*py]!=0){
				
				if(a[i][j]!=0){ 
				    *px-=*wx;
                	*py-=*wy;
				    return 0;
				}
			} 
		}
	}
	*px-=*wx;
    *py-=*wy;
	return 1;
}
void equaliser(int x[4][4],int y[4][4]){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
		    x[i][j]=y[i][j];
     	}
	}
}

void screen(int a[22][12],int n[4][4],int *px,int *py,int score){
	system("cls");
	int i,j;
	for(i=4;i<22;i++){
		for(j=0;j<12;j++){
			if(i>=*px && i<=*px+3 && j>=*py && j<=*py+3 && n[i-*px][j-*py]!=0){
				printf("[]");
			}else{
				if(a[i][j]==0){
					printf("  ");
				}
				if(a[i][j]==-1){
					printf("[]");
				}
				if(a[i][j]==1){
					printf(" Q");
				}
				if(a[i][j]==2){
					printf(" W");
				}
				if(a[i][j]==3){
					printf(" E");
				}
				if(a[i][j]==4){
					printf(" F");
				}
				if(a[i][j]==5){
					printf(" K");
				}
				if(a[i][j]==6){
					printf(" L");
				}
				if(a[i][j]==7){
					printf(" M");
				}
				if(a[i][j]==8){
					printf(" A");
				}
				if(a[i][j]==9){
					printf(" T");
				}
				if(a[i][j]==10){
					printf(" V");
				}
				if(a[i][j]==11){
					printf(" C");
				}
				if(a[i][j]==12){
					printf(" N");
				}
				if(a[i][j]==13){
					printf(" Z");
				}
				if(a[i][j]==14){
					printf(" H");
				}
				if(a[i][j]==15){
					printf(" R");
				}
				if(a[i][j]==16){
					printf(" U");
				}
				if(a[i][j]==17){
					printf(" O");
				}
				if(a[i][j]==18){
					printf(" D");
				}
				if(a[i][j]==19){
					printf(" X");
				}
				if(a[i][j]==20){
					printf(" I");
				}
				if(a[i][j]==21){
					printf(" J");
				}
				if(a[i][j]==30){
					printf("--");
				}
				
			}
		}
		printf("\n");
	}
	printf("     SCORE :    %d   \n",score);
}


void emptying(int n[4][4]){
	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
		    n[i][j]=0;
     	}
	}
}

int rotateright(int a[4][4]){
	int i,j;
	int tmp;
	
	for(i=0;i<4;i++){
		for(j=0;j<=i;j++){
			tmp=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=tmp;
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<2;j++){
			tmp=a[i][j];
			a[i][j]=a[i][3-j];
			a[i][3-j]=tmp;
		}
	}
}

int rotateleft(int a[4][4]){
	int i,j;
	int tmp;
	
	
	for(i=0;i<4;i++){
		for(j=0;j<2;j++){
			tmp=a[i][j];
			a[i][j]=a[i][3-j];
			a[i][3-j]=tmp;
		}
	}
	for(i=0;i<4;i++){
		for(j=0;j<=i;j++){
			tmp=a[i][j];
			a[i][j]=a[j][i];
			a[j][i]=tmp;
		}
	}
}



void placing(int a[22][12],int n[4][4],int *px,int *py,int *r){
	int i,j;
	for(i=0;i<22;i++){
		for(j=0;j<12;j++){
			if(i>=*px && i<=*px+3 && j>=*py && j<=*py+3 ){
				if(n[i-*px][j-*py]!=0){
					a[i][j]=n[i-*px][j-*py]*(*r);
				}
		    }
		}
	}
}

void full(int a[22][12],int *s,int x,int y,int empty[4][4],int score){
	int check=0;
	int i,j,k;
	int tmp;
	int t=6;
	for(i=4;i<21;i++){
	   check=0;
	   for(j=1;j<11;j++){
	   	  if(a[i][j]==0){
	   	  	   check=1;
			}
	    }
		if(check==0){
			*s+=1000;
			for(j=1;j<11;j++){
				a[i][j]=30;
            }
            while(t>0){
			    screen(a,empty,&x,&y,score);
			    t-=1;
			}
            for(j=1;j<11;j++){
				a[i][j]=0;
				for(k=i;k>0;k--){
                    tmp=a[k][j];
                    a[k][j]=a[k-1][j];
                    a[k-1][j]=tmp;
		    	}
            }
				
		}
		t=6;	
	}
}

