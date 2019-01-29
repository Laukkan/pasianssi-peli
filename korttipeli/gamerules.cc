#include "gamerules.hh"
#include "card.hh"


// Funktio saa parametrinaan alla olevan kortin ja päälle tulevan kortin
// tiedot merkkijonomuodossa.
bool GameRules::checkIfHeartAndOneHigher(std::string bottom, std::string top)
{

    return suitAndValueChecker(bottom, top, HEART);
}

bool GameRules::checkIfDiamondAndOneHigher(std::string bottom, std::string top)
{

    return suitAndValueChecker(bottom, top, DIAMOND);
}

bool GameRules::checkIfClubAndOneHigher(std::string bottom, std::string top)
{

    return suitAndValueChecker(bottom, top, CLUB);
}

bool GameRules::checkIfSpadeAndOneHigher(std::string bottom, std::string top) {

    return suitAndValueChecker(bottom, top, SPADE);
}

bool GameRules::checkIfLegalPlay(std::string bottom, std::string top){

    // Päälimmäisen kortin tietojen käsittely.
    int valueTop = stoi(top.substr(0,top.find_first_of(",")));
    int suitTop = stoi(top.substr(top.find_first_of(",")+1,1));
    // Jos paikka on tyhjä, vain kuningas voidaan lisätä.
    if(bottom == ""){
        if(valueTop == 13){
            return true;
        } else {
            return false;
        }
    } else {
        // Alimmaisen kortin tiedot voidaan käsitellä vasta nyt.
        int suitBottom = stoi(bottom.substr(bottom.find_first_of(",")+1,1));
        int valueBottom = stoi(bottom.substr(0,bottom.find_first_of(",")));
        // Vain vastakkaisen väristä maata voi lisätä.
        if((suitTop == SPADE or suitTop == CLUB) and
                (suitBottom != HEART and suitBottom != DIAMOND)){
            return false;
        } else if((suitTop == HEART or suitTop == DIAMOND) and
                  (suitBottom != SPADE and suitBottom != CLUB)) {
            return false;
        // Vain kortteja jotka ovat yhden pienempiä voi lisätä.
        } else if(valueBottom != valueTop+1){
            return false;
        } else {
            return true;
        }

    }



}

bool GameRules::suitAndValueChecker(std::string bottom, std::string top, int suitToCheckFor)
{
    // Päälimmäisen kortin tietojen käsittely.
    int valueTop = stoi(top.substr(0,top.find_first_of(",")));
    int suitTop = stoi(top.substr(top.find_first_of(",")+1,1));
    // Jos korttipaikka tyhjä, vain ykkönen voidaan lisätä.
    if(bottom == ""){
        if(valueTop != 1 or suitTop != suitToCheckFor){
            return false;
        } else {
            return true;
        }
    } else {
        // Alimmaisen kortin tideot voidaan käsitellä vasta nyt, maalla ei ole
        // väliä sillä se on tarkistettu korttia alunperin lisättäessä.
        int valueBottom = stoi(bottom.substr(0,bottom.find_first_of(",")));
        // Kortin tulee olla oikeaa maata...
        if(suitTop != suitToCheckFor){
            return false;
        // ja yhden suurempi kuin edellinen kortti.
        } else if(valueTop != valueBottom + 1){
            return false;
        } else {
            return true;
        }
    }
}
