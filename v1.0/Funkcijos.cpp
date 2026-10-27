
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
#include <utility>
#include <iterator>

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

// Antra strategija: studentu skirstymas naudojant viena nauja konteineri
void skirstytiStudentusStrategija2(
    std::vector<Studentas>& studentai,
    std::vector<Studentas>& vargsiukai
) {
    vargsiukai.clear();

    // Skirstymo laiko matavimo pradzia
    auto pradzia = std::chrono::steady_clock::now();

    auto it = studentai.begin();

    while (it != studentai.end()) {
        if (it->getGalutinisVid() < 5.0) {
            vargsiukai.push_back(std::move(*it));
            it = studentai.erase(it);
        }
        else {
            ++it;
        }
    }

    // Skirstymo laiko matavimo pabaiga
    auto pabaiga = std::chrono::steady_clock::now();

    std::chrono::duration<double> trukme = pabaiga - pradzia;

    std::cout << "\n--- STRATEGIJA 2 ---\n";

    std::cout << "Skirstymo laikas: "
        << trukme.count() << " s\n";

    std::cout << "Vargsiukai: "
        << vargsiukai.size() << "\n";

    std::cout << "Kietiakiai: "
        << studentai.size() << "\n";
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

// Dvieju skirstymo strategiju nasumo palyginimas
void palygintiStrategijas(
    const std::string& failoPavadinimas
) {
    std::cout << "\n========================================\n";
    std::cout << "       STRATEGIJU PALYGINIMAS           \n";
    std::cout << "========================================\n";

    // Nuskaitome studentus is failo
    std::vector<Studentas> studentai;
    nuskaitytiIsFailo(failoPavadinimas, studentai);

    std::cout << "\nStudentu skaicius: "
        << studentai.size() << "\n";

    // VECTOR - PIRMA STRATEGIJA
    {
        std::cout << "\n--- VECTOR: STRATEGIJA 1 ---\n";

        std::vector<Studentas> vectorVargsiukai;
        std::vector<Studentas> vectorKietiakiai;

        auto pradzia = std::chrono::steady_clock::now();

        for (const Studentas& studentas : studentai) {
            if (studentas.getGalutinisVid() < 5.0) {
                vectorVargsiukai.push_back(studentas);
            }
            else {
                vectorKietiakiai.push_back(studentas);
            }
        }

        auto pabaiga = std::chrono::steady_clock::now();

        std::chrono::duration<double> trukme = pabaiga - pradzia;

        std::cout << "Skirstymo laikas: "
            << trukme.count() << " s\n";

        std::cout << "Vargsiukai: "
            << vectorVargsiukai.size() << "\n";

        std::cout << "Kietiakiai: "
            << vectorKietiakiai.size() << "\n";

        // VECTOR - PIRMOS STRATEGIJOS ATMINTIES IVERTINIMAS
        size_t vectorAtmintis1 =
            (studentai.capacity() +
                vectorVargsiukai.capacity() +
                vectorKietiakiai.capacity()) * sizeof(Studentas);

        std::cout << "Apytiksle konteineriu atmintis: "
            << vectorAtmintis1 / 1024.0
            << " KB\n";
    }

    // Dideliems failams letesnes strategijos netestuojamos
    bool vykdytiLetasStrategijas = studentai.size() <= 10000;

    // VECTOR - ANTRA STRATEGIJA
    if (vykdytiLetasStrategijas) {
    std::cout << "\n--- VECTOR: STRATEGIJA 2 ---\n";

    // Sukuriame pradinių duomenu kopija
    std::vector<Studentas> vectorStudentai2 = studentai;
    std::vector<Studentas> vectorVargsiukai2;

    auto pradzia2 = std::chrono::steady_clock::now();

    auto it = vectorStudentai2.begin();

    while (it != vectorStudentai2.end()) {
        if (it->getGalutinisVid() < 5.0) {
            vectorVargsiukai2.push_back(std::move(*it));
            it = vectorStudentai2.erase(it);
        }
        else {
            ++it;
        }
    }

    auto pabaiga2 = std::chrono::steady_clock::now();

    std::chrono::duration<double> trukme2 = pabaiga2 - pradzia2;

    std::cout << "Skirstymo laikas: "
        << trukme2.count() << " s\n";

    std::cout << "Vargsiukai: "
        << vectorVargsiukai2.size() << "\n";

    std::cout << "Kietiakiai: "
        << vectorStudentai2.size() << "\n";

    // VECTOR - ANTROS STRATEGIJOS ATMINTIES IVERTINIMAS
    size_t vectorAtmintis2 =
        (vectorStudentai2.capacity() +
            vectorVargsiukai2.capacity()) * sizeof(Studentas);

    std::cout << "Apytiksle konteineriu atmintis: "
        << vectorAtmintis2 / 1024.0
        << " KB\n";

    }
    else {
        std::cout << "\n--- VECTOR: STRATEGIJA 2 ---\n";
        std::cout << "Strategija praleista: daugiau nei 10000 studentu.\n";
    }

    // LIST - PIRMA STRATEGIJA
    {
        std::cout << "\n--- LIST: STRATEGIJA 1 ---\n";

        // Sukuriame LIST konteineri su tais paciais studentais
        std::list<Studentas> listStudentai(
            studentai.begin(),
            studentai.end()
        );

        std::list<Studentas> listVargsiukai;
        std::list<Studentas> listKietiakiai;

        // Skirstymo laiko matavimo pradzia
        auto listPradzia = std::chrono::steady_clock::now();

        for (const Studentas& studentas : listStudentai) {
            if (studentas.getGalutinisVid() < 5.0) {
                listVargsiukai.push_back(studentas);
            }
            else {
                listKietiakiai.push_back(studentas);
            }
        }

        // Skirstymo laiko matavimo pabaiga
        auto listPabaiga = std::chrono::steady_clock::now();

        std::chrono::duration<double> listTrukme =
            listPabaiga - listPradzia;

        std::cout << "Skirstymo laikas: "
            << listTrukme.count() << " s\n";

        std::cout << "Vargsiukai: "
            << listVargsiukai.size() << "\n";

        std::cout << "Kietiakiai: "
            << listKietiakiai.size() << "\n";

        // LIST - PIRMOS STRATEGIJOS ATMINTIES IVERTINIMAS
        size_t listAtmintis1 =
            (listStudentai.size() +
                listVargsiukai.size() +
                listKietiakiai.size()) * sizeof(Studentas);

        std::cout << "Apytiksle elementu atmintis: "
            << listAtmintis1 / 1024.0
            << " KB\n";
    }

    // LIST - ANTRA STRATEGIJA
    {
        std::cout << "\n--- LIST: STRATEGIJA 2 ---\n";

        // Sukuriame pradinių duomenu kopija
        std::list<Studentas> listStudentai2(
            studentai.begin(),
            studentai.end()
        );

        std::list<Studentas> listVargsiukai2;

        // Skirstymo laiko matavimo pradzia
        auto listPradzia2 = std::chrono::steady_clock::now();

        auto listIt = listStudentai2.begin();

        while (listIt != listStudentai2.end()) {
            if (listIt->getGalutinisVid() < 5.0) {
                auto perkeliamas = listIt++;
                listVargsiukai2.splice(
                    listVargsiukai2.end(),
                    listStudentai2,
                    perkeliamas
                );
            }
            else {
                ++listIt;
            }
        }

        // Skirstymo laiko matavimo pabaiga
        auto listPabaiga2 = std::chrono::steady_clock::now();

        std::chrono::duration<double> listTrukme2 =
            listPabaiga2 - listPradzia2;

        std::cout << "Skirstymo laikas: "
            << listTrukme2.count() << " s\n";

        std::cout << "Vargsiukai: "
            << listVargsiukai2.size() << "\n";

        std::cout << "Kietiakiai: "
            << listStudentai2.size() << "\n";

        // LIST - ANTROS STRATEGIJOS ATMINTIES IVERTINIMAS
        size_t listAtmintis2 =
            (listStudentai2.size() +
                listVargsiukai2.size()) * sizeof(Studentas);

        std::cout << "Apytiksle elementu atmintis: "
            << listAtmintis2 / 1024.0
            << " KB\n";
    }

    // DEQUE - PIRMA STRATEGIJA
    {
        std::cout << "\n--- DEQUE: STRATEGIJA 1 ---\n";

        // Sukuriame DEQUE konteineri su tais paciais studentais
        std::deque<Studentas> dequeStudentai(
            studentai.begin(),
            studentai.end()
        );

        std::deque<Studentas> dequeVargsiukai;
        std::deque<Studentas> dequeKietiakiai;

        // Skirstymo laiko matavimo pradzia
        auto dequePradzia = std::chrono::steady_clock::now();

        for (const Studentas& studentas : dequeStudentai) {
            if (studentas.getGalutinisVid() < 5.0) {
                dequeVargsiukai.push_back(studentas);
            }
            else {
                dequeKietiakiai.push_back(studentas);
            }
        }

        // Skirstymo laiko matavimo pabaiga
        auto dequePabaiga = std::chrono::steady_clock::now();

        std::chrono::duration<double> dequeTrukme =
            dequePabaiga - dequePradzia;

        std::cout << "Skirstymo laikas: "
            << dequeTrukme.count() << " s\n";

        std::cout << "Vargsiukai: "
            << dequeVargsiukai.size() << "\n";

        std::cout << "Kietiakiai: "
            << dequeKietiakiai.size() << "\n";

        // DEQUE - PIRMOS STRATEGIJOS ATMINTIES IVERTINIMAS
        size_t dequeAtmintis1 =
            (dequeStudentai.size() +
                dequeVargsiukai.size() +
                dequeKietiakiai.size()) * sizeof(Studentas);

        std::cout << "Apytiksle elementu atmintis: "
            << dequeAtmintis1 / 1024.0
            << " KB\n";
    }

    // DEQUE - ANTRA STRATEGIJA
    if (vykdytiLetasStrategijas) {
    std::cout << "\n--- DEQUE: STRATEGIJA 2 ---\n";

    // Sukuriame pradiniu duomenu kopija
    std::deque<Studentas> dequeStudentai2(
        studentai.begin(),
        studentai.end()
    );

    std::deque<Studentas> dequeVargsiukai2;

    // Skirstymo laiko matavimo pradzia
    auto dequePradzia2 = std::chrono::steady_clock::now();

    auto dequeIt = dequeStudentai2.begin();

    while (dequeIt != dequeStudentai2.end()) {
        if (dequeIt->getGalutinisVid() < 5.0) {
            dequeVargsiukai2.push_back(std::move(*dequeIt));
            dequeIt = dequeStudentai2.erase(dequeIt);
        }
        else {
            ++dequeIt;
        }
    }

    // Skirstymo laiko matavimo pabaiga
    auto dequePabaiga2 = std::chrono::steady_clock::now();

    std::chrono::duration<double> dequeTrukme2 =
        dequePabaiga2 - dequePradzia2;

    std::cout << "Skirstymo laikas: "
        << dequeTrukme2.count() << " s\n";

    std::cout << "Vargsiukai: "
        << dequeVargsiukai2.size() << "\n";

    std::cout << "Kietiakiai: "
        << dequeStudentai2.size() << "\n";

    // DEQUE - ANTROS STRATEGIJOS ATMINTIES IVERTINIMAS
    size_t dequeAtmintis2 =
        (dequeStudentai2.size() +
            dequeVargsiukai2.size()) * sizeof(Studentas);

    std::cout << "Apytiksle elementu atmintis: "
        << dequeAtmintis2 / 1024.0
        << " KB\n";

    }
    else {
        std::cout << "\n--- DEQUE: STRATEGIJA 2 ---\n";
        std::cout << "Strategija praleista: daugiau nei 10000 studentu.\n";
    }

    // VECTOR - OPTIMIZUOTA STRATEGIJA SU STD::PARTITION
    {
        std::cout << "\n--- VECTOR: STD::PARTITION ---\n";

        // Sukuriame studentu kopija
        std::vector<Studentas> vectorOptimizuotas = studentai;

        // Pradedame matuoti laika
        auto partitionPradzia = std::chrono::steady_clock::now();

        // Atskiriame studentus pagal galutini bala
        auto riba = std::partition(
            vectorOptimizuotas.begin(),
            vectorOptimizuotas.end(),
            [](const Studentas& s) {
                return s.getGalutinisVid() >= 5.0;
            }
        );

        // Sukuriame viena nauja konteineri vargsiukams
        std::vector<Studentas> partitionVargsiukai(
            std::make_move_iterator(riba),
            std::make_move_iterator(vectorOptimizuotas.end())
        );

        // Pasaliname vargsiukus is pradinio konteinerio
        vectorOptimizuotas.erase(riba, vectorOptimizuotas.end());

        // Baigiame matuoti laika
        auto partitionPabaiga = std::chrono::steady_clock::now();

        std::chrono::duration<double> partitionTrukme =
            partitionPabaiga - partitionPradzia;

        std::cout << "Skirstymo laikas: "
            << partitionTrukme.count() << " s\n";

        std::cout << "Vargsiukai: "
            << partitionVargsiukai.size() << "\n";

        std::cout << "Kietiakiai: "
            << vectorOptimizuotas.size() << "\n";

        // VECTOR - OPTIMIZUOTOS STRATEGIJOS ATMINTIES IVERTINIMAS
        size_t partitionAtmintis =
            (vectorOptimizuotas.capacity() +
                partitionVargsiukai.capacity()) * sizeof(Studentas);

        std::cout << "Apytiksle konteineriu atmintis: "
            << partitionAtmintis / 1024.0
            << " KB\n";
    }

    // VECTOR - OPTIMIZUOTA STRATEGIJA SU STD::STABLE_PARTITION
    {
        std::cout << "\n--- VECTOR: STD::STABLE_PARTITION ---\n";

        // Sukuriame studentu kopija
        std::vector<Studentas> vectorStable = studentai;
        std::vector<Studentas> stableVargsiukai;

        // Pradedame matuoti laika
        auto stablePradzia = std::chrono::steady_clock::now();

        // Skirstome studentus islaikydami ju pradine tvarka
        auto stableRiba = std::stable_partition(
            vectorStable.begin(),
            vectorStable.end(),
            [](const Studentas& s) {
                return s.getGalutinisVid() >= 5.0;
            }
        );

        // Perkeliame vargsiukus i nauja konteineri
        stableVargsiukai.assign(
            std::make_move_iterator(stableRiba),
            std::make_move_iterator(vectorStable.end())
        );

        // Pasaliname vargsiukus is pradinio konteinerio
        vectorStable.erase(stableRiba, vectorStable.end());

        // Baigiame matuoti laika
        auto stablePabaiga = std::chrono::steady_clock::now();

        std::chrono::duration<double> stableTrukme =
            stablePabaiga - stablePradzia;

        std::cout << "Skirstymo laikas: "
            << stableTrukme.count() << " s\n";

        std::cout << "Vargsiukai: "
            << stableVargsiukai.size() << "\n";

        std::cout << "Kietiakiai: "
            << vectorStable.size() << "\n";

        // Atminties ivertinimas
        size_t stableAtmintis =
            (vectorStable.capacity() +
                stableVargsiukai.capacity()) * sizeof(Studentas);

        std::cout << "Apytiksle konteineriu atmintis: "
            << stableAtmintis / 1024.0
            << " KB\n";
    }

    // VECTOR - OPTIMIZUOTA STRATEGIJA SU STD::REMOVE_IF
    {
        std::cout << "\n--- VECTOR: STD::REMOVE_IF ---\n";

        // Sukuriame studentu kopija
        std::vector<Studentas> vectorRemove = studentai;
        std::vector<Studentas> removeVargsiukai;

        // Pradedame matuoti laika
        auto removePradzia = std::chrono::steady_clock::now();

        // Nukopijuojame vargsiukus i nauja konteineri
        std::copy_if(
            vectorRemove.begin(),
            vectorRemove.end(),
            std::back_inserter(removeVargsiukai),
            [](const Studentas& s) {
                return s.getGalutinisVid() < 5.0;
            }
        );

        // Pasaliname vargsiukus is pradinio konteinerio
        auto removeRiba = std::remove_if(
            vectorRemove.begin(),
            vectorRemove.end(),
            [](const Studentas& s) {
                return s.getGalutinisVid() < 5.0;
            }
        );

        vectorRemove.erase(removeRiba, vectorRemove.end());

        // Baigiame matuoti laika
        auto removePabaiga = std::chrono::steady_clock::now();

        std::chrono::duration<double> removeTrukme =
            removePabaiga - removePradzia;

        std::cout << "Skirstymo laikas: "
            << removeTrukme.count() << " s\n";

        std::cout << "Vargsiukai: "
            << removeVargsiukai.size() << "\n";

        std::cout << "Kietiakiai: "
            << vectorRemove.size() << "\n";

        // Atminties ivertinimas
        size_t removeAtmintis =
            (vectorRemove.capacity() +
                removeVargsiukai.capacity()) * sizeof(Studentas);

        std::cout << "Apytiksle konteineriu atmintis: "
            << removeAtmintis / 1024.0
            << " KB\n";
    }
}

