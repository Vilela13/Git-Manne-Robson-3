/*
 * Modelo.hpp
 *
 *  Created on: 16/04/2015
 *      Author: mateus
 */

#ifndef MODELO_HPP_
#define MODELO_HPP_

#include "Biblioteca.hpp"


class No{

public:
    No();                                       // construtora da classe

 /* Escreve arquivo TXT */

    int NumPlantas;						// Número de plantas
    int NumEntregas;					// Número de entregas
    int NumVeiculos;					// Número de veículos

    double Velocidade;

    vector < int > TamanhoConjuntoVeiculoPlanta;
    vector < vector < int > > ConjuntoVeiculoPlanta;

    vector < int > TamanhoConjuntoDemandasEntrada;
    vector < vector < int > > ConjuntoDemandasEntrada;

    vector < vector < double > > Localizacao;
    vector < vector < double > > DistanciaPlantaEntrega;
    vector < vector < double > > DistanciaEntregaPlanta;

    vector < vector < vector < double > > > TempoParaDescarregamento;

    vector <  double  > TempoEntreChegadas;

    vector < vector < vector < double > > > TempoParaIrEmUmaEntradaEOutra;

    vector <  double  > TempoInicioEntrada;
    vector <  double  > TempoFinalEntrada;

    vector <  double  > TempoInicioPlanta;
    vector <  double  > TempoFinalPlanta;

    void PreencheEstrutura();
    void CriaTXT();

/* Le arquivo para resolver o CPLEX, parametros */
    ifstream arq;

    int NP;						// Número de plantas
	int NE;					// Número de entregas
	int NV;					// Número de veículos

	double V;

	vector < int > TCVP;
	vector < vector < int > > CVP;

	vector < int > TCDE;
	vector < vector < int > > CDE;

	vector < vector < double > > L;
	vector < vector < double > > Dpe;
	vector < vector < double > > Dep;

	vector < vector < vector < double > > > Pvi;

	vector <  double  >Omega;

	vector < vector < vector < vector < vector < double > > > > >Svii;

	vector <  double  > TminE;
	vector <  double  > TmaxE;

	vector <  double  > TminP;
	vector <  double  > TmaxP;

	int LeDados(char*);

/* Variaveis do CPLEX */

	vector < vector < vector < int > > > AlfaImprimir;
	vector < vector < vector < vector < vector < int > > > > > BetaImprimir;
	vector < double > ZeImprimir;
	vector < double > ZrImprimir;
	vector < vector < vector < double > > > TveiImprime;
	vector < double > TvImprime;



/* Funções Cplex */

    void Cplex(char *a);

/* Escrever em diretorio a saída */

    char *c1;
    char *c2;
    string Nome1;
    string Nome2;

 // Pegar o tempo

    double Tempo1;
    double Tempo2;

    ~No();       // Destruidora
};



No::No(){
	NumPlantas = 131313;
	NumEntregas = 131313;
	NumVeiculos  = 131313;
	NP  = 131313;
	NE  = 131313;
	NV  = 131313;
	V = 131313;
	Velocidade  = 131313;
}

void No::PreencheEstrutura(){

/* Coloca o numero de plantas, entregas, veiculos e velocidade */

	NumPlantas = NumeroDePlantasVariaveisFixas;
	NumEntregas = NumeroDeEntregasVariaveisFixas;
	NumVeiculos = NumeroDeVeiculosVariaveisFixas;
	Velocidade = VelocidadeVariaveisFixas;

/* Preenche o numero veiculos por planta  */

	TamanhoConjuntoVeiculoPlanta.resize( NumPlantas );
	TamanhoConjuntoVeiculoPlanta[0]=3;
	TamanhoConjuntoVeiculoPlanta[1]=2;

	ConjuntoVeiculoPlanta.resize( NumPlantas );
	ConjuntoVeiculoPlanta[0].resize( TamanhoConjuntoVeiculoPlanta[0] );
	ConjuntoVeiculoPlanta[1].resize( TamanhoConjuntoVeiculoPlanta[1] );

	int aux1;
	int aux2;
	aux1 = 0;
	aux2 = 0;
	for (int i = 0; i < NumVeiculos ; i ++){
		if( aux1 == TamanhoConjuntoVeiculoPlanta[aux2]){
			aux2 = aux2 + 1 ;
			aux1 = 0;
		}
		ConjuntoVeiculoPlanta[aux2][aux1] = i+1;
		aux1 = aux1 + 1;
	}

/* Preenche o numero de demandas por entrada  */

	TamanhoConjuntoDemandasEntrada.resize(NumEntregas);
	TamanhoConjuntoDemandasEntrada[0] = 2;
	TamanhoConjuntoDemandasEntrada[1] = 1;
	TamanhoConjuntoDemandasEntrada[2] = 3;
	TamanhoConjuntoDemandasEntrada[3] = 2;

	ConjuntoDemandasEntrada.resize(NumEntregas);
	for( int i = 0; i < NumEntregas ; i++){
		ConjuntoDemandasEntrada[i].resize( TamanhoConjuntoDemandasEntrada[i] );
		for( int j = 0; j < TamanhoConjuntoDemandasEntrada[i] ; j++){
			ConjuntoDemandasEntrada[i][j] = j + 1;
		}
	}

/* Preenche as localizações das plantas e entradas  */

	Localizacao.resize( NumPlantas + NumEntregas);
	for( int i = 0 ; i < NumPlantas + NumEntregas ; i++){
		Localizacao[i].resize( 2);
	}

	/* Localização plantas (x,Y)*/
	Localizacao[0][0]= -7;	Localizacao[0][1]= 1; // planta 1
	Localizacao[1][0]= -2;	Localizacao[1][1]= 1; // planta 2

	/* Localização entradas (x,Y)*/
	Localizacao[2][0]= -9;	Localizacao[2][1]= 9; //Entrada 1
	Localizacao[3][0]= -9;	Localizacao[3][1]= -5;//Entrada 2
	Localizacao[4][0]= -4;	Localizacao[4][1]= 6; //Entrada 3
	Localizacao[5][0]= 0;	Localizacao[5][1]= -5;//Entrada 4

/* Distâncias das Plantas para as Entradas */

	DistanciaPlantaEntrega.resize( NumPlantas);
	for( int i = 0; i <  NumPlantas; i++){
		DistanciaPlantaEntrega[i].resize( NumEntregas);
	}

	for( int i = 0; i <  NumPlantas; i++){
	    for( int j = NumPlantas; j <  (NumPlantas + NumEntregas); j++){
	    	DistanciaPlantaEntrega[i][j-NumPlantas] = sqrt( pow( Localizacao[i][0] - Localizacao[j][0],2) + pow( Localizacao[i][1] - Localizacao[j][1],2) ) / Velocidade;
	   	}
	}

/* Distâncias das Entradas para as Plantas */

	DistanciaEntregaPlanta.resize( NumEntregas);
		for( int i = 0; i <  NumEntregas; i++){
			DistanciaEntregaPlanta[i].resize( NumPlantas);
		}

	for( int i = NumPlantas; i <  (NumPlantas + NumEntregas); i++){
		for( int j = 0; j <  NumPlantas; j++){
			DistanciaEntregaPlanta[i-NumPlantas][j] = sqrt( pow( Localizacao[i][0] - Localizacao[j][0],2) + pow( Localizacao[i][1] - Localizacao[j][1],2) ) / Velocidade;
		}
	}

/* Tempo para descarregamento de cada veiculo */

	TempoParaDescarregamento.resize( NumVeiculos);
	for( int i = 0; i <  NumVeiculos; i++){
		TempoParaDescarregamento[i].resize( NumEntregas);
		for( int j = 0; j <  NumEntregas; j++){
			TempoParaDescarregamento[i][j].resize(TamanhoConjuntoDemandasEntrada[j]);
			for( int z = 0; z <  TamanhoConjuntoDemandasEntrada[j]; z++){
			TempoParaDescarregamento[i][j][z] = 0.2;
			}
		}
	}

/* Tempo entre chegadas */

	TempoEntreChegadas.resize(NumEntregas);
	for( int j = 0; j <  NumEntregas; j++){
		TempoEntreChegadas[j] = 0.3;
	}
/*  Tempo para ir em uma entrada e outra */

	 TempoParaIrEmUmaEntradaEOutra.resize(NumVeiculos);
	 for( int i = 0; i <  NumVeiculos; i++){
		 TempoParaIrEmUmaEntradaEOutra[i].resize(NumEntregas);
		for( int j = 0; j <  NumEntregas; j++){
			TempoParaIrEmUmaEntradaEOutra[i][j].resize(NumEntregas);
		}
	 }


	 aux1 = 0;
	 for( int i = 0; i < NumPlantas; i++){
		 for( int j = 0; j <  TamanhoConjuntoVeiculoPlanta[i]; j++){
			 for( int z = 0; z <  NumEntregas ; z++){
				 for( int k = 0; k <  NumEntregas ; k++){
					 TempoParaIrEmUmaEntradaEOutra[aux1][z][k] =  DistanciaEntregaPlanta[z][i] + 	DistanciaPlantaEntrega[i][k]  ;
				 	}
			 }
			 aux1 = aux1 + 1;
		 }
	 }

/*  Tempo inicio e termino Entrada */
	 TempoInicioEntrada.resize(NumEntregas);
	 for( int i = 0; i <  NumEntregas; i++){
		 TempoInicioEntrada[i] = 8;
	 }
	 TempoFinalEntrada.resize(NumEntregas);
	 for( int i = 0; i <  NumEntregas; i++){
		TempoFinalEntrada[i] = 16;
	 }

 /*  Tempo inicio e termino Planta */
	 TempoInicioPlanta.resize(NumPlantas);
	 for( int i = 0; i <  NumPlantas; i++){
		 TempoInicioPlanta[i] = 8;
	 }
	 TempoFinalPlanta.resize(NumPlantas);
	 for( int i = 0; i <  NumPlantas; i++){
		TempoFinalPlanta[i] = 16;
	 }


}

void No::CriaTXT(){

	ofstream Instancia;
	Instancia.open("T-M-V1-2P-4E-5C.txt");

cout << "T-M-V1-2P-4E-5C" << endl;
	Instancia <<"T-M-V1-2P-4E-5C" << endl;

cout << " Numero de Plantas " << endl << '\t';
    cout << NumPlantas << endl;
    Instancia << NumPlantas << endl;

cout << " Numero de Entregas " << endl << '\t';
    cout << NumEntregas << endl;
    Instancia << NumEntregas << endl;

cout << " Numero de Veículos " << endl << '\t';
    cout << NumVeiculos <<  endl;
    Instancia << NumVeiculos  << endl;

cout << " Velocidade " << endl << '\t';
	cout << Velocidade <<  endl;
    Instancia << Velocidade  << endl;

cout << "Conjunto de Veiculos por Planta " << endl;
    for( int i = 0; i <  NumPlantas; i++){
    	cout << '\t' << "Planta " << i + 1 <<  " ( " << TamanhoConjuntoVeiculoPlanta[i] << " ) -> ";
    	Instancia << TamanhoConjuntoVeiculoPlanta[i] << " ";
    	for( int j = 0; j <  TamanhoConjuntoVeiculoPlanta[i]; j++){
    		cout << ConjuntoVeiculoPlanta[i][j] << " ";
    		Instancia << ConjuntoVeiculoPlanta[i][j] << " ";
    	}
    	cout << endl;
    	Instancia << endl;
	}


cout << "Conjunto de Demandas por Entrega " << endl;
	for( int i = 0; i <  NumEntregas; i++){
		cout << '\t' << "Entrega " << i + 1 <<  " ( " << TamanhoConjuntoDemandasEntrada[i] << " ) -> ";
		Instancia << TamanhoConjuntoDemandasEntrada[i] << " ";
		for( int j = 0; j <  TamanhoConjuntoDemandasEntrada[i]; j++){
			cout << ConjuntoDemandasEntrada[i][j] << " ";
			Instancia << ConjuntoDemandasEntrada[i][j] << " ";
		}
		cout << endl;
		Instancia << endl;
	}

cout << "Distancia Planta - Entrega " << endl;
	cout << ' ';
	for( int j = 0; j <  NumEntregas; j++){
		cout << '\t' << j+1 ;
	}
	cout << endl;
	for( int i = 0; i <  NumPlantas; i++){
		cout << i+1 << '\t';
		for( int j = 0; j <  NumEntregas; j++){
			cout << DistanciaPlantaEntrega[i][j] << '\t';
			Instancia << DistanciaPlantaEntrega[i][j] << " ";
		}
		cout << endl;
		Instancia << endl;
	}

cout << "Distancia Entrega - Planta " << endl;
	cout << ' ';
	for( int j = 0; j <  NumPlantas; j++){
		cout << '\t' << j+1 ;
	}
	cout << endl;
	for( int i = 0; i <  NumEntregas; i++){
		cout << i+1 << '\t';
		for( int j = 0; j <  NumPlantas; j++){
			cout << DistanciaEntregaPlanta[i][j] << '\t';
			Instancia << DistanciaEntregaPlanta[i][j] << " ";
		}
		cout << endl;
		Instancia << endl;
	}

cout << "Tempo Para Descarregamento " << endl;

	for( int i = 0; i <  NumVeiculos; i++){
	cout << '\t' << '\t' << "Veiculo " << i+1 << endl;
	Instancia << i+1 << endl;
		for( int j = 0; j <  NumEntregas; j++){
			cout << "Entrega " << j+1 << " (" << TamanhoConjuntoDemandasEntrada[j] << ") " <<  '\t';
			Instancia << TamanhoConjuntoDemandasEntrada[j] << '\t';
			for( int z = 0; z <  TamanhoConjuntoDemandasEntrada[j]; z++){
			cout << TempoParaDescarregamento[i][j][z] << '\t';
			Instancia << TempoParaDescarregamento[i][j][z] << '\t';
			}
			cout << endl;
			Instancia << endl;
		}
	}

cout << " Tempo entre chagadas " << endl;

	for( int j = 0; j <  NumEntregas; j++){
		cout << TempoEntreChegadas[j] << '\t';
		Instancia << TempoEntreChegadas[j] << '\t';
	}
	cout << endl;
	Instancia << endl;

cout << " Tempo para ir de uma entrada a outra " << endl;
	for( int i = 0; i <  NumVeiculos; i++){
		cout << '\t' << '\t' << "Veiculo " << i+1 << endl ;
		Instancia << i+1 << endl;
		for( int j = 0; j <  NumEntregas; j++){
			cout  <<'\t' << j+1 ;
		}
		cout << endl;
		for( int j = 0; j <  NumEntregas; j++){
			cout << j+1 << '\t';
			for( int z = 0; z <  NumEntregas; z++){
				cout << TempoParaIrEmUmaEntradaEOutra[i][j][z] << '\t';
				Instancia << TempoParaIrEmUmaEntradaEOutra[i][j][z] << '\t';
			}
			cout << endl;
			Instancia << endl;
		 }
	}

cout << " Tempo Inicio Entrada " << endl;
	 for( int i = 0; i <  NumEntregas; i++){
		cout << i << ' ' << TempoInicioEntrada[i]<< endl;
		Instancia << TempoInicioEntrada[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;

cout << " Tempo Final Entrada " << endl;
	 for( int i = 0; i <  NumEntregas; i++){
		cout << i << ' ' << TempoFinalEntrada[i]<< endl;
		Instancia << TempoFinalEntrada[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;

cout << " Tempo Inicio Planta " << endl;
	 for( int i = 0; i <  NumPlantas; i++){
		 cout << i << ' ' << TempoInicioPlanta[i] << endl;
		 Instancia << TempoInicioPlanta[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;

cout << " Tempo Final Planta " << endl;
	 for( int i = 0; i <  NumPlantas; i++){
		 cout << i << ' ' << TempoFinalPlanta[i] << endl;
		 Instancia << TempoFinalPlanta[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;

    Instancia.close();
}

int No::LeDados(char *a){

	int Aux1;
	int comentarios;
	char *b;
	string Instancia;
	string CaminhoArquivo1;

	comentarios = 0;

	double AuxSvii;

// Abre arquivo das instâncias

	CaminhoArquivo1 = "./InstS/";

	b = new char[CaminhoArquivo1.size()+1];
	b[CaminhoArquivo1.size()]=0;
	memcpy(b,CaminhoArquivo1.c_str(),CaminhoArquivo1.size());
	strcat(b,a);

	arq.open(b);
	if (arq.is_open()){

	// le nome instância
		arq >> Instancia;
		if( comentarios == 1){
			cout << " Nome instancia "<<  Instancia << endl;
		}

	// le número de plantas
		arq >> NP;
		if( comentarios == 1){
			cout << " Numero de plantas "<<  NP << endl;
		}

	// le número de entregas
		arq >> NE;
		if( comentarios == 1){
			cout << " Numero de Entregas "<< NE << endl;
		}

	// le número de veículos
		arq >> NV;
		if( comentarios == 1){
			cout << " Numero de Veiculos "<< NV << endl;
		}

	// le V
		arq >> V;
		if( comentarios == 1){
			cout << " V "<< V << endl;
		}

	// le número de veículos por planta
		if( comentarios == 1){
			cout << "Conjunto de Veiculos por Planta " << endl;
		}
		TCVP.resize(NP);
		CVP.resize(NP);
		for( int i = 0; i < NP ; i++){
			arq >> Aux1;
			TCVP[i] = Aux1;
			if( comentarios == 1){
				cout << '\t' << "Planta " << i + 1 <<  " ( " << TCVP[i] << " ) -> ";
			}
			CVP[i].resize(Aux1);
			for( int j = 0; j < Aux1 ; j++){
				arq >>  CVP[i][j];
				if( comentarios == 1){
					cout << CVP[i][j] << " ";
				}
			}
			if( comentarios == 1){
				cout << endl;
			}
		}
		if( comentarios == 1){
			cout << endl;
		}

	// le número de demandas por entrega
		if( comentarios == 1){
			cout << "Conjunto de Demandas por Entrega " << endl;
		}
		TCDE.resize(NE);
		CDE.resize(NE);
		for( int i = 0; i < NE ; i++){
			arq >> Aux1;
			TCDE[i] = Aux1;
			if( comentarios == 1){
				cout << '\t' << "Entrega " << i + 1 <<  " ( " << TCDE[i] << " ) -> ";
			}
			CDE[i].resize(Aux1);
			for( int j = 0; j < Aux1 ; j++){
				arq >>  CDE[i][j];
				if( comentarios == 1){
					cout << CDE[i][j] << " ";
				}
			}
			if( comentarios == 1){
				cout << endl;
			}
		}
		if( comentarios == 1){
			cout << endl;
		}

	// le distâncias da planta as Entregas (tempo)
		Dpe.resize(NP);
		for(int p = 0; p < NP; p++){
			Dpe[p].resize(NE);
		}

		if( comentarios == 1){
			cout << "Distancia Planta - Entrega " << endl;
			cout << ' ';
			for( int e = 0; e <  NE; e++){
				cout << '\t' << e+1 ;
			}
			cout << endl;
		}
		for( int p = 0; p <  NP; p++){
			if( comentarios == 1){
				cout << p+1 << '\t';
			}
			for( int e = 0; e <  NE; e++){
				arq >> Dpe[p][e];
				if( comentarios == 1){
					cout << Dpe[p][e] << " ";
				}
			}
			if( comentarios == 1){
				cout << endl;
			}
		}

	// le distâncias das Entregas as plantas (tempo)
		Dep.resize(NE);
		for(int e = 0; e < NE; e++){
			Dep[e].resize(NP);
		}

		if( comentarios == 1){
			cout << "Distancia Entrega - Planta " << endl;
			cout << ' ';
			for( int p = 0; p <  NP; p++){
				cout << '\t' << p+1 ;
			}
			cout << endl;
		}
		for( int e = 0; e <  NE; e++){
			if( comentarios == 1){
				cout << e+1 << '\t';
			}
			for( int p = 0; p <  NP; p++){
				arq >> Dep[e][p];
				if( comentarios == 1){
					cout << Dep[e][p] << " ";
				}
			}
			if( comentarios == 1){
				cout << endl;
			}
		}

	// le tempos de processamento de cada veículo em cada entrega

		Pvi.resize( NV);
		for( int i = 0; i <  NV; i++){
			Pvi[i].resize( NE);
			for( int j = 0; j <  NE; j++){
				Pvi[i][j].resize(TCDE[j]);
			}
		}

		if( comentarios == 1){
			cout << "Tempo Para Descarregamento " << endl;
		}

		for( int i = 0; i <  NV; i++){
			arq >> Aux1;
			if( comentarios == 1){
				cout << '\t' << '\t' << "Veiculo " << Aux1 << endl;
			}
			for( int j = 0; j <  NE; j++){
				arq >> Aux1;
				if( comentarios == 1){
					cout << "Entrega " << j+1 << " (" << Aux1 << ") " <<  '\t';
				}
				for( int z = 0; z <  Aux1; z++){
					arq >> Pvi[i][j][z];
					if( comentarios == 1){
						cout << Pvi[i][j][z] << '\t';
					}
				}
				if( comentarios == 1){
					cout << endl;
				}
			}
		}

	// le tempos entre chegadas

		Omega.resize(NE);

		if( comentarios == 1){
			cout << " Tempo entre chagadas " << endl;
		}

		for( int e = 0; e <  NE; e++){
			arq >>Omega[e];
			if( comentarios == 1){
				cout <<Omega[e] << '\t';
			}
		}
		if( comentarios == 1){
			cout << endl;
		}

	// le  tempo para ir em uma entrada e outra

		Svii.resize(NV);
		for( int v = 0; v <  NV; v++){
			 Svii[v].resize(NE);
			 for( int e1 = 0; e1 <  NE; e1++){
				 Svii[v][e1].resize(TCDE[e1]);
				 for (int i = 0; i < TCDE[e1]; i++) {
					 Svii[v][e1][i].resize(NE);
					 for( int e2 = 0; e2 <  NE; e2++){
						 Svii[v][e1][i][e2].resize(TCDE[e2]);
					 }
				 }
			 }
		}



		if( comentarios == 1){
			cout << " Tempo para ir de uma entrada a outra " << endl;
		}
		for( int v = 0; v <  NV; v++){
			arq >> Aux1;
			if( comentarios == 1){
				cout << '\t' << '\t' << "Veiculo " << Aux1 << endl ;
				for( int e = 0; e <  NE; e++){
					cout  <<'\t' << e+1 ;
				}
				cout << endl;
			}
			for( int e1 = 0; e1 <  NE; e1++){
				if( comentarios == 1){
					cout << e1+1 << '\t';
				}
				for( int e2 = 0; e2 <  NE; e2++){
					arq >>  AuxSvii;
					for( int i = 0; i < TCDE[e1]; i++){
						for( int j = 0; j < TCDE[e2]; j++){
							Svii[v][e1][i][e2][j] = AuxSvii;
						}
					}
					if( comentarios == 1){
						cout << AuxSvii << '\t';
					}
				}
				if( comentarios == 1){
					cout << endl;
				}
			 }
		}







	// le  tempo inicio e final entrada

		TminE.resize(NE);
		if( comentarios == 1){
			cout << " Tempo Inicio Entrada " << endl;
		}
		 for( int i = 0; i <  NE; i++){
			 arq >> TminE[i];
			 if( comentarios == 1){
				 cout << i + 1 << ' ' << TminE[i]<< endl;
			 }
		 }
		 if( comentarios == 1){
			 cout << endl;
		 }

		TmaxE.resize(NE);
		if( comentarios == 1){
			cout << " Tempo Final Entrada " << endl;
		}
		for( int i = 0; i <  NE; i++){
			arq >> TmaxE[i];
			if( comentarios == 1){
				cout << i + 1 << ' ' << TmaxE[i]<< endl;
			}
		 }
		if( comentarios == 1){
			cout << endl;
		}

	// le  tempo inicio e final planta
		 TminP.resize(NP);
		 if( comentarios == 1){
			 cout << " Tempo Inicio Planta " << endl;
		 }
		 for( int i = 0; i <  NP; i++){
			 arq >> TminP[i];
			 if( comentarios == 1){
				 cout << i + 1 << ' ' << TminP[i] << endl;
			 }
		 }
		 if( comentarios == 1){
			 cout << endl;
		 }

		TmaxP.resize(NP);
		if( comentarios == 1){
			cout << " Tempo Final Planta " << endl;
		}
		for( int i = 0; i <  NP; i++){
			arq >> TmaxP[i];
			if( comentarios == 1){
				cout << i + 1 << ' ' << TmaxP[i] << endl;
			}
		}
		if( comentarios == 1){
			cout << endl;
		}




		arq.close();
		return 1;
	}else{
		cout << "         Fudeu Muito! Não abriu o arquivo " << a << endl << endl;
		return 0;
	}
}

void No::Cplex(char *a){

	char varName[24];

	int vAux;
	int Escreve;
	int EscreveVariaveis;
	int OutPut1;
	int OutPut2;
	int SaidaPastaSeparada;

	int UsouCaminhao;
	int AtendeCliente;

	Escreve = 0;
	EscreveVariaveis = 0;
	OutPut1 = 1;
	OutPut2 = 1;
	SaidaPastaSeparada = 1;

// Começa a escrever modelo do Cplex

	IloEnv env;
	IloModel model(env);

/* Declara variaveis */

// Variavel ALFA

	IloArray<IloArray<IloBoolVarArray> > Alfa(env, NV);
	for (int v = 0; v < NV; v++) {
		Alfa[v] = IloArray< IloBoolVarArray>(env, NE);
		for (int e = 0; e < NE; e++) {
			Alfa[v][e] =  IloBoolVarArray(env, TCDE[e]);
			for (int k = 0; k < TCDE[e]; k++) {
				sprintf(varName, "Alfa_%d_%d_%d", v, e,k);
				Alfa[v][e][k] = IloBoolVar(env,varName);
				if ( Escreve == 1){
					cout << " Alfa["<< v << "][" << e << "][" << k << "] "<< endl;
				}
			}
			if ( Escreve == 1){
				cout << endl;
			}
		}
	}

// Variavel BETA

	IloArray< IloArray< IloArray< IloArray< IloBoolVarArray > > > > Beta(env, NV);
	for (int v = 0; v < NV; v++) {
		Beta[v] = IloArray< IloArray< IloArray< IloBoolVarArray> > >(env, NE);
		for (int e1 = 0; e1 < NE; e1++) {
			Beta[v][e1] =  IloArray< IloArray< IloBoolVarArray > > (env, TCDE[e1]);
			for (int i = 0; i < TCDE[e1]; i++) {
				Beta[v][e1][i] =   IloArray< IloBoolVarArray >  (env, NE);
				for (int e2 = 0; e2 < NE; e2++) {
					Beta[v][e1][i][e2] =  IloBoolVarArray (env, TCDE[e2]);
					for (int j = 0; j < TCDE[e2]; j++) {
						if( e1 == e2 and i == j){

						}else{
							if( e1 == e2){
								sprintf(varName, "Beta_%d_%d_%d_%d_%d", v, e1, i, e2,  j);
								Beta[v][e1][i][e2][j] = IloBoolVar(env,varName);
								if ( Escreve == 1){
									cout << " Beta["<< v << "][" << e1 << "][" << i << "][" << e2 << "][" << j << "] "<< endl;
								}
							}
						}
					}
					if ( Escreve == 1){
						cout << endl;
					}
				}
			}
		}
		if ( Escreve == 1){
			cout << endl;
			cout << endl;
		}
	}



// Variavel Ze

	IloFloatVarArray Ze(env,NE);
	for (int e = 0; e < NE; e++) {
		sprintf(varName, "Ze_%d", e);
		Ze[e] = IloFloatVar(env,varName);
		if ( Escreve == 1){
			cout << " Z_Entrada["<< e << "] "<< endl;
		}
	}
	if ( Escreve == 1){
		cout << endl;
	}

// Variavel Zr

	IloFloatVarArray Zr(env,NP);
	for (int p = 0; p < NP; p++) {
		sprintf(varName, "Zr_%d", p);
		Zr[p] = IloFloatVar(env,varName);
		if ( Escreve == 1){
			cout << " Z_Retorno["<< p << "] "<< endl;
		}
	}
	if ( Escreve == 1){
		cout << endl;
	}

// Variavel Tvei

	IloArray < IloArray < IloFloatVarArray > > Tvei(env,NV);
	for (int v = 0; v < NV; v++) {
		Tvei[v] = IloArray < IloFloatVarArray >(env,NE);
		for (int e = 0; e < NE; e++) {
			Tvei[v][e] = IloFloatVarArray(env,TCDE[e]);
			for (int i = 0; i < TCDE[e]; i++) {
				sprintf(varName, "Tvei_%d_%d_%d", v, e, i);
				Tvei[v][e][i] = IloFloatVar(env,varName);
				if ( Escreve == 1){
					cout << " Tvei["<< v << "]["<< e << "]["<< i << "] "<< endl;
				}
			}
			if ( Escreve == 1){
				cout << endl;
			}
		}
	}
	if ( Escreve == 1){
		cout << endl;
	}

// Variavel Tvp

	IloFloatVarArray Tv(env,NV);
	for (int v = 0; v < NV; v++) {
		sprintf(varName, "Tv_%d", v);
		Tv[v] = IloFloatVar(env,varName);
		if ( Escreve == 1){
			cout << " Tv["<< v << "] "<< endl;
			cout << endl;
		}
	}

	if ( Escreve == 1){
		cout << endl;
	}



// Funcao Objetivo
	IloExpr funcao_objetivo(env);
	for (int e = 0; e < NE; e++) {
		funcao_objetivo += Ze[e];
	}
	for (int p = 0; p < NP; p++) {
		funcao_objetivo += Zr[p];
	}
	IloObjective obj = IloMinimize(env, funcao_objetivo);
	model.add(obj);
	funcao_objetivo.end();

// Restrição de não negatividade
	for (int e = 0; e < NE; e++) {
		IloExpr expr(env);
		expr += Ze[e];
		model.add(expr >= 0);
		expr.end();
	}

	for (int p = 0; p < NP; p++) {
		IloExpr expr(env);
		expr += Zr[p];
		model.add(expr >= 0);
		expr.end();
	}



// Restrição 1 : de que os caminhões temq ue suprir as demandas

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			IloExpr expr(env);
			for (int v = 0; v < NV; v++) {
				expr += Alfa[v][e][i];
			}
			model.add(expr == 1);
			expr.end();
		}
	}



// Restrição  2 : de lower bound Ze

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			for (int v = 0; v < NV; v++) {
				model.add( Ze[e] >=  Tvei[v][e][i] + Pvi[v][e][i] - BigM * ( 1 - Alfa[v][e][i]) );
			}
		}
	}



// Restrição  3 : de lower bound Tvi



	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			vAux = 0;
			for (int p = 0; p < NP; p++) {
				for (int v = 0; v < TCVP[p]; v++) {
					if ( Escreve == 1){
						cout << " Tvei[ " << vAux << "][" << e<< "][ " << i << "] >=  Tv[" << vAux << "] + Dpe[" << p << "][" << e << "] - BigM * ( 1 - Alfa[" << vAux << "][" << e << "][" << i << "])" << endl;
					}
					model.add(   Tvei[vAux][e][i] >=  Tv[vAux] + Dpe[p][e] - BigM * ( 1 - Alfa[vAux][e][i]) );
					vAux = vAux + 1;
				}
			}
		}
	}



// Restrição  4 : de lower bound Zr

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			vAux = 0;
			for (int p = 0; p < NP; p++) {
				for (int v = 0; v < TCVP[p]; v++) {
					if ( Escreve == 1){
						cout << " Zr[ " << p << "] >=  Tvei[" << vAux << "][" << e << "][" << i << "]+ Dep[" << vAux << "][" << e << "][" << i << "] + Dep[" << e << "][" << p << "] - BigM * ( 1 - Alfa[" << vAux << "][" << e << "][" << i << "])" << endl;
					}
					model.add( Zr[p] >=  Tvei[vAux][e][i] + Pvi[vAux][e][i] + Dep[e][p] - BigM * ( 1 - Alfa[vAux][e][i]) );
					vAux = vAux + 1;
				}
			}
		}
	}



// Restrição  6 e 7: de precedencia

	for (int e1 = 0; e1 < NE; e1++) {
		for (int i = 0; i < TCDE[e1]; i++) {
			for (int e2 = 0; e2 < NE; e2++) {
				for (int j = 0; j < TCDE[e2]; j++) {
					for (int v = 0; v < NV; v++) {
						if ( i == j and e1 == e2){

						}else{
							//if( e1 == e2){
								if ( Escreve == 1){
									cout << " BigM * ( 1 - Alfa[" <<v<< "][" <<e1<< "][" <<i<< "]) + BigM * ( 1 - Alfa[" <<v<< "][" <<e2<< "][" <<j<< "]) + BigM *(1- Beta[" <<v<< "][" <<e1<< "][" <<i<< "][" <<e2<< "][" <<j<< "])  + Tvei[" <<v<< "][" <<e2<< "][" <<j<< "] >= Tvei[" <<v<< "][" <<e1<< "][" <<i<< "] +  Pvi[" <<v<< "][" <<e1<< "][" <<i<< "] + Svii[" <<v<< "][" <<e1<< "][" <<i<< "][" <<e2<< "][" <<j<< "])" << endl;
								}
								model.add( BigM * ( 1 - Alfa[v][e1][i]) + BigM * ( 1 - Alfa[v][e2][j]) + BigM *(1- Beta[v][e1][i][e2][j])  + Tvei[v][e2][j] >= Tvei[v][e1][i] +  Pvi[v][e1][i] + Svii[v][e1][i][e2][j]);
								if ( Escreve == 1){
									cout << " BigM * ( 1 - Alfa[" <<v<< "][" <<e1<< "][" <<i<< "]) + BigM * ( 1 - Alfa[" <<v<< "][" <<e2<< "][" <<j<< "]) + BigM * Beta[" <<v<< "][" <<e1<< "][" <<i<< "][" <<e2<< "][" <<j<< "]  + Tvei[" <<v<< "][" <<e2<< "][" <<j<< "] >= Tvei[" <<v<< "][" <<e1<< "][" <<i<< "] +  Pvi[" <<v<< "][" <<e1<< "][" <<i<< "] + Svii[" <<v<< "][" <<e1<< "][" <<i<< "][" <<e2<< "][" <<j<< "])" << endl;
								}
								model.add( BigM * ( 1 - Alfa[v][e1][i]) + BigM * ( 1 - Alfa[v][e2][j]) + BigM * Beta[v][e1][i][e2][j]  + Tvei[v][e1][i] >= Tvei[v][e2][j] +  Pvi[v][e2][j] + Svii[v][e2][j][e1][i]);
							}
						//}
					}
				}
			}
		}
	}


// Restrição  8:

/*
	for (int v1 = 0; v1 < NV; v1++) {
		for (int v2 = 0; v2 < NV; v2++) {
			for (int e1 = 0; e1 < NE; e1++) {
				for (int i = 0; i < (TCDE[e1] - 1); i++) {
					if ( Escreve == 1){
						cout << "  Tvei[" <<v1<< "][" <<e1<< "][" <<i+1<< "] >= Tvei[" <<v2<< "][" <<e1<< "][" <<i<< "] + Omega["<<e1<<"]" << endl;
					}
						model.add(  Tvei[v1][e1][i+1] >= Tvei[v2][e1][i] + Omega[e1]);
				}
			}
		}
	}

*/
// Com o Big M

	for (int v1 = 0; v1 < NV; v1++) {
			for (int v2 = 0; v2 < NV; v2++) {
				for (int e1 = 0; e1 < NE; e1++) {
					for (int i = 0; i < (TCDE[e1] - 1); i++) {
						if ( Escreve == 1){
							cout <<" BigM * ( 1 - Alfa[" <<v1<< "][" <<e1<< "][" <<i<< "]) +  Tvei[" <<v1<< "][" <<e1<< "][" <<i<< "] >= - BigM * ( 1 - Alfa[" <<v2<< "][" <<e1<< "][" <<i<< "]) Tvei[" <<v2<< "][" <<e1<< "][" <<i<< "] + Omega["<<e1<<"]" << endl;
						}
							model.add( BigM * ( 1 - Alfa[v1][e1][i+1]) +  Tvei[v1][e1][i+1] >= - BigM * ( 1 - Alfa[v2][e1][i]) + Tvei[v2][e1][i] + Omega[e1]);
					}
				}
			}
		}

// Restrição  9:

	for (int v = 0; v < NV; v++) {
		for (int e1 = 0; e1 < NE; e1++) {
			for (int i = 0; i < TCDE[e1]; i++) {
				if ( Escreve == 1){
					cout << "  Tvei[" <<v<< "][" <<e1<< "][" <<i<< "] >= TminE[" << e1 <<"]" << endl;
				}
				model.add(  Tvei[v][e1][i] >= TminE[e1] );
				if ( Escreve == 1){
					cout << "  Tvei[" <<v<< "][" <<e1<< "][" <<i<< "] <= TmaxE[" << e1 <<"]" << endl;
				}
				model.add(  Tvei[v][e1][i] <= TmaxE[e1] );
			}
		}
	}

// Restrição  10:


	vAux = 0;
	for (int p = 0; p < NP; p++) {
		for (int v = 0; v < TCVP[p]; v++) {
			if ( Escreve == 1){
				cout << "  Tv[" <<vAux<< "] >= TminP[" << p <<"]" << endl;
			}
			model.add(  Tv[vAux] >= TminP[p] );
			if ( Escreve == 1){
				cout << "  Tv[" <<vAux<< "] <= TmaxP[" << p <<"]" << endl;
			}
			model.add(  Tv[vAux] <= TmaxP[p] );
			vAux = vAux + 1;
		}
	}


// Modelo
	IloCplex cplex(model);
	cplex.exportModel("model.lp");


	if(!opendir ("Out")){
		cout <<  "\n\n Nao tem diretorio \"Out\" !!        FUDEU MUITO!! \n" << endl;

		if(system("mkdir Out;") == 0){
			cout << " Criou pasta Out" << endl;
		}else{
			cout << " Problema ao criar pasta Out" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		if(!opendir ("Out")){
			cout << "\n Nao tem diretorio  \"InstS\" !!        FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"Out\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"Out\" !!  " << endl;
	}

	Nome1 = "./Out/";
	c1 = new char[Nome1.size()+1];
	c1[Nome1.size()]=0;
	memcpy(c1,Nome1.c_str(),Nome1.size());
	strcat(c1,a);

	cout << endl << endl << " arquivo a gravar a saida " << c1 << endl << endl;

	ofstream logfile1(c1);

	if(SaidaPastaSeparada == 1){
		cplex.setOut(logfile1);
	}
	cplex.setParam(IloCplex::TiLim, 120);

	Tempo1 = cplex.getCplexTime();

// Resolve o modelo.
	if (!cplex.solve()) {
		cerr << "Failed to optimize LP." << endl;
		throw(-1);
	}

	Tempo2 = cplex.getCplexTime();

	if(!opendir ("Sol")){
		cout <<  "\n\n Nao tem diretorio \"Sol\" !!        FUDEU MUITO!! \n" << endl;

		if(system("mkdir Sol;") == 0){
			cout << " Criou pasta Sol" << endl;
		}else{
			cout << " Problema ao criar pasta Sol" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		if(!opendir ("Sol")){
			cout << "\n Nao tem diretorio  \"Sol\" !!        FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"Sol\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"Sol\" !!  " << endl;
	}

	Nome2 = "./Sol/";
	c2 = new char[Nome2.size()+1];
	c2[Nome2.size()]=0;
	memcpy(c2,Nome2.c_str(),Nome2.size());
	strcat(c2,a);

	cout << endl << endl << " arquivo a gravar a ssolucao " << c2 << endl << endl;

	ofstream logfile2(c2);





	cout << "Solution status = " << cplex.getStatus() << endl;
	logfile2 <<  "Solution status = " << cplex.getStatus() << endl;
	cout << "Solution primal cost = " << cplex.getObjValue() << endl;
	logfile2 << "Solution primal cost = " << cplex.getObjValue() << endl;
	cout << "Solution dual cost = " << cplex.getBestObjValue() << endl ;
	logfile2 << "Solution dual cost = " << cplex.getBestObjValue() << endl ;
	cout << "Gap = " << 100 * ( cplex.getObjValue() - cplex.getBestObjValue() ) / cplex.getObjValue() << "%" << endl ;
	logfile2 << "Gap = " << 100 * ( cplex.getObjValue() - cplex.getBestObjValue() ) / cplex.getObjValue() << "%" << endl ;
	cout << "Tempo = " << Tempo2 - Tempo1 << " segundos. " << endl<< endl;
	logfile2 << "Tempo = " << Tempo2 - Tempo1 << " segundos. " << endl << endl;


// inicializa variaveis para imprimir

	AlfaImprimir.resize(NV);
	for (int v = 0; v < NV; v++) {
		AlfaImprimir[v].resize(NE);
		for (int e = 0; e < NE; e++) {
			AlfaImprimir[v][e].resize(TCDE[e]);
		}
	}

	BetaImprimir.resize(NV);
	for (int v = 0; v < NV; v++) {
		BetaImprimir[v].resize(NE);
		for (int e1 = 0; e1 < NE; e1++) {
			BetaImprimir[v][e1].resize(TCDE[e1]);
			for (int i = 0; i < TCDE[e1]; i++) {
				BetaImprimir[v][e1][i].resize(NE);
				for (int e2 = 0; e2 < NE; e2++) {
					BetaImprimir[v][e1][i][e2].resize(TCDE[e2]);
				}
			}
		}
	}

	ZeImprimir.resize(NE);
	ZrImprimir.resize(NP);

	TveiImprime.resize(NV);
	for (int v = 0; v < NV; v++) {
		TveiImprime[v].resize(NE);
		for (int e = 0; e < NE; e++) {
			TveiImprime[v][e].resize(TCDE[e]);
		}
	}

	TvImprime.resize(NV);

// Coloca valor das variaveis do modelo na estrutura do programa

	for (int v = 0; v< NV; v++) {
		for (int e = 0; e < NE; e++) {
			for( int i = 0; i < TCDE[e]; i++){
				AlfaImprimir[v][e][i] = cplex.getValue(Alfa[v][e][i]) ;
			}
		}
	}

	for (int v = 0; v< NV; v++) {
		for (int e1 = 0; e1 < NE; e1++) {
			for( int i = 0; i < TCDE[e1]; i++){
				for (int e2 = 0; e2 < NE; e2++) {
					for( int j = 0; j < TCDE[e2]; j++){
						if( e1 == e2 and i == j){

						}else{
							if( e1 == e2){
								BetaImprimir[v][e1][i][e2][j] = cplex.getValue(Beta[v][e1][i][e2][j]) ;
							}
						}
					}
				}
			}
		}
	}

	for (int e = 0; e < NE; e++) {
		ZeImprimir[e] = cplex.getValue(Ze[e]);
	}

	for (int p = 0; p < NP; p++) {
		ZrImprimir[p] = cplex.getValue(Zr[p]);
	}

	for (int v = 0; v < NV; v++) {
		for (int e = 0; e < NE; e++) {
			for( int i = 0; i < TCDE[e]; i++){
				TveiImprime[v][e][i] = cplex.getValue(Tvei[v][e][i]);
			}
		}
	}

	for (int v = 0; v < NV; v++) {
		TvImprime[v] = cplex.getValue(Tv[v]);
	}

// Imprimi Variaveis

	if( EscreveVariaveis == 1){

		for (int v = 0; v< NV; v++) {
			cout << " Veiculo " << v << endl;
			for (int e = 0; e < NE; e++) {
				for( int i = 0; i < TCDE[e]; i++){
					cout << Alfa[v][e][i].getName() << " [" << cplex.getValue(Alfa[v][e][i]) << "]  ";
					logfile2 << Alfa[v][e][i].getName() << " [" << cplex.getValue(Alfa[v][e][i]) << "]  ";
				}
			cout << endl;
			logfile2 << endl;
			}
		}

		for (int v = 0; v< NV; v++) {
			cout << " Veiculo " << v << endl;
			for (int e1 = 0; e1 < NE; e1++) {
				for( int i = 0; i < TCDE[e1]; i++){
					for (int e2 = 0; e2 < NE; e2++) {
						for( int j = 0; j < TCDE[e2]; j++){
							if( e1 == e2 and i == j){

							}else{
								if( e1 == e2){
									cout << Beta[v][e1][i][e2][j].getName() << " [" << cplex.getValue(Beta[v][e1][i][e2][j]) << "]  ";
									logfile2 << Beta[v][e1][i][e2][j].getName() << " [" << cplex.getValue(Beta[v][e1][i][e2][j]) << "]  ";
								}
							}
						}
					}
					cout << endl;
					logfile2 << endl;
				}
			}
		}

		for (int v = 0; v < NV; v++) {
			cout << " Veiculo " << v << endl;
			for (int e = 0; e < NE; e++) {
				for( int i = 0; i < TCDE[e]; i++){
					cout << Tvei[v][e][i].getName() << " [" << cplex.getValue(Tvei[v][e][i]) << "]  ";
					logfile2 << Tvei[v][e][i].getName() << " [" << cplex.getValue(Tvei[v][e][i]) << "]  ";
				}
				cout << endl;
				logfile2 << endl;
			}
		}

		vAux = 0;
		for (int p = 0; p < NP; p++) {
			for (int v = 0; v < TCVP[p]; v++) {
				cout << Tv[vAux].getName() << " [" << cplex.getValue(Tv[vAux]) << "]  ";
				logfile2 << Tv[vAux].getName() << " [" << cplex.getValue(Tv[vAux]) << "]  ";
				vAux = vAux + 1;
			}
			cout << endl;
			logfile2 << endl;
		}

	}




	if( OutPut1 == 1){
		vAux = 0;
		for (int p = 0; p < NP; p++) {
			for (int v = 0; v < TCVP[p]; v++) {
				cout << " Veiculo " << vAux + 1 << " Sai as ";
				logfile2 << " Veiculo " << vAux + 1 << " Sai as ";
				cout <<  cplex.getValue(Tv[vAux]) << endl;
				logfile2 <<  cplex.getValue(Tv[vAux]) << endl;
				for (int e = 0; e < NE; e++) {
					for( int i = 0; i < TCDE[e]; i++){
						if( cplex.getValue(Alfa[vAux][e][i]) == 1){
							cout << '\t' << " Entrega[Construcao->" << e+1 << "][Job->" << i+1<< "] as ";
							logfile2 << '\t' << " Entrega[Construcao->" << e+1 << "][Job->" << i+1<< "] as ";
							printf("%.2f", cplex.getValue(Tvei[vAux][e][i]) );
							logfile2 << cplex.getValue(Tvei[vAux][e][i]);
							cout << endl;
							logfile2 << endl;
						}
					}
				}
				vAux = vAux + 1;
			}
		}
	}

	if( OutPut2 == 1){

// Tempo de cada entrega em cada cliente

		cout << endl << endl;
		logfile2 << endl << endl;
		cout << "           Tempo de entrega em cada cliente         " << endl;
		logfile2 <<  "           Tempo de entrega em cada cliente         " << endl;
		for (int e = 0; e < NE; e++) {
			cout << " Cliente " << e +1 << "\t[ ";
			logfile2 << " Cliente " << e +1 << "\t[ ";
			printf("%.2f", TminE[e]);
			logfile2 << TminE[e];
			cout << "\t<=\t";
			logfile2 << "\t<=\t";
			for( int i = 0; i < TCDE[e]; i++){
				vAux = 0;
				for (int p = 0; p < NP; p++) {
					for (int v = 0; v < TCVP[p]; v++) {
						if( AlfaImprimir[vAux][e][i] == 1 ){
							//cout << "   Tvei[" << vAux << "][" << e << "][" << i <<"] " << TveiImprime[vAux][e][i];
							cout << "\t";
							logfile2 << "\t";
							printf("%.2f", TveiImprime[vAux][e][i]);
							logfile2 << TveiImprime[vAux][e][i];
							cout << "[v" << vAux + 1<< "]";
							logfile2 << "[v" << vAux + 1<< "]";
						}
						vAux++;
					}

				}
			}
			cout << "\t<=\t";
			logfile2 << "\t<=\t";
			printf("%.2f", TmaxE[e]);
			logfile2 << TmaxE[e];
			cout << "]" << endl;
			logfile2 << "]" << endl;
		}

// Veiculos usados

		cout << endl << endl;
		logfile2 << endl << endl;
		cout << "           Veiculos usados         " << endl;
		logfile2 << "           Veiculos usados         " << endl;
		vAux = 0;
		for (int p = 0; p < NP; p++) {
			cout << "Planta " << p + 1 << endl;
			logfile2 << "Planta " << p + 1 << endl;
			for (int v = 0; v < TCVP[p]; v++) {
				UsouCaminhao = 0;
				for (int e = 0; e < NE; e++) {
					for( int i = 0; i < TCDE[e]; i++){
						if( AlfaImprimir[vAux][e][i] == 1 ){
							UsouCaminhao = 1;
						}
					}
				}
				if( UsouCaminhao == 1){
					cout << "  Veiculo " << vAux + 1 << " \t[clientes ->\t";
					logfile2  << "  Veiculo " << vAux + 1 << " \t[clientes ->\t";
					for (int e = 0; e < NE; e++) {
						AtendeCliente = 0;
						for( int i = 0; i < TCDE[e]; i++){
							if( AlfaImprimir[vAux][e][i] == 1 ){
								AtendeCliente = 1;
							}
						}
						if( AtendeCliente == 1){
							cout << e + 1 << "\t";
							logfile2 << e + 1 << "\t";
						}
					}
					cout << "]" << endl;
					logfile2  << "]" << endl;
				}
				vAux++;
			}
			cout << endl;
			logfile2 << endl;
		}



	}

	logfile1.close();
	logfile2.close();

}

No::~No(){
}




#endif /* MODELO_HPP_ */
