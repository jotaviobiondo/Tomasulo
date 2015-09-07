#ifndef COMPONENTE_H
#define COMPONENTE_H

#include <stdbool.h>
#include "instrucao.h"
#include "fila.h"

#define MAX_RESERVA 100
#define	NUM_REGISTRADOR 32

typedef enum tipo_componente {LOAD, STORE, SOMADOR, MULTIPLICADOR} TipoComponente;

typedef struct registrador {
	int64_t valor;
	int qi;
	int id; 	//id da instrução que gera o valor
} Registrador;

typedef struct est_reserva{
	int id;
	Operacoes opcode;
	int qj;
	int qk;
	int vj;
	int vk;
	bool busy;
    int A;
} EstacaoReserva;

typedef struct comp_est_reserva {
	EstacaoReserva *est_reserva;
	int tam;
	int tamMax;
} ComponenteER;

typedef struct unidade_funcional {
	int id;
	Operacoes opcode;
	int vj;
	int vk;
	bool busy;
	int ciclos;
} UnidadeFuncional;

typedef struct comp_unidade_funcional {
	UnidadeFuncional *un_funcional;
	int tam;
	int tamMax;
} ComponenteUF;

typedef struct buffer{
	Operacoes opcode;
	int origem;
	int destino;
	bool busy;
} Buffer;

typedef struct comp_buffer {
	Buffer *buffer;
	int tam;
	int tamMax;
} ComponenteBuffer;

typedef struct un_endereco{
	Operacoes opcode;
	int origem;
	int destino;
	bool busy;
} UnidadeEndereco;

typedef struct campo_barramento {
	int64_t dado;
	int id;
} CampoBarramento;

typedef struct cdb {
	CampoBarramento *campo;
	int tamMax;
} CDB;


extern Fila fila;
extern Registrador registrador[NUM_REGISTRADOR];
extern UnidadeEndereco unidadeEndereco;
extern ComponenteER er_somador;
extern ComponenteER er_multiplicador;
extern ComponenteUF somador;
extern ComponenteUF multiplicador;
extern ComponenteBuffer load;
extern ComponenteBuffer store;
extern CDB barramento;

/* FILA */
void inicializaFila(int tamanho);

/* ESTAÇÃO DE RESERVA */
void inicializaER(ComponenteER *er, ComponenteUF *uf);
void estacaoInsere(ComponenteER *er, int id, Operacoes opcode, int qj, int qk, int vj, int vk, int A, int posicao);
void estacaoRemove(ComponenteER *er, int posicao);
int procuraEstacao(ComponenteER er);
bool estReservaCheia(ComponenteER er);
void mostraEstacao(ComponenteER *er, int tamanho);
char* erToString(EstacaoReserva er);

/* UNIDADE FUNCIONAL */
bool unFuncionalCheia(ComponenteUF uf);
int procuraUF(ComponenteUF uf, int posicao);
void uFuncionalInsere(ComponenteUF *uf, int posicao, int id, Operacoes opcode, int vj, int vk, int ciclos);
void uFuncionalRemove(ComponenteUF *uf, int posicao);
char* ufToString(UnidadeFuncional uf);

/* BUFFER LOAD/STORE */
void inicializaBuffer(ComponenteBuffer *buffer);
void bufferInsere(ComponenteBuffer *buf, Operacoes opcode, int origem, int destino);
int procuraBuffer(ComponenteBuffer buf);
bool bufferCheio(ComponenteBuffer buf);
int bufferLivre(ComponenteBuffer buf);
void bufferRemove(ComponenteBuffer *buf, int posicao);
char* bfToString(Buffer buffer);

/* UNIDADE DE ENDERECO*/
void uEnderecoInsere(UnidadeEndereco *ue, Operacoes opcode, int origem, int destino);
void uEnderecoRemove(UnidadeEndereco *ue);
bool uEnderecoCheia();
char* ueToString(UnidadeEndereco ue);

/* REGISTRADOR */
void inicializaRegistrador(Registrador reg[]);
void registradorMudaQI(Registrador reg[], int posicao, int id, int estacao, TipoComponente tipo);
int registradorObterQI(Registrador reg[], int posicao);
void registradorEscreve(Registrador reg[], int posicao, int64_t valor);
int procuraRegistrador(Registrador reg[], int estacao, TipoComponente tipo);

/* BARRAMENTO */
void inicializaBarramento(CDB *barramento, int tam_load, int tam_store, int tam_somador, int tam_mult);
void barramentoInsere(CDB *barramento, int64_t dado, int id, int posicao, TipoComponente tipo);
void barramentoLimpar(CDB *barramento);

#endif
