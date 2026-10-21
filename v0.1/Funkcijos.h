
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
