
# StudentuSistema

Studentu galutiniu pazymiu skaiciavimo programa,
sukurta naudojant C++ programavimo kalba.

## Versija v0.1

Programa leidzia:
- Ivesti studentu duomenis rankiniu budu.
- Ivesti neribota namu darbu pazymiu skaiciu.
- Generuoti atsitiktinius studentu pazymius.
- Nuskaityti studentu duomenis is tekstinio failo.
- Apskaiciuoti galutini pazymi pagal vidurki.
- Apskaiciuoti galutini pazymi pagal mediana.
- Surusiuoti studentus pagal pavarde ir varda.
- Isvesti rezultatus lenteleje.

## Versija v0.2

Versijoje v0.2 programa papildyta naujomis funkcijomis.

Programa leidzia:
- Generuoti studentu duomenu failus su 1000, 10000, 100000, 1000000 ir 10000000 studentu.
- Nuskaityti sugeneruotus studentu duomenis is failu.
- Suskirstyti studentus i dvi grupes pagal galutini pazymi.
- Vargsiukai - studentai, kuriu galutinis vidurkis mazesnis nei 5.0.
- Kietiakiai - studentai, kuriu galutinis vidurkis yra 5.0 arba didesnis.
- Issaugoti abi studentu grupes atskiruose tekstiniuose failuose.
- Matuoti failu generavimo, nuskaitymo, studentu skirstymo ir rezultatu irasymo laika.
- Palyginti std::vector, std::list ir std::deque konteineriu nasuma.

Nasumo testai atlikti naudojant x64-Release rezima.

### Konteineriu nasumo tyrimas

Buvo palyginti trys C++ konteineriai:
- `std::vector`
- `std::list`
- `std::deque`

Testavimui naudoti penki skirtingo dydzio studentu duomenu failai. Buvo matuojamas duomenu nuskaitymo, studentu skirstymo ir rezultatu irasymo laikas sekundemis.

#### Duomenu nuskaitymo laikas (s)

| Studentu skaicius | Vector | List | Deque |
|---|---:|---:|---:|
| 1 000 | 0.00563 | 0.00394 | 0.00378 |
| 10 000 | 0.03075 | 0.02259 | 0.02286 |
| 100 000 | 0.24804 | 0.23132 | 0.23347 |
| 1 000 000 | 2.443 | 2.320 | 2.299 |
| 10 000 000 | 24.369 | 23.234 | 23.778 |

#### Studentu skirstymo laikas (s)

| Studentu skaicius | Vector | List | Deque |
|---|---:|---:|---:|
| 1 000 | 0.000261 | 0.000102 | 0.000115 |
| 10 000 | 0.002438 | 0.001042 | 0.001106 |
| 100 000 | 0.021062 | 0.011744 | 0.012417 |
| 1 000 000 | 0.209057 | 0.100832 | 0.105161 |
| 10 000 000 | 3.38641 | 2.11595 | 3.31281 |

#### Rezultatu irasymo laikas (s)

| Studentu skaicius | Vector | List | Deque |
|---|---:|---:|---:|
| 1 000 | 0.00189 | 0.00150 | 0.00156 |
| 10 000 | 0.01230 | 0.01147 | 0.01127 |
| 100 000 | 0.12435 | 0.10246 | 0.10727 |
| 1 000 000 | 0.98314 | 1.05624 | 1.07401 |
| 10 000 000 | 12.48835 | 11.3393 | 11.8903 |

Pastaba: `vector` konteinerio irasymo laikas apskaiciuotas sudedant abieju rezultatu failu irasymo laikus.

Visi testai atlikti naudojant `x64-Release` rezima.

### Nasumo tyrimo isvados

Atlikus testus su skirtingais studentu duomenu kiekiais, pastebeta:

- Didejant studentu skaiciui, visu triju konteineriu duomenu apdorojimo laikas ilgeja.
- `std::list` daugelyje testu greiciausiai suskirste studentus i dvi grupes.
- `std::deque` kai kuriuose testuose greiciausiai nuskaito duomenis is failo.
- `std::vector` geriausiai pasirode irasant 1 000 000 studentu rezultatus.
- Testuojant 10 000 000 studentu, `std::list` buvo greiciausias visose trijose operacijose.

**Isvada:** visi trys konteineriai tinkami studentu duomenims apdoroti. Ju nasumas priklauso nuo atliekamos operacijos ir duomenu kiekio. Siuose testuose `std::list` dazniausiai parode geriausius rezultatus, taciau `std::vector` ir `std::deque` taip pat buvo efektyvus.

Rezultatai gali skirtis priklausomai nuo kompiuterio techniniu charakteristiku ir programos vykdymo salygu.

## Galutinio pazymio formule

Galutinis = 0.4 * ND + 0.6 * Egzaminas

ND - namu darbu vidurkis arba mediana.

## Naudojami konteineriai

Studentu duomenys saugomi std::vector<Studentas>.

Namu darbu pazymiai saugomi std::vector<int>.

## Klase Studentas

Klaseje realizuota:
- Konstruktoriai
- Kopijavimo konstruktorius
- Kopijavimo priskyrimo operatorius
- Destruktorius
- Ivedimo operatorius >>
- Isvedimo operatorius <<
- Galutinio pazymio skaiciavimo metodas

## Programos failai

- main.cpp - pagrindinis programos meniu.
- Studentas.h - Studentas klases aprasymas.
- Studentas.cpp - Studentas klases realizacija.
- Funkcijos.h - funkciju deklaracijos.
- Funkcijos.cpp - funkciju realizacija.
- kursiokai.txt - testiniai studentu duomenys.

## Naudojimosi instrukcija

Paleidus programa, pateikiamas meniu:

1 - Ivesti studentus rankiniu budu.

2 - Generuoti atsitiktinius pazymius.

3 - Nuskaityti studentus is failo.

4 - Generuoti studentu duomenu failus (1000, 10000, 100000, 1000000 ir 10000000 studentu).

5 - Suskirstyti studentus i dvi grupes: vargsiukai ir kietiakiai.

6 - Palyginti std::vector, std::list ir std::deque konteineriu nasuma.

0 - Baigti programa.

Pasirinkus duomenu ivedimo buda, galima
pasirinkti galutinio pazymio skaiciavima:

1 - Pagal vidurki.
2 - Pagal mediana.
3 - Rodyti abu rezultatus.

Rankiniu budu ivedant namu darbu pazymius,
skaicius 0 uzbaigia namu darbu ivedima.

## Duomenu failo formatas

Pirmoje eiluteje pateikiamos stulpeliu antrastes.

Toliau kiekvienoje eiluteje rasoma:

Vardas Pavarde ND1 ND2 ... Egzaminas

Paskutinis pazymys yra egzamino rezultatas.

## Klaidu apdorojimas

Programoje naudojamas try/catch mechanizmas.

Jeigu failas neegzistuoja arba duomenys
neteisingi, pateikiamas klaidos pranesimas.

## Kompiliavimas

Programa sukurta naudojant C++17.

Visual Studio aplinkoje:
1. Atidaryti projekta.
2. Pasirinkti Build / Sukurti sprendima.
3. Paleisti programa su Ctrl + F5.

Taip pat projektui numatytas CMake palaikymas.

## Versiju istorija

### v0.1
- Sukurta Studentas klase.
- Realizuota Rule of Three.
- Realizuotas rankinis duomenu ivedimas.
- Pridetas atsitiktiniu pazymiu generavimas.
- Pridetas duomenu nuskaitymas is failo.
- Realizuotas vidurkio ir medianos skaiciavimas.
- Pridetas studentu rusiavimas.
- Realizuotas formatuotas rezultatu isvedimas.
- Pridetas klaidu apdorojimas.

### v0.2
- Pridetas penkiu skirtingo dydzio studentu duomenu failu generavimas.
- Realizuotas studentu skirstymas i dvi grupes pagal galutini vidurki.
- Sukurti atskiri rezultatu failai vargsiukams ir kietiakiai grupei.
- Pridetas operaciju vykdymo laiko matavimas naudojant `std::chrono`.
- Realizuotas triju konteineriu palyginimas: `std::vector`, `std::list` ir `std::deque`.
- Atlikti nasumo testai su 1 000, 10 000, 100 000, 1 000 000 ir 10 000 000 studentu.
- Testu rezultatai pateikti lentelese.
- Atlikta konteineriu nasumo analize.