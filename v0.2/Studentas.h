
#pragma once

#include <iostream>
#include <string>
#include <vector>

class Studentas {
private:
    // Studento duomenys
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> namuDarbai_;
    int egzaminas_;

    // Galutiniai pazymiai
    double galutinisVid_;
    double galutinisMed_;

public:
    // Numatytasis konstruktorius
    Studentas();

    // Konstruktorius su parametrais
    Studentas(
        const std::string& vardas,
        const std::string& pavarde,
        const std::vector<int>& namuDarbai,
        int egzaminas
    );

    // Rule of Three
    Studentas(const Studentas& kitas);
    Studentas& operator=(const Studentas& kitas);
    ~Studentas();

    // Galutiniu pazymiu skaiciavimas
    void skaiciuotiGalutini();

    // Duomenu gavimo metodai
    std::string getVardas() const;
    std::string getPavarde() const;
    double getGalutinisVid() const;
    double getGalutinisMed() const;

    // Duomenu ivedimas (cin)
    friend std::istream& operator>>(
        std::istream& in,
        Studentas& studentas
        );

    // Duomenu isvedimas (cout)
    friend std::ostream& operator<<(
        std::ostream& out,
        const Studentas& studentas
        );
};
