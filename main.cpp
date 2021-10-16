#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>
#include<cstdlib>
#include<ctime>
#include <fstream>
#include <sstream>
#include <string.h>
using namespace std;
int len=4; //len bits para cada parte; decimal y entera
vector<vector<int> > Binario(double a); //Convierte un decimal en binario
double Decimal(vector<vector<int> >); //Convertir un binario a decimal
double Rosembrock(vector<double> X ); //función Rosembrock para un vector de tamaño n
void Imprimir(vector< vector <vector<vector<int> > > >); //Imprimir poblaciones
vector< vector <vector<vector<int> > > >  Poblacion(int M, int n); //Genera la población aleatoria
//toma una muestra de la población
vector< vector <vector<vector<int> > > > Muestra(vector< vector <vector<vector<int> > > > poblacion, vector< double > fpoblacion); 

//Calcula la Distribucion de probabilidad
vector< vector< vector <double> > >  DP(vector< vector <vector<vector<int> > > > muestra, int t);

//Crea una nueva poblacion con la distribucion de probabilidades
vector< vector <vector<vector<int> > > > NuevaPoblacion(int n,vector< vector< vector <double> > > probabilidades);
double Wood(vector<double> X );
void ImprimirBinario(vector<vector<int> > B);
//Evalua la funcion Rosembrock con los valores de una poblacion
vector<double> FuncPob(vector< vector <vector<vector<int> > > > poblacion);
//Evalua la funcion Wood
vector<double> FuncPob2(vector< vector <vector<vector<int> > > > poblacion);
/*Retorna el indice donde se encuentra el valor mínimo, los indices de la función de entrada están relacionados
con los indices de la población  */
int Minimo(vector<double> fpoblacion);
int main() {
	srand(time(NULL));	
	//Algoritmo UMDA Rosembrock n=2
	
	//Generar la población aleatoria
	cout<<"----------------------------------------------------"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"Rosembrock n=2"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	vector< vector <vector<vector<int> > > > poblacion=Poblacion(20,2);
	//Evaluar la funcion en la poblacion inicial Rosembrock
	vector<double> fpoblacion=FuncPob(poblacion);
	int k=Minimo(fpoblacion);
	ofstream archivo;
	archivo.open("Rosembrock2.txt");
	for(int m=0; m<40;m++){ //bucle de repetición
		//imprime el minimo evaluado en la funcion
		cout<<"Minimo: "<<setprecision(30)<<fpoblacion[k]<<endl;
		
		//escribir el mínimo enun archivo de tecto	
		archivo<<setprecision(30)<<fpoblacion[k]<<endl;

		//Muestra, tomando los individuos que minimizan la funcion
		vector< vector <vector<vector<int> > > > muestra=Muestra(poblacion, fpoblacion);

		//Estimar la distribucion de probabilidad
		vector< vector< vector <double> > > probabilidades=DP(muestra,2);
		
		//Nueva poblacion
		poblacion.clear();
		poblacion = NuevaPoblacion(20,probabilidades);
		

		
		fpoblacion=FuncPob(poblacion);
		k=Minimo(fpoblacion);
		
		//Verificar la tolerancia
		double t=fpoblacion[k]-0.0;
		if(t<0){
			t=-t;
		}
		if(t<0.1){
			break;
		}
		//evalua la funcion en la nueva poblacion
		
	}	
	cout<<"MINIMO: "<<setprecision(30)<<fpoblacion[k]<<endl;
	archivo<<fpoblacion[k]<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	
	//Algoritmo UMDA Rosembrock n=100
	cout<<"\nRosembrock n=100"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	vector< vector <vector<vector<int> > > > poblacion2=Poblacion(20,100);
	ofstream archivo2;
	archivo2.open("Rosembrock100.txt");
	//Evaluar la funcion en la poblacion inicial
	vector<double> fpoblacion2=FuncPob(poblacion2);
	int k2=Minimo(fpoblacion2);
	for(int m=0; m<40;m++){ //bucle de repetición
		
		cout<<"Minimo: "<<setprecision(20)<<fpoblacion2[k2]<<endl;	
		archivo2<<setprecision(20)<<fpoblacion2[k2]<<endl;
		//Muestra, tomando los  individuos que minimizan la funcion
		vector< vector <vector<vector<int> > > > muestra=Muestra(poblacion2, fpoblacion2);
		

		//Estimar la distribucion de probabilidad
		vector< vector< vector <double> > > probabilidades=DP(muestra,100);
		
		//Nueva poblacion
		poblacion2.clear();
		poblacion2 = NuevaPoblacion(20,probabilidades);
		
		//evaluar la funcion en la nueva poblacion
		fpoblacion2=FuncPob(poblacion2);
		k2=Minimo(fpoblacion2);
		double t=fpoblacion2[k2]-0.0;
		if(t<0){
			t=-t;
		}
		if(t<0.1){
			break;
		}
		
	}
	cout<<"MINIMO: "<<setprecision(30)<<fpoblacion2[k2]<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	archivo2<<setprecision(30)<<fpoblacion2[k2]<<endl;
	
	//Algoritmo UMDA Wood Function
	cout<<"\nWood"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	vector< vector <vector<vector<int> > > > poblacion3=Poblacion(20,4);
	//Evaluar la funcion en la poblacion inicial
	vector<double> fpoblacion3=FuncPob(poblacion3);
	int k3=Minimo(fpoblacion3);
	ofstream archivo3;
	archivo3.open("Wood.txt");
	for(int m=0; m<40;m++){ //bucle de repetición
		
		cout<<"Minimo: "<<setprecision(30)<<fpoblacion3[k3]<<endl;	
		archivo3<<setprecision(30)<<fpoblacion3[k3]<<endl;
		//Muestra, tomando los  individuos que minimizan la funcion
		vector< vector <vector<vector<int> > > > muestra=Muestra(poblacion3, fpoblacion3);

		//Estimar la distribucion de probabilidad
		vector< vector< vector <double> > > probabilidades=DP(muestra,4);
		
		//Nueva poblacion
		poblacion3.clear();
		poblacion3 = NuevaPoblacion(20,probabilidades);
		double t=fpoblacion3[k3]-0.0;
		fpoblacion3=FuncPob(poblacion3);
		k3=Minimo(fpoblacion3);
		if(t<0){
			t=-t;
		}
		if(t<0.1){
			break;
		}
		//evaluala funcion en la nueva poblacion
		
	}
	cout<<"MINIMO: "<<setprecision(30)<<fpoblacion3[k3]<<endl;
	cout<<"----------------------------------------------------"<<endl;
	cout<<"----------------------------------------------------"<<endl;
	archivo3<<setprecision(30)<<fpoblacion3[k3]<<endl;
	return 0;
}
int Minimo(vector<double> fpoblacion){
	double min;
	int k=0;
	min=fpoblacion[0];
	for(int i=0; i<fpoblacion.size(); i++){
		if(min>=fpoblacion[i]){
			min=fpoblacion[i];
			k=i;
		}
	}
	return k;
}
double Wood(vector<double> X ){
	double temp=100*pow(pow(X[0],2)-X[1],2)+pow(X[0]-1,2)+pow(X[2]-1,2)+90*pow(pow(X[2],2)-X[3],2)+19.8*(X[1]-1)*(X[3]-1);
	double temp1=10.1*(pow(X[1]-1,2) + pow(X[3]-1,2));
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
vector<double> FuncPob(vector< vector <vector<vector<int> > > > poblacion){
	vector <vector<vector<int> > > temp;
		vector<double> fpoblacion; //Obtener los valores de la funcion en los elementos de la poblacion
		for(int i=0; i<20;i++){ //20 es el tamaño de la poblacion
			temp.clear();
			temp=poblacion[i];
			vector <double> eval;
			eval.clear();
			for(int j=0; j<temp.size(); j++){
				eval.push_back(Decimal(temp[j]));
			}
			double a=Rosembrock(eval);
			fpoblacion.push_back(a);	
		}
	return fpoblacion;
}

vector<double> FuncPob2(vector< vector <vector<vector<int> > > > poblacion){
	vector <vector<vector<int> > > temp;
		vector<double> fpoblacion; //Obtener los valores de la funcion en los elementos de la poblacion
		for(int i=0; i<20;i++){ //20 es el tamaño de la poblacion
			temp.clear();
			temp=poblacion[i];
			vector <double> eval;
			eval.clear();
			for(int j=0; j<temp.size(); j++){
				
				eval.push_back(Decimal(temp[j]));
			}
			double a=Wood(eval);
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
vector< vector <vector<vector<int> > > > NuevaPoblacion(int n,vector< vector< vector <double> > > probabilidades){
	vector< vector <vector<vector<int> > > > pob2;
	double p,q;
	vector <vector<vector<int> > > coordenada;
	for(int i=0; i<n; i++){ //Tamaño de la nueva poblacion
		coordenada.clear();
		vector<vector<int> > temp2; //Coordenada binaria que se agrega al vector coordenada
		for(int k=0; k<probabilidades.size();k++){ //tamaño del vector
			vector< vector <double> > temp=probabilidades[k];
			temp2.clear();
			vector<int> Entera;
			vector<int> Decimal;
			for(int j=0; j<len; j++){
				p=rand()%101;
				p=p/100;
				q=rand()%101;
				q=q/100;
				if(p<=temp[0][j] ){ //verfica la distribución de probabilidad por bit de la parte entera
					Entera.push_back(1);
				}
				else{
					Entera.push_back(0);
				}
				if(q<=temp[1][j] ){  //verfica la distribución de probabilidad por bit de la parte decimal
					Decimal.push_back(1);
				}
				else{
					Decimal.push_back(0);
				}
						
			}
			temp2.push_back(Entera);
			temp2.push_back(Decimal); 
	 		coordenada.push_back(temp2);   	
		}
		pob2.push_back(coordenada);
	}

	return pob2;
}
vector< vector <vector<vector<int> > > > Muestra(vector< vector <vector<vector<int> > > > poblacion, vector< double > fpoblacion){
	vector< vector <vector<vector<int> > > >  temp=poblacion;
	vector< vector <vector<vector<int> > > > muestra;
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
void Imprimir(vector< vector <vector<vector<int> > > > X){
	for(int i=0; i<X.size();i++){
		int n=X[i].size();
		for(int j=0; j<n; j++){
			cout<<"|";
		   ImprimirBinario(X[i][j]);
			cout<<"|";	
		}
		cout<<endl;
		
	}
}
vector< vector <vector<vector<int> > > > Poblacion(int M, int n){
	vector< vector <vector<vector<int> > > > poblacion; //Elemento a retornar
	vector <vector<vector<int> > > X;
	for (int i=0; i<M; i++){ //M tamaño de la poblacion
		X.clear();
		vector<vector<int> > Bin;
		for(int j=0; j<n; j++){
			Bin.clear();
			vector<int> Entera;
			vector<int> Decimal;
			for(int j=0;j<len;j++){
				int numero;
	            numero = rand() % 2;
    	    	Entera.push_back(numero);		
			}
			for(int j=0;j<len;j++){
				int numero;
	            numero = rand() % 2;
    	    	Decimal.push_back(numero);		
			}
			Bin.push_back(Entera);
			Bin.push_back(Decimal);
			X.push_back(Bin);	
	    }
	    poblacion.push_back(X);
	}
	return poblacion;
}
vector< vector< vector <double> > >  DP(vector< vector <vector<vector<int> > > > muestra, int t){
	vector< vector< vector <double> > > probabilidades; //Probabilidades por cada bit, t es la dimencion Rt
	for(int k=0; k<t; k++){
			vector< vector <double> > bit;
			vector <double> Entera;
			vector <double> Decimal;
			for(int i=0; i<len; i++){
				double conteo=0; //cuenta el número de1's en la i-esima posicion de la parte entera
				double conteo2=0;//cuenta el número de1's en la i-esima posicion de la parte decimal
				for(int j=0; j<muestra.size();j++){
					vector<int> temp=muestra[j][k][0];
					vector<int> temp2=muestra[j][k][1];
					if(temp[i]==1){
						conteo++; //En la parte entera
					}
					if(temp2[i]==1){
						conteo2++; //En la parte decimal
					}
					
				}
				if( conteo==muestra.size() ){
					Entera.push_back(0.85);
				}else if(conteo ==0){
					Entera.push_back(0.0000000000000001);
				}
				else{
					Entera.push_back(conteo/muestra.size());
						
				}
				
				if( conteo2==muestra.size() ){
					Decimal.push_back(0.85);
					
				}else if(conteo2 ==0){
					Decimal.push_back(0.0000000000000001);
					
				}
				else{
					Decimal.push_back(conteo2/muestra.size());
						
				}
				
			}
			bit.push_back(Entera);
			bit.push_back(Decimal);
			probabilidades.push_back(bit);
			
	}
	
	return probabilidades;
	
}
void ImprimirBinario(vector<vector<int> >  B){
	int n=B.size();
	for (int i=0; i<n; i++){
		int m=B[i].size();
		for(int j=0; j<m; j++){
			if(i==0){
				cout<<B[i][m-j-1];	
			}
			else{
				cout<<B[i][j];
			}
		}
		if(n>1 && i==0 ){
			cout<<".";
		}
	}
}
