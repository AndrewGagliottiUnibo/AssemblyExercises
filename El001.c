/*******************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 1

Descrizione: Data una stringa C (terminata dal carattere nullo), contenente una
			 frase (ossia parole separate da spazi e/o segni di punteggiatura),
			 trovare al suo interno la parola più lunga e successivamente 
			 cifrare/decifrare un testo con il cifrario di Vigenère, usando come
			 chiave la parola trovata.

Note:
- In caso di parole di uguale lunghezza, considerare la prima da sinistra.
- La parola più lunga va copiata in un array di caratteri come stringa C
  (terminata dal carattere nullo).
- I segni di punteggiatura da considerare sono: ".,;:'?!"
- Nel testo cifrato il codice ASCII di ogni carattere è aumentato del codice ASCII
  del corrispondente carattere nella parola chiave sovrapposta (e ripetuta se
  necessario) al testo.

********************************************************************************/

#include <stdio.h>

void main()
{
    // Input
	char frase[1024] = "Cantami, o Diva, del Pelide Achille l'ira funesta che infiniti addusse lutti agli Achei";
	char testo[1024] = "Questo e' il testo da cifrare";
	char decifra = 0; // 0 = cifra; 1 = decifra
	
	// Output
	char parolaMax[100];	//La parola più lunga
	char risultato[1024]; 	//Il testo cifrato/decifrato

	// Blocco assembler
	__asm
	{
        /*--------------------------INIZIALIZZAZIONE REGISTRI COINVOLTI NELLA PARTE 1 DELL'ELABORATO--------------------------*/


        /*registro usato per spostarsi nell'array*/
        XOR ECX, ECX
        /*registro usato per la posizione di inizio parola corrente*/
        XOR EDX, EDX
        /*registro usato come contatore della lunghezza della parola*/
        XOR EBX, EBX
        /*    registro usato per confrontare la lunghezza della parola    *
        *    inizializzato a 0 perchè così siamo sicuri che la prima    *
        *    parola venga sempre considerata                                */
        MOV EDI, 0


        /*------------------------------------INIZIO ANALISI PAROLA PIU' LUNGA------------------------------------*/


        /*    per ogni ciclo avremo che ECX indicherà sempre la posizione corrente nel vettore,                    *
        *    EDX indicherà sempre la posizione di inizio di una parola, AL analizzerà il carattere corrente        */
    Ciclo:
        MOV AL, frase[ECX]
            /*se la lettera incontrata corrisponde a uno spazio*/
            CMP AL, 32
            JE FineParola
            /*se la lettera incontrata corrisponde a !*/
            CMP AL, 33
            JE FineParola
            /*se la lettera incontrata corrisponde a '*/
            CMP AL, 39
            JE FineParola
            /*se la lettera incontrata corrisponde a ,*/
            CMP AL, 44
            JE FineParola
            /*se la lettera incontrata corrisponde a .*/
            CMP AL, 46
            JE FineParola
            /*se la lettera incontrata corrisponde a :*/
            CMP AL, 58
            JE FineParola
            /*se la lettera incontrata corrisponde a ;*/
            CMP AL, 59
            JE FineParola
            /*se la lettera incontrata corrisponde a ?*/
            CMP AL, 63
            JE FineParola
            /*se raggiungiamo la fine del vettore*/
            CMP AL, 0
            JE FineRicerca

            /*    se nessuno dei casi precedenti è stato valutato    incremento    *
        *    il counter della lunghezza e ritorno ad inizio ciclo        */
            INC EBX
            INC ECX
            JMP Ciclo

            /*    se si arriva alla fine di una parola confronto la sua lunghezza con        *
            *    quella della parola più lunga, se ho appena analizzato una                *
            *    parola più lunga di quella precedentemente salvata, la sostituisco        *
            *    con un ciclo di copia partendo dalla posizione EDX fino alla posizione    *
            *    ECX - 1.                                                                *
            *    Infine aggiorno i contatori della stringa alle nuove posizioni            */
        FineParola:
        CMP EBX, EDI
            JG CopiaParolaMax
            XOR EBX, EBX
            INC ECX
            MOV EDX, ECX
            JMP Ciclo

            /*    in caso si trovi una parola più lunga di quella già precedentemente salvata            *
            *    aggiorno la lunghezza della parola più lunga, poi copio dalla posizione indicata    *
            *    da EDX fino a quella di ECX -1                                                        */
        CopiaParolaMax:
        MOV EDI, EBX
            XOR EBX, EBX
            CicloCopia :
        MOV AL, frase[EDX]
            MOV parolaMax[EBX], AL
            INC EDX
            INC EBX
            CMP ECX, EDX
            JE Ciclo
            JMP CicloCopia

            /*    se si arriva a fine stringa si effettua un ultimo controllo sull'ultima        *
            *    parola e in caso di validità si effettua una copia altrimenti si prosegue    *
            *    con la seconda parte della consegna    dell'elaborato 1                        */
        FineRicerca:
        CMP EBX, EDI
            JG CopiaParolaMax
            MOV parolaMax[EDI], 0

            /*    in questa seconda parte useremo EDI per indicare la lunghezza della stringa    *
        *    parolaMax. Inizializzo gli altri registri. EAX sarà il registro ospite del    *
        *    carattere da cifrare/decifrare                                                */
        /*registro usato per spostarsi nell'array testo*/
            XOR ECX, ECX
            /*    registro usato per spostarsi nell'array parolaMax    *
            *    se l'array parolaMax è nullo allora non avviene        *
            *    nessuna cifratura/decifratura                        */
        Azzero:
        XOR EBX, EBX
            CMP EDI, 0
            JE CicloRisultato

            /*    controllo il valore della variabile decifra e decido    *
            *    in base al suo valore che operazione effettuare            */
            MOV AL, decifra
            CMP AL, 0
            JE Cifratura
            XOR EAX, EAX
            JMP Decifratura

            /*    sposto la prima lettera del testo da cifrare in AL    *
            *    poi ad esso sommo il valore ASCII della lettera in    *
            *    posizione EBX della parola scelta per cifrare,        *
            *    incremento poi i contatori fino alla fine della        *
            *    stringa da cifrare. quando raggiungo la fine di        *
            *    parolaMax, azzero EBX cosicché l'algoritmo di        *
            *    cifratura funzioni correttamente                    */
        Cifratura:
        CMP EBX, EDI
            JE Azzero
            MOV AL, testo[ECX]
            CMP AL, 0
            JE Fine
            ADD AL, parolaMax[EBX]
            MOV risultato[ECX], AL
            INC EBX
            INC ECX
            JMP Cifratura
            /*    analogamente a prima, motivo per cui è stato respinto    *
                    *    l'elaborato la prima volta, avevo letto male la consegna*
                    *    e non avevo capito di dover inserire anche la            *
                    *    decifratura; l'operazione è analoga a prima, solamente    *
                    *    che al posto di sommare il valore in ASCII devo            *
                    *    decrementarlo                                            */
        Decifratura:
        CMP EBX, EDI
            JE Azzero
            MOV AL, testo[ECX]
            CMP AL, 0
            JE Fine
            SUB AL, parolaMax[EBX]
            MOV risultato[ECX], AL
            INC EBX
            INC ECX
            JMP Decifratura

            /*    in quest'ultima parte avviene la copia del vettore nel    *
            *    caso in cui parolaMax o il testo da cifrare siano nulli    */
        CicloRisultato:
        MOV AL, testo[ECX]
            MOV risultato[EBX], AL
            INC EBX
            INC ECX
            CMP AL, testo[ECX]
            JZ Fine
            JMP CicloRisultato

            /*    inserimento del carattere terminatore a fine stringa sia se            *
            *    avviene la cifratura (double check, lavorare con le stringhe nel    *
            *    primo semestre è stato traumatico per me che non avevo mai            *
            *    programmato), sia che non avvenga                                    */
        Fine:
        MOV risultato[ECX], AL
	}

	// Stampa a video
	printf("Frase: %s\n", frase);
	printf("Testo: %s\n\n\n",testo);
	printf("Parola piu' lunga: %s\n\n", parolaMax);
	// Stampa su video testo cifrato
	printf("Risultato: %s\n\n", risultato);
	printf("Risultato (in esadecimale):\n");
	// N.B. Nella stringa precedente alcuni caratteri possono non essere stampabili: 
	//		crea anche una stringa con tutti i caratteri come codici ascii esadecimali
	char* t = risultato;
	while (*t)
	{
		printf("\\x%02X", (unsigned char)(*t++));
	}
}