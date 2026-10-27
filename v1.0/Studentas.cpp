
#include "Studentas.h"

#include <sstream>
#include <algorithm>
#include <iomanip>
#include <numeric>
#include <stdexcept>
#include <utility>

// Numatytasis konstruktorius
Studentas::Studentas()
    : vardas_(""),
    pavarde_(""),
    egzaminas_(0),
    galutinisVid_(0.0),
    galutinisMed_(0.0) {
}

// Konstruktorius su parametrais
Studentas::Studentas(
    const std::string& vardas,
    const std::string& pavarde,
    const std::vector<int>& namuDarbai,
    int egzaminas
)
    : vardas_(vardas),
    pavarde_(pavarde),
    namuDarbai_(namuDarbai),
    egzaminas_(egzaminas),
    galutinisVid_(0.0),
    galutinisMed_(0.0) {

    skaiciuotiGalutini();
}

// Kopijavimo konstruktorius
Studentas::Studentas(const Studentas& kitas)
    : vardas_(kitas.vardas_),
    pavarde_(kitas.pavarde_),
    namuDarbai_(kitas.namuDarbai_),
    egzaminas_(kitas.egzaminas_),
    galutinisVid_(kitas.galutinisVid_),
    galutinisMed_(kitas.galutinisMed_) {
}

// Kopijavimo priskyrimo operatorius
Studentas& Studentas::operator=(const Studentas& kitas) {
    if (this != &kitas) {
        vardas_ = kitas.vardas_;
        pavarde_ = kitas.pavarde_;
        namuDarbai_ = kitas.namuDarbai_;
        egzaminas_ = kitas.egzaminas_;
        galutinisVid_ = kitas.galutinisVid_;
        galutinisMed_ = kitas.galutinisMed_;
    }

    return *this;
}

// Destruktorius
Studentas::~Studentas() {
}

// Galutiniu pazymiu skaiciavimas
void Studentas::skaiciuotiGalutini() {
    if (namuDarbai_.empty()) {
        galutinisVid_ = egzaminas_ * 0.6;
        galutinisMed_ = egzaminas_ * 0.6;
        return;
    }

    // Namu darbu vidurkis
    double suma = std::accumulate(
        namuDarbai_.begin(),
        namuDarbai_.end(),
        0.0
    );

    double vidurkis = suma / namuDarbai_.size();

    // Namu darbu mediana
    std::vector<int> surusiuoti = namuDarbai_;

    std::sort(
        surusiuoti.begin(),
        surusiuoti.end()
    );

    size_t n = surusiuoti.size();
    double mediana;

    if (n % 2 == 0) {
        mediana = (
            surusiuoti[n / 2 - 1] +
            surusiuoti[n / 2]
            ) / 2.0;
    }
    else {
        mediana = surusiuoti[n / 2];
    }

    // Galutinis pazymys:
    // 40% namu darbai + 60% egzaminas
    galutinisVid_ = 0.4 * vidurkis + 0.6 * egzaminas_;
    galutinisMed_ = 0.4 * mediana + 0.6 * egzaminas_;
}

// Duomenu gavimo metodai
std::string Studentas::getVardas() const {
    return vardas_;
}

std::string Studentas::getPavarde() const {
    return pavarde_;
}

double Studentas::getGalutinisVid() const {
    return galutinisVid_;
}

double Studentas::getGalutinisMed() const {
    return galutinisMed_;
}

// Duomenu ivedimo operatorius
std::istream& operator>>(
    std::istream& in,
    Studentas& studentas
    ) {
    std::string vardas;
    std::string pavarde;
    std::vector<int> namuDarbai;
    int egzaminas;

    if (!(in >> vardas >> pavarde)) {
        return in;
    }

    // Skaitome visa likusia eilute
    std::string eilute;
    std::getline(in, eilute);

    std::istringstream ss(eilute);
    std::vector<int> pazymiai;
    int pazymys;

    while (ss >> pazymys) {
        if (pazymys < 1 || pazymys > 10) {
            in.setstate(std::ios::failbit);
            return in;
        }

        pazymiai.push_back(pazymys);
    }

    if (pazymiai.empty() || !ss.eof()) {
        in.setstate(std::ios::failbit);
        return in;
    }

    egzaminas = pazymiai.back();
    pazymiai.pop_back();

    namuDarbai = std::move(pazymiai);

    studentas = Studentas(
        vardas,
        pavarde,
        namuDarbai,
        egzaminas
    );

    return in;
}

// Duomenu isvedimo operatorius
std::ostream& operator<<(
    std::ostream& out,
    const Studentas& studentas
    ) {
    out << std::left
        << std::setw(18) << studentas.pavarde_
        << std::setw(18) << studentas.vardas_
        << std::right
        << std::fixed << std::setprecision(2)
        << std::setw(18) << studentas.galutinisVid_
        << std::setw(18) << studentas.galutinisMed_;

    return out;
}
