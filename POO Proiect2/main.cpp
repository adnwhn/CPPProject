#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Review {
    string nume;
    int nrZile;
    int nota;
public:
    Review() : nume("NULL"), nrZile(0), nota(0) {}

    Review(const string &nume, int nrZile, int nota) : nume(nume), nrZile(nrZile), nota(nota) {}

    int getNota() const {
        return nota;
    }

    friend istream &operator>>(istream &is, Review &aReview) {
        return aReview.citire(is);
    }

    virtual istream &citire(istream &is) {
        cout << "\nnume: ";
        is >> nume;
        cout << "\nnr Zile: ";
        is >> nrZile;
        cout << "\nnota: ";
        is >> nota;
        return is;
    }

    friend ostream &operator<<(ostream &os, const Review &aReview) {
        return aReview.afisare(os);
    }

    virtual ostream &afisare(ostream &os) const {
        os << "\nnume: " << nume
           << "\nnr Zile: " << nrZile
           << "\nnota: " << nota;
        return os;
    }
};

class Discount {
protected:
    double discount;
    bool isPercentile;
public:
    Discount() : discount(0), isPercentile(false) {}

    Discount(double discount, bool isPercentile) : discount(discount), isPercentile(isPercentile) {}

    virtual ~Discount() = default;

    double getDiscount() const {
        return discount;
    }

    void setDiscount(double _discount) {
        discount = _discount;
    }
};

class MountainsDiscount : public Discount {
public:
    MountainsDiscount() : Discount() {}

    MountainsDiscount(double discount) : Discount(discount, isPercentile) {
        isPercentile = false;
    }
};

class IslandsDiscount : public Discount {
public:
    IslandsDiscount() : Discount() {}

    IslandsDiscount(double discount) : Discount(discount, isPercentile) {
        isPercentile = false;
    }
};

class PercentileDiscount : public Discount {
public:
    PercentileDiscount() : Discount() {}

    PercentileDiscount(double discount) : Discount(discount, isPercentile) {
        isPercentile = true;
        if (discount > 50) {
            throw 1;  // cod de eroare pt valori mai mari de 50%
        }
    }
};

class Destination {
    string tara;
    string oras;
    string denumire;
    double pretPerZi;
    vector<Review *> Reviews;
public:
    Destination() : tara("NULL"), oras("NULL"), denumire("NULL"), pretPerZi(0.0) {}

    Destination(const string &tara, const string &oras, const string &denumire, double pretPerZi) :
            tara(tara), oras(oras), denumire(denumire), pretPerZi(pretPerZi) {}

    const string &getTara() const {
        return tara;
    }

    const string &getOras() const {
        return oras;
    }

    const string &getDenumire() const {
        return denumire;
    }

    const vector<Review *> &getReviews() const {
        return Reviews;
    }

    double getPretPerZi() const {
        return pretPerZi;
    }

    friend istream &operator>>(istream &is, Destination &aDestination) {
        return aDestination.citire(is);
    }

    virtual istream &citire(istream &is) {
        cout << "\ntara: ";
        is >> tara;
        cout << "\noras: ";
        is >> oras;
        cout << "\ndenumire: ";
        is >> denumire;
        cout << "\npret per zi: ";
        is >> pretPerZi;
        return is;
    }

    friend ostream &operator<<(ostream &os, const Destination &aDestination) {
        return aDestination.afisare(os);
    }

    virtual ostream &afisare(ostream &os) const {
        os << "\ntara: " << tara
           << "\noras: " << oras
           << "\ndenumire: " << denumire
           << "\npret per zi: " << pretPerZi;
        return os;
    }

    void addReview(Review *aReview) {
        Reviews.push_back(aReview);
    }

    double notaMedieDestinatie() {
        if (Reviews.empty()) {
            return 0;
        }

        double notaMedie;
        int sumaNote;

        for (auto aReview = Reviews.begin(); aReview != Reviews.end(); aReview++) {
            sumaNote += (*aReview)->getNota();
        }

        return notaMedie = double(sumaNote) / (Reviews.size());
    }
};

class IslandDestination : public Destination {
    string iesire;
    int nrInsule;
public:
    IslandDestination() : Destination(), nrInsule(0) {}

    IslandDestination(const string &tara, const string &oras, const string &denumire, double pretPerZi, string iesire,
                      int nrInsule) :
            Destination(tara, oras, denumire, pretPerZi), iesire(iesire), nrInsule(nrInsule) {}

    istream &citire(istream &is) override {
        Destination::citire(is);
        cout << "\niesire (mare/ocean): ";
        is >> iesire;
        cout << "\nnr Insule: ";
        is >> nrInsule;
        return is;
    }

    ostream &afisare(ostream &os) const override {
        Destination::afisare(os);
        os << "\niesire la: " << iesire
           << "\nnr Insule: " << nrInsule;
        return os;
    }
};

class MountainDestination : public Destination {
    double inaltime;
    double distanta;
    int nrTrasee;
public:
    MountainDestination() : Destination(), inaltime(0.0), distanta(0.0), nrTrasee(0) {}

    MountainDestination(const string &tara, const string &oras, const string &denumire, double pretPerZi,
                        double inaltime, double distanta, int nrTrasee) :
            Destination(tara, oras, denumire, pretPerZi), inaltime(inaltime), distanta(distanta), nrTrasee(nrTrasee) {}

    istream &citire(istream &is) override {
        Destination::citire(is);
        cout << "\ninaltime: ";
        is >> inaltime;
        cout << "\ndistanta: ";
        is >> distanta;
        cout << "\nnr Trasee: ";
        is >> nrTrasee;
        return is;
    }

    ostream &afisare(ostream &os) const override {
        Destination::afisare(os);
        os << "\ninaltime: " << inaltime
           << "\ndistanta: " << distanta
           << "\nnr Trasee: " << nrTrasee;
        return os;
    }
};

Destination *citireDestination() {
    Destination *aDestination;
    string tip;
    cout << "\ntip destinatie(insulara/montana): ";
    cin >> tip;

    if (tip == "insulara") {
        aDestination = new IslandDestination;
        cin >> *aDestination;
    } else if (tip == "montana") {
        aDestination = new MountainDestination;
        cin >> *aDestination;
    }

    cin >> *aDestination;
    return aDestination;
}

class TravelAgency {
    vector<Destination *> Destinations;
    vector<Discount *> discounts;
    TravelAgency() {}; // constructor privat pentru Singleton
    static TravelAgency *instance; // variabila statica pointer pentru a verifica (!=0); initializata in afara clasei
public:
    // metoda care da instanta
    static TravelAgency *getInstance() {
        if(instance == nullptr){
            instance = new TravelAgency();
        }
        return instance;
    }

    void addIsland(IslandDestination *anIsland) {
        Destinations.push_back(anIsland);
    }

    void addMountain(MountainDestination *aMountain) {
        Destinations.push_back(aMountain);
    }

    void addDiscount(Discount *aDiscount) {
        discounts.push_back(aDiscount);
    }

    // Bonus 3 meniu interactiv
    void showMenu() {
        cout << "\nOptiunea 1: Adauga destinatie\n";
        cout << "Optiunea 2: Sterge destinatie\n";
        cout << "Optiunea 3: Adauga recenzie\n";
        cout << "Optiunea 4: Adauga discount\n";
        cout << "Optiunea 5: Afiseaza informatii despre o destinatie\n";
        cout << "Optiunea 6: Exit\n";
    }

    void addDestination() {
        Destinations.push_back(citireDestination());
        cout << "\nDestinatia a fost adaugata!";
    }

    void deleteDestination() {
        string nume;
        cout << "\nIntroduceti numele destinatiei pe care doriti sa o stergeti: ";
        cin >> nume;
        remove(Destinations.begin(), Destinations.end(), searchDestination(nume));
        cout << "\nDestinatia " << nume << " a fost stearsa!";
    }


    Destination *searchDestination(string nume) {
        for (auto *aDestination: Destinations) {
            if (nume == aDestination->getDenumire()) {
                return aDestination;
            }
        }
        cout << "\nNu s-a gasit destinatia!";
        return 0;
    }

    void addReview(Destination &aDestination) {
        Review *aReview = new Review;
        cin >> *aReview;
        aDestination.addReview(aReview);
        cout << "\nRecenzia a fost adaugata!";
    }

    void addDiscount() {
        Discount *aDiscount;
        cout << "\nIntroduceti tipul discountului (Mountain/Island/Percentile): ";
        string tip;
        cin >> tip;
        if (tip == "Mountain") {
            aDiscount = new MountainsDiscount;
        } else if (tip == "Island") {
            aDiscount = new IslandsDiscount;
        } else if (tip == "Percentile") {
            aDiscount = new PercentileDiscount;
        }

        cout << "\nIntroduceti valoarea discountului: ";
        double discount;
        // Bonus 4 testarea erorilor

        try {
            cin >> discount;
            if (tip == "Percentile" && discount > 50) {
                throw 1;  // cod de eroare pt valori mai mari de 50%
            }
        }
        catch (int err) {
            if (err == 1) {
                cout << "\nDiscountul procentual trebuie sa aiba intotdeauna o valoarea mai mica decat 50%!";
                cout << "\nDiscountul nu a fost adaugat!";
                return;
            }
        }

        aDiscount->setDiscount(discount);
        discounts.push_back(aDiscount);
        cout << "\nDiscountul a fost adaugat!";
    }

    string destinationType(Destination *aDestination) {
        if (dynamic_cast<IslandDestination *>(aDestination)) {
            return "insula";
        } else if (dynamic_cast<MountainDestination *>(aDestination)) {
            return "munte";
        }
        return "ERRdestinationType";
    }

    string discountType(Discount *aDiscount) {
        if (dynamic_cast<MountainsDiscount *>(aDiscount)) {
            return "munte";
        } else if (dynamic_cast<IslandsDiscount *>(aDiscount)) {
            return "insula";
        } else if (dynamic_cast<PercentileDiscount *>(aDiscount)) {
            return "procent";
        }
        return "ERRdiscountType";
    }

    double maxDiscount(string tip) {
        double maxDiscount = 0;
        for (auto aDiscount = discounts.begin(); aDiscount != discounts.end(); aDiscount++) {
            if (discounts.empty()) {
                cout << "\nNu exista reduceri care pot fi aplicate!";
            } else if ((tip == discountType(*aDiscount)) && (maxDiscount < ((*aDiscount)->getDiscount()))) {
                maxDiscount = (*aDiscount)->getDiscount();
            }
        }
        return maxDiscount;
    }

    double computeDiscountedPrice(Destination *aDestination) {
        string tip = destinationType(aDestination);
        if (tip == "insula") {
            double pretDiscountSimplu, pretDiscountProcentual;
            pretDiscountSimplu = aDestination->getPretPerZi() - maxDiscount("insula");
            pretDiscountProcentual =
                    aDestination->getPretPerZi() - (aDestination->getPretPerZi()) * ((maxDiscount("procent")) / 100.0);
            return min(pretDiscountSimplu, pretDiscountProcentual);
        } else if (tip == "munte") {
            double pretDiscountSimplu, pretDiscountProcentual;
            pretDiscountSimplu = aDestination->getPretPerZi() - maxDiscount("munte");
            pretDiscountProcentual =
                    aDestination->getPretPerZi() - (aDestination->getPretPerZi()) * ((maxDiscount("procent")) / 100.0);
            return min(pretDiscountSimplu, pretDiscountProcentual);
        }
        return aDestination->getPretPerZi();
    }

    void showSummary() {
        for (auto aDestination = Destinations.begin(); aDestination != Destinations.end(); aDestination++) {
            cout << "\ntara: " << (*aDestination)->getTara()
                 << "\noras: " << (*aDestination)->getOras()
                 << "\ndenumire: " << (*aDestination)->getDenumire()
                 << "\nnr recenzii: " << (*aDestination)->getReviews().size()
                 << "\nmedia recenziilor(nota): " << (*aDestination)->notaMedieDestinatie()
                 << "\npret cu reducere pentru o zi: " << computeDiscountedPrice(*aDestination);
        }
    }

    void run() {
        while (true) {
            showMenu();
            int optiune;
            cin >> optiune;
            if (optiune == 1) {
                addDestination();
            } else if (optiune == 2) {
                deleteDestination();
            } else if (optiune == 3) {
                string nume;
                cout << "\nCare este numele destinatiei cautate?";
                cin >> nume;
                Destination *aDestination = searchDestination(nume);
                if (aDestination) {
                    cout << "\nIntroduceti datele recenziei pentru destinatia aleasa: ";
                    addReview(*aDestination);
                }
            } else if (optiune == 4) {
                addDiscount();
            } else if (optiune == 5) {
                showSummary();
            } else if (optiune == 6) {
                break;
            }
        }
        cout << "Final!";
    }
};

TravelAgency* TravelAgency::instance = 0;

int main() {
    IslandDestination Filicudi("Sicily", "Lipari", "Filicudi", 297.0, "mare", 4);
    IslandDestination Flatey("Iceland", "Flatey", "Flatey", 360.0, "ocean", 9);
    MountainDestination Aoraki("New Zeeland", "Fox Glacier", "Aoraki", 552.70, 3724.4, 26.3, 4);
    MountainDestination MountRosa("Switzerland", "Zermatt", "MountRosa", 459.99, 4634.2, 21.0, 7);
    MountainDestination Grossglockner("Austria", "Heiligenblut", "Grossglockner", 505.05, 3798.9, 13.7, 5);

    TravelAgency *aTravelAgency = TravelAgency::getInstance();

    aTravelAgency->addIsland(&Filicudi);
    aTravelAgency->addIsland(&Flatey);
    aTravelAgency->addMountain(&Aoraki);
    aTravelAgency->addMountain(&MountRosa);
    aTravelAgency->addMountain(&Grossglockner);

    MountainsDiscount aMountainDiscount(75);
    IslandsDiscount anIslandDiscount(46.9);
    PercentileDiscount aPercentileDiscount;
    // Bonus 4 testarea erorilor
    try {
        aPercentileDiscount = PercentileDiscount(10);
    }
    catch (int err) {
        if (err == 1) {
            cout << "\nDiscountul procentual trebuie sa aiba intotdeauna o valoarea mai mica decat 50%!";
        }
    }

    aTravelAgency->addDiscount(&aMountainDiscount);
    aTravelAgency->addDiscount(&anIslandDiscount);
    aTravelAgency->addDiscount(&aPercentileDiscount);

    aTravelAgency->run();
    return 0;
}