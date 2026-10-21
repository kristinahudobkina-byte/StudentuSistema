
#include "Funkcijos.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>

// Sveikojo skaiciaus ivedimas su tikrinimu
int ivestiSkaiciu(int min, int max) {
    int skaicius;

    while (true) {
        if (std::cin >> skaicius &&
            skaicius >= min &&
            skaicius <= max) {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );
            return skaicius;
        }

        std::cout << "Neteisinga ivestis. Iveskite skaiciu nuo "
            << min << " iki " << max << ": ";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

// Studentu ivedimas rankiniu budu
void ivestiStudentus(std::vector<Studentas>& studentai) {
    std::cout << "\nKiek studentu norite ivesti? ";
    int kiekis = ivestiSkaiciu(1, 100000);

    for (int i = 0; i < kiekis; ++i) {
        std::string vardas;
        std::string pavarde;
        std::vector<int> namuDarbai;

        std::cout << "\nStudentas Nr. " << i + 1 << "\n";

        std::cout << "Vardas: ";
        std::cin >> vardas;

        std::cout << "Pavarde: ";
        std::cin >> pavarde;

        std::cout << "Iveskite namu darbu pazymius (0 - baigti):\n";

        while (true) {
            std::cout << "ND: ";
            int pazymys = ivestiSkaiciu(0, 10);

            if (pazymys == 0) {
                break;
            }

            namuDarbai.push_back(pazymys);
        }

        std::cout << "Egzamino pazymys: ";
        int egzaminas = ivestiSkaiciu(1, 10);

        studentai.emplace_back(
            vardas,
            pavarde,
            namuDarbai,
            egzaminas
        );
    }
}

// Atsitiktiniu pazymiu generavimas
void generuotiStudentus(std::vector<Studentas>& studentai) {
    std::cout << "\nKiek studentu norite sugeneruoti? ";
    int kiekis = ivestiSkaiciu(1, 100000);

    std::cout << "Kiek namu darbu pazymiu generuoti? ";
    int ndKiekis = ivestiSkaiciu(1, 100);

    std::random_device rd;
    std::mt19937 generatorius(rd());
    std::uniform_int_distribution<int> pazymys(1, 10);

    for (int i = 1; i <= kiekis; ++i) {
        std::vector<int> namuDarbai;

        for (int j = 0; j < ndKiekis; ++j) {
            namuDarbai.push_back(pazymys(generatorius));
        }

        int egzaminas = pazymys(generatorius);

        studentai.emplace_back(
            "Vardas" + std::to_string(i),
            "Pavarde" + std::to_string(i),
            namuDarbai,
            egzaminas
        );
    }

    std::cout << "\nStudentu duomenys sugeneruoti sekmingai.\n";
}

// Studentu nuskaitymas is failo
void nuskaitytiIsFailo(
    const std::string& failoPavadinimas,
    std::vector<Studentas>& studentai
) {
    std::ifstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        throw std::runtime_error(
            "Nepavyko atidaryti failo: " + failoPavadinimas
        );
    }

    std::string eilute;

    // Praleidziame antrastes eilute
    std::getline(failas, eilute);

    int eilutesNumeris = 1;
    int nuskaityta = 0;

    while (std::getline(failas, eilute)) {
        ++eilutesNumeris;

        if (eilute.empty()) {
            continue;
        }

        std::istringstream srautas(eilute);
        Studentas studentas;

        if (!(srautas >> studentas)) {
            throw std::runtime_error(
                "Neteisingi duomenys failo eiluteje: " +
                std::to_string(eilutesNumeris)
            );
        }

        studentai.push_back(studentas);
        ++nuskaityta;
    }

    if (failas.bad()) {
        throw std::runtime_error(
            "Klaida skaitant faila: " + failoPavadinimas
        );
    }

    std::cout << "\nSekmingai nuskaityta studentu: "
        << nuskaityta << "\n";
}

// Studentu rusiavimas pagal pavarde ir varda
void rusiuotiStudentus(std::vector<Studentas>& studentai) {
    std::sort(
        studentai.begin(),
        studentai.end(),
        [](const Studentas& a, const Studentas& b) {
            if (a.getPavarde() == b.getPavarde()) {
                return a.getVardas() < b.getVardas();
            }

            return a.getPavarde() < b.getPavarde();
        }
    );
}

// Studentu rezultatu isvedimas
void isvestiStudentus(
    const std::vector<Studentas>& studentai,
    int budas
) {
    if (studentai.empty()) {
        std::cout << "\nStudentu sarasas tuscias.\n";
        return;
    }

    std::cout << "\n";

    std::cout << std::left
        << std::setw(18) << "Pavarde"
        << std::setw(18) << "Vardas";

    if (budas == 1) {
        std::cout << std::setw(20) << "Galutinis (Vid.)";
    }
    else if (budas == 2) {
        std::cout << std::setw(20) << "Galutinis (Med.)";
    }
    else {
        std::cout << std::setw(20) << "Galutinis (Vid.)"
            << std::setw(20) << "Galutinis (Med.)";
    }

    std::cout << "\n"
        << std::string(budas == 3 ? 76 : 56, '-')
        << "\n";

    for (const Studentas& studentas : studentai) {
        std::cout << std::left
            << std::setw(18) << studentas.getPavarde()
            << std::setw(18) << studentas.getVardas()
            << std::right
            << std::fixed
            << std::setprecision(2);

        if (budas == 1) {
            std::cout << std::setw(20)
                << studentas.getGalutinisVid();
        }
        else if (budas == 2) {
            std::cout << std::setw(20)
                << studentas.getGalutinisMed();
        }
        else {
            std::cout << std::setw(20)
                << studentas.getGalutinisVid()
                << std::setw(20)
                << studentas.getGalutinisMed();
        }

        std::cout << "\n";
    }
}
