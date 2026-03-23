//PUNKT 2
#include <LPC21xx.H>

int main() {
    // 1. Ustawi pin 16 i TYLKO 16 portu P1 jako wyjściowy
    IO1DIR = 0x00010000; 

    // 2. Ustawi pin 16 i TYLKO 16 portu P1 na „1”
    IO1SET = 0x00010000;

    // 3. Ustawi pin 16 i TYLKO 16 portu P1 na „0”
    IO1CLR = 0x00010000;

    // 4. Wejdzie w pętle nieskończoną
    while(1) {
        // Pusta pętla
    }
}




//PUNKT3
#include <LPC21xx.H>

int main() {
    // konfiguracja wyjscia
    IO1DIR = 0x00010000; 

    while(1) {
        // Ustawienie pinu 16 na "1"
        IO1SET = 0x00010000;
        
        // Kasowanie pinu 16 (ustawienie "0")
        IO1CLR = 0x00010000;
        
        // 1 0 1 0 1 0... w IO1SET
    }
}



//PUNKT 4 
#include <LPC21xx.H>

// difinicja funkcji delay
// void - nic nie zwraca
void Delay() {
    int iLoopCounter;
    // petla for wykonujaca 1000 pustych przebiegów
    for(iLoopCounter = 0; iLoopCounter < 1000; iLoopCounter++) {
        // pusto w srodku - tylko czekamy
    }
}

int main() {
    // pin 16 jako wyjscie
    IO1DIR = 0x00010000; 

    while(1) {
        // ustawienie pinu na 1
        IO1SET = 0x00010000;
        
        // wywolujemy opoznienie miedzy set a clr
        Delay();
        
        // ustawienie pinu na 0
        IO1CLR = 0x00010000;
        
        // dodajemy delay zeby zobaczyc 0 na pinie (extra)
        Delay();
    }
}
// delay zajmuje 0.00666842 sec
// zmienimy w forze na 1499600 iteracji




//PUNKT 5 
#include <LPC21xx.H>

void Delay() {
    int iLoopCounter;
    // zmiana w forze
    for(iLoopCounter = 0; iLoopCounter < 1499600; iLoopCounter++) {

    }
}

int main() {

    IO1DIR = 0x00010000; 

    while(1) {

        IO1SET = 0x00010000; // tutaj breakpoint i zerujemy licznik
        
        Delay();
        
        IO1CLR = 0x00010000; // tutaj tez
        

    }
}

// 1499600 iteracji podzielic na 1000 -> okolo 1500 - nasz nowy mnoznik do podawania delay w ms






// PUNKT 6
#include <LPC21xx.H>

// dodajemy (int iDelayInMS) zeby widzialo co wpisujemy w main
void Delay(int iDelayInMS) {
    int iLoopCounter;
    
    // tworzymy zmienna pomocnicza która mnozy milisekundy przez przelicznik (2500 bo 1500 jednak cos nie styka)
    int iIterations = iDelayInMS * 2500; 
    
    // w petli uzywamy obliczonej liczby iteracji
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {
        // pusto
    }
}

int main() {
    IO1DIR = 0x00010000; 

    while(1) {
        IO1SET = 0x00010000; // breakpoint
        
        Delay(1); // delay 1000 dla sekundy i 1 dla 1ms
        
        IO1CLR = 0x00010000; //breakpoint
    }
}








//PUNKT7
#include <LPC21xx.H>

// delay z mnoznikiem 2500
void Delay(int iDelayInMS) {
	
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
	
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

int main() {
    // pin 16 jako wyjscie (maska dla LED0)
    IO1DIR = 0x00010000; 

    while(1) {
        // zapalamy diode (1)
        IO1SET = 0x00010000;
        Delay(1000); // czekamy sekundke
        
        // gasimy diode
        IO1CLR = 0x00010000;
        Delay(1000); // czekamy sekundke
    }
}
// obserwujemy pin 16 w symulatorze po kliknieciu f5 - zapala sie i znika co sekunde






//PUNKT 8
#include <LPC21xx.H>

// delay z mnoznikiem 2500
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

int main() {
    IO1DIR = 0x00010000; // pin 16 na wyjscie

    while(1) {
        IO1SET = 0x00010000; // dioda ON
        Delay(50);           // czekaj 50 ms
        
        IO1CLR = 0x00010000; // dioda OFF
        Delay(50);           // czekaj 50 ms - razem 10Hz
    }
}





//PUNKT 9
#include <LPC21xx.H>

// definicja maski bitowej dla diody LED0 (pin 16)
#define LED0_bm 0x00010000

// stary dobry delay z 2500
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

int main() {
    // ustawienie kierunku za pomoca maski
    IO1DIR = LED0_bm; 

    while(1) {
        // zapalenie diody za pomoca maski
        IO1SET = LED0_bm; 
        Delay(50); // 10 Hz (50ms ON + 50ms OFF = 100ms cykl)
        
        // zgaszenie diody za pomoca maski
        IO1CLR = LED0_bm; 
        Delay(50);
    }
}




//PUNKT 10
//led3 bedzie na pinie 19 skoro 0 byl na 16
#include <LPC21xx.H>

#define LED0_bm 0x00010000
// nowa maska zgodnie z zyczeniem (*2^3)
#define LED3_bm 0x00080000 

// stary delay
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

int main() {
    // teraz ustawiamy kierunek dla pinu diody LED3
    IO1DIR = LED3_bm; 

    while(1) {
        // pulsujemy dioda LED3 (z czestotliwoscia 10 Hz jak poprzednio)
			// teraz powinien migac bit 19 :OOOO
        IO1SET = LED3_bm; 
        Delay(50);
        
        IO1CLR = LED3_bm; 
        Delay(50);
    }
}





//PUNKT 11
#include <LPC21xx.H>

// definicje wszystkich masek dla diod LED0-LED3
#define LED0_bm 0x00010000 // Pin 16
#define LED1_bm 0x00020000 // Pin 17
#define LED2_bm 0x00040000 // Pin 18
#define LED3_bm 0x00080000 // Pin 19

int main() {
    // ustawiamy wszystkie cztery piny jako wyjsciowe za pomoca sumy bitowej (|)
    IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;

    // to dla pewnosci ze nie swieca:
    IO1CLR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;

    // zapalanie po kolei bez opóznien:
    IO1SET = LED0_bm; // Swieci LED0
    IO1SET = LED1_bm; // Swieci LED0 i LED1
    IO1SET = LED2_bm; // Swieci LED0, LED1 i LED2
    IO1SET = LED3_bm; // Swieca wszystkie cztery (LED0, LED1, LED2, LED3)

    while(1) {
        // petla nieskonczona, zeby program nie skonczyl dzialania
    }
}






//PUNKT12
#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

// dobry delay
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

int main() {
    // wszystkie 4 piny jako wyjscia
    IO1DIR = LED0_bm | LED1_bm | LED2_bm | LED3_bm;

    while(1) {
        // LED0
        IO1SET = LED0_bm;
        Delay(250);         // 0.25 sekundy
        IO1CLR = LED0_bm;

        // LED1
        IO1SET = LED1_bm;
        Delay(250);
        IO1CLR = LED1_bm;

        // LED2
        IO1SET = LED2_bm;
        Delay(250);
        IO1CLR = LED2_bm;

        // LED3
        IO1SET = LED3_bm;
        Delay(250);
        IO1CLR = LED3_bm;
    }
}





//PUNKT13
#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

// dobry delay
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

void LedInit() {
    // ustawiamy piny LED0-LED3 jako wyjsciowe
    // uzywamy sumy bitowej (|), aby polaczyc wszystkie maski
    IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // najpierw gasimy wszystkie diody zeby miec czysty stan
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // zapalamy tylko diode LED0 na start (zgodnie z poleceniem)
    IO1SET = LED0_bm;
}


int main() {
    // jedno wywolanie zamiast ustawiania rejestrów recznie
    LedInit(); 
    
    // realizujemy wedrujace swiatelko z 12 punktu
    while(1) {
        // skoro LED0 juz sie swieci (z LedInit), to czekamy i gasimy
        Delay(250);
        IO1CLR = LED0_bm;

        IO1SET = LED1_bm;
        Delay(250);
        IO1CLR = LED1_bm;

        IO1SET = LED2_bm;
        Delay(250);
        IO1CLR = LED2_bm;

        IO1SET = LED3_bm;
        Delay(250);
        IO1CLR = LED3_bm;

        // na koniec petli znów zapalamy LED0 zeby cykl sie powtórzyl
        IO1SET = LED0_bm;
    }
}






//PUNKT14
#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

// dobry delay
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

void LedInit() {
    // BLAD: Zwykle przypisanie "=" zamiast "IO1DIR |="
    // To sprawi, ze bit 23 (i kazdy inny) ustawiony w DIR zniknie!
    IO1DIR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm); 
    
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {
    // gasimy wszystko
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // zapalamy odpowiedznia diode na podstawie indeksu
    switch(ucLedIndeks) {
        case 0:
            IO1SET = LED0_bm;
            break;
        case 1:
            IO1SET = LED1_bm;
            break;
        case 2:
            IO1SET = LED2_bm;
            break;
        case 3:
            IO1SET = LED3_bm;
            break;
        default:
            // to jakby podano zly numer (np. 67) - zadna sie nie zapali
            break;
    }
}


// teraz main realizujacy 12 wyglada tak:
int main() {
    LedInit(); // ustawia wyjscia i zapala LED0

    while(1) {
        LedOn(0);
        Delay(250);
        
        LedOn(1); // LedOn za kazdym razem czysci rejestr i ustawia tylko jeden bit
        Delay(250);
        
        LedOn(2);
        Delay(250);
        
        LedOn(3);
        Delay(250);
    }
}






//PUNNKT15
#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

// dobry delay
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

void LedInit() {
    // WERSJA POPRAWNA (punkt 15):
    // Uzywamy "IO1DIR |", zeby zachowac inne bity (np. bit 23)
    IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // Gasimy wszystkie diody na start
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // Zapalamy tylko LED0 (punkt 13)
    IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {
    // gasimy wszystko
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // zapalamy odpowiedznia diode na podstawie indeksu
    switch(ucLedIndeks) {
        case 0:
            IO1SET = LED0_bm;
            break;
        case 1:
            IO1SET = LED1_bm;
            break;
        case 2:
            IO1SET = LED2_bm;
            break;
        case 3:
            IO1SET = LED3_bm;
            break;
        default:
            // to jakby podano zly numer (np. 67) - zadna sie nie zapali
            break;
    }
}


// teraz main realizujacy 12 wyglada tak:
int main() {
    LedInit(); // ustawia wyjscia i zapala LED0

    while(1) {
        LedOn(0);
        Delay(250);
        
        LedOn(1); // LedOn za kazdym razem czysci rejestr i ustawia tylko jeden bit
        Delay(250);
        
        LedOn(2);
        Delay(250);
        
        LedOn(3);
        Delay(250);
    }
}
// TEST: USTAWIC W SYMULATORZE RECZNIE 23 BIT - PO URUCHOMIENIU POWINIEN ZOSTAC







//PUNKT16 - tu cos nie dziala ale nie mam sily
#include <LPC21xx.H>

#define S0_bm 0x00000010  // bit 4 w rejestrze 32-bitowym

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

// dobry delay
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

void LedInit() {
    // WERSJA POPRAWNA (punkt 15):
    // Uzywamy "IO1DIR |", zeby zachowac inne bity (np. bit 23)
    IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // Gasimy wszystkie diody na start
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // Zapalamy tylko LED0 (punkt 13)
    IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {
    // gasimy wszystko
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // zapalamy odpowiedznia diode na podstawie indeksu
    switch(ucLedIndeks) {
        case 0:
            IO1SET = LED0_bm;
            break;
        case 1:
            IO1SET = LED1_bm;
            break;
        case 2:
            IO1SET = LED2_bm;
            break;
        case 3:
            IO1SET = LED3_bm;
            break;
        default:
            // to jakby podano zly numer (np. 67) - zadna sie nie zapali
            break;
    }
}

unsigned char ReadButton1() {
    // jesli po nalozeniu maski na rejestr PIN wynik to 0
    // znaczy ze przycisk jest zwarty do masy (nacisniety)
    if ((IO0PIN & S0_bm) == 0) {
        return 1; // przycisk nacisniety
    } else {
        return 0; // przycisk puszczony
    }
}



int main() {
		
		LedInit(); // ustawia wyjscia dla diod na Porcie 1

    while(1) {
        if (ReadButton1() == 1) {
            LedOn(1); // zapal LED1 (pin 17)
        } else {
            LedOn(0); // zapal LED0 (pin 16)
        }
    }
}







//PUNKT17
#include <LPC21xx.H>

#define S0_bm 0x00000010  // bit 4 w rejestrze 32-bitowym

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

// dobry delay
void Delay(int iDelayInMS) {
    int iLoopCounter;
    int iIterations = iDelayInMS * 2500; 
    for(iLoopCounter = 0; iLoopCounter < iIterations; iLoopCounter++) {}
}

void LedInit() {
    // WERSJA POPRAWNA (punkt 15):
    // Uzywamy "IO1DIR |", zeby zachowac inne bity (np. bit 23)
    IO1DIR = IO1DIR | (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // Gasimy wszystkie diody na start
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // Zapalamy tylko LED0 (punkt 13)
    IO1SET = LED0_bm;
}

void LedOn(unsigned char ucLedIndeks) {
    // gasimy wszystko
    IO1CLR = (LED0_bm | LED1_bm | LED2_bm | LED3_bm);
    
    // zapalamy odpowiedznia diode na podstawie indeksu
    switch(ucLedIndeks) {
        case 0:
            IO1SET = LED0_bm;
            break;
        case 1:
            IO1SET = LED1_bm;
            break;
        case 2:
            IO1SET = LED2_bm;
            break;
        case 3:
            IO1SET = LED3_bm;
            break;
        default:
            // to jakby podano zly numer (np. 67) - zadna sie nie zapali
            break;
    }
}

// definicja typu enum (zgodnie z instrukcja)
enum ButtonState {RELASED, PRESSED}; 

// funkcja zwracajaca typ enum
enum ButtonState ReadButton1() {
    if ((IO0PIN & S0_bm) == 0) {
        return PRESSED;
    } else {
        return RELASED;
    }
}

int main() {
	
    LedInit();

    while(1) {
        // wybór diody za pomoca instrukcji switch
        switch(ReadButton1()) {
            case PRESSED:
                LedOn(1);
                break;
            case RELASED:
                LedOn(0);
                break;
            default:
                break;
        }
    }
}
