#ifndef GAMERULES_HH
#define GAMERULES_HH
#include <string>
#include <vector>

using function = bool (*)(std::string, std::string);

namespace GameRules {

    // Tarkastusfunktiot, joilla tarkastetaan että päälle saa laittaa vain
    // tiettyä maata. Kaikille toimintaperiaate sama.
    /**
     * @brief checkIfHeartAndOneHigher tarkistaa, että parametrin top kortti
     * on herttaa ja yhden suurempi arvoltaan kuin parametrin bottom kortti.
     * @param bottom, alla olevan kortin data muodossa value,suit,open.
     * @param top, yllä olevan kortin data muodossa value,suit,open.
     * @return bool, true jos top on oikeaa maata ja oikean arvoinen, muutoin false.
     *
     * Käytetään yläpalkin checkFunction funktioina. Käyttää suitAndValueCheckeriä.
     */
    bool checkIfHeartAndOneHigher(std::string bottom, std::string top);
    bool checkIfSpadeAndOneHigher(std::string bottom, std::string top);
    bool checkIfClubAndOneHigher(std::string bottom, std::string top);
    bool checkIfDiamondAndOneHigher(std::string bottom, std::string top);

    /**
     * @brief suitAndValueChecker tarkistaa, että parametrin top kortti
     * on suitToCheckFor:parametrin maata ja yhden suurempi arvoltaan kuin
     * parametrin bottom kortti.
     * @param bottom, alla olevan kortin data muodossa value,suit,open.
     * @param top, yllä olevan kortin data muodossa value,suit,open.
     * @param suitToCheckFor, maa jota kortin pitäisi olla.
     * @return bool, true jos top on oikeaa maata ja oikean arvoinen, muutoin false.
     */
    bool suitAndValueChecker(std::string bottom, std::string top ,int suitToCheckFor);

    // Tarkistusfunktiot vektorissa, josta ne on helppo antaa yläpalkin
    // card slotteihin yksi kerrallaan mainwindowissa.
    static std::vector<function> suitCheckVector = {
        &checkIfSpadeAndOneHigher,
        &checkIfClubAndOneHigher,
        &checkIfDiamondAndOneHigher,
        &checkIfHeartAndOneHigher
    };

    /**
     * @brief checkIfLegalPlay alapalkin korttipaikkojen checkFunction functio.
     * Tarkastaa, että lisättävä kortti on vastakkaista maata ja yhden pienempi,
     * tai että lisättäv kortti on kuningas jos paikkan on tyhjä.
     * @param bottom, alla olevan kortin data muodossa value,suit,open.
     * @param top, yllä olevan kortin data muodossa value,suit,open.
     * @return bool, true jos top on oikeaa maata ja oikean arvoinen, muutoin false.
     */
    bool checkIfLegalPlay(std::string bottom, std::string top);
}



#endif // GAMERULES_HH
