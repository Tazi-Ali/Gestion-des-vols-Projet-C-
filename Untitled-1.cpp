#include <iostream>
#include <string>
#include <deque>
#include <list>
#include <map>
#include <set>
#include <ctime>
#include <algorithm>

using namespace std;

// Définition de la structure Date
// Cette structure est utilisée pour représenter une date sans l'heure (jour, mois, année)
// Les attributs sont publics pour simplifier l'accès
// Les valeurs par défaut sont initialisées à 0
// Les valeurs par défaut sont utilisées si l'utilisateur ne fournit pas de valeurs lors de la création d'un objet Date
// Les valeurs fournit par l'user sont utilisées pour initialiser les attributs de l'objet Date avec le constructeur par defaut
struct Date
{
    int day;
    int month;
    int year;
};

// Les classes sont déclarées avant d'être utilisées dans les fonctions
// Ceci est nécessaire car les classes sont utilisées dans les fonctions pour eviter les erreurs de compilation
// Les fonctions sont définies après la définition des classes
class Paiement;
class Reservation;

// Définition de la classe Vol
// Cette classe utilise des attributs protégés pour que les classes dérivées puissent y accéder directement
class Vol
{
protected:
    int numeroVol;
    string aeroportDepart;
    string aeroportArrivee;
    Date dateDepart;
    Date dateArrivee;
    int placesDisponibles;
    double prix;
    
public:
    // Constructeur par défaut
    Vol() : numeroVol(0), aeroportDepart(""), aeroportArrivee(""), dateDepart({0, 0, 0}), dateArrivee({0, 0, 0}), placesDisponibles(0), prix(0.0) {}

    // Constructeur paramétré
    Vol(int numeroVol, string aeroportDepart, string aeroportArrivee, Date dateDepart, Date dateArrivee, int placesDisponibles, double prix)
    {
        this->numeroVol = numeroVol;
        this->aeroportDepart = aeroportDepart;
        this->aeroportArrivee = aeroportArrivee;
        this->dateDepart = dateDepart;
        this->dateArrivee = dateArrivee;
        this->placesDisponibles = placesDisponibles;
        this->prix = prix;
    }

    // Getters and setters
    int getNumeroVol() { return numeroVol; }
    int getPlacesDisponibles() { return placesDisponibles; }
    Date getDateDepart() { return dateDepart; }
    Date getDateArrivee() { return dateArrivee; }
    double getPrix() { return prix; }
    void setPrix(double prix) { this->prix = prix; }


    // Fonction ajouter
    void ajouter()
    {
        cout << "Entrez le numero de vol: ";
        cin >> numeroVol;
        cout << "Entrez l'aeroport de depart: ";
        cin >> aeroportDepart;
        cout << "Entrez l'aeroport d'arrivee: ";
        cin >> aeroportArrivee;
        cout << "Entrez la date de depart (jj mm aaaa): ";
        cin >> dateDepart.day >> dateDepart.month >> dateDepart.year;
        cout << "Entrez la date d'arrivee (jj mm aaaa): ";
        cin >> dateArrivee.day >> dateArrivee.month >> dateArrivee.year;
        cout << "Entrez le nombre de places disponibles: ";
        cin >> placesDisponibles;
        cout << "Entrez le prix: ";
        cin >> prix;
    }

    // Fonction modifier
    void modifier()
    {
        cout << "Entrez le nouveau aeroport de depart: ";
        cin >> aeroportDepart;
        cout << "Entrez le nouveau aeroport d'arrivee: ";
        cin >> aeroportArrivee;
        cout << "Entrez la nouvelle date de depart (jj mm aaaa): ";
        cin >> dateDepart.day >> dateDepart.month >> dateDepart.year;
        cout << "Entrez la nouvelle date d'arrivee (jj mm aaaa): ";
        cin >> dateArrivee.day >> dateArrivee.month >> dateArrivee.year;
        cout << "Entrez le nouveau nombre de places disponibles: ";
        cin >> placesDisponibles;
        cout << "Entrez le nouveau prix: ";
        cin >> prix;
    }

    void afficher()
    {
        cout << "Numero de vol: " << numeroVol << endl;
        cout << "Aeroport de depart: " << aeroportDepart << endl;
        cout << "Aeroport d'arrivee: " << aeroportArrivee << endl;
        cout << "Date de depart: " << dateDepart.day << "/" << dateDepart.month << "/" << dateDepart.year << endl;
        cout << "Date d'arrivee: " << dateArrivee.day << "/" << dateArrivee.month << "/" << dateArrivee.year << endl;
        cout << "Places disponibles: " << placesDisponibles << endl;
        cout << "Prix: " << prix << endl;
    }

    bool isDans12Mois()
    {
        // La date actuelle
        Date currentDate;

        time_t now = time(0);
        tm* localTime = localtime(&now);

        currentDate.day = localTime->tm_mday;
        currentDate.month = localTime->tm_mon + 1;
        currentDate.year = localTime->tm_year + 1900;

        // Vérifier si la date de départ est dans 12 mois
        if (dateDepart.year > currentDate.year)
        {
            return true;
        }
        else if (dateDepart.year == currentDate.year)
        {
            if (dateDepart.month > currentDate.month)
            {
                return true;
            }
            else if (dateDepart.month == currentDate.month)
            {
                if (dateDepart.day >= currentDate.day)
                {
                    return true;
                }
            }
        }

        return false;
    }

    // Fonction augmenterPrixVingtPourcent
    void augmenterPrixVingtPourcent()
    {
        // Si le vol est dans 12 mois
        if (isDans12Mois())
        {
            // Augmenter le prix de 20%
            prix = prix * 1.2;
        }
    }

    // Destructeur virtuel
    virtual ~Vol() {}
};

// Définition de la classe VolEconomique
class VolEconomique : public Vol
{
    // Constructeur paramétré
    VolEconomique(int numeroVol, string aeroportDepart, string aeroportArrivee, Date dateDepart, Date dateArrivee, int placesDisponibles, double prix) : Vol(numeroVol, aeroportDepart, aeroportArrivee, dateDepart, dateArrivee, placesDisponibles, prix) {}
};

// Définition de la classe VolBusiness
class VolBusiness : public Vol
{
private:
    bool confort;

public:
    // Constructeur paramétré
    VolBusiness(int numeroVol, string aeroportDepart, string aeroportArrivee, Date dateDepart, Date dateArrivee, int placesDisponibles, double prix, bool confort) : Vol(numeroVol, aeroportDepart, aeroportArrivee, dateDepart, dateArrivee, placesDisponibles, prix)
    {
        this->confort = confort;
    }
};


// Définition de la classe Passager
class Passager
{
private:
    static int nextId;
    int idPassager;
    string nom;
    string telephone;
    string passeport;

public:
    // Constructeur par défaut
    Passager() : idPassager(0), nom(""), telephone(""), passeport("") {}

    // Constructeurs parametré
    Passager(string nom, string telephone, string passeport) {
        this->idPassager = nextId++;
        this->nom = nom;
        this->telephone = telephone;
        this->passeport = passeport;
    }

    // Getters and setters
    int getIdPassager() { return idPassager; }

    string getNom() { return nom; }

    string getTelephone() { return telephone; }

    string getPasseport() { return passeport; }

    void setNom(string nom) { this->nom = nom; }

    void setTelephone(string telephone) { this->telephone = telephone; }

    void setPasseport(string passeport) { this->passeport = passeport; }

    void facturePaiement(map<int, Reservation> reservations, deque<Vol> vols);

    void afficher()
    {
        cout << "ID Passager: " << idPassager << endl;
        cout << "Nom: " << nom << endl;
        cout << "Telephone: " << telephone << endl;
        cout << "Passeport: " << passeport << endl;
    }
};

//* Initialisation du compteur d'ID Passager
int Passager::nextId = 1;

// Définition de la classe Reservation
class Reservation
{
private:
    int idReservation;
    Date dateReservation;
    Passager *passager;
    Paiement *paiement;  


public:
    // Constructeur par défaut
    Reservation() : idReservation(0), dateReservation({0, 0, 0}), passager(nullptr), paiement(nullptr) {}
    // Constructeur paramétré
    Reservation(int id, Date date, Passager *passager, Paiement *paiement) : idReservation(id), dateReservation(date), passager(passager), paiement(paiement) {}
    // Getters
    int getIdReservation() { return idReservation; }
    Date getDateReservation() { return dateReservation; }
    Passager *getPassager() { return passager; }
    Paiement *getPaiement() { return paiement; }
    // Setters
    void setIdReservation(int id) { idReservation = id; }
    void setDateReservation(Date date) { dateReservation = date; }
    void setPassager(Passager *passager) { this->passager = passager; }
    void setPaiement(Paiement *paiement) { this->paiement = paiement; }
    // Methode pour afficher les informations de la reservation
    void afficher()
    {
        cout << "ID Reservation: " << idReservation << endl;
        cout << "Date Reservation: " << dateReservation.day << "/" << dateReservation.month << "/" << dateReservation.year << endl;
        cout << "Passager: " << passager->getNom() << endl;
    }
};

// Définition de la classe Paiement
class Paiement
{
private:
    int idPaiement;
    double montant;
    Date datePaiement;
    string methodePaiement;
    
public:
    // Constructeur par défaut
    Paiement() : idPaiement(0), montant(0.0), datePaiement({0, 0, 0}), methodePaiement("") {}

    // Constructeur paramétré
    Paiement(int idPaiement, double montant, Date datePaiement, string methodePaiement) {
        this->idPaiement = idPaiement;
        this->montant = montant;
        this->datePaiement = datePaiement;
        this->methodePaiement = methodePaiement;
    }

    //getters and setters for Paiement class
    int getIdPaiement() { return idPaiement; }
    double getMontant() { return montant; }
    void setMontant(double montant) { this->montant = montant;  }
    Date getDatePaiement() { return datePaiement; }
    void setDatePaiement(Date datePaiement) { this->datePaiement = datePaiement; }
    string getMethodePaiement() { return methodePaiement; }
    void setMethodePaiement(string methodePaiement) { this->methodePaiement = methodePaiement; }

    // Methode pour afficher les informations du paiement
    void afficher()
    {
        cout << "ID Paiement: " << idPaiement << endl;
        cout << "Montant: " << montant << endl;
        cout << "Date Paiement: " << datePaiement.day << "/" << datePaiement.month << "/" << datePaiement.year << endl;
        cout << "Methode Paiement: " << methodePaiement << endl;
    }

    // Methode pour appliquer une réduction de 15% si le paiement est en espèces
    void appliquerReduction15() {
        if (methodePaiement == "Cash")
        {
            montant *= 0.85; // Réduction de 15%
        }
    }
};



// Programme Principal
//-------------------------------------------------------------------------------------------------------------------------------

//todo: Fonction pour afficher le menu principal
void afficherMenu()
{
    cout << "\033[31;1m+++++++ Menu Principal : +++++++\033[0m" << endl;
    cout << "\033[32m1. Gerer les passagers\033[0m" << endl;
    cout << "\033[33m2. Gerer les vols\033[0m" << endl;
    cout << "\033[34m3. Gerer les reservations\033[0m" << endl;
    cout << "\033[90;1m4. Quitter\033[0m" << endl;
}

// Fonction pour modifier un passager
// Cette fonction prend en parametre une liste de passagers et modifie les informations d'un passager
// Pour eviter de modifier un passager par erreur, on affiche tous les passagers avec leurs ID
// L'utilisateur doit entrer l'ID du passager a modifier
void modifierPassager(list<Passager> &passagers) {
    // Logique pour modifier un passager
    // Afficher tous les passagers avec leurs ID
    for (Passager &passager : passagers)
    {
        cout << "ID: " << passager.getIdPassager() << ", Nom: " << passager.getNom() << endl;
    }
    // Recherche du passager par son ID
    int idPassager;
    cout << "Entrez l'ID du passager a modifier: ";
    cin >> idPassager;
    // si le passager existe
    auto it = find_if(passagers.begin(), passagers.end(), [idPassager](Passager &passager)
                      { return passager.getIdPassager() == idPassager; });
    if (it != passagers.end())
    {
        string nom, telephone, passeport;
        cout << "Entrez le nouveau nom: ";
        cin >> nom;
        cout << "Entrez le nouveau telephone: ";
        cin >> telephone;
        cout << "Entrez le nouveau passeport: ";
        cin >> passeport;
        // Modifier les informations du passager
        it->setNom(nom);
        it->setTelephone(telephone);
        it->setPasseport(passeport);
        // Message de confirmation
        cout << "\033[92;1mPassager modifie avec succes.\033[0m" << endl;
    }
    else
    {
        cout << "Passager non trouve." << endl;
    }
    // Attendre l'entrée de l'utilisateur
    cout << "Appuyez sur une touche pour continuer...";
    system("pause > nul");
}

// Fonction pour supprimer un passager
void suprimmerPassager(list<Passager> &passagers) {
    // Logique pour supprimer un passager
    // Afficher tous les passagers avec leurs ID
    for (Passager &passager : passagers)
    {
        cout << "ID: " << passager.getIdPassager() << ", Nom: " << passager.getNom() << endl;
    }
    // Recherche du passager par son ID
    int idPassager;
    cout << "Entrez l'ID du passager a supprimer: ";
    cin >> idPassager;
    // si le passager existe
    auto it = find_if(passagers.begin(), passagers.end(), [idPassager](Passager &passager)
                      { return passager.getIdPassager() == idPassager; });
    if (it != passagers.end())
    {
        passagers.erase(it);
        // Message de confirmation
        cout << "\033[92;1mPassager supprime avec succes.\033[0m" << endl;
    }
    else
    {
        cout << "Passager non trouve." << endl;
    }
    // Attendre l'entrée de l'utilisateur
    cout << "Appuyez sur une touche pour continuer...";
    system("pause > nul");
}

// Fonction pour calculer le montant dépensé par un passager
void montantDepense(Passager &passager, map<int, Reservation> &reservations, deque<Vol> &vols) {
    double montantTotal = 0.0;
    for (auto& pair : reservations) {
        if (pair.second.getPassager()->getIdPassager() == passager.getIdPassager()) {
            // Trouver le vol correspondant à la réservation
            int numeroVol = pair.second.getIdReservation();
            auto volIt = find_if(vols.begin(), vols.end(), [numeroVol](Vol &vol) {
                return vol.getNumeroVol() == numeroVol;
            });

            if (volIt != vols.end()) {
                // Ajouter le prix du vol au montant total
                montantTotal += volIt->getPrix();
            }
        }
    }
    cout << "Montant dépensé par " << passager.getNom() << " : " << montantTotal << endl;
}

// Methode pour reduire le prix de 20%
void appliquerReduction(Passager& passager, map<int, Reservation> &reservations, deque<Vol> &vols)
{
    int reservationCount = 0;
    for (auto &reservation : reservations)
    {
        if (reservation.second.getPassager()->getIdPassager() == passager.getIdPassager())
        {
            reservationCount++;
        }
    }

    if (reservationCount > 5)
    {

        double total = 0.0;
        for (auto &reservation : reservations)
        {
            if (reservation.second.getPassager()->getIdPassager() == passager.getIdPassager())
            {
                int numeroVol = reservation.second.getIdReservation();
                auto volIt = find_if(vols.begin(), vols.end(), [numeroVol](Vol &vol)
                                    { return vol.getNumeroVol() == numeroVol;});

                if (volIt != vols.end())
                {
                    total += volIt->getPrix();
                }
            }
        }

        double reduction = total * 0.2;
        cout << "Passager " << passager.getNom() << " eu une reduction de " << reduction << " pour " << reservationCount << " reservations." << endl;

        // Appliquer la reduction de 20%
        for (auto &reservation : reservations)
        {
            if (reservation.second.getPassager()->getIdPassager() == passager.getIdPassager())
            {
                int numeroVol = reservation.second.getIdReservation();
                auto volIt = find_if(vols.begin(), vols.end(), [numeroVol](Vol &vol)
                                    { return vol.getNumeroVol() == numeroVol;});

                if (volIt != vols.end())
                {
                    double newPrice = volIt->getPrix() * (1 - reduction);
                    volIt->setPrix(newPrice);
                }
            }
        }
    }
}

// Surcharge de method facturePaiement
void Passager::facturePaiement(map<int, Reservation> reservations, deque<Vol> vols)
{
    cout << "\033[92;1m+++++++++++ Facture de paiement pour : +++++++++++\033[0m" << endl;
    cout << "\033[93;1m- Identifiant passager: \033[0;1m" << idPassager << "\033[0m" << "\033[93;1m - Numero passeport: \033[0;1m" << passeport << "\033[0m" << endl;
    cout << "\033[93;1m-Nom passager: \033[0;1m" << nom << "\033[0m" << endl;
    cout << endl;
    cout << "\033[92;1m-Reservations:" << endl;
    cout << endl;
    cout << "\033[93;1mIdentifiant reservation\t\tDate\t\tNumero de vol\t\tPrix\033[0m" << endl;

    double totalPaiement = 0.0;

    for (auto &pair : reservations)
    {
        if (pair.second.getPassager()->getIdPassager() == idPassager)
        {
            int numeroVol = pair.second.getIdReservation();
            auto volIt = find_if(vols.begin(), vols.end(), [numeroVol](Vol &vol)
                                    { return vol.getNumeroVol() == numeroVol; });

            if (volIt != vols.end())
            {
                cout << pair.second.getIdReservation() << "\t \t";
                cout << "\t \t" << pair.second.getDateReservation().day << "/" << pair.second.getDateReservation().month << "/" << pair.second.getDateReservation().year << "\t";
                cout << "\t" << volIt->getNumeroVol() << "\t";
                cout << "\t" << volIt->getPrix() << endl;

                totalPaiement += volIt->getPrix();
            }
        }
    }

    cout << "\n\033[94;1mTotal à payer: \033[0;1m" << totalPaiement <<  "\033[0m" << endl;
}

//fonction pour Appliquer une réduction de 15% aux paiements effectue par cash
void appliquerReduction15Cash(map<int, Reservation> &reservations)
{
    for (auto it = reservations.begin(); it != reservations.end(); ++it)
    {
        Reservation &reservation = it->second;
        Paiement *paiement = reservation.getPaiement();

        if (paiement && paiement->getMethodePaiement() == "Cash")
        {
            paiement->appliquerReduction15();
        
        }
    }
}

//todo: Fonction pour afficher le menu de gestion des passagers
void afficherMenuPassagers(list<Passager> &passagers, map<int, Reservation> &reservations, deque<Vol> &vols)
{
    int choix;
    
    do
    {
        system("cls"); // Effacer l'écran

        cout << "\033[31;1m+++++++ Menu de gestion des passagers : +++++++\033[0m" << endl;
        cout << "\033[32m1. Ajouter un/des passager(s)\033[0m" << endl;
        cout << "\033[33m2. Modifier un passager\033[0m" << endl;
        cout << "\033[34m3. Supprimer un passager\033[0m" << endl;
        cout << "\033[95m4. Afficher liste des passagers\033[0m" << endl;
        cout << "\033[33m5. Afficher le montant depense de chaque reservation des passagers\033[0m" << endl;
        cout << "\033[92m6. Trier liste des vols par nom passager\033[0m" << endl;
        cout << "\033[35m7. Effectuer reduction 20 pourcent\033[0m" << endl;
        cout << "\033[36m8. Afficher facture paiement des passagers\033[0m" << endl;
        cout << "\033[90;1m9. Retour au menu principal\033[0m" << endl;

        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix)
        {
        case 1:
            // Logique pour ajouter un passager
            system("cls");  // Effacer l'écran
            int nombrePassagers;
            cout << "\033[34mCombien de passagers souhaitez-vous ajouter ? \033[0m";
            cin >> nombrePassagers;

            for (int i = 0; i < nombrePassagers; ++i) {
                string nom, telephone, passeport;
                cout << "Passager " << i + 1 << ":" << endl;
                cout << "Nom : ";
                cin >> nom;
                cout << "Telephone : ";
                cin >> telephone;
                cout << "Passeport : ";
                cin >> passeport;
                // Ajouter le passager à la liste
                passagers.push_back(Passager(nom, telephone, passeport));
            }
            // Message de confirmation
            cout << "\033[92;1mPassager(s) ajoute(s) avec succes.\033[0m" << endl;
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        case 2:
            // Logique pour modifier un passager
            system("cls");  // Effacer l'écran
            modifierPassager(passagers);
            break;
        case 3:
            // Logique pour supprimer un passager
            system("cls");  // Effacer l'écran
            suprimmerPassager(passagers);
            break;
        case 4:
            // Logique pour afficher les passagers
            system("cls");  // Effacer l'écran
            cout << "\033[93;1m++++++++ Liste des passagers: ++++++++\033[0m \n" << endl;
            for(Passager &passager : passagers)
            {
                passager.afficher();
                cout << endl;
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        case 5:
            // Logique pour afficher le montant depense de chaque reservation des passagers
            system("cls");  // Effacer l'écran
            // Methode pour claculer le montant depense de chaque reservation
            for (Passager &passager : passagers)
            {
                montantDepense(passager, reservations, vols);
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        case 6:
            // Logique pour trier la liste des vols par nom passager
            system("cls");  // Effacer l'écran
            passagers.sort([](Passager &a, Passager &b) {
                return a.getNom() < b.getNom();
            });
            // Message de confirmation
            cout << "\033[91mListe des passagers triee par nom.\033[0m \n" << endl;
            // Affichage de la liste des passagers
            for (Passager &passager : passagers)
            {
                passager.afficher();
                cout << endl;
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        case 7:
            // Logique pour effectuer une réduction de 20%
            system("cls");  // Effacer l'écran
            // Réduction de 20%
            for (Passager &passager : passagers)
            {
                // Réduction de 20%
                appliquerReduction(passager,reservations, vols);
            }
            // Message de confirmation
            cout << "Reduction de 20% effectuee." << endl;
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        case 8:
            // Logique pour afficher la facture de paiement des passagers
            system("cls");  // Effacer l'écran
            // Afficher la facture de paiement des passagers
            for (Passager &passager : passagers)
            {
                // Afficher la facture de paiement
                passager.facturePaiement(reservations, vols);
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        case 9:
            system("cls");  // Effacer l'écran
            afficherMenu(); // Retour au menu principal
            break;          // Retour au menu principal
        default:
            cout << "Choix invalide. Veuillez reessayer." << endl;
        }
    } while (choix != 9);
}

//todo: Fonction pour afficher le menu de gestion des vols
void afficherMenuVols(deque<Vol> &vols)
{
    int choix;

    do
    {
        system("cls"); // Effacer l'écran

        cout << "\033[31;1m+++++++ Menu de gestion des vols : +++++++\033[0m" << endl;
        cout << "\033[34m1. Ajouter un vol\033[0m" << endl;
        cout << "\033[35m2. Modifier un vol\033[0m" << endl;
        cout << "\033[33m3. Supprimer un vol\033[0m" << endl;
        cout << "\033[32m4. Afficher les vols dans 12 mois\033[0m" << endl;
        cout << "\033[36m5. Augmenter le prix de 20 pourcent pour les vols dans 12 mois et places restantes est < 10\033[0m" << endl;
        cout << "\033[91m6. Afficher liste des vols\033[0m" << endl;
        cout << "\033[90;1m7. Retour au menu principal\033[0m" << endl;

        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix)
        {
        case 1:
        {
            system("cls");  // Effacer l'écran
            Vol vol;
            vol.ajouter();
            vols.push_back(vol);
            // Message de confirmation
            cout << "\033[92;1mVol ajoute avec succes.\033[0m" << endl;
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        }
        case 2:
        {
            system("cls");  // Effacer l'écran
            int numeroVol;
            cout << "Entrez le numero de vol a modifier: ";
            cin >> numeroVol;

            auto it = find_if(vols.begin(), vols.end(), [numeroVol](Vol &vol)
                                   { return vol.getNumeroVol() == numeroVol; });

            if (it != vols.end())
            {
                it->modifier();
                // Message de confirmation
                cout << "\033[92;1mVol modifie avec succes.\033[0m" << endl;
            }
            else
            {
                cout << "Vol non trouve." << endl;
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        }
        case 3:
        {
            int numeroVol;
            cout << "Entrez le numero de vol a supprimer: ";
            cin >> numeroVol;
            // Recherche du vol par son numéro
            // Utilisation de la fonction lambda pour comparer le numéro de vol
            // La fonction lambda retourne vrai si le numéro de vol est égal au numéro de vol recherché
            // auto = deque<Vol>::iterator
            auto it = find_if(vols.begin(), vols.end(), [numeroVol](Vol &vol)
                                   { return vol.getNumeroVol() == numeroVol; });

            if (it != vols.end())
            {
                vols.erase(it);
                // Message de confirmation
                cout << "\033[92;1mVol supprime avec succes.\033[0m" << endl;
            }
            else
            {
                cout << "Vol non trouve." << endl;
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        }
        case 4:
        {
            cout << "Vols avec date de depart dans 12 mois:" << endl;
            for (Vol &vol : vols)
            {
                if (vol.isDans12Mois())
                {
                    cout << "Numero de vol: " << vol.getNumeroVol() << endl;
                    cout << "Places restantes: " << vol.getPlacesDisponibles() << endl;
                }
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        }
        case 5:
            system("cls");  // Effacer l'écran
            // Augmenter le prix de 20% pour les vols dans 12 mois et places restantes est < 10
            for (Vol &vol : vols)
            {
                if (vol.isDans12Mois() && vol.getPlacesDisponibles() < 10)
                {
                    vol.augmenterPrixVingtPourcent();
                }
            }
            // Message de confirmation
            cout << "Les prix des vols dans 12 mois ont ete augmentes de 20%" << endl;
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;  // Retour au menu principal
        case 6:
            system("cls");  // Effacer l'écran
            // Afficher la liste des vols
            if (vols.empty())
            {
                cout << "Aucun vol trouve." << endl;
            }
            else
            {
                cout << "\033[31;1m+++++++ Liste des vols: +++++++\033[0m" << endl;
                for (Vol &vol : vols)
                {
                    vol.afficher();
                    cout << endl;
                }
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;  // Retour au menu principal
        case 7:
            system("cls");  // Effacer l'écran
            afficherMenu(); // Retour au menu principal
            break;          // Retour au menu principal
        default:
            cout << "Choix invalide. Veuillez reessayer." << endl;
        }
    } while (choix != 7);
}

//todo: Fonction pour afficher le menu de gestion des réservations
void afficherMenuReservations(map<int,Reservation> &reservations, deque<Vol> &vols, list<Passager> &passagers)
{
    int choix;

    do
    {
        system("cls"); // Effacer l'écran

        cout << "\033[91;1m+++++++ Menu de gestion des reservations : +++++++\033[0m" << endl;
        cout << "\033[36m1. Ajouter une reservation\033[0m" << endl;
        cout << "\033[35m2. Modifier une reservation\033[0m" << endl;
        cout << "\033[33m3. Supprimer une reservation\033[0m" << endl;
        cout << "\033[96m4. Afficher les reservations\033[0m" << endl;
        cout << "\033[92m5. Appliquer la reduction de 15% pour les paiements en cash\033[0m" << endl;
        cout << "\033[90;1m6. Retour au menu principal\033[0m" << endl;

        cout << "Entrez votre choix : ";
        cin >> choix;

        if (choix == 1)
        {
            // Logique pour ajouter une réservation
            system("cls");  // Effacer l'écran
            int idReservation;
            int numeroVol;
            int idPassager;
            Date dateReservation;

            cout << "Entrez l'identifiant de la reservation : ";
            cin >> idReservation;

            cout << "Entrez le numero de vol : ";
            cin >> numeroVol;

            cout << "Entrez l'identifiant du passager : ";
            cin >> idPassager;

            // Recherche du vol par son numéro
            auto volIt = find_if(vols.begin(), vols.end(), [numeroVol](Vol &vol)
                                { return vol.getNumeroVol() == numeroVol; });

            // Recherche du passager par son ID
            auto passagerIt = find_if(passagers.begin(), passagers.end(), [idPassager](Passager &passager)
                                    { return passager.getIdPassager() == idPassager; });

            // Si le vol et le passager existent
            if (volIt != vols.end() && passagerIt != passagers.end())
            {
                dateReservation.day = volIt->getDateDepart().day;
                dateReservation.month = volIt->getDateDepart().month;
                dateReservation.year = volIt->getDateDepart().year;

                Reservation newReservation;
                newReservation.setIdReservation(idReservation);
                newReservation.setDateReservation(dateReservation);
                newReservation.setPassager(&(*passagerIt)); // Adresse du passager dans la liste des passagers

                // Ajouter la réservation dans le map
                reservations[idReservation] = newReservation;

                // Message de confirmation
                cout << "\033[92;1mReservation ajoutee avec succes.\033[0m" << endl;
            }
            else
            {
                cout << "\033[91mVol ou passager non trouve.\033[0m" << endl;
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
        }
        else if (choix == 2)
        {
            // Logique pour modifier une réservation
            system("cls");  // Effacer l'écran
            // Recherche de la réservation par son ID
            int idReservation;
            cout << "Entrez l'identifiant de la reservation a modifier: ";
            cin >> idReservation;
            // si la reservation existe
            auto it = reservations.find(idReservation);
            if (it != reservations.end())
            {
                // Modifier les informations de la réservation
                it->second.afficher();
                int nouveauNumeroVol;
                int nouvelIdPassager;
                cout << "Entrez le nouveau numero de vol: ";
                cin >> nouveauNumeroVol;
                cout << "Entrez le nouvel identifiant du passager: ";
                cin >> nouvelIdPassager;
                
                // Recherche du nouveau vol par son numéro
                auto nouveauVolIt = find_if(vols.begin(), vols.end(), [nouveauNumeroVol](Vol &vol)
                                            { return vol.getNumeroVol() == nouveauNumeroVol; });
                
                // Recherche du nouveau passager par son ID
                auto nouveauPassagerIt = find_if(passagers.begin(), passagers.end(), [nouvelIdPassager](Passager &passager)
                                                { return passager.getIdPassager() == nouvelIdPassager; });
                
                // Si le nouveau vol et le nouveau passager existent
                if (nouveauVolIt != vols.end() && nouveauPassagerIt != passagers.end())
                {
                    Date nouvelleDate;
                    cout << "Entrez la nouvelle date de reservation (jj mm aaaa): ";
                    cin >> nouvelleDate.day >> nouvelleDate.month >> nouvelleDate.year;
                    
                    it->second.setDateReservation(nouvelleDate);
                    it->second.setPassager(&(*nouveauPassagerIt));
                    
                    // Message de confirmation
                    cout << "\033[92;1mReservation modifiee avec succes.\033[0m" << endl;
                }
                else
                {
                    cout << "Nouveau vol ou nouveau passager non trouve." << endl;
                }
            }
            else
            {
                cout << "Reservation non trouvee." << endl;
            }
            
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
            break;
        }
        else if (choix == 3)
        {
            // Logique pour supprimer une réservation
            system("cls");  // Effacer l'écran
            // Recherche du Reservation par son ID
            int idReservation;
            cout << "\033[34mEntrez l'ID du Reservation a supprimer: \033[0m";
            cin >> idReservation;
            // Si le Reservation existe
            auto it = reservations.find(idReservation);
            if (it != reservations.end())
            {
                reservations.erase(it);
                // Message de confirmation
                cout << "\033[92;1mReservation supprimee avec succes.\033[0m" << endl;
            }
            else
            {
                cout << "\033[91mReservation non trouvee.\033[0m" << endl;
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");

        }
        else if (choix == 4)
        {
            // Logique pour afficher les réservations
            system("cls");  // Effacer l'écran
            // Si la liste des réservations est vide
            if (reservations.empty())
            {
                cout << "Aucune reservation trouvee." << endl;
            }
            else
            {
                cout << "\033[93;1m++++++++ Liste des reservations: ++++++++\033[0m \n" << endl;
                for (auto &reservation : reservations)
                {
                    reservation.second.afficher();
                    cout << endl;
                }
            }
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
        }
        else if (choix == 5)
        {
            // Logique pour appliquer la réduction de 15% pour les paiements en cash
            system("cls");  // Effacer l'écran
            appliquerReduction15Cash(reservations);
            // Attendre l'entrée de l'utilisateur
            cout << "Appuyez sur une touche pour continuer...";
            system("pause > nul");
        }
        else if (choix == 6)
        {
            system("cls");  // Effacer l'écran
            afficherMenu(); // Retour au menu principal
        }
        else
        {
            cout << "Choix invalide. Veuillez reessayer." << endl;
        }
    } while (choix != 6);
}


//! Fonction Main
int main()
{
    deque<Vol> vols;
    list<Passager> passagers;
    map<int, Reservation> reservations;
    set<Paiement> paiements;

    //* Menu de navigation
    int choix;

    do {
        system("cls"); // Effacer l'écran
        afficherMenu();
        cout << "Entrez votre choix : ";
        cin >> choix;

        switch (choix) {
            case 1:
                // Logique pour ajouter un passager
                afficherMenuPassagers(passagers, reservations, vols);
                break;
            case 2:
                // Logique pour réserver un vol
                afficherMenuVols(vols);
                break;
            case 3:
                // Logique pour afficher les réservations
                afficherMenuReservations(reservations, vols, passagers);
                break;
            case 4:
                system("cls");  // Effacer l'écran
                // Quitter le programme
                cout << "Au revoir !" << endl;
                break;
            default:
                cout << "Choix invalide. Veuillez reessayer." << endl;
        }
    } while (choix != 4);

    return 0;
}
