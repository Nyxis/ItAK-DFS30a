#include "Encounter.hpp"

Encounter::Encounter(const std::string& titre, const std::string& description,
                     int seuilFumble, int seuilEchec, int seuilReussite, int seuilCritique)
    : titre(titre), description(description),
      seuilFumble(seuilFumble), seuilEchec(seuilEchec),
      seuilReussite(seuilReussite), seuilCritique(seuilCritique) {}

std::string Encounter::getTitre() const {
    return titre;
}

std::string Encounter::getDescription() const {
    return description;
}

std::string Encounter::evaluer(int pourcentage) const {
    if (pourcentage <= seuilFumble)
        return "Fumble";
    else if (pourcentage <= seuilEchec)
        return "Échec";
    else if (pourcentage <= seuilReussite)
        return "Réussite";
    else
        return "Réussite critique";
}
