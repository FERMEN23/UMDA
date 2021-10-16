#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include<cstdlib>
#include<ctime>
#include <sstream>
#include <string.h>
using namespace std;
vector<vector<int> > Binario(double a); //Convierte un decimal en binario
double Decimal(vector<vector<int> >); //Convertir un binario a decimal
double Rosembrock(vector<double> X ); 
void Imprimir(vector <vector<vector<int> > > X); 
bool Revisar(vector <double> A, double b);
vector <vector<vector<int> > > Poblacion(int M, int n); //Genera la población aleatoria
vector <vector<vector<int> > > Muestra(vector <vector<vector<int> > > poblacion, vector< double > fpoblacion); //toma una muestra de la población
vector< vector <double> > DP(vector <vector<vector<int> > > muestra,int t);
vector <vector<vector<int> > > NuevaPoblacion(int n,vector< vector <double> > probabilidades);
double Wood(double x1, double x2,double x3, double x4);
void ImprimirBinario(vector<int> B);
vector<double> FuncPob(vector <vector<vector<int> > > poblacion);
int main() {
	srand(time(NULL));	
	//Algoritmo UMDA

	//Generar la población aleatoria
	vector <vector<vector<int> > > poblacion=Poblacion(20,2);
	cout<<"Poblacion inicial\n";
	Imprimir(poblacion);
	for(int m=0; m<100;m++){ //bucle de repetición
		//Evaluar la funcion en la poblacion Rosembrock
		vector<double> fpoblacion=FuncPob(poblacion);
	//	cout<<endl;
		//for(int i=0; i<fpoblacion.size();i++){
		//	cout<<fpoblacion[i]<<" ";
		//}
		
		//Muestra, tomando los  individuos que minimizan la funcion
		vector <vector<vector<int> > > muestra=Muestra(poblacion, fpoblacion);
		
		//Estimar la distribucion de probabilidad
		vector< vector <double> > probabilidades=DP(muestra,2);
		//Nueva población
		poblacion.clear();
		poblacion = NuevaPoblacion(fpoblacion.size(),probabilidades);
	}
	cout<<"\nPoblacion final"<<endl;
	Imprimir(poblacion);
	vector<double> fpoblacion=FuncPob(poblacion);
	double min;
	int k=0;
	min=fpoblacion[0];
	for(int i=0; i<fpoblacion.size(); i++){
		if(min>=fpoblacion[i]){
			min=fpoblacion[i];
			k=i;
		}
	}
	cout<<"Minimo: ";
	for(int i=0; i< poblacion[k].size();i++){
		ImprimirBinario(poblacion[k][i]);
		cout<<" ";
	}
	cout<<fpoblacion[k];
	//for(int i=0; i<fpoblacion.size();i++){
	//	cout<<fpoblacion[i]<<endl;
	//}
	

	//for(int i=0; i< probabilidades.size();i++){
	//	int n=probabilidades[i].size();
	//	for(int j=0; j<n;j++){
	//		cout<<probabilidades[i][j]<<" ";
	//	}
	//	cout<<endl;
	//}
	
	return 0;
}

double Wood(double x1, double x2,double x3, double x4){
	double temp=100*pow(pow(x1,2)-x2,2)+pow(x1-1,2)+pow(x3-1,2)+90*pow(pow(x3,2)-x4,2)+19.8*(x2-1)*(x4-1);
	double temp1=10.1*(pow(x2-1,2) + pow(x4-1,2));
	return temp + temp1;
}
double Rosembrock(vector<double> X ){
	int n=X.size();
	double result=0;
	for(int i=0; i<n-1; i++){		
		result=100*pow((X[i+1]-pow(X[i],2)),2)+pow(1-X[i],2);
	}
	return result;
}
vector<double> FuncPob(vector <vector<vector<int> > > poblacion){
	vector<vector<int> > temp;
		vector<double> fpoblacion; //Obtener los valores de la funcion en los elementos de la poblacion
		for(int i=0; i<20;i++){
			temp.clear();
			temp=poblacion[i];
			vector <double> eval;
			eval.clear();
			for(int j=0; j<temp.size(); j++){
				vector<vector<int> > temp2;
				temp2.push_back(temp[j]) ;
				eval.push_back(Decimal(temp2));
			}
			double a=Rosembrock(eval);
			fpoblacion.push_back(a);	
		}
	return fpoblacion;
}
vector<vector<int> > Binario(double a){
	vector<int> A;
	//Convertir la parte entera de a
	int temp=floor(a);
	int cociente=floor(temp/2);
	int residuo=temp%2;
	A.push_back(residuo);
	while(cociente!=0){
		residuo=cociente%2;
		cociente=floor(cociente/2);
		A.push_back(residuo);
	}
	vector<vector<int> > B;
	B.push_back(A);
	//Convertir la parte decimal si tiene
	double decimal=a-temp;
	A.clear();
	if(decimal!=0){
		int entero=floor(decimal*2);
		double decim=(decimal*2)-entero;
		A.push_back(entero);
		while(decim!=0){
			entero=floor(decim*2);
			decim=(decim*2)-entero;
			A.push_back(entero);
		}
		B.push_back(A);
	}
	return B;
}
bool Revisar(vector <double> A, double b){
	int n = A.size();
	for (int i=0; i<n; i++){
		if(A[i]==b){
			return true;
		}
	}
	return false;
}
double Decimal(vector<vector<int> > A){
	double result=0;
	int n=A[0].size();
	for(int i=0;i<n;i++){
		result+=A[0][i]*pow(2,i);
	}
	if(A.size()>1){
		int m=A[1].size();
		for(int i =0; i<m; i++){
			result+=A[1][i]*pow(2,-(i+1));	
		}
		
	}
	
	return result;
}
vector <vector<vector<int> > > NuevaPoblacion(int n,vector< vector <double> > probabilidades){
	vector <vector<vector<int> > > pob2;
	double p;
	for(int i=0; i<n; i++){
		vector<vector<int> > coordenada;
		vector<int> temp2;
		for(int k=0; k<probabilidades.size();k++){
			temp2.clear();
			for(int j=0; j<16; j++){
			p=rand()%101;
			p=p/100;
			//cout<<"Probabilidad "<<probabilidades[i][j]<<endl;
			if(p<probabilidades[k][j] ){
				temp2.push_back(1);
			}
			else{
				temp2.push_back(0);
			}
 		  }
 		  coordenada.push_back(temp2);
		   //cout<<"  ";	
		}
		//cout<<endl;
		pob2.push_back(coordenada);
	}
	return pob2;
}
vector <vector<vector<int> > > Muestra(vector <vector<vector<int> > > poblacion, vector< double > fpoblacion){
	vector <vector<vector<int> > >  temp=poblacion;
	vector <vector<vector<int> > > muestra;
	int N=temp.size();
	N=floor(N/2);
	while(temp.size()>N){
		int M=temp.size();
		double min;
		int k=0;
		min=fpoblacion[0];
		for(int i=0; i<M; i++){
			if(min>=fpoblacion[i]){
				min=fpoblacion[i];
				k=i;
			}
		}
		muestra.push_back(temp[k]);
		temp.erase(temp.begin()+k);
	}
	return muestra;
}
void Imprimir(vector <vector<vector<int> > > X){
	for(int i=0; i<X.size();i++){
		int n=X[i].size();
		for(int j=0; j<n; j++){
		   ImprimirBinario(X[i][j]);
			cout<<" ";	
		}
		cout<<endl;
		
	}
}
vector <vector<vector<int> > > Poblacion(int M, int n){
	vector <vector<vector<int> > > poblacion;
	vector<vector<int> > X;
	for (int i=0; i<M; i++){
		X.clear();
		vector<int> Bin;
		for(int j=0; j<n; j++){
			Bin.clear();
			for(int j=0;j<16;j++){
				int numero;
	            numero = rand() % 2;
    	    	Bin.push_back(numero);		
			}
			X.push_back(Bin);	
	    }
	    poblacion.push_back(X);
	}
	return poblacion;
}
vector< vector <double> > DP(vector <vector<vector<int> > > muestra, int t){
	vector< vector <double> > probabilidades; //Probabilidades por cada bit
	for(int k=0; k<t; k++){
			vector <double > bit;
			for(int i=0; i<16; i++){
				
				double conteo=0;
				for(int j=0; j<muestra.size();j++){
					vector<int> temp=muestra[j][k];
					if(temp[i]==1){
						conteo++;
					}
				}
				if( conteo==muestra.size() ){
					bit.push_back(0.5);
				}else if(conteo ==0){
					bit.push_back(0.01);
				}
				else{
					bit.push_back(conteo/muestra.size());	
				}
				

			}
			probabilidades.push_back(bit);
	}
	return probabilidades;
	
}
void ImprimirBinario(vector<int> B){
	int n=B.size();
	for (int i=0; i<n; i++){
		cout<<B[n-i-1];
	}
}
