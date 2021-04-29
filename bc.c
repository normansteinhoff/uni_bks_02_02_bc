
// --------------------------------------------------------------------------------------

// Autor:
    // Norman Steinhoff

// Jahr
    // 2021

// --------------------------------------------------------------------------------------

// Verwendete Abkürzungen:
    // Vor. == Voraussetzung
    // Eff. == Effekt
    // Erg. == Ergebnis
    // Anm. == Anmerkung

// --------------------------------------------------------------------------------------

// Standard_Header einbinden
#include <stdio.h>
#include <stdbool.h>

// Konstanten
#define OK 0
#define ERROR 1
#define ADD '+'
#define SUB '-'
#define MUL '*'
#define DIV '/'

// Vor.:
// -
// Eff.:
// *    Falls { op } einen der Werte { ADD, SUB, MUl, DIV } hat, wird { acc } angepasst.
// *    Ansonsten wird ein Fehler registriert.
// Erg.:
// *    Falls ein Fehler registriert wurde, ist { ERROR } geliefert.
// *    Ansonsten ist { OK } geliefert.
// Anm.:
// -
int adjust_accumulator(int *acc, char op, int x) {

    // Ergebnis initialisieren
    int result = OK;

    // Anpassung des Akkumulators vornehmen
    switch (op) {
        case ADD: // Addition
            (*acc) += x;
            break;
        case SUB: // Subtraktion
            (*acc) -= x;
            break;
        case MUL: // Multiplikation
            (*acc) *= x;
            break;
        case DIV: // Division
            (*acc) /= x;
            break;
        default: // Ein Fehler ist aufgetreten.
            result = ERROR;
    }

    //Ergebnis liefern
    return result;
}

// Vor.:
// *    Die Datei { file } ist eine erfolgreich zum Lesen geöffnete Datei.
// Eff.:
// *    Die Anweisungen in der Datei { file } werden ausgeführt.
// Erg.:
// -
// Anm.:
// *    Sobald eine der Anweisungen nicht ausgeführt werden kann, wird die Funktion beendet.
void start_calculator_loop(FILE *file) {

    // Akkumulator initialisieren
    int acc = 0;

    // Start_Wert anzeigen
    printf("acc = %d\n", acc);

    // In der Schleife benötigte Variablen deklarieren
    char op;
    int x;
    int successfulScans;
    int adjustment_status;

    // Endlos_Schleife starten
    while (true) {

        // Eingaben lesen
        successfulScans = fscanf(file, " %c %d", &op, &x);

        // Prüfen, ob die Anzahl der Eingaben korrekt war
        if (2 != successfulScans) {

            // Abbruch
            return;
        }

        // Anpassung des Akkumulators
        adjustment_status = adjust_accumulator(&acc, op, x);

        // Prüfen, ob die Anpassung erfolgreich war
        if ( ERROR == adjustment_status ) {

            //Abbruch
            return;
        }

        //aktualisierten Wert des Akkumulators anzeigen
        printf("acc = %d\n", acc);
    }
}

// Vor.:
// *    Der Wert von { file_count } entspricht der Anzahl der Elemente in { file_list }.
// Eff.:
// *    Die in { file_list } angegebenen Dateien werden der Reihe nach verarbeitet.
// Erg.:
// *    Falls ein Fehler auftrat ist { ERROR }  geliefert.
// *    Ansonsten ist { OK } geliefert.
// Anm.:
// *    { OK } und { ERROR } sind Makro_Konstanten.
int process_files(int file_count, char *file_list[]) {

    // Ergebnis initialisieren
    int result = OK;

    // Datei_Zeiger deklarieren
    FILE *sourceFile;

    // über angegebene Dateien iterieren
    for (int a = 1; a < file_count; ++a) {

        // versuchen die aktuelle Datei zu öffnen
        sourceFile = fopen(file_list[a], "r");
        
        // prüfen, ob die Datei geöffnet wurde
        if (NULL == sourceFile) { // Die Datei konnte nicht geöffnet werden.
            
            // aufgetretenen Fehler registrieren
            result = ERROR;

            // Fehlermeldung ausgeben
            perror(file_list[a]);
        }
        else { // Die Datei wurde geöffnet.
            
            // Berechnungen durchführen
            start_calculator_loop(sourceFile);

            // Datei schließen
            fclose(sourceFile);
        }
    }

    // Ergebnis liefern
    return result;
}

// Vor.:
// -
// Eff.:
// *    Ein Segen für alle die in Mathe geschlafen haben :)
// Erg.:
// *    Falls ein Fehler auftrat ist { ERROR }  geliefert.
// *    Ansonsten ist { OK } geliefert.
// Anm.:
// *    { OK } und { ERROR } sind Makro_Konstanten.
int main(int argc, char *argv[]) {
    
    // Ergebnis initialisieren
    int result = OK;

    // Die Anzahl der Programm_Argumente überprüfen
    if (argc < 2) {

        // direkt mit der Standardeingabe arbeiten
        start_calculator_loop(stdin);
    }
    else {
        
        // angegebene Dateien verarbeiten
        result = process_files(argc, argv);
    }

    // Ergebnis liefern
    return result;
}
