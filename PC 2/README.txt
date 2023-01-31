// main //

Pentru rezolvarea fiecarui task am creat cate o functie separata apelata din main in functie de valuarea variabilei task
In momentul in care una din functii este apelata avem return 0 pentru a nu trece inutil prin restul if-urilor.

// functii aditionale//

    * InitBoard *
    --> initializeaza elementele tablei de joc cu '.'

    * ExtractInfo *
    --> citeste si desparte informarile de pe randurile de tip X Y D WORD
    --> converteste valorile la tip int si returneaza coordonatele si cuvantul citite

    * ExtractInfoPrime *
    --> citeste si extrage subsirurile de bonus si numarul de cuvinte

    * PlaceWord *
    --> primeste ca parametrii tabla, cuvantul si coordonatele sale
    --> plaseaza cuvantul pe tabla de joc la coordonatele indicate

    * WordScore *
    --> calculeaza scorul de baza al cuvantului indicat, fara bonusuri

    * SubstringCheck *
    --> primeste cuvantul, subsirul de comparat si numarul de bonus pentru care se comparat
    --> pentru 1 cauta subsirul string in cuvant si returneaza 0 daca este gasit, adica cuvantul e eligibil pentru bonusul *2
    --> pentru 2 verifica daca subsirul string este sufix si returneaza 0 daca cuvantul este eligibil pentru bonusul *3
    --> daca cuvantul nu este eligibil pentru bonus, returneaza 1

    * WordScoreBonus *
    --> primeste un sir de caractere c_Info (compresedInfo) si un nr intreg c_Int (compresedInt)
    --> extrage informatile codificate in cei doi parametri
    --> verifica si calculeaza multiplicatorul fiecarui cuvant prin apelarea functiei SubstringCheck
    --> var multiplicator retine numarul de multiplicitate a bonusul
    --> calculeaza si returneaza scorul cu bonus al cuvantului

    * CheckSpace *
    --> primeste un sir de caractere c_Info (compresedInfo) si un nr intreg c_Int (compresedInt)
    --> extrage informatile codificate in cei doi parametri
    --> parametrul write este 1 pentru taskul 4 si 0 pentru taskul 5
    --> pentru task 4 functia scrie cuvantul pe tabla daca acesta are loc
    --> penru task 5 functia returneaza scorul cuvantului in spatiul gasit si directia pe care acesta se poate pozitiona
    --> functia verica conditile mai intai pe orizontala, iar apoi pe verticala
    --> parametrul free retine daca cuvantul are loc (1 pentru nu, 0 pentru da)
    --> daca cuvantul nu are loc nici pe verticala nici pe orizontala se returneaza 1

    * BestPosibleWord *
    --> cauta si identifica cel mai bun cuvant care poate fi jucat in continuare
    --> cauta cuvantul care va aduce cel mai mare scor posibil
    --> vectorul UsedWord memoreaza indexul cuvintelor deja plasate pe tabla
    --> pentru fiecare cuvant neutilizat se cauta prima sa litera
    --> daca cuvantul este valid pentru a fi jucat mai departe se retine indexul acestuia
    --> indexul inglobeaza nr cuvantului din vector,coordonatele optime si scorul cuvantului
    --> functia returneaza indexul

// functiile specifice pe task //

    * DoTask0 *
    --> initializeaza si printeaza tabla

    * DoTask1 *
    --> pentru fiecare cuvant citeste si extrage informatile
    --> printeaza cuvintele pe tabla
    --> printeaza tabla

    * DoTask2 *
    --> pentru fiecare cuvant extrage informatile
    --> pentru i par cuvantul apartine player-lui 1, altfel player-lui 2
    --> se obtine scorul de baza al cuvantului (fara bonus) cu functia WordScore
    --> printeaza rezultatul

    * DoTask3 *
    --> intr-un mod similar ca la taskul 2, se calculeaza scorurile playerilor (cu bonus)
    --> creaza sirurile de informatii necesare functiei WordScoreBonus
    --> printeaza rezultatul

    * DoTask4 *
    --> extrage informatile si printeaza cuvintele primite
    --> vectorul UsedWord retine cuvintele deja printate pe tabla
    --> var search retine daca s-a gasit deja sau nu un cuvant optime
    --> daca se gaseste cuvantul cautat, search devine 0 iar cautarea se opreste
    --> printarea tablei

    * DoTask5 *
    --> pentru fiecare cuvant citit se creaza sirurile de informatie compresata
    --> se calculeaza scorurile fiecarui jucator in mod asemanator ca la task 3
    --> se apeleaza cautarea celui mai bun cuvant
    --> daca cuvantul gasit ineplineste conditia de win se plaseaza pe tabla si se printeaza tabla
    --> daca nu, se printeaza mesajul de fail

    * DoTask6 *
    --> pentru fiecare cuvant citit al playerui 1 se va printa acesta
    --> se cauta un cuvant optim pentru player 2
    --> se calculeaza constant scorurile celor 2 playeri
    --> se afeaseaza mesajul de win