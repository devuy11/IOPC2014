#include<bits/stdc++.h>
#include<string.h>
using namespace std;
char use[5001];
struct brute{
	char str[5001];
	int M;  
}input[2501];
int find(int s,int e)
{
        return s+(rand()%(e-s+1));
}
void strRan(int s)
{
	for(int i=0;i<s;i++)	use[i]='b'+find(0,24);
	use[s]='\0';
}
void gen(char file[],int N,int T,int s,int e,int r)
{
	int sum=0,curr,counter=0,x,op;
	FILE *fp = fopen(file,"w");
	if(r){
		while(1){
			curr=find(1,400);
			input[counter].M=find(1,curr);
			strRan(curr);
			op=find(input[counter].M,curr);
			while(op--){
				use[rand()%curr]='a';
			}
			strcpy(input[counter].str,use);
			sum+=curr;
			if(sum>5000)	break;
			counter++;
		}
		fprintf(fp,"%d\n",counter);
		for(int i=0;i<counter;i++){
			fprintf(fp,"%s\n%d\n",input[i].str,input[i].M);
		}
	}
	else{
		fprintf(fp,"%d\n",T);
		while(T--){	
			strRan(N);
			curr=find(s,e);
			while(curr--){
				while(1){
					x=find(0,N-1);
					if(use[x]!='a'){
						use[x]='a';
						break;
					}
				}
			}
			fprintf(fp,"%s\n%d\n",use,find(s,e));
		}
	}
	fclose(fp);
}
void brutly(char file1[],char file2[],char file3[],char file4[])
{
	int counter=0,a;
	for(int i=0;i<256;i++){	
		for(int j=0;j<=8;j++){
			strRan(8);
			for(int k=0;k<8;k++)	if((i&(1<<k))!=0)	use[k]='a';
			for(int k=0;k<8;k++)	input[counter].str[k]=use[k];
			input[counter].str[8]='\0';
			input[counter].M=j;
			counter++;
		}
	}
	//576 Test case Per File
	FILE *fp1= fopen(file1,"w"),*fp2= fopen(file2,"w"),*fp3= fopen(file3,"w"),*fp4= fopen(file4,"w");
	fprintf(fp1,"576\n");
	fprintf(fp2,"576\n");
	fprintf(fp3,"576\n");
	fprintf(fp4,"576\n");
	for(int i=0;i<576;i++){
		fprintf(fp1,"%s\n%d\n",input[i].str,input[i].M);
		fprintf(fp2,"%s\n%d\n",input[i+576].str,input[i+576].M);
		fprintf(fp3,"%s\n%d\n",input[i+1152].str,input[i+1152].M);
		fprintf(fp4,"%s\n%d\n",input[i+1728].str,input[i+1178].M);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
}
void fuck_all(char file[],int N,int T,int s,int e)
{
	int sum=0,curr,counter=0,x,op;
	FILE *fp = fopen(file,"w");
	fprintf(fp,"%d\n",T);
	while(T--){
		strRan(N);
		curr=find(s,e);
		while(curr--){
			while(1){
				x=find(0,N-1);
				if(use[x]!='a'){
					use[x]='a';
					break;
				}
			}
		}
		fprintf(fp,"%s\n%d\n",use,find(1,s));
	}
	fclose(fp);
}
int main()
{
	char in_files[27][20]={"input/input00.txt" ,"input/input01.txt","input/input02.txt","input/input03.txt","input/input04.txt","input/input05.txt","input/input06.txt","input/input07.txt","input/input08.txt","input/input09.txt","input/input10.txt","input/input11.txt","input/input12.txt","input/input13.txt","input/input14.txt","input/input15.txt","input/input16.txt","input/input17.txt"};
	brutly(in_files[0],in_files[1],in_files[2],in_files[3]);
	gen(in_files[4],100,50,25,75,0);
	gen(in_files[5],200,25,50,125,0);
	gen(in_files[6],500,10,125,375,0);
	gen(in_files[7],1000,5,250,750,0);
	gen(in_files[8],5000,1,1250,3750,0);
	gen(in_files[9],0,0,0,0,1);
	gen(in_files[10],0,0,0,0,1);
	gen(in_files[11],0,0,0,0,1);
	gen(in_files[12],0,0,0,0,1);
	fuck_all(in_files[13],50,100,20,40);
	fuck_all(in_files[14],40,125,10,30);
	fuck_all(in_files[15],30,166,8,22);
	fuck_all(in_files[16],20,250,7,15);
	return 0;
}
