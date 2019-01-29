#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include "deck.hh"
#include "opendeck.hh"
#include "cardslot.hh"
#include "gamerules.hh"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    void setupLayout();
    /**
     * @brief checkForVictory tarkistaa onko kaikissa ylärivin korttipaikoissa
     * päälimmäisenä kuningas. Jos on, peli on voitettu.
     */
    void checkForVictory();
    /**
     * @brief reset resetoi pelin, eli kutsuu kaikkien korttipaikkojen sekä
     * avoimen pakasta kaikki kortit, luo uuden pakan.
     */
    void reset();
    /**
     * @brief dealCards, jakaa aloitus kortit alarivin korripaikkoihin
     */
    void dealCards();

    // Talletetaan attribuuteiksi ne widgetit, joita saattaa tarvita käsitellä pelin aikana.
    // Ohjelmakoodipohjassa näitä ei käytetä mihinkään.
    Deck* deck_;
    OpenDeck* pickedCards_;

    // Vektorit, johon ala- ja ylärivin korttipaikkojen osoittimet tallennetaan
    std::vector<CardSlot*> topSlotsVector_;
    std::vector<CardSlot*> bottomSlotsVector_;
};

#endif // MAINWINDOW_HH
