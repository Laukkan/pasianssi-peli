#include "deck.hh"

#include <QDrag>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QPainter>
#include <QLabel>
#include <algorithm>
#include <ctime>

Deck::Deck(QWidget *parent) : QFrame(parent)
{
    setMinimumSize(180, 260);
    setMaximumSize(180, 260);
    setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    createDeck();
    shuffleDeck();
}

Card* Deck::pickCard()
{
    if (cards_.empty()){
        return nullptr;
    } else {
        Card* card = cards_.back();
        cards_.pop_back();
        return card;
    }
}

void Deck::shuffleDeck()
{
    // Sekoittaa pakan shuffle:metodilla käyttäen satunnaisluku generaattoria
    // joka ottaa siemenen koneen kellosta.
    std::default_random_engine deckShuffler;
    deckShuffler.seed(time(NULL));
    std::shuffle(cards_.begin(),cards_.end(), deckShuffler);
}

void Deck::createDeck()
{
    // Alkuperäisessä koodissa rakentajassa tehty pakan teko siirettynä omaam
    // metodiinsa.
    for (int suit = SPADE; suit != SUIT_COUNT; ++suit){

        for (unsigned value = 1; value <= 13; ++value){
            auto card = new Card(static_cast<CardSuit>(suit), value, this);
            int xOffset = (this->width() - card->width()) / 2;
            int yOffset = (this->height() - card->height()) / 2;
            card->move(xOffset, yOffset);
            cards_.push_back(card);
        }
    }
}

void Deck::resetDeck()
{
    cards_.clear();
    createDeck();
    shuffleDeck();

}

void Deck::replaceDeck(std::vector<Card *> deck)
{

    cards_ = deck;
    for(Card* card : cards_){
        card->setParent(this);
        // Käännetään kortit.
        card->turn();
        // Ja asetetaan ne näkyviksi.
        card->show();
    }
}

// Suoritetaan, kun pakkaa klikataan.
void Deck::mousePressEvent(QMouseEvent *event)
{
    // Ohjelma ei saa kaatua tyhjän pakan klikkaukseen.
    if (cards_.empty()){
        emit emptyDeckClicked();
        return;

    }

    // Otetaan osoittimen päähän pakan päällimmäinen kortti ja poistetaan se pakasta.
    Card* card = cards_.back();
    cards_.pop_back();

    // Ohjelma ei saa kaatua, jos korttia ei olekaan.
    if (!card){
        return;
    }

    // Ilmoitetaan, että pakasta otettiin kortti.
    emit cardPicked(card);

    // Hyväksytään klikkaus, koska se käsitellään aina tässä metodissa.
    event->accept();
}
