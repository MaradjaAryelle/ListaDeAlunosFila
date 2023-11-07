#include <iostream>
#include <string>

using namespace std;

struct Conteudo{
	string titulo;
	Conteudo* next;
};

struct Disciplina {
    string nome;
    int creditos;
    Conteudo* conteudo;
    Disciplina* next;
};

struct Aluno {
    string nome;
    string cpf;
    int idade;
    string matricula;
    Disciplina* disciplina;
};

struct ElementoFila {
    Aluno aluno;
    ElementoFila* next;
};

void enqueue(ElementoFila*& inicio, ElementoFila*& fim, Aluno& aluno) {
    ElementoFila* elemento = new ElementoFila;
    elemento -> aluno = aluno;
    elemento -> next = NULL;
    
    if (inicio == NULL) {
        inicio = elemento;
        fim = elemento;
    } else {
        fim -> next = elemento;
        fim = elemento;
    }
}

Aluno dequeue(ElementoFila*& inicio, ElementoFila*& fim) {
    if (inicio == NULL) {
        cout << "Erro: Fila vazia" << endl;
        return Aluno();
        
    } else if(inicio == fim){
    	ElementoFila* aux = inicio;
    	inicio = NULL;
    	fim = NULL;
    	// testar erro aqui
    	Aluno alunoDeletado = aux -> aluno;
    	delete aux;
    	return alunoDeletado;
    	
	} else {
        ElementoFila* aux = inicio;
        inicio = inicio -> next;
        Aluno alunoDeletado = aux -> aluno;
        delete aux;
        return alunoDeletado;
    }
};
/// lembrar de testar se erro nao ta aqui, tirar if
bool isEmpty(ElementoFila*& inicio, ElementoFila*& fim) {
    if (inicio == NULL && fim == NULL){
    	return true;
	} else {
		return false;
	}
};

Aluno front(ElementoFila* inicio) {
    if (inicio == NULL) {
        cout << "Erro: Fila vazia" << endl;
        exit(1);
    }
    // ver se erro nao ta aqi
    return inicio -> aluno;
};

int size(ElementoFila* inicio) {
    int total = 0;
    ElementoFila* aux = inicio;
    
	while (aux != NULL) {
        aux = aux ->next;
        total++;
    }
    return total;
};

void adicionarDisciplina(Disciplina*& inicio, Disciplina disciplina) {
	Disciplina* newDisciplina = new Disciplina;
	newDisciplina -> nome = disciplina.nome;
	newDisciplina -> creditos = disciplina.creditos;
	newDisciplina -> conteudo = NULL;
	newDisciplina -> next = NULL;
	
	if (inicio == NULL){
		inicio = newDisciplina;
		return;
	}
	Disciplina *aux = inicio;
	
	while (aux -> next != NULL){
		aux = aux -> next;
	}
	aux -> next = newDisciplina;
	
};

void removerDisciplina(Aluno& aluno, string& nomeDisciplina) {
	Disciplina* anterior = NULL;
	Disciplina* disciplina = aluno.disciplina;
	
	while (disciplina != NULL) {
        if (disciplina -> nome == nomeDisciplina) {
            if (anterior == NULL) {
                aluno.disciplina = disciplina -> next;
                
            } else {
                anterior -> next = disciplina -> next;
            }
            
            cout << "Disciplina " << nomeDisciplina << " removida com sucesso!" << endl;
            return; 
        }
        
        anterior = disciplina;
        disciplina = disciplina -> next;
    }

    cout << "Voce solicitou a remocao de uma disciplina que nao existe na grade do aluno. Tente novamente." << nomeDisciplina << endl;
};

void listarDisciplinas(Disciplina* disciplina) {
    if (disciplina == NULL) {
        cout << "Nnenhuma disciplina inserida na grade curricular do aluno!" << endl;
        return;
    }

    cout << "Lista de disciplinas cursadas pelo aluno: " << endl;
    while (disciplina != NULL) {
        cout << " -> " << disciplina -> nome << endl;
        disciplina = disciplina -> next;
    }
};

void adicionarConteudo(Disciplina& disciplina, string& titulo) {
    Conteudo* newConteudo = new Conteudo;
    newConteudo -> titulo = titulo;
    newConteudo -> next = disciplina.conteudo;
    disciplina.conteudo = newConteudo;
};

void removerConteudo(Disciplina& disciplina, string& titulo) {
    Conteudo* anterior = NULL;
	Conteudo* conteudo = disciplina.conteudo;
	
	while (conteudo != NULL) {
        if (conteudo -> titulo == titulo) {
            if (anterior == NULL) {
                disciplina.conteudo = conteudo -> next;;
                
            } else {
                anterior -> next = conteudo -> next;
            }
            
            delete conteudo; 
            cout << "Conteudo removido da disciplina com sucesso!" << endl;
            return; 
        }
        
        anterior = conteudo;
        conteudo = conteudo -> next;
    }

    cout << titulo << " nao esta inserido na disciplina. Tente novamente." << endl;
};

void listarConteudos(Disciplina& disciplina) {
	Conteudo *conteudo = disciplina.conteudo;
	
    if (conteudo == NULL) {
        cout << "Nao ha enhum conteudo no plano de curso da disciplina!" << endl;
        return;
    }

    cout << "Lista de conteudos da disciplina: " << endl;
    while (conteudo != NULL) {
        cout << " -> " << conteudo -> titulo << endl;
        conteudo = conteudo -> next;
    }
};

void listarAlunos(ElementoFila* inicio) {
    ElementoFila* aux = inicio;
    
    if (inicio == NULL){
    	cout << "Nao ha alunos na fila!" << endl;
    	return;
	}
    
    while (aux != NULL) {
        Aluno aluno = aux-> aluno; 
        cout << "Nome do aluno: " << aluno.nome << endl;
        cout << "CPF: " << aluno.cpf << " - Idade: " << aluno.idade << " - Codigo de matricula: " << aluno.matricula << endl;

        Disciplina* disciplina = aluno.disciplina;
        
        while (disciplina != NULL) {
            cout << "Disciplina: " << disciplina->nome << " - Creditos: " << disciplina->creditos << endl;

            Conteudo* conteudo = disciplina->conteudo;
            cout << "Conteudos: ";
            while (conteudo != NULL) {
                cout << conteudo->titulo << ", ";
                conteudo = conteudo->next;
            }

            disciplina = disciplina->next;
        }
        aux = aux -> next;
    }
};

int main() {
	ElementoFila* inicio = NULL;
    ElementoFila* fim = NULL;

    Aluno aluno1;
    aluno1.nome = "ARYELE";
    aluno1.cpf = "123456789-01";
    aluno1.idade = 31;
    aluno1.matricula = "010203";
    aluno1.disciplina = NULL;
    
	enqueue(inicio, fim, aluno1);
	
    Aluno aluno2;
    aluno2.nome = "JEFFERSON";
    aluno2.cpf = "987654321-01";
    aluno2.idade = 30;
    aluno2.matricula = "145278";
    aluno2.disciplina = NULL;

    enqueue(inicio, fim, aluno2);

    cout << "Tamanho da fila: " << size(inicio) << endl;

    Disciplina* disciplina1 = NULL;
    Disciplina* disciplina2 = NULL;

    Disciplina d1;
    d1.nome = "POO";
    d1.creditos = 6;
    d1.conteudo = NULL;

    Disciplina d2;
    d2.nome = "Arquitetura e organizao de pcs";
    d2.creditos = 6;
    d2.conteudo = NULL;

    adicionarDisciplina(disciplina1, d1);
    adicionarDisciplina(disciplina2, d2);

    aluno1.disciplina = disciplina1;
    aluno1.disciplina = disciplina2;
    aluno2.disciplina = disciplina2;

    listarAlunos(inicio);

    listarDisciplinas(disciplina1);
    listarDisciplinas(disciplina2);

    string conteudo1 = "Tratamento de erro";
    adicionarConteudo(d1, conteudo1);

    listarConteudos(d1);

    string conteudo2 = "Hardware";
    adicionarConteudo(d2, conteudo2);

    listarConteudos(d2);

    string nomeRemover = "Estrutura de Dados";
    removerDisciplina(aluno1, nomeRemover);

    listarDisciplinas(disciplina1);
    
    nomeRemover = "Estrutura de Dados";
    removerDisciplina(aluno1, nomeRemover);

    listarDisciplinas(disciplina1);

    string conteudoRemover = "Arvore binaria";
    removerConteudo(d1, conteudoRemover);

    listarConteudos(d1);

    return 0;
}


