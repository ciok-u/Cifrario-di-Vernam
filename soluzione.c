#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Funzione cifratura e decifratura
void xor(char *input, char *key, char *output, int len_data) {
    
    for(int i = 0; i < len_data; i++) {

        //Utilizzo operatore xor per la cifratura/decifratura del testo
        output[i] = input[i] ^ key[i];
    }
    
    // Aggiunge il terminatore di stringa alla fine per sicurezza
    output[len_data] = '\0';
}


int main(){
    // Dichiarazione array
    char plaintext[24]; 
    char key[24];
    char cipher[24];
    char decipher[24];
    char riprova;

    // Inizio del ciclo principale del programma
    do {

        printf("Inserisci il plaintext:\n");
        // Legge la stringa 
        fgets(plaintext, sizeof(plaintext), stdin);
        

        // Scorre la stringa, tiene solo le lettere e le converte in minuscolo
        int j = 0;
        for(int i = 0; plaintext[i] != '\0'; i++){
            if(isalpha(plaintext[i])){
                
                plaintext[j] = tolower(plaintext[i]);
                j++;
            }
        }
        plaintext[j] = '\0'; 

        // Inserimento della chiave
        printf("Inserisci la chiave:\n");
        fgets(key, sizeof(key), stdin);

        // Rimuove il carattere "Invio" (\n) dalla chiave
        key[strcspn(key, "\n")] = 0; 

        int len_key = strlen(key);

        // Allunga la chiave ripetendola fino a coprire la lunghezza del plaintext (j)
        for(int i = 0; i < j; i++){
            key[i] = key[i % len_key]; 
        }
        key[j] = '\0'; 

        // Mando i valori alla funzione "xor" per cifrare il messaggio
        xor(plaintext, key, cipher, j);

        // Stampo il risultato in esadecimale
        printf("Testo cifrato (Hex): \n");
        for(int i = 0; i < j; i++) { 
            printf("%X", (char)cipher[i]);
        }
        printf("\n");

        // Mando i valori alla funzione "xor" per cifrare il messaggio
        xor(cipher, key, decipher, j);

        printf("Testo decifrato: \n");
        printf("%s\n", decipher);
        
        printf("Vuoi riprovare?(y/n)\n");

        while(1){
            
            scanf(" %c", &riprova);

            // Leva tutti i caratteri rimasti fino a fine riga
            while(getchar() != '\n');

            // Controllo validità: accetta solo 'n' oppure 'y'
            if(riprova != 'n' && riprova != 'y'){
                printf("Rispondi solo con y o n\n");
                continue; 
            } else {
                break; 
            }
        }
    
    // Se l'utente ha premuto 'y' il ciclo ricomincia da capo
    } while(riprova == 'y');

    printf("Programma terminato\n");
    return 0;
}
