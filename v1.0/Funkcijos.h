
#pragma once

#include "Studentas.h"

#include <string>
#include <vector>

// Studentu ivedimas rankiniu budu
void ivestiStudentus(
    std::vector<Studentas>& studentai
);

// Atsitiktiniu pazymiu generavimas
void generuotiStudentus(
    std::vector<Studentas>& studentai
);

// Studentu duomenu nuskaitymas is failo
void nuskaitytiIsFailo(
    const std::string& failoPavadinimas,
    std::vector<Studentas>& studentai
);

// Studentu rusiavimas pagal pavarde ir varda
void rusiuotiStudentus(
    std::vector<Studentas>& studentai
);

// Studentu rezultatu isvedimas i ekrana
// budas: 1 - vidurkis, 2 - mediana
void isvestiStudentus(
    const std::vector<Studentas>& studentai,
    int budas
);

// Studentu duomenu failo generavimas
void generuotiStudentuFaila(
    const std::string& failoPavadinimas,
    int studentuKiekis
);

// Studentu skirstymas pagal galutini bala
void skirstytiStudentus(
    const std::vector<Studentas>& studentai,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai
);

// Antra strategija: skirstymas naudojant viena nauja konteineri
void skirstytiStudentusStrategija2(
    std::vector<Studentas>& studentai,
    std::vector<Studentas>& vargsiukai
);

// Studentu saraso isvedimas i faila
void isvestiStudentusIFaila(
    const std::string& failoPavadinimas,
    const std::vector<Studentas>& studentai
);

// Studentu konteineriu nasumo palyginimas
void palygintiKonteinerius(
    const std::string& failoPavadinimas
);

// Dvieju skirstymo strategiju nasumo palyginimas
void palygintiStrategijas(
    const std::string& failoPavadinimas
);
