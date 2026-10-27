#include "Studentas.h"
#include "Funkcijos.h"

#include <stdexcept>
#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <exception>

// Meniu pasirinkimo ivedimas
int pasirinkti(int min, int max) {
    int pasirinkimas;

    while (true) {
        if (std::cin >> pasirinkimas &&
            pasirinkimas >= min &&
            pasirinkimas <= max) {

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return pasirinkimas;
        }

        if (std::cin.eof()) {
            throw std::runtime_error("Ivesties srautas uzdarytas.");
        }

        std::cout << "Neteisingas pasirinkimas. Bandykite dar karta: ";

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

int main() {
    std::vector<Studentas> studentai;

    try {
        while (true) {
            std::cout << "\n";
            std::cout << "========================================\n";
            std::cout << "           STUDENTU SISTEMA             \n";
            std::cout << "========================================\n";
            std::cout << "1. Ivesti studentus rankiniu budu\n";
            std::cout << "2. Generuoti atsitiktinius pazymius\n";
            std::cout << "3. Nuskaityti studentus is failo\n";
            std::cout << "4. Generuoti studentu failus\n";
            std::cout << "5. Skirstyti studentus i dvi grupes\n";
            std::cout << "6. Palyginti vector, list ir deque\n";
            std::cout << "7. Palyginti skirstymo strategijas\n";
            std::cout << "0. Baigti programa\n";
            std::cout << "----------------------------------------\n";
            std::cout << "Pasirinkite: ";

            int pasirinkimas = pasirinkti(0, 7);

            if (pasirinkimas == 0) {
                std::cout << "\nPrograma baigta.\n";
                break;
            }

            // Naujam veiksmui naudojamas tuscias sarasas
            studentai.clear();

            try {
                if (pasirinkimas == 1) {
                    ivestiStudentus(studentai);
                }
                else if (pasirinkimas == 2) {
                    generuotiStudentus(studentai);
                }
                else if (pasirinkimas == 3) {
                    std::string failoPavadinimas;

                    std::cout << "\nIveskite failo pavadinima "
                        << "(pvz. kursiokai.txt): ";

                    std::getline(std::cin, failoPavadinimas);

                    if (failoPavadinimas.empty()) {
                        failoPavadinimas = "kursiokai.txt";
                    }

                    nuskaitytiIsFailo(
                        failoPavadinimas,
                        studentai
                    );
                }

                else if (pasirinkimas == 4) {
                    std::cout << "\nGeneruojami studentu failai...\n";

                    generuotiStudentuFaila("studentai1000.txt", 1000);
                    generuotiStudentuFaila("studentai10000.txt", 10000);
                    generuotiStudentuFaila("studentai100000.txt", 100000);
                    generuotiStudentuFaila("studentai1000000.txt", 1000000);
                    generuotiStudentuFaila("studentai10000000.txt", 10000000);

                    std::cout << "\nVisi failai sugeneruoti!\n";
                    continue;
                }

                else if (pasirinkimas == 5) {
                    std::string failoPavadinimas;

                    std::cout << "\nStudentu skirstymas i dvi grupes...\n";
                    std::cout << "Iveskite failo pavadinima: ";
                    std::cin >> failoPavadinimas;

                    // Studentu duomenu nuskaitymas
                    studentai.clear();
                    nuskaitytiIsFailo(failoPavadinimas, studentai);

                    // Sukuriame dvi studentu grupes
                    std::vector<Studentas> vargsiukai;
                    std::vector<Studentas> kietiakiai;

                    // Skirstymo strategijos pasirinkimas
                    std::cout << "\nPasirinkite skirstymo strategija:\n";
                    std::cout << "1. Strategija 1 - du nauji konteineriai\n";
                    std::cout << "2. Strategija 2 - vienas naujas konteineris\n";
                    std::cout << "Pasirinkite: ";

                    int strategija = pasirinkti(1, 2);

                    // Skirstome studentus pagal pasirinkta strategija
                    if (strategija == 1) {
                        skirstytiStudentus(
                            studentai,
                            vargsiukai,
                            kietiakiai
                        );
                    }
                    else {
                        skirstytiStudentusStrategija2(
                            studentai,
                            vargsiukai
                        );

                        // Po antros strategijos studentai konteineryje lieka kietiakiai
                        kietiakiai = std::move(studentai);
                    }

                    // Isvedame rezultatus i atskirus failus
                    isvestiStudentusIFaila(
                        "vargsiukai.txt",
                        vargsiukai
                    );

                    isvestiStudentusIFaila(
                        "kietiakiai.txt",
                        kietiakiai
                    );

                    std::cout << "\nStudentu skirstymas baigtas!\n";
                    continue;
                }

                else if (pasirinkimas == 6) {
                    std::string failoPavadinimas;

                    std::cout << "\nKonteineriu nasumo palyginimas...\n";
                    std::cout << "Iveskite failo pavadinima: ";
                    std::cin >> failoPavadinimas;

                    palygintiKonteinerius(failoPavadinimas);

                    std::cout << "\nKonteineriu palyginimas baigtas!\n";
                    continue;
                }

                else if (pasirinkimas == 7) {
                    std::string failoPavadinimas;

                    std::cout << "\nStrategiju nasumo palyginimas...\n";
                    std::cout << "Iveskite failo pavadinima: ";
                    std::cin >> failoPavadinimas;

                    palygintiStrategijas(failoPavadinimas);

                    std::cout << "\nStrategiju palyginimas baigtas!\n";
                    continue;
                    }

                if (studentai.empty()) {
                    std::cout << "\nStudentu sarasas tuscias.\n";
                    continue;
                }

                // Studentu rusiavimas
                rusiuotiStudentus(studentai);

                // Galutinio pazymio pasirinkimas
                std::cout << "\nPasirinkite rezultatu skaiciavimo buda:\n";
                std::cout << "1. Pagal vidurki\n";
                std::cout << "2. Pagal mediana\n";
                std::cout << "3. Rodyti abu rezultatus\n";
                std::cout << "Pasirinkite: ";

                int budas = pasirinkti(1, 3);

                // Rezultatu isvedimas
                isvestiStudentus(studentai, budas);

                std::cout << "\nIs viso studentu: "
                    << studentai.size() << "\n";
            }
            catch (const std::exception& e) {
                std::cerr << "\nKlaida: " << e.what() << "\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "\nKritine klaida: "
            << e.what() << "\n";
        return 1;
    }

    return 0;
}
