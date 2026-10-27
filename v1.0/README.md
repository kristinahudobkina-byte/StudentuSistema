
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
- - Testuojant 10 000 000 studentu, `std::deque` greiciausiai nuskaite duomenis, o `std::list` greiciausiai suskirste studentus ir irase rezultatus i failus.

**Isvada:** visi trys konteineriai tinkami studentu duomenims apdoroti. Ju nasumas priklauso nuo atliekamos operacijos ir duomenu kiekio. Siuose testuose `std::list` dazniausiai parode geriausius rezultatus, taciau `std::vector` ir `std::deque` taip pat buvo efektyvus.

Rezultatai gali skirtis priklausomai nuo kompiuterio techniniu charakteristiku ir programos vykdymo salygu.

## Versija v1.0

Versijoje v1.0 atliktas dvieju studentu skirstymo strategiju nasumo tyrimas, naudojant skirtingus C++ STL konteinerius.

### Skirstymo strategijos

**Strategija 1:**

Studentai suskirstomi i du naujus konteinerius:
- Vargsiukai - studentai, kuriu galutinis vidurkis mazesnis nei 5.0.
- Kietiakiai - studentai, kuriu galutinis vidurkis yra 5.0 arba didesnis.

**Strategija 2:**

Naudojamas vienas papildomas konteineris vargsiukams. Kietiakiai lieka pradiniame konteineryje.

Abi strategijos isbandytos naudojant:
- `std::vector`
- `std::list`
- `std::deque`

### STL algoritmu optimizavimas

Papildomai isbandyti trys algoritmai su `std::vector`:

- `std::partition` - suskirsto studentus pagal galutini bala.
- `std::stable_partition` - suskirsto studentus islaikydamas pradine ju tvarka.
- `std::remove_if` - naudojamas kartu su `std::copy_if`, kad studentai butu suskirstyti i dvi grupes.

### Nasumo ir atminties tyrimas

Programa matuoja studentu skirstymo laika naudojant `std::chrono`.

Taip pat pateikiamas apytikslis konteineriu elementu atminties ivertinimas. Sis ivertinimas neatspindi visos programos faktiskai naudojamos operatyviosios atminties.

Siekiant sumazinti atminties naudojima, kiekvieno testo laikini konteineriai sunaikinami pasibaigus testui.

Del dideles vykdymo trukmes antroji `std::vector` ir `std::deque` strategija vykdoma tik tada, kai studentu skaicius nevirsija 10 000.

Visi nasumo testai atliekami naudojant `x64-Release` rezima.

### Strategiju nasumo palyginimo rezultatai

Testavimas atliktas naudojant `x64-Release` rezima. Lentelese pateikiamas studentu skirstymo laikas sekundemis.

#### 1 000 ir 10 000 studentu

| Strategija | 1 000 studentu (s) | 10 000 studentu (s) |
|---|---:|---:|
| Vector - strategija 1 | 0.0004097 | 0.0023396 |
| Vector - strategija 2 | 0.0043901 | 0.219306 |
| List - strategija 1 | 0.0001233 | 0.0012927 |
| List - strategija 2 | 0.0000057 | 0.0004937 |
| Deque - strategija 1 | 0.0001011 | 0.0030511 |
| Deque - strategija 2 | 0.0010447 | 0.0919648 |
| Vector - std::partition | 0.0000473 | 0.000484 |
| Vector - std::stable_partition | 0.0000699 | 0.0007761 |
| Vector - std::remove_if | 0.0000953 | 0.0011908 |

Studentu pasiskirstymas:

| Grupe | 1 000 studentu | 10 000 studentu |
|---|---:|---:|
| Vargsiukai | 427 | 4 149 |
| Kietiakiai | 573 | 5 851 |

Visos strategijos buvo vykdomos, nes studentu skaicius nevirsijo 10 000.

#### 100 000 studentu

| Strategija | Skirstymo laikas (s) |
|---|---:|
| Vector - strategija 1 | 0.02122439 |
| Vector - strategija 2 | Nevykdyta |
| List - strategija 1 | 0.010107 |
| List - strategija 2 | 0.0023199 |
| Deque - strategija 1 | 0.0140798 |
| Deque - strategija 2 | Nevykdyta |
| Vector - std::partition | 0.0046434 |
| Vector - std::stable_partition | 0.0074105 |
| Vector - std::remove_if | 0.0131298 |

Studentu pasiskirstymas:
- Vargsiukai: 41 505
- Kietiakiai: 58 495

Antroji `vector` ir `deque` strategija nebuvo vykdoma, nes studentu skaicius virsijo 10 000.

#### 1 000 000 studentu

Duomenu nuskaitymo laikas: **2.47266 s**

| Strategija | Skirstymo laikas (s) |
|---|---:|
| Vector - strategija 1 | 0.210062 |
| Vector - strategija 2 | Nevykdyta |
| List - strategija 1 | 0.112180 |
| List - strategija 2 | 0.0217285 |
| Deque - strategija 1 | 0.111893 |
| Deque - strategija 2 | Nevykdyta |
| Vector - std::partition | 0.0527587 |
| Vector - std::stable_partition | 0.0868182 |
| Vector - std::remove_if | 0.112041 |

Studentu pasiskirstymas:
- Vargsiukai: 413 683
- Kietiakiai: 586 317

#### 10 000 000 studentu

Duomenu nuskaitymo laikas: **25.0727 s**

| Strategija | Skirstymo laikas (s) |
|---|---:|
| Vector - strategija 1 | 2.71759 |
| Vector - strategija 2 | Nevykdyta |
| List - strategija 1 | 1.21787 |
| List - strategija 2 | 0.244106 |
| Deque - strategija 1 | 1.30199 |
| Deque - strategija 2 | Nevykdyta |
| Vector - std::partition | 0.623911 |
| Vector - std::stable_partition | 0.852525 |
| Vector - std::remove_if | 1.31775 |

Studentu pasiskirstymas:
- Vargsiukai: 4 132 387
- Kietiakiai: 5 867 613

**Pastaba:** Antroji `std::vector` ir `std::deque` strategija failams, kuriuose yra daugiau nei 10 000 studentu, nebuvo vykdoma del dideles skaiciavimo trukmes.

Pateikti laikai apima tik studentu skirstymo operacijas, o ne pradiniu konteineriu sukurima. Rezultatai gauti atliekant po viena matavima, todel gali skirtis kituose bandymuose.

### Strategiju nasumo tyrimo isvados

Atlikus testus su 1 000, 10 000, 100 000, 1 000 000 ir 10 000 000 studentu, nustatyta:

- `std::list` antroji strategija buvo greiciausia is visu testuotu skirstymo budu.
- `std::list` konteineryje naudojama `splice` operacija leidzia perkelti elementus nekopijuojant ju duomenu.
- `std::vector` antroji strategija buvo gerokai letesne del dazno elementu salinimo naudojant `erase`.
- `std::deque` antroji strategija taip pat buvo leta, todel dideliems duomenu kiekiams nebuvo vykdoma.
- Is optimizuotu `std::vector` algoritmu geriausius rezultatus parode `std::partition`.
- `std::stable_partition` islaiko pradine studentu tvarka, taciau testuose buvo letesnis uz `std::partition`.
- Dideliems duomenu kiekiams svarbu ne tik vykdymo greitis, bet ir atminties naudojimas.

**Galutine isvada:** siuose bandymuose efektyviausiai studentus suskirste `std::list` antroji strategija. Naudojant `std::vector`, geriausius rezultatus parode `std::partition`. Tinkamiausios strategijos pasirinkimas priklauso nuo naudojamo konteinerio, duomenu kiekio ir poreikio islaikyti pradine elementu tvarka.

Rezultatai gali skirtis priklausomai nuo kompiuterio charakteristiku ir testavimo salygu.

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

7 - Palyginti studentu skirstymo strategijas ir STL algoritmu nasuma.

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

### Reikalavimai

- C++17 palaikantis kompiliatorius.
- CMake.
- Visual Studio 2022 arba kita CMake palaikanti kurimo aplinka.

### Kompiliavimas naudojant Visual Studio 2022

1. Atidaryti Visual Studio 2022.
2. Pasirinkti `File -> Open -> Folder`.
3. Atidaryti projekto aplanka, kuriame yra `CMakeLists.txt`.
4. Pasirinkti `x64-Release` konfiguracija.
5. Sukompiliuoti projekta naudojant `Build -> Build All`.
6. Paleisti programa.

### Kompiliavimas naudojant CMake

Projekto aplanke atidaryti terminala ir ivykdyti:

```bash
cmake -S . -B build
cmake --build build --config Release```

Sukompiliavus projekta, paleisti sukurta vykdomaji faila.

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

### v1.0
- Realizuotos dvi studentu skirstymo strategijos.
- Abi strategijos isbandytos su `std::vector`, `std::list` ir `std::deque` konteineriais.
- Antroji `std::list` strategija optimizuota naudojant `splice`.
- Papildomai pritaikyti STL algoritmai: `std::partition`, `std::stable_partition`, `std::remove_if` ir `std::copy_if`.
- Pridetas apytikslis konteineriu atminties naudojimo ivertinimas.
- Optimizuotas laikinu konteineriu atminties atlaisvinimas.
- Atlikti nasumo testai su penkiais skirtingais studentu duomenu kiekiais.
- Palyginti skirtingu strategiju vykdymo laikai.
- Testavimo rezultatai ir isvados pateikti README faile.