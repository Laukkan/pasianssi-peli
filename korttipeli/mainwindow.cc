#include <QFrame>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>

#include "mainwindow.hh"
#include "cardslot.hh"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    setupLayout();
    connect(deck_, &Deck::cardPicked, pickedCards_, &OpenDeck::addCard);
    // Tyhjää pakkaa klikatessa avoin pakka palauttaa korttinsa..
    connect(deck_, &Deck::emptyDeckClicked, pickedCards_, &OpenDeck::getCards);
    // Varsinaiseen pakkaan jossa ne käännetään ja asetetaan näkyväksi.
    connect(pickedCards_, &OpenDeck::returnCards, deck_, &Deck::replaceDeck);
    // Ylärivin korttipaikat lähettävät kingAdded signaalin kun niihin lisätään
    // kuningas, jolloin pääikkuna tarkistaa, onko peli voitettu.
    for(CardSlot* cardSlot : topSlotsVector_){
        connect(cardSlot, &CardSlot::kingAdded, this, &MainWindow::checkForVictory);
    }
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupLayout()
{
    // Pääikkunan isoimpana rakenteena on frame, joka sisältää...
    QFrame* frame = new QFrame;
    QVBoxLayout* frameLayout = new QVBoxLayout(frame);

    // ... alarivin ja ylärivin.
    QHBoxLayout* bottomRowLayout = new QHBoxLayout();
    QHBoxLayout* topRowLayout = new QHBoxLayout();
    frameLayout->addLayout(topRowLayout);
    frameLayout->addLayout(bottomRowLayout);

    // Luodaan pakkaoliot.
    deck_ = new Deck(this);
    pickedCards_ = new OpenDeck(this);

    // Lisätään yläpalkkiin slotit, joihin kortit tulee pasianssissa saada ja
    // tallennetaan ne topSlotsVector_:iin
    for(int i=0; i<SUIT_COUNT;i++){
        topSlotsVector_.push_back(new CardSlot(GameRules::suitCheckVector[i], this,0, i));
        topRowLayout->addWidget(topSlotsVector_[i]);
    }
    // Lisätään yläriville suljettu ja avoin pakka...
    topRowLayout->addWidget(deck_);
    topRowLayout->addWidget(pickedCards_);

    // ... ja alariville 7 card slottia, joihin jaetaan aloitus kortit.
    // Ensimmäiseen 1, seuraavaan 2 jne.
    for(int i = 0; i < 7; i++) {
        CardSlot* newCardSlot = new CardSlot(&GameRules::checkIfLegalPlay, this);
        // Alarivin korttipaikat tallennetaan bottomSlotsVector_:iin.
        bottomSlotsVector_.push_back(newCardSlot);
        bottomRowLayout->addWidget(newCardSlot);
        setCentralWidget(frame);
        setCentralWidget(frame);
    }
    dealCards();
    // Lisätään yläreunaan reset nappi, jonka painaminen resetoi pelin pääikkunan
    // reset metodilla
    QPushButton* resetButton = new QPushButton("Reset", this);
    connect(resetButton, QPushButton::clicked, this, &MainWindow::reset);
}

void MainWindow::checkForVictory()
{
    bool victory = true;
    // Tarkistetaan onko jonkin ylärivin korttipaikan päälimmäinen kortti jokin
    // muu kuin kuningas.
    for(CardSlot* cardSlot: topSlotsVector_){
        if(!(cardSlot->checkIfTopKing())){
            victory = false;
        }
    }
    // Jos ei, peli on voitettu.
    if(victory){
        QMessageBox victoryBox;
        victoryBox.setText("VICTORY");
        victoryBox.exec();
    }
}

void MainWindow::reset()
{
    // Kutsuu korttipaikkojen ja avoimen pakan tyhjennys metodia.
    for(CardSlot* cardSlot: topSlotsVector_){
        cardSlot->emptyOut();
    }
    for(CardSlot* cardSlot: bottomSlotsVector_){
        cardSlot->emptyOut();
    }
    pickedCards_->emptyOut();
    // Kutsuu pakan resetointi metodia.
    deck_->resetDeck();
    // Jaetaan uudet kortit.
    dealCards();
}

void MainWindow::dealCards() {
    int cardsToDeal = 1;
    // Jaetaan jokaiseen alarivin korttipaikkaan kortit, ensimmäiseen yksi,
    // toiseen kaksi jne.
    for(CardSlot* cardSlot: bottomSlotsVector_) {
        for(int i=0; i < cardsToDeal; i++){
            Card* nextCard = deck_->pickCard();
            cardSlot->addCard(nextCard);
            // Käännetään viimeinen kortti.
            if(cardsToDeal == i+1){
                nextCard->turn();
            }
        }
        cardsToDeal++;
    }
}


