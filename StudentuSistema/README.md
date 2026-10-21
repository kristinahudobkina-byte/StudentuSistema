
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