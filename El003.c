/*******************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 3
Descrizione: Data una sequenza di bit, restituire la lunghezza media (arrotondata
             all’intero più vicino), minima e massima delle sotto-sequenze di
			 bit (contigui) a 0 e a 1.

********************************************************************************/

#include <stdio.h>

void main()
{
	// Input
	unsigned char vet[] = { 0x1E, 0xFE };	//Sequenza di bit
	unsigned short int len = 13;				// Lunghezza (in bit) della sequenza
	
	// Output
	unsigned short int minLungSeq0;		//Lunghezza minima sotto-sequenza di 0
	unsigned short int maxLungSeq0;		//Lunghezza massima sotto-sequenza di 0
	unsigned short int mediaLungSeq0;	//Media arrotondata sotto-sequenze di 0
	unsigned short int minLungSeq1;		//Lunghezza minima sotto-sequenza di 1
	unsigned short int maxLungSeq1;		//Lunghezza massima sotto-sequenza di 1
	unsigned short int mediaLungSeq1;	// Media arrotondata sotto-sequenze di 1

	// Blocco assembler
	__asm
	{
		/*inizializzo le lunghezze in memoria nel caso non trovi valori corrispondenti da inserire*/
		MOV maxLungSeq0, 0
		MOV maxLungSeq1, 0
		MOV minLungSeq0, 0
		MOV minLungSeq1, 0
		MOV mediaLungSeq0, 0
		MOV mediaLungSeq1, 0

		/*--------------------------INIZIALIZZAZIONE REGISTRI COINVOLTI NELLA PARTE 1 DELL'ELABORATO--------------------------*/
		
		/****************************************************************************************************************************
		*	L'elevato numero di consegne fallite di questo elaborato  è dovuto purtroppo al fatto che stavo correggendo la parte	*
		*	sbagliata del programma quando invece dovevo controllare bene il calcolo della media, che svoglevo in modo sbagliato	*
		*	e c'era un piccolo errore nell'azzeramento del registro counter delle sottosequenze per quanto riguarda il conteggio	*
		*	delle sottosequenze trovate																								*
		*****************************************************************************************************************************/

		/*CONTEGGIO ZERO NELL'ARRAY*/
		/*registro che conta le sottosequenze di 0 massime*/
			XOR EAX, EAX
		/*registro che conta le sottosequenze di 0 minime*/
			MOV EBX, 0FFh
		/*registro usato come counter del ciclo di calcolo*/
			XOR ECX, ECX
		/*registro usato per analizzare il bit corrente*/
			XOR EDX, EDX
		/*registro che conta le sottosequenze di 0*/
			XOR ESI, ESI
		/*registro usato per muoversi nel vettore*/
			XOR EDI, EDI
		/*inserisco in CX il numero di bit da analizzare*/
			MOV CX, len
			JMP CicloWord0

		/*	nel caso di qualunque sia il valore di len procedo con l'analisi di un solo byte	*
		*	per ECX bit. l'analisi comincia con il caricamento in DL del numero esadecimale		*
		*	presente nel vettore in posizione EDI, procedo ad analizzare ogni singolo bit:		*
		*	con TEST verifico il valore dell'													*
		*	ultimo bit e se risulta essere pari a 0 incremento il registro contatore, altrimenti*
		*	ho incontrato un 1 che termina la mia sequenza attuale di 0. eseguita la valutazione*
		*	dello 0 eseguo uno shift logico a destra di un bit nel registro DL, decremento ECX e*
		*	procedo nella mia analisi dei bit													*/
		CicloByte0:
			MOV DL, vet[EDI]
		CicloBit0:
			TEST DL, 1
			JZ Zero
			JMP FineSequenza0
		ProssimoBit0:
			SHR DL, 1
			DEC ECX
			CMP ECX, 0
			JG CicloBit0
			JMP Controllo0

		/*ogni volta che incontro uno 0 incremento il registro counter*/
		Zero:
			INC ESI
			JMP ProssimoBit0

		/*	se arrivo al termine di una sequenza di lettura di 0, innanzitutto controllo che non	*
		*	abbia incontrato solo 1 per il momento, in caso negativo procedo con il salvattaggio	*
		*	della sequenza, altrimenti torno all'analisi logica dei bit. confronto il counter		*
		*	attuale di bit a 0 con quello massimo già incontrato, e decido come procedere se ho un	*
		*	nuovo minimo o un nuovo massimo. nel caso di nuovo massimo aggiorno sia il suo valore in*
		*	memoria che il registro counter massimo e alla fine torno all'analisi dei bit dopo aver	*
		*	azzerato anche il counter dei bit a 0 attuali											*
		*	un ulteriore controllo verifica il corretto salvataggio del minimo nel caso in cui non	*
		*	esista un minimo																		*/
		FineSequenza0:
			CMP SI, 0
			JE FineSalvo0
			CMP SI, AX
			JL Minimo0
			MOV maxLungSeq0, SI
			CMP BX, 0FFh
			JE Cambiamento0
			JMP ProceduraNormale0
		Cambiamento0:
			MOV BX, SI
			MOV minLungSeq0, SI
		ProceduraNormale0:
			MOV AX, SI
		FineSalvo0:
			XOR ESI, ESI
			JMP ProssimoBit0
		
		/*	nel caso di nuovo minimo possibile lo confronto con l'attuale minimo e se risulta maggiore	*
		*	o uguale torno all'analisi dei bit, altrimenti salvo il nuovo minimo in memoria e aggiorno	*
		*	il registro counter. al termine torno alla analisi dei bit									*/
		Minimo0:
			CMP SI, BX
			JGE FineSalvo0
			MOV minLungSeq0, SI
			MOV BX, SI
			JMP FineSalvo0

		/*	qui controllo che ci siano ulteriori byte da analizzare, eseguo lo shift logico a destra	*
		*	di ciò che rimane in EDX e lo confronto a 0. se è uguale a 0 salto a controllare che non ci *
		*	siano rimasti valori in ESI, altrimenti mi sposto in avanti nel vettore e sposto il valore	*
		*	dei bit da analizzare in CX per poterli analizzare nuovamente.								*
		*	a questo punto controllo il valore di ECX e se rimangono 8 o meno bit li vado ad analizzare *
		*	immediatamente altrimenti sottraggo 8 bit da ECX, copio il valore in EDX, eseguo lo shift	*
		*	logico a sinistra e poi imposto a 8 il counter di analisi del byte corrente, al termine		*
		*	torno alla analisi del singolo byte															*/
		Controllo0:
			SHR EDX, 16
			CMP DX, 0
 			JE ControlloSimax0
			INC EDI
			MOV CX, DX
		CicloWord0:
			CMP ECX, 8
			JLE CicloByte0
			SUB ECX, 8
			MOV EDX, ECX
			SHL EDX, 16
			MOV ECX, 8
			JMP CicloByte0

		/*	quest'ultima sezione effettua un controllo nel caso in cui siano rimasti sequenze valide da	*
		*	memorizzare. prima controllo che ci sia effettivamente una sequenza, poi che sia una		*
		*	sequenza massima, e nel caso di esito positivo la aggiorno, altrimenti controllo che sia una*
		*	sequenza minima, e nel caso la aggiorno. se tutti i controlli danno esito negativo procedo	*
		*	con la parte successiva del programma														*/
		ControlloSimax0:
			CMP SI, 0
			JE Parte2
			CMP SI, AX
			JL ControlloSimin0
			MOV maxLungSeq0, SI
		ControlloSimin0:
			CMP SI, BX
			JG Parte2
			MOV minLungSeq0, SI

		/*--------------------------INIZIALIZZAZIONE REGISTRI COINVOLTI NELLA PARTE 2 DELL'ELABORATO--------------------------*/

		Parte2:
		/*CONTEGGIO UNO NELL'ARRAY*/
		/*registro che conta le sottosequenze di 1 massime*/
		XOR EAX, EAX
		/*registro che conta le sottosequenze di 1 minime*/
		MOV EBX, 0FFh
		/*registro usato come counter del ciclo di calcolo*/
		XOR ECX, ECX
		/*registro usato per analizzare il bit corrente*/
		XOR EDX, EDX
		/*registro che conta le sottosequenze di 1*/
		XOR ESI, ESI
		/*registro usato per muoversi nel vettore*/
		XOR EDI, EDI
		/*inserisco in CX il numero di bit da analizzare*/
		MOV CX, len
		JMP CicloWord1

		/*	nel caso di qualunque sia il valore di len procedo con l'analisi di un solo byte	*
		*	per ECX bit. l'analisi comincia con il caricamento in DL del numero esadecimale		*
		*	presente nel vettore in posizione EDI, procedo ad analizzare ogni singolo bit:		*
		*	con TEST verifico il valore dell'													*
		*	ultimo bit e se risulta essere != da 0 incremento il registro contatore, altrimenti	*
		*	ho incontrato uno 0 che termina la mia sequenza attuale di 1. eseguita la valutazione*
		*	dell' 1 eseguo uno shift logico a destra di un bit nel registro DL, decremento ECX e*
		*	procedo nella mia analisi dei bit													*/
		CicloByte1:
			MOV DL, vet[EDI]
		CicloBit1:
			TEST DL, 1
			JNZ Uno
			JMP FineSequenza1
		ProssimoBit1:
			SHR DL, 1
			DEC ECX
			CMP ECX, 0
			JG CicloBit1
			JMP Controllo1

		/*ogni volta che incontro un 1 incremento il registro counter*/
		Uno:
			INC ESI
			JMP ProssimoBit1

		/*	se arrivo al termine di una sequenza di lettura di 1, innanzitutto controllo che non	*
		*	abbia incontrato solo 0 per il momento, in caso negativo procedo con il salvattaggio	*
		*	della sequenza, altrimenti torno all'analisi logica dei bit. confronto il counter		*
		*	attuale di bit a 1 con quello massimo già incontrato, e decido come procedere se ho un	*
		*	nuovo minimo o un nuovo massimo. nel caso di nuovo massimo aggiorno sia il suo valore in*
		*	memoria che il registro counter massimo e alla fine torno all'analisi dei bit dopo aver	*
		*	azzerato anche il counter dei bit a 1 attuali											*
		*	un ulteriore controllo verifica il corretto salvataggio del minimo nel caso in cui non	*
		*	esista un minimo																		*/
		FineSequenza1:
			CMP SI, 0
			JE FineSalvo1
			PUSH ESI
			CMP SI, AX
			JL Minimo1
			MOV maxLungSeq1, SI
			CMP BX, 0FFh
			JE Cambiamento1
			JMP ProceduraNormale1
		Cambiamento1:
			MOV BX, SI
			MOV minLungSeq1, SI
		ProceduraNormale1:
			MOV AX, SI
		FineSalvo1:
			XOR ESI, ESI
			JMP ProssimoBit1

		/*	nel caso di nuovo minimo possibile lo confronto con l'attuale minimo e se risulta maggiore	*
		*	o uguale torno all'analisi dei bit, altrimenti salvo il nuovo minimo in memoria e aggiorno	*
		*	il registro counter. al termine torno alla analisi dei bit									*/
		Minimo1:
			CMP SI, BX
			JGE FineSalvo1
			MOV minLungSeq1, SI
			MOV BX, SI
			JMP FineSalvo1

		/*	qui controllo che ci siano ulteriori byte da analizzare, eseguo lo shift logico a destra	*
		*	di ciò che rimane in EDX e lo confronto a 0. se è uguale a 0 salto a controllare che non ci *
		*	siano rimasti valori in ESI, altrimenti mi sposto in avanti nel vettore e sposto il valore	*
		*	dei bit da analizzare in CX per poterli analizzare nuovamente.								*
		*	a questo punto controllo il valore di ECX e se rimangono 8 o meno bit li vado ad analizzare *
		*	immediatamente altrimenti sottraggo 8 bit da ECX, copio il valore in EDX, eseguo lo shift	*
		*	logico a sinistra e poi imposto a 8 il counter di analisi del byte corrente, al termine		*
		*	torno alla analisi del singolo byte															*/
		Controllo1:
			SHR EDX, 16
			CMP DX, 0
			JE ControlloSimax1
			INC EDI
			MOV CX, DX
		CicloWord1:
			CMP ECX, 8
			JLE CicloByte1
			SUB ECX, 8
			MOV EDX, ECX
			SHL EDX, 16
			MOV ECX, 8
			JMP CicloByte1

		/*	quest'ultima sezione effettua un controllo nel caso in cui siano rimasti sequenze valide da	*
		*	memorizzare. prima controllo che ci sia effettivamente una sequenza, poi che sia una		*
		*	sequenza massima, e nel caso di esito positivo la aggiorno, altrimenti controllo che sia una*
		*	sequenza minima, e nel caso la aggiorno. se tutti i controlli danno esito negativo procedo	*
		*	con la parte successiva del programma														*/
		ControlloSimax1:
			CMP SI, 0
			JE Parte3
			PUSH ESI
			CMP SI, AX
			JL ControlloSimin1
			MOV maxLungSeq1, SI
		ControlloSimin1:
			CMP SI, BX
			JG Parte3
			MOV minLungSeq1, SI

		/*--------------------------INIZIALIZZAZIONE REGISTRI COINVOLTI NELLA PARTE 3 DELL'ELABORATO--------------------------*/

		Parte3:
		/*CONTEGGIO SEQUENZE NELL'ARRAY*/
		/*registro che conta le sottosequenze di 1*/
		XOR EAX, EAX
		/*registro che conta le sottosequenze di 0*/
		XOR EBX, EBX
		/*registro usato come counter del ciclo di calcolo*/
		XOR ECX, ECX
		/*registro usato per analizzare il bit corrente*/
		XOR EDX, EDX
		/*registro usato come booleano per distinguere 0 e 1*/
		MOV ESI, 2
		/*registro usato per muoversi nel vettore*/
		XOR EDI, EDI
		/*inserisco in CX il numero di bit da analizzare*/
		MOV CX, len
		JMP CicloSequenza

		/*	il ragionamento di analisi dei bit è identico ai precedenti, solo che questa	*
		*	volta saltiamo se troviamo un uno o uno 0 per una successiva analisi del		*
		*	carattere																		*/
		CicloByteS:
			MOV DL, vet[EDI]
		CicloBitS:
			TEST DL, 1
			JNZ Seq1
			JMP Seq0
		ProssimoBitS:
			SHR DL, 1
			DEC ECX
			CMP ECX, 0
			JG CicloBitS
			JMP Restart

		/*	essendo il registro booleano diverso da 0 e 1, posso valutare bene il primo carattere	*
		*	incontrato e settarlo a 0 o 1 e finchè incontrerò sempre un carattere uguale, il booleano*
		*	mi aiuterà a distinguere le diverse sequenze											*/
		Seq1:
			CMP ESI, 1
			JE ProssimoBitS
			MOV ESI, 1
			INC EAX
			JMP ProssimoBitS
		Seq0:
			CMP ESI, 0
			JE ProssimoBits
			MOV ESI, 0
			INC EBX
			JMP ProssimoBitS

		/*il ragionamento di spostamento nei vari byte è logicamente identico ai precedenti*/
		Restart:
			SHR EDX, 16
			CMP DX, 0
			JE SalvataggioDati
			INC EDI
			MOV CX, DX
		CicloSequenza:
			CMP ECX, 8
			JLE CicloByteS
			SUB ECX, 8
			MOV EDX, ECX
			SHL EDX, 16
			MOV ECX, 8
			JMP CicloByteS

		/*per praticità ho deciso di salvare i valori delle sequenze nelle rispettive medie*/
		SalvataggioDati:
			MOV mediaLungSeq1, AX
			MOV mediaLungSeq0, BX

		/*--------------------------INIZIALIZZAZIONE REGISTRI COINVOLTI NELLA PARTE 4 DELL'ELABORATO--------------------------*/

		/*CALCOLO MEDIA SOTTOSEQUENZE E SISTEMAZIONE RISULTATI*/
		/*registro usato per contenere il numero di bit a 1*/
			XOR EBX, EBX
		/*registro ospite del resto della media*/
			XOR EDX, EDX
		/*registro usato nella POP dei valori inseriti nello stack*/
			XOR ESI, ESI
		/*registro inizializzato al numero di sottosequenze a 1 trovate e usate come counter della POP*/
			MOV CX, mediaLungSeq1
			CMP ECX, 0
			JE Media

		/*	in questa prima parte conto tutti i bit a 1 eseguendo la POP delle varie	*
		*	sottosequenze trovate e sommandole tutte in EBX								*/
		PopSeq1:
			POP ESI
			ADD EBX, ESI
			XOR ESI, ESI
			DEC ECX
			CMP ECX, 0 
			JG PopSeq1

		Media:
		/*CALCOLO MEDIA SOTTOSEQUENZE*/
		/*registro usato come ospite del valore di len*/
			XOR EAX, EAX

		/*	EAX = len - bit a 1										*
		*	la media delle sottosequenze a 0 è un semplice calcolo	*
		*	( bit a 0 / sottosequenze a 0 ). salvo poi il dato		*/
			MOV AX, len
			SUB EAX, EBX
			MOV CX, mediaLungSeq0
			CMP ECX, 0
			JE Media1
			DIV ECX
			MOV mediaLungSeq0, AX
			SHL EDX, 1
			CMP ECX, EDX
			JG Media1
			INC mediaLungSeq0
		
		Media1:
		/*	EAX = EBX ( bit a 1 )									*
		*	la media delle sottosequenze a 1 è un semplice calcolo	*
		*	( bit a 1 / sottosequenze a 1 ). salvo poi il dato		*/
			XOR EAX, EAX
			XOR EDX, EDX
			MOV EAX, EBX 
			MOV CX, mediaLungSeq1
			CMP ECX, 0
			JE Fine
			DIV ECX
			MOV mediaLungSeq1, AX
			SHL EDX, 1
			CMP ECX, EDX
			JG Fine
			INC mediaLungSeq1

		Fine:
		/*----------------------------------------------------------------Nukerip was here-----------------------------------------------------------------*/
	}

	// Stampa su video
	printf("Lunghezza minima delle sotto-sequenze di 0: %d\n", minLungSeq0);
	printf("Lunghezza massima delle sotto-sequenze di 0: %d\n", maxLungSeq0);
	printf("Lunghezza Media delle sotto-sequenze di 0: %d\n", mediaLungSeq0);
	printf("Lunghezza minima delle sotto-sequenze di 1: %d\n", minLungSeq1);
	printf("Lunghezza massima delle sotto-sequenze di 1: %d\n", maxLungSeq1);
	printf("Lunghezza Media delle sotto-sequenze di 1: %d\n", mediaLungSeq1);
}

