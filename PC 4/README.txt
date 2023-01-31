//  RotateMatrix //
    --> convertesc inputul
    --> aloc un sir de caractere in care retin matricea rezultat
    --> folosesc primul elementent pentru initializarea matricei
    --> restul elementelor sunt construite cu ajutorului unui sir auxiliar "nr"

// DecodeString //
    --> convertesc inputul
    --> separ numerele date si le adun la suma
    --> rezultatul e copiat intr-un sir de caractere

// InvertArray //
    --> convertesc inputul
    --> iau primul element al vectorului si ordonez elementele corespunzator
    --> aloc sirul rezultat cu numarul de elementele al vectorului rezultat
    --> cu ajutorului unui sir auxiliar formez sirul rezultat

// allocPlayer //
    --> aloc memorie pentru structura
    --> aloc memorie pentru fiecare camp cerut 

// allocGame //
    --> aloc memorie structurii allocGame
    --> aloc memorie numelui

// ReadPlayer //
    --> alloc memorie structurii cu ajutorul functiei deja definite
    --> citesc datele de intrare date despre player 
    --> setez componentele alive si indexOfLocation la valorile initiale 
    --> aloc memorie vectorului de locatii egala cu numarul de elemente 
    --> pentru fiecare locatie citesc sirul de caractere de forma (a,b) 
    --> sirul este despartit pentru a se obtine coordonatele 
    --> citesc rolul si atribui valoarea si abilitatea respectiva

// ReadGame //
    --> aloc memorie jocului
    --> citesc datele de intrare
    --> aloc memorie sirului de jucatori si citesc fiecare jucatori
    --> citesc impostorul

// WritePlayer //
    --> obtin rolul jucatorului prin convertirea numarului corespunzator 
    --> printez fiecare bucatica a mesajului corespunzator
    --> printez fiecare locatie in formatul cerut

// WriteGame //
    --> printez fieacre bucatica a mesajului cerut
    --> printez mesajul pentru fiecare player in parte
    --> printez mesajul pentru impostor 

// KillPlayer //
    --> am definit o functie auxiliara pentru calcularea distantei "Dist"
    --> convertesc inputul
    --> obtin indexul locatiei actuale a impostorului
    --> retn in variabila impostor locatia impostorului
    --> best_dist retine cea mai mica distanta gasita
    --> best_dist e initiata cu killRange deoarece orice distanta mai mare nu ar fi buna
    --> cwr_index retine numarul playerului care va fi ucis
    --> daca nu se poate ucide, cwr_index ramane -1
    --> pentru fiecare player calculez distanta si verific posibilitatea de ucidere
    --> aloc sirul de caractere pentru rezultat
    --> creez sirul de caractere corespunzator

// CalculateNextCycleOfGame //
    --> pentru fiecare player verific daca este in viata si afisez mesajul corespunzator
    --> daca indicele de locatie ajunge la finalul vectorului, il resetez
    --> pentru impostor verific daca poate omora si afisez mesajul corespunzator

// FreePlayer //
    --> eliberez structurile alocare pentru fiecare camp
    --> eliberez structura totala a playerului 

// FreeGame //
    --> eliberez fiecare jucator si impostorul
    --> eliberez restul campurilor alocate si structura Game