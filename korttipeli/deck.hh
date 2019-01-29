#ifndef DECK_HH
#define DECK_HH

#include <vector>
#include <QFrame>
#include "card.hh"

class Deck : public QFrame
{
    Q_OBJECT

public:
    Deck(QWidget *parent = 0);

    // Korttipakasta voi nostaa päällimmäisen kortin.
    Card* pickCard();

    /**
     * @brief shuffleDeck, sekoittaa pakan tietokoneen kellosta otetun siemenen
     * arvolla.
     */
    void shuffleDeck();
    /**
     * @brief createDeck, rakentaa uuden pakan.
     *
     * Käytetään peliä resetoidessa resetDeck:issä
     */
    void createDeck();
    /**
     * @brief resetDeck resetoi pakan, eli postaa siinä olevat kortit, kutsuu
     * creatDeck:iä lisätäkseen uudet ja sekoittaa uuden pakan.
     */
    void resetDeck();

    // TODO: Lisää tähän uusia toimintoja, joita korttipakalle voi suorittaa.

signals:
    // Signaali, jonka pakka lähettää, kun kortti nostetaan.
    void cardPicked(Card* card);
    // Signaali, joka lähetetään, kun tyhjää pakkaa painetaan. Tällöin opendeckin
    // kortit siirretään takaisin pakkaan.
    void emptyDeckClicked();

public slots:
    /**
     * @brief turnAndSetCardsVisable korvaa pakan uudella, kääntää uudet kortit
     *  ja asettaa ne näkyväksi.
     * @param deck, vektori jossa osoittimia kortteihin. Pakka, jossa kortit on
     * kuvapuoli ylöspäin.
     *
     * Käytetään pakan kääntämisessä kun tyhjää pakkaa on klikattu.
     */
    void replaceDeck(std::vector<Card*> deck);

protected:
    // Itse toteutettu Qt:n widgetin klikkaamiseen liittyvä metodi.
    void mousePressEvent(QMouseEvent *event);

private:
    // Korttipakan sisältämät kortit.
    std::vector<Card*> cards_;
};

#endif // DECK_HH
