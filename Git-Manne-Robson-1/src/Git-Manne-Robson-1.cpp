#include "Biblioteca.hpp"


int main(int argc, char **argv) {


	char *a;
	list<char*> ListaInstancias;
	string Nome;

	list<char*>::iterator it;

	ofstream escreve;

// RecriaInstancias

// -------------------------- Le arquivo com as instancias de Solomon e as guarda em uma lista ----------------------- //

	ifstream ArquivoInstanciaSaloman( "ArquivosSaloman.txt" );
	if(!ArquivoInstanciaSaloman){
		cout << " Arquivo nao Existe! \n FUDEU MUITO! \n";
	}else{


		ArquivoInstanciaSaloman >> Nome;
		while( Nome != "EOF"){
			a = new char[Nome.size()+1];
			a[Nome.size()]=0;
			memcpy(a,Nome.c_str(),Nome.size());
			cout << "  " << a  << endl ;
			ListaInstancias.push_back(a);
			ArquivoInstanciaSaloman >> Nome;
		}

		//cout << " Tamanho = " << ListaInstancias.size() << endl << endl;
	 }

	ArquivoInstanciaSaloman.close();


// -------------------------- Le nome dos arquivos Solomon, carrega os dados, cria arquivo do R, Excel e cria arquivo que pode ser lido pelo Modelo ----------------------- //

	DadosSaloman *InstanciaSaloman = new DadosSaloman;

	while( ListaInstancias.size() > 0){
		it = ListaInstancias.begin();
		a = *it;
		ListaInstancias.pop_front();
		//cout <<  " ai 1" << endl;

		cout << a << endl;

		//cout <<  " ai 2" << endl;

		InstanciaSaloman->CarregarNumeroNosCoordenadas(a);

		InstanciaSaloman->EscreverDadosLidosInstanciaSaloman();

		//cout << " entrei1" << endl;

		InstanciaSaloman->EscreverComandosR(a,'4');
		// 1 => .ps	  2 =>.png   3 =>.jpeg    4 =>.pdf

		//cout << " entrei2" << endl;

		InstanciaSaloman->EscreverComandosExcel(a);

		InstanciaSaloman->CriarInstanciaSaloman(a);
	}


	free(InstanciaSaloman);




// Resolve o problema


	No PreInstancia;


	ifstream ArquivoInstancia( "Instancias.txt" );
	ArquivoInstancia >> Nome;
	while( Nome != "EOF"){
		a = new char[Nome.size()+1];
		a[Nome.size()]=0;
		memcpy(a,Nome.c_str(),Nome.size());
		cout << a  << endl ;
		ListaInstancias.push_back(a);
		ArquivoInstancia >> Nome;
	}

	ArquivoInstancia.close();




 // ----------- Cria uma Instancia para testes -------------------------- //

	//PreInstancia.PreencheEstrutura();
	//PreInstancia.CriaTXT();

// ----------- Le um arquivo com as instancias a serem resolvidas pelo modelo, abre o arquivo com a instancia e o resolve -------------------------- //

	//cout << endl << endl << " Lendo arquivo " << endl << endl << endl;


	No *Instancia = new No;

	while( !ListaInstancias.empty()){
		it = ListaInstancias.begin();
		a = *it;
		ListaInstancias.pop_front();
		cout << " Modelo <= " << a << endl;

		Instancia->LeDados(a);
		Instancia->Cplex();
	}


	free(Instancia);




	//cout << endl << " BigM -> " << BigM << endl;




	cout << " Galo! \n";


}
