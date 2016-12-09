#include "prerequisite.h"
#include "mainwindow.h"
#include "registerwindow.h"
#include "reguserdb.h"
#include "userds.h"
#include "sellerdb.h"
#include "buyerwindow.h"
#include "menuwindow.h"
#include "menudb.h"
#include "orderwindow.h"
#include "orderdb.h"
#include "smenudb.h"
#include "sellerwindow.h"
#include "sellerorderwindow.h"
#include "sorderdb.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSharedPointer<RegUserDB> rudb = QSharedPointer<RegUserDB>(new RegUserDB);
    QSharedPointer<UserDS> SessionUser = QSharedPointer<UserDS>(new UserDS);
    QSharedPointer<SellerDB> sdb = QSharedPointer<SellerDB>(new SellerDB);
    QSharedPointer<MenuDB> menudb = QSharedPointer<MenuDB>(new MenuDB);
    QSharedPointer<OrderDB> odb = QSharedPointer<OrderDB>(new OrderDB);
    QSharedPointer<SMenuDB> smdb = QSharedPointer<SMenuDB>(new SMenuDB);
    QSharedPointer<SOrderDB> sodb = QSharedPointer<SOrderDB>(new SOrderDB);

    MainWindow lw(rudb, SessionUser);
    RegisterWindow rw(rudb, SessionUser);
    BuyerWindow bw(sdb, SessionUser);
    MenuWindow mw(menudb, SessionUser);
    OrderWindow ow(odb, SessionUser);
    SellerWindow smw(smdb, SessionUser);
    SellerOrderWindow sow(sodb, SessionUser);

    QObject::connect(&lw, SIGNAL(showbw()), &bw, SLOT(showBuyerw()));
    QObject::connect(&lw, SIGNAL(showrw()), &rw, SLOT(show()));
    QObject::connect(&lw, SIGNAL(showsw()), &sow, SLOT(showSellerOrderw()));

    QObject::connect(&rw, SIGNAL(showlw()), &lw, SLOT(show()));
    QObject::connect(&rw, SIGNAL(showbw()), &bw, SLOT(showBuyerw()));

    QObject::connect(&bw, SIGNAL(showmw(int)), &mw, SLOT(showMenuw(int)));
    QObject::connect(&bw, SIGNAL(showow()), &ow, SLOT(showOrderw()));
    QObject::connect(&bw, SIGNAL(showlw()), &lw, SLOT(show()) );

    QObject::connect(&mw, SIGNAL(showbw()), &bw, SLOT(showBuyerw()));
    QObject::connect(&mw, SIGNAL(showow()), &ow, SLOT(showOrderw()));

    QObject::connect(&ow, SIGNAL(showbw()), &bw, SLOT(showBuyerw()));

    QObject::connect(&smw, SIGNAL(showsow()), &sow, SLOT(showSellerOrderw()));

    QObject::connect(&sow, SIGNAL(showlw()), &lw, SLOT(show()));
    QObject::connect(&sow, SIGNAL(showsmw()), &smw, SLOT(showSellerw()));
    lw.show();

    return a.exec();
}
