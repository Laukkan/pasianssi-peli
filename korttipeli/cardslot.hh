#ifndef CARDSLOT_HH
#define CARDSLOT_HH

#include "gamerules.hh"
#include "card.hh"

#include <list>
#include <string>
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

using CheckFunction = bool(*)(std::string, std::string);

class CardSlot: public QFrame
{
    Q_OBJECT
public:
    // Rakentaja ja metodi, jolla slotiin voidaan lisätä kortti.
    /**
     * @brief CardSlot
     * @param function
     * @param parent
     * @param offset, int, kuinka paljon kortteja siiretään alaspäin jos ne
     * tulisivat toisen kortin päälle. Yläpalkin kortti paikoilla 0.
     * @param suit, int, kortti paikan maata card.hh:n CardSuitin mukaan
     * vastaava int. Jos oletus arvo eli SUIT_COUNT, ei maata.
     */
    CardSlot(CheckFunction function, QWidget* parent = 0, int offset = DEFAULT_STACK_OFFSET, int suit = SUIT_COUNT);
    void addCard(Card* card);

    // Itse toteutetut Qt:n widgetin raahaukseen liittyvät metodit.
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief checkIfTopKing tarkistaa, onko topCard_:in arvo 13.
     * @return, bool, true jost arvo 13, false jos ei.
     *
     * Käytetään voiton tarkastamiseen.
     */
    bool checkIfTopKing();
    /**
     * @brief emptyOut poistaa kaikki kortit kortti paikasta
     *
     * Käytetään pelin resetoimiseen
     */
    void emptyOut();

signals:
    // Yläpalkin korttipaikat lähettävät signaalin kun niihin raahataan
    // kuningas, jolloin mainwindow tarkastaa onko peli voitettu.
    void kingAdded();

private:
    // Apumetodeita dropEventin käyttöön.
    void parseNewCards(std::list<Card*>& newCards, QStringList& newCardsData);
    void setupNewCards(std::list<Card*>& newCards);

    // Sama funktio kun card:illa, valitsee minkä maan kuva näytetään.
    void setSuitPixmap();
    /**
     * @brief drawSuitPixmap, piirtää oikean maan kuvion cardslottiin.
     *
     * Käytetään yläpalkin korttipaikoissa.
     */
    void drawSuitPixmap();

    // Päällimmäisenä oleva kortti on talletettu attribuutiksi, koska se vaikuttaa
    // siihen, mitä tähän slotiin saa raahata. Muut kortit ovat vain tämän widgetin
    // lapsia, ja niihin päästään tarvittaessa käsiksi Qt:n parent-mekanismin avulla.
    Card* topCard_;

    // Pelisääntöfunktio, joka määrittelee, mitä kortteja tähän widgettiin saa raahata.
    CheckFunction checkFunction_;

    // Väli, joka jätetään kun kortteja kasataan päällekkäin tähän pakkaan.
    int offset_;
    // Korttipaikan maa, jos 5 eli SUIT_COUNT ei maata.
    int suit_;
    // Jos kortilla on maa, on tämä maan kuva.
    QPixmap suitPixmap_;
};

#endif // CARDSLOT_HH
