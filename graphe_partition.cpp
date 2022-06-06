#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#define MAX_ITER 20
#define VIE 9
using namespace std;


//Class Utilisable

class p_Graphe
{
private:
int N;
int ** graphe;
int ** T;
public:
p_Graphe(char*);
int get_N() ;
void print();
int get_poids(int, int);
int get_T(int n,int m);
void set_initia(int n,int m);
void set_decrim(int n,int m);
int f(int *A);
void RechercheTabou();
void print_T();
int  equals(int *A,int *B);
};







//Constructeur de ce classe



p_Graphe::p_Graphe(char* filename){
int number,i,j;
//ouvrir une flux
ifstream input_file(filename);
//lecture du nombre de villes
input_file >> number;
//initialise l'attribue num_cities
N=number;
//remplissage d'une matrice triangulaire nbr_ligne=num_cities-1 
graphe=new int* [N];
T=new int* [N];
cout<<N<<endl;
for(i=0;i<N;i++){
graphe[i]=new int[N-i];
T[i]=new int[N-i];
for(j=0;j<N-i-1;j++){
input_file >> number;
*(graphe[i]+j)=number;
 *(T[i]+j)=0;
}
}
input_file.close();
}
//Fin de d?finition



//retourn le nombre de villes
int p_Graphe::get_N(){
return N;
}


void p_Graphe::set_initia(int n,int m){
if(n<m)
 T[n][m-n-1]=VIE;
else
T[m][n-m-1]=VIE;
}

void p_Graphe::set_decrim(int n,int m){
if(n<m&&get_T(n,m)>0)
 T[n][m-n-1]-=1;
if(n>m&&get_T(n,m)>0)
T[m][n-m-1]-=1;
}


//Affichage du matrice des distances 
void p_Graphe::print(){
int i,j,k;
cout<<"Number of Point: "<<get_N()<<endl;
cout<<"Matrix of poids between point"<<endl;
for(i=0;i<get_N();i++){
for(k=0;k<i;k++){
cout<<*(graphe[k]+i-k-1)<<"\t"; 
}
cout<<0<<"\t"; 
for(j=0;j<get_N()-i-1;j++){
cout<<*(graphe[i]+j)<<"\t";
}
cout<<endl;
}
}

void p_Graphe::print_T(){
int i,j,k;
for(i=0;i<get_N();i++){
for(k=0;k<i;k++){
cout<<*(T[k]+i-k-1)<<"\t"; 
}
cout<<0<<"\t"; 
for(j=0;j<get_N()-i-1;j++){
cout<<*(T[i]+j)<<"\t";
}
cout<<endl;
}
}
//Fin de d?finition
//distances entre de villes m et n
int p_Graphe::get_poids(int n,int m){
if(n==m)
return 0;
else if(n<m)
return graphe[n][m-n-1];
else
return graphe[m][n-m-1];
}

int p_Graphe::get_T(int n,int m){
if(n==m)
return 0;
else if(n<m)
return T[n][m-n-1];
else
return T[m][n-m-1];
}
//fin
int p_Graphe::f(int *A){
	int i,j;
	int s=0;
	for(i=0;i<N-1;i++){
		for(j=i+1;j<N;j++){
			if(A[j]!=A[i]){
				s+=get_poids(i,j);
			}
		}
	}
	return s;
}
int p_Graphe::equals(int *A,int *B){
		int i;
		for(i=0;i<N;i++){
		if(A[i]!=B[i])
			return 0;
     	}
     	return 1;
}
 void p_Graphe::RechercheTabou()
 {
 	int i,b,j,p,o,m;
 	int ib,jb,is,js;
	//génaration du solution initiale
	int A0[N];
		for(i=0;i<N/2;i++){
		b=rand()%RAND_MAX;
		if(b%10>(N/2)){
			A0[i]=0;
			A0[N-i-1]=1;
		}
		else{
			A0[i]=1;
			A0[N-i-1]=0;
		}
	}
	//Best solution
	int B_A[N];
	for(i=0;i<N;i++)
	{
		B_A[i]=A0[i];
	}
	//seconde solution
	int SB_A[N];
	//Solution Courant
	int C_A[N];
	for(i=0;i<N;i++)
	{
		C_A[i]=A0[i];
	}
	//Voisinage
	int V_A[N];
	//Best Iteration
	int BI_A[N];
	for(i=0;i<N;i++)
	{
		BI_A[i]=A0[i];
	}
	//Best Value
	int best_f=f(A0);
	int k=0;
			/*	for(i=0;i<N;i++){
		printf("A0[%d]=%d\n",i,A0[i]);
	}*/
	while(k<MAX_ITER)
	{
		k++;		
		m=10000000;
		//Génération du s
		for(i=0;i<N-1;i++){
			for(j=i+1;j<N;j++){
					for(o=0;o<N;o++)
	    			{
					V_A[o]=C_A[o];
     				}
				if(V_A[j]!=V_A[i]){
				p=V_A[j];
				V_A[j]=V_A[i];
				V_A[i]=p;
				if(get_T(i,j)==0)
				{	
					printf("i=%d j=%d f(V_A)=%d f(BI_A)=%d\n",i,j,f(V_A),f(BI_A));
				for(o=0;o<N;o++)
	    			{
					printf("%d",V_A[o]);
     				}
     					printf("\n");
     			for(o=0;o<N;o++)
	    			{
					printf("%d",BI_A[o]);
     				}	
     			printf("\n");
					//printf("cc\n");
					if(f(V_A)<m&&equals(V_A,B_A)==0){
     				m=f(V_A);
     				for(o=0;o<N;o++)
	    			{
					SB_A[o]=V_A[o];
     				}
     				is=i;
     				js=j;
				 	}
				 	if(f(V_A)<f(BI_A)&&equals(V_A,B_A)==0){
					ib=i;
					jb=j;
					for(o=0;o<N;o++)
					BI_A[o]=V_A[o];
     			    }
				}
				if(f(V_A)<f(B_A)&&(get_T(i,j)>0))
				{
					ib=i;
					jb=j;
					for(o=0;o<N;o++)
	    			{	
					BI_A[o]=V_A[o];
     				}
				}
		     	}	
     		}
			}
			
			if(equals(BI_A,C_A)==0)	{
			for(o=0;o<N;o++)	
			C_A[o]=BI_A[o];
			}
     		else
     		{
     		printf("is=%d js=%d f(SB_A)=%d SB_A=",is,js,f(SB_A));
     		for(o=0;o<N;o++)
	    	{	
			C_A[o]=SB_A[o];
			BI_A[o]=SB_A[o];
			printf("%d",SB_A[o]);
     		}
     		ib=is;
     		jb=js;
     		//printf("ib=%d jb=%d",ib,jb);
			}
			 	printf("\n\n\n\n\n\n");
			if(best_f>f(BI_A)){
				best_f=f(BI_A);
					for(o=0;o<N;o++)
	    			{
					B_A[o]=BI_A[o];
     				}
			}
			//mis à jour list tabou
			
				for(o=0;o<N-1;o++)
					for(i=o+1;i<N;i++)
					{
	    			{	//printf("o=%d i=%d ib=%d jb=%d\n",o,i,ib,jb);
	    				if((o==ib&&i==jb)||(o==jb&&i==ib)){
	    				//printf("cc\n");
	    				set_initia(ib,jb);
	    				}
						else{
						set_decrim(o,i);
						}
     				}
     				}
		//Comparaison entre s et s_best
			printf("\n\n\n\n\n%d\n\n\n\n\n",k);
			print_T();
			}
			printf("%d\n",best_f);
 }
/*---------------------------------------APPLICATION-------------------------------
-------------------------------------
-----------------------------------------APPLICATION-------------------------------
-------------------------------------
-----------------------------------------APPLICATION-------------------------------
-----------------------------------*/
int main(){
int i;
char c;
string f;
char*filename;
cout<<"Enter the input file name : ";
cin>>f;
filename=(char*)f.c_str();
p_Graphe test(filename);
test.print();

test.RechercheTabou();

return 0;
}
