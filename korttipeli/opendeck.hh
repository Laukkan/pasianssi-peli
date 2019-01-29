#ifndef OPENDECK_HH
#define OPENDECK_HH
#include <QFrame>

QT_BEGIN_NAMESPACE
class QDragEnterEvent;
class QDropEvent;
QT_END_NAMESPACE

#include <QStackedLayout>

#include "card.hh"
class OpenDeck : public QFrame
{
    Q_OBJECT
public:
    OpenDeck(QWidget* parent = 0);
    /**
     * @brief emptyOut tyhjentää pakan eli postaa kaikki kortit.
     */
    void emptyOut();
signals:
    // Signaali, jolla avoin pakka palauttaa pakan varsinaiseen pakkaan.
    void returnCards(std::vector<Card*> deck);
public slots:
    /**
     * @brief addCard lisää kortin avoimeen pakkaan.
     * @param card, Card*, osoitin lisättävään korttiin.
     *
     * Kutsutaan kun varsinaisen pakan korttia klikataan.
     */
    void addCard(Card* card);
    /**
     * @brief getCards laittaa kaikki avoimen pakan korttien osoittimet
     * vektoriin ja palauttaa sen varsinaiselle pakalle returnCards signaalin
     * avulla.
     */
    void getCards();
protected:
    void mousePressEvent(QMouseEvent *event);
private:
    QStackedLayout* layout_;  // Sisältää ne kortti-widgetit, jotka avopakassa on.
};

#endif // OPENDECK_HH
