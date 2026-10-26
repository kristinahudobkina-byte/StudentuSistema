
#include "Funkcijos.h"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <sstream>
#include <stdexcept>
#include <list>
#include <deque>

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
    // Failo nuskaitymo laiko matavimo pradzia
    auto pradzia = std::chrono::steady_clock::now();

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

    // Failo nuskaitymo laiko matavimo pabaiga
    auto pabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> trukme = pabaiga - pradzia;

    std::cout << "Nuskaitymo laikas: "
        << trukme.count() << " s\n";

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

// Studentu duomenu failo generavimas
void generuotiStudentuFaila(
    const std::string& failoPavadinimas,
    int studentuKiekis
) {
    // Failo generavimo laiko matavimo pradzia
    auto pradzia = std::chrono::steady_clock::now();

    std::ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        throw std::runtime_error(
            "Nepavyko sukurti failo: " + failoPavadinimas
        );
    }

    std::random_device rd;
    std::mt19937 generatorius(rd());
    std::uniform_int_distribution<int> pazymys(1, 10);

    // Failo antraste
    failas << "Vardas Pavarde ND1 ND2 ND3 ND4 ND5 Egzaminas\n";

    // Studentu duomenu generavimas
    for (int i = 1; i <= studentuKiekis; ++i) {
        failas << "Vardas" << i
            << " Pavarde" << i;

        // Penki namu darbu pazymiai
        for (int j = 0; j < 5; ++j) {
            failas << " " << pazymys(generatorius);
        }

        // Egzamino pazymys
        failas << " " << pazymys(generatorius) << "\n";
    }

    if (!failas) {
        throw std::runtime_error(
            "Klaida irasant duomenis i faila: " + failoPavadinimas
        );
    }

    // Uztikriname, kad visi duomenys butu irasyti
    failas.close();

    if (failas.fail()) {
        throw std::runtime_error(
            "Klaida uzdarant faila: " + failoPavadinimas
        );
    }

    // Failo generavimo laiko matavimo pabaiga
    auto pabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> trukme = pabaiga - pradzia;

    std::cout << "Generavimo laikas: "
        << trukme.count() << " s\n";

    std::cout << "\nFailas " << failoPavadinimas
        << " sekmingai sugeneruotas.\n";
}

// Studentu skirstymas pagal galutini bala
void skirstytiStudentus(
    const std::vector<Studentas>& studentai,
    std::vector<Studentas>& vargsiukai,
    std::vector<Studentas>& kietiakiai
) {
    // Isvalome ankstesnius rezultatus
    vargsiukai.clear();
    kietiakiai.clear();

    // Studentu skirstymo laiko matavimo pradzia
    auto pradzia = std::chrono::steady_clock::now();

    for (const Studentas& studentas : studentai) {
        if (studentas.getGalutinisVid() < 5.0) {
            vargsiukai.push_back(studentas);
        }
        else {
            kietiakiai.push_back(studentas);
        }
    }

    // Studentu skirstymo laiko matavimo pabaiga
    auto pabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> trukme = pabaiga - pradzia;

    std::cout << "\nStudentu skirstymo laikas: "
        << trukme.count() << " s\n";

    std::cout << "Vargsiukai: "
        << vargsiukai.size() << "\n";

    std::cout << "Kietiakiai: "
        << kietiakiai.size() << "\n";
}

// Studentu saraso isvedimas i faila
void isvestiStudentusIFaila(
    const std::string& failoPavadinimas,
    const std::vector<Studentas>& studentai
) {
    // Failo irasymo laiko matavimo pradzia
    auto pradzia = std::chrono::steady_clock::now();

    std::ofstream failas(failoPavadinimas);

    if (!failas.is_open()) {
        throw std::runtime_error(
            "Nepavyko sukurti failo: " + failoPavadinimas
        );
    }

    // Failo antraste
    failas << std::left
        << std::setw(18) << "Pavarde"
        << std::setw(18) << "Vardas"
        << std::setw(20) << "Galutinis (Vid.)"
        << std::setw(20) << "Galutinis (Med.)"
        << "\n";

    // Studentu rezultatu irasymas
    for (const Studentas& studentas : studentai) {
        failas << studentas << "\n";
    }

    if (!failas) {
        throw std::runtime_error(
            "Klaida irasant duomenis i faila: " + failoPavadinimas
        );
    }

    // Uzdarome faila
    failas.close();

    if (failas.fail()) {
        throw std::runtime_error(
            "Klaida uzdarant faila: " + failoPavadinimas
        );
    }

    // Failo irasymo laiko matavimo pabaiga
    auto pabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> trukme = pabaiga - pradzia;

    std::cout << "\nFailas " << failoPavadinimas
        << " sekmingai sukurtas.\n";

    std::cout << "Irasytu studentu skaicius: "
        << studentai.size() << "\n";

    std::cout << "Irasymo laikas: "
        << trukme.count() << " s\n";
}

// Studentu konteineriu nasumo palyginimas
void palygintiKonteinerius(
    const std::string& failoPavadinimas
) {
    std::cout << "\n========================================\n";
    std::cout << "       KONTEINERIU PALYGINIMAS          \n";
    std::cout << "========================================\n";
    std::cout << "Failas: " << failoPavadinimas << "\n";

    // Konteineriai studentu duomenims
    std::vector<Studentas> vectorStudentai;
    std::list<Studentas> listStudentai;
    std::deque<Studentas> dequeStudentai;

    std::cout << "\nKonteineriai paruosti testavimui.\n";

    // VECTOR konteinerio nuskaitymo testas
    std::cout << "\n--- VECTOR ---\n";

    auto vectorPradzia = std::chrono::steady_clock::now();

    nuskaitytiIsFailo(failoPavadinimas, vectorStudentai);

    auto vectorPabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> vectorTrukme =
        vectorPabaiga - vectorPradzia;

    std::cout << "VECTOR bendras nuskaitymo laikas: "
        << vectorTrukme.count() << " s\n";

    // LIST konteinerio nuskaitymo testas
    std::cout << "\n--- LIST ---\n";

    auto listPradzia = std::chrono::steady_clock::now();

    std::ifstream listFailas(failoPavadinimas);

    if (!listFailas.is_open()) {
        throw std::runtime_error(
            "Nepavyko atidaryti failo: " + failoPavadinimas
        );
    }

    std::string listEilute;

    // Praleidziame antraste
    std::getline(listFailas, listEilute);

    while (std::getline(listFailas, listEilute)) {
        if (listEilute.empty()) {
            continue;
        }

        std::istringstream srautas(listEilute);
        Studentas studentas;

        if (srautas >> studentas) {
            listStudentai.push_back(std::move(studentas));
        }
    }

    listFailas.close();

    auto listPabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> listTrukme =
        listPabaiga - listPradzia;

    std::cout << "LIST nuskaitytu studentu skaicius: "
        << listStudentai.size() << "\n";

    std::cout << "LIST nuskaitymo laikas: "
        << listTrukme.count() << " s\n";

    // DEQUE konteinerio nuskaitymo testas
    std::cout << "\n--- DEQUE ---\n";

    auto dequePradzia = std::chrono::steady_clock::now();

    std::ifstream dequeFailas(failoPavadinimas);

    if (!dequeFailas.is_open()) {
        throw std::runtime_error(
            "Nepavyko atidaryti failo: " + failoPavadinimas
        );
    }

    std::string dequeEilute;

    // Praleidziame antraste
    std::getline(dequeFailas, dequeEilute);

    while (std::getline(dequeFailas, dequeEilute)) {
        if (dequeEilute.empty()) {
            continue;
        }

        std::istringstream srautas(dequeEilute);
        Studentas studentas;

        if (srautas >> studentas) {
            dequeStudentai.push_back(std::move(studentas));
        }
    }

    dequeFailas.close();

    auto dequePabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> dequeTrukme =
        dequePabaiga - dequePradzia;

    std::cout << "DEQUE nuskaitytu studentu skaicius: "
        << dequeStudentai.size() << "\n";

    std::cout << "DEQUE nuskaitymo laikas: "
        << dequeTrukme.count() << " s\n";

    // VECTOR studentu skirstymo testas
    std::cout << "\n--- VECTOR SKIRSTYMAS ---\n";

    std::vector<Studentas> vectorVargsiukai;
    std::vector<Studentas> vectorKietiakiai;

    auto vectorSkirstymoPradzia =
        std::chrono::steady_clock::now();

    for (const Studentas& studentas : vectorStudentai) {
        if (studentas.getGalutinisVid() < 5.0) {
            vectorVargsiukai.push_back(studentas);
        }
        else {
            vectorKietiakiai.push_back(studentas);
        }
    }

    auto vectorSkirstymoPabaiga =
        std::chrono::steady_clock::now();

    std::chrono::duration<double> vectorSkirstymoTrukme =
        vectorSkirstymoPabaiga - vectorSkirstymoPradzia;

    std::cout << "VECTOR vargsiukai: "
        << vectorVargsiukai.size() << "\n";

    std::cout << "VECTOR kietiakiai: "
        << vectorKietiakiai.size() << "\n";

    std::cout << "VECTOR skirstymo laikas: "
        << vectorSkirstymoTrukme.count() << " s\n";

    // LIST studentu skirstymo testas
    std::cout << "\n--- LIST SKIRSTYMAS ---\n";

    std::list<Studentas> listVargsiukai;
    std::list<Studentas> listKietiakiai;

    auto listSkirstymoPradzia =
        std::chrono::steady_clock::now();

    for (const Studentas& studentas : listStudentai) {
        if (studentas.getGalutinisVid() < 5.0) {
            listVargsiukai.push_back(studentas);
        }
        else {
            listKietiakiai.push_back(studentas);
        }
    }

    auto listSkirstymoPabaiga =
        std::chrono::steady_clock::now();

    std::chrono::duration<double> listSkirstymoTrukme =
        listSkirstymoPabaiga - listSkirstymoPradzia;

    std::cout << "LIST vargsiukai: "
        << listVargsiukai.size() << "\n";

    std::cout << "LIST kietiakiai: "
        << listKietiakiai.size() << "\n";

    std::cout << "LIST skirstymo laikas: "
        << listSkirstymoTrukme.count() << " s\n";

        // DEQUE studentu skirstymo testas
    std::cout << "\n--- DEQUE SKIRSTYMAS ---\n";

    std::deque<Studentas> dequeVargsiukai;
    std::deque<Studentas> dequeKietiakiai;

    auto dequeSkirstymoPradzia =
        std::chrono::steady_clock::now();

    for (const Studentas& studentas : dequeStudentai) {
        if (studentas.getGalutinisVid() < 5.0) {
            dequeVargsiukai.push_back(studentas);
        }
        else {
            dequeKietiakiai.push_back(studentas);
        }
    }

    auto dequeSkirstymoPabaiga =
        std::chrono::steady_clock::now();

    std::chrono::duration<double> dequeSkirstymoTrukme =
        dequeSkirstymoPabaiga - dequeSkirstymoPradzia;

    std::cout << "DEQUE vargsiukai: "
        << dequeVargsiukai.size() << "\n";

    std::cout << "DEQUE kietiakiai: "
        << dequeKietiakiai.size() << "\n";

    std::cout << "DEQUE skirstymo laikas: "
        << dequeSkirstymoTrukme.count() << " s\n";

    // VECTOR rezultatu irasymo testas
    std::cout << "\n--- VECTOR IRASYMAS ---\n";

    isvestiStudentusIFaila(
        "vector_vargsiukai.txt",
        vectorVargsiukai
    );

    isvestiStudentusIFaila(
        "vector_kietiakiai.txt",
        vectorKietiakiai
    );

    // LIST rezultatu irasymo testas
    std::cout << "\n--- LIST IRASYMAS ---\n";

    auto listIrasymoPradzia =
        std::chrono::steady_clock::now();

    std::ofstream listVargsiukaiFailas("list_vargsiukai.txt");

    if (!listVargsiukaiFailas.is_open()) {
        throw std::runtime_error("Nepavyko sukurti list_vargsiukai.txt");
    }

    for (const Studentas& studentas : listVargsiukai) {
        listVargsiukaiFailas << studentas << "\n";
    }

    listVargsiukaiFailas.close();

    if (listVargsiukaiFailas.fail()) {
        throw std::runtime_error("Klaida irasant list_vargsiukai.txt");
    }

    std::ofstream listKietiakiaiFailas("list_kietiakiai.txt");

    if (!listKietiakiaiFailas.is_open()) {
        throw std::runtime_error("Nepavyko sukurti list_kietiakiai.txt");
    }

    for (const Studentas& studentas : listKietiakiai) {
        listKietiakiaiFailas << studentas << "\n";
    }

    listKietiakiaiFailas.close();

    if (listKietiakiaiFailas.fail()) {
        throw std::runtime_error("Klaida irasant list_kietiakiai.txt");
    }

    auto listIrasymoPabaiga =
        std::chrono::steady_clock::now();

    std::chrono::duration<double> listIrasymoTrukme =
        listIrasymoPabaiga - listIrasymoPradzia;

    std::cout << "LIST bendras irasymo laikas: "
        << listIrasymoTrukme.count() << " s\n";

    // DEQUE rezultatu irasymo testas
    std::cout << "\n--- DEQUE IRASYMAS ---\n";

    auto dequeIrasymoPradzia =
        std::chrono::steady_clock::now();

    std::ofstream dequeVargsiukaiFailas("deque_vargsiukai.txt");

    if (!dequeVargsiukaiFailas.is_open()) {
        throw std::runtime_error("Nepavyko sukurti deque_vargsiukai.txt");
    }

    for (const Studentas& studentas : dequeVargsiukai) {
        dequeVargsiukaiFailas << studentas << "\n";
    }

    dequeVargsiukaiFailas.close();

    if (dequeVargsiukaiFailas.fail()) {
        throw std::runtime_error("Klaida irasant deque_vargsiukai.txt");
    }

    std::ofstream dequeKietiakiaiFailas("deque_kietiakiai.txt");

    if (!dequeKietiakiaiFailas.is_open()) {
        throw std::runtime_error("Nepavyko sukurti deque_kietiakiai.txt");
    }

    for (const Studentas& studentas : dequeKietiakiai) {
        dequeKietiakiaiFailas << studentas << "\n";
    }

    dequeKietiakiaiFailas.close();

    if (dequeKietiakiaiFailas.fail()) {
        throw std::runtime_error("Klaida irasant deque_kietiakiai.txt");
    }

    auto dequeIrasymoPabaiga =
        std::chrono::steady_clock::now();

    std::chrono::duration<double> dequeIrasymoTrukme =
        dequeIrasymoPabaiga - dequeIrasymoPradzia;

    std::cout << "DEQUE bendras irasymo laikas: "
        << dequeIrasymoTrukme.count() << " s\n";
}