#ifndef CARD_HH
#define CARD_HH

#include <QLabel>
#include <QFrame>

unsigned const DEFAULT_STACK_OFFSET = 35;

enum CardSuit {SPADE, CLUB, DIAMOND, HEART, SUIT_COUNT};

class Card : public QFrame
{
    Q_OBJECT

public:
    Card(CardSuit suit, unsigned value, QWidget *parent = 0);

    // Kortin sisäisen tilan tarkastelemiseen ja muokkaamiseen.
    bool isOpen();
    void allowOpen();
    /**
     * Estetään kortin kääntäminen asettamalla canOpen_ falseksi.
     * @brief disableOpen
     */
    void disableOpen();

    // Kortin päällä olevien korttien käsittelemiseen.
    void stackCard(Card* card, int offset = DEFAULT_STACK_OFFSET);
    void removeStackedCards();

    // Palauttaa kortin tiedot (arvo, maa, onko auki) merkkijonona. Tarvitaan
    // kortin raahaamisessa.
    std::string getCardData();
    /**
    * @brief getCardValue Palauttaa vain kortin arvon.
    * @return int, kortin arvon value_ attribuutissa.
    */
    int getCardValue();

    // Kun korttia raahataan, raahaus-event tarvitsee kuvan, jota näytetään.
    // Sen saa haettua tällä metodilla.
    QLabel* getCurrentSideLabel();

signals:
    // Kun kortin päälle (tai sen päällä olevien korttien päällä olevien korttien
    // päälle) lisätään kortti, tarvii piirrettävän widgetin kokoa kasvattaa.
    void resized();

public slots:
    // Lisää toimenpiteitä, joita kortille voidaan suorittaa.
    void turn();
    void expand();

protected:
    // Itse toteutettu Qt:n widgetin klikkaamiseen liittyvä metodi.
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    // Apumetodeita muiden metodien käyttöön.
    void setupLayout();
    void setSuitPixmap();
    void setupBack();
    void setupFront();

    // Korttiwidgetin sisäinen tila.
    CardSuit suit_;
    unsigned value_;
    bool open_;
    bool canOpen_;

    // Kuvat joita tarvitaan, kun korttia piirretään setupBack- ja setupFront-metodeissa.
    QPixmap suitPixmap_;
    QPixmap backPixmap_;

    // Osoitin kortin päällä mahdollisesti olevaan korttiin.
    Card* stackedCard_;
};

#endif // CARD_HH
