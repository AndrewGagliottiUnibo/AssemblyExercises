/*******************************************************************************
*                                                                              *
*                   Architetture dei sistemi di Elaborazione                   *
*                                                                              *
********************************************************************************

Elaborato 2
Descrizione: Dato un insieme di n punti m-dimensionali, scomporre in fattori 
             primi il prodotto degli indici del punto più vicino e di quello
			 più lontano rispetto a un punto p.

Note:
- I valori delle coordinate dei vari punti sono compresi nell’intervallo
  [-100;100].
- Per trovare la distanza minima e massima non è necessario calcolare la
  radice quadrata.
- I fattori primi devono essere riportati nell'array in ordine crescente.

********************************************************************************/

#include <stdio.h>

void main()
{
	// Input
	short pointP[] = { 73,-42,100,-84,0,-34,-71,52,-93 };								//Punto p
	short pointset[] = { 65,69,3,43,95,-40,60,-74,32,95,-27,-16,52,91,-85,87,69,41,-72,98,-85,45,61,-63,14,78,-35,64,-44,-20,3,-52,-94,-61,33,-13,-67,-54,-45,32,-76,88,26,10,8,-10,-80,-33,84,-71,32,25,-99,54,92,-81,-93,-34,-72,-84,96,97,71,-48,-9,-75,-22,12,-43,28,54,23,-14,-3,74,-72,-82,-49,30,-77,58,98,80,-74,48,78,-53,-48,-52,14,-20,67,-83,-61,36,-72,-84,-26,-82,-18,-88,9,-90,-44,-25,-91,-61,5,81,64,-99,56,36,-95,-41,99,-84,44,4,13,78,-74,-37,44,-53,87,5,-54,61,45,-89,44,-67,-53,-89,-52,88,23,51,39,39,42,-29,-15,12,25,-70,-88,81,38,-89,-27,71,5,4,87,-55,-34,-91,-11,4,93,44,-64,52,-43,22,-11,94,-90,-89,-7,93,65,75,-64,55,79,-69,23,57,-8,-34,-77,33,39,74,28,43,-75,-97,21,14,-38,-66,47,99,-65,34,-45,-98,42,-82,70,27,19,-20,-95,31,-32,-69,-34,-66,-14,32,-89,26,21,3,-88,-16,95,46,69,-94,-10,80,31,31,-73,-63,20,-55,77,20,-86,-26,-4,-3,-86,-41,68,98,-26,94,37,-14,-73,30,-78,-80,-22,32,21,71,-92,96,-50,63,-64,39,49,-25,3,-69,12,-79,-43,66,18,38,-70,-77,-11,54,16,97,-28,75,-30,-96,52,-100,8,-93,60,88,25,-95,12,-81,-77,33,-39,-25,10,-7,-6,-57,-19,16,-72,-38,-88,-15,91,-46,-57,67,-45,-89,24,-25,-7,-69,88,49,68,-4,-28,25,-4,-48,-46,-2,15,-3,63,-87,-57,-77,2,-72,-6,55,76,-10,88,-78,-84,5,45,58,51,0,-5,49,-60,-71,-12,61,26,99,72,57,-81,77,-93,15,71,-6,-9,-71,24,-68,10,-5,82,39,-44,-2,62,45,-21,67,80,39,1,54,-97,66,-44,34,26,-18,-3,3,-43,37,36,99,-18,-27,-48,23,-87,16,-66,19,91,100,67,2,73,90,100,82,20,-96,78,-20,-24,-46,11,-96,-63,57,3,-59,35,-94,-62,-55,-98,-43,-84,-11,-8,56,53,-36,5,83,64,-97,100,55,62,36,-17,16,83,-47,59,-45,23,-73,62,-52,-14,-44,-88,94,84,84,62,22,-1,16,74,11,-11,65,-49,13,76,-7,-9,8,-96,-17,96,68,58,-82,-77,85,-14,48,34,89,27,-56,-30,-4,-48,11,99,80,-58,-22,-45,-54,62,73,-74,-82,-99,-54,-21,-70,37,-46,-57,-98,-39,-56,-65,65,61,77,-65,52,82,86,85,-55,-6,55,-39,-36,-5,11,-35,27,-73,50,-95,86,93,-96,84,-60,-32,4,-49,-28,-100,-33,-65,-93,-25,-67,-81,-35,-58,4,-36,77,89,82,24,-54,86,-86,35,-74,89,16,76,11,-61,-50,73,56,94,96,-17,-23,35,12,-55,-73,20,-47,90,-38,-8,-100,-15,23,-15,-71,98,-89,-20,37,-45,-47,70,-76,-16,-16,-9,25,69,-75,-40,-36,-29,-54,-79,88,-59,-24,36,-3,27,32,-75,-27,34,89,-69,-47,-75,-90,-48,62,-25,-43,41,-71,8,10,-73,61,36,96,-15,64,-99,-72,29,-62,1,-2,88,21,-25,84,-91,23,-72,-4,-9,-4,-48,-62,-1,58,73,-1,89,-86,6,92,-21,32,-51,76,61,32,-54,-38,-29,6,-41,94,52,27,-78,32,-13,-9,-52,-83,-99,-89,-81,32,8,-2,-4,27,91,3,-61,15,33,10,-81,-44,-28,-1,-78,-23,-23,66,-75,85,-64,-41,-14,72,36,-59,-88,-2,67,-12,90,-33,12,17,-32,-37,-64,19,-29,68,-33,45,-39,-58,8,66,-41,88,-31,71,41,-65,87,-66,-4,-51,-89,24,92,50,-9,42,48,-56,20,52,44,56,-69,59,-59,58,-5,-43,18,-9,98,-56,-36,70,82,-76,-72,97,47,55,-19,-23,-80,-82,-49,12,28,22,-23,26,97,-84,22,56,-78,4,56,10,29,84,41,29,17,-96,-48 };//Array di short contenente
															//le coordinate degli n punti
	unsigned int m = 9;										//Numero delle dimensioni di
															//ogni punto
	unsigned int n = sizeof(pointset) / (sizeof(pointset[0]) * m); //Numero di punti

	// Output
	unsigned short indiceMin; 	//Indice del punto più vicino a p
	unsigned short indiceMax; 	//Indice del punto più lontano da p
	unsigned int prodotto; 		//Prodotto degli indici del punto più vicino e del punto
								//più lontano
	unsigned int fattori[100];	//Fattori primi trovati
	unsigned int numFattori;	// Numero dei fattori trovati

	// Blocco assembler
	__asm
	{
		/*--------------------------INIZIALIZZAZIONE REGISTRI COINVOLTI NELLA PARTE 1 DELL'ELABORATO--------------------------*/


        /*   inizializzo il registro ECX come contatore per spostarsi nell'array pointset e     *
        *    il registro EBX come contatore per muoversi nell'array pointP.                     */
        MOV EAX, n
        MOV EBX, m
        MUL EBX
        MOV ECX, EAX
        /*   ESI, EDI saranno i registri che conterranno uno la differenza euclidea massima,               *
        *    l'altro il massimo indiceMin. azzero poi ulteriori registri che mi potrebbero servire dopo    *
        *    ERRORE PRIMA CONSEGNA: ESI andava azzerato                                                    */
        XOR ESI, ESI
        MOV EDI, 2147483647
        XOR EAX, EAX

        /*   controllo sulle dimensioni di pointset: se m == n allora supponiamo che      *
        *    indice minimo e massimo coincidano, quindi...                                */
        CMP ECX, EBX
        JE Verifica1
        JMP CicloLettura

    Verifica1:
        MOV indiceMax, 0
        MOV indiceMin, 0
        JMP Prodotto

        /*   sposto nel registro AX l'ultima coordinata m dimensionale, la sotraggo alla        *
        *    ralativa dimensione nell'array pointP, elevo la differenza al quadrato e           *
        *    poi eseguo la PUSH di questo valore    nello stack. decremento il registro EBX     *
        *    e itero il processo fino a che non eseaurisco le prime m dimensioni.               *
        *    le condizioni del ciclo sono che EBX non sia minore di 0, per quanto               *
        *    riguarda il calcolo dell'indice, e ECX > 0 per il continuo della lettura di        *
        *    pointset. Restart è una etichetta che prevede il controllo su ECX e il reset       *
        *    del counter EBX dell'array pointP. Lo XOR di EDX, EAX ad ogni inizio ciclo mi serve*
        *    per resettare il registro che contiene l'estensione del segno                      */
    Restart:
        MOV EBX, m
        XOR EDX, EDX
        XOR EAX, EAX
        CMP ECX, 0
        JE Prodotto
    CicloLettura:
        MOV AX, pointset[ECX * 2 - 2]
        SUB AX, pointP[EBX * 2 - 2]
        IMUL AX
        /*soluzione al problema dei 16 bit*/
        PUSH DX
        PUSH AX
        DEC EBX
        /*esaurite le m dimensioni procedo al calcolo dell'indice*/
        CMP EBX, 0
        JE Indice
        /*se non ho esaurito le m dimensioni continuo a leggere l'array pointset*/
        DEC ECX
        JMP CicloLettura

        /*    esaurite le m dimensioni azzero qualche registro che mi tornerà utile    *
        *    e sfrutto il registro EBX come counter della POP                        */
    Indice:
        XOR EDX, EDX
        XOR EAX, EAX
        MOV EBX, m
        /*   itero la POP dello stack e sommo il valore estatto al registro EDX.    *
        *    itero il processo per le m dimensioni e poi procedo alla verifica      *
        *    della loro grandezza: se la somma è minore di quella massima che è     *
        *    contenuta in ESI, lo considero come temporaneo indiceMin e lo valuto   *
        *    nuovamente, altrimenti si aggiorna il massimo trovato, IndiceMax e     *
        *    torno a Restart                                                        */

        /*  ERRORE CONSEGNA 2: non ricordavo si parlasse di m-uple coordinate,      *
        *   si risolve semplicemente con un blocco dedicato alle divisioni dei      *
        *   due indici per m e poi al calcolo del loro prodotto                     *
        *   ERRORE CONSEGNA 3: 16 bit per la memorizzazione delle coordinate non    *
        *   erano sufficienti ho adottato una soluzione in CicloLettura, inoltre ho *
        *   risolto lo stesso problema per il salvataggio della coordinata in ECX   */
    IndiceMax:
        POP EAX
        ADD EDX, EAX
        DEC EBX
        CMP EBX, 0
        JG IndiceMax
        CMP EDX, ESI
        JL IndiceMin
        MOV ESI, EDX
        DEC ECX
        XOR EDX, EDX
        MOV EAX, ECX
        MOV EBX, m
        DIV EBX
        MOV indiceMax, AX
        JMP Restart

        /*   se abbiamo trovato un possibile indiceMin lo confrontiamo il precedente    *
        *    indiceMin, se risulta più grande torno a restart, altrimenti aggiorno      *
        *    indiceMin e torno a Restart                                                */
    IndiceMin:
        DEC ECX
        CMP EDX, EDI
        JGE Restart
        MOV EDI, EDX
        XOR EDX, EDX
        MOV EAX, ECX
        MOV EBX, m
        DIV EBX
        MOV indiceMin, AX
        JMP Restart

        /*alla fine effettuo il prodotto tra le coordinate*/
    Prodotto:
        MOV BX, indiceMax
        MOV AX, indiceMin
        MUL BX
        MOV prodotto, EAX

		/*--------------------------INIZIALIZZAZIONE REGISTRI COINVOLTI NELLA PARTE 2 DELL'ELABORATO--------------------------*/


		/*EBX è il registro che ci farà scorrere nell'array fattori e che salverà il numero di fattori stessi trovati*/
		XOR EBX, EBX
		/*EDI è il registro contatore dei fattori trovati*/
		XOR EDI, EDI
		/*EAX, ECX e EDX sono i registri che ci serviranno per scomporre in fattori primi il prodotto*/
		MOV EAX, prodotto
		MOV ECX, prodotto
		XOR EDX, EDX
		/*ESI sarà il registro divisore della nostra scomposizione*/
		MOV ESI, 2

		/*innanzitutto controllo che il prodotto degli indici non sia <= 0, in caso termino subito*/
	ControlloProdotto:
		CMP EAX, 0
		JLE Fine

		/*	azzero immediatamente il registro contenente il resto della divisione EAX/ESI	*
		*	e subito dopo averla effettuata controllo se il resto è rimasto a 0. nel caso	*
		*	in cui il resto sia uguale a 0 ho un fattore primo, altrimenti incremento ESI,	*
		*	ritorno al dividendo precedente e itero il processo								*/
	Scomposizione:
		XOR EDX, EDX
		DIV ESI
		CMP EDX, 0
		JE FattoreOk
		INC ESI
		MOV EAX, ECX
		JMP Scomposizione

		/*	se ho trovato un fattore primo incremento il contatore dei fattori primi	*
		*	trovati, aggiorno il backup del dividendo con il nuovo risultante con cui	*
		*	ricominciare alla prossima iterazione del clico di scomposizione; a questo	*
		*	punto verifico che il dividendo non sia uguale a 1 perchè in caso positivo	*
		*	ho esaurito il processo di scomposizione, in caso negativo incremento il	*
		*	registro EBX che ci consente di muoverci nell'array fattori e ritorno al	*
		*	processo di scomposizione													*/
	FattoreOk:
		INC EDI
		MOV ECX, EAX
		MOV fattori[EBX*4], ESI
		CMP ECX, 1
		JE Fine
		INC EBX
		JMP Scomposizione

		/*alla fine salvo il numero dei fattori primi trovati*/
	Fine:
		MOV numFattori, EDI
		/*----------------------------------------------------------------Nukerip was here-----------------------------------------------------------------*/
	}
	
	// Stampa su video
	printf("Indice del punto piu' vicino a p: %d\n", indiceMin);
	printf("Indice del punto piu' lontano da p: %d\n", indiceMax);
	printf("Prodotto degli indici: %d\n", prodotto);
	printf("Numero di fattori primi=%d\n", numFattori);
	for (unsigned int i = 0; i < numFattori; i++)
		printf("%d\n", fattori[i]);
}
