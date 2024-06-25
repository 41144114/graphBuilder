#include "palettemngr.h"

#include <QPalette>

PaletteMngr::PaletteMngr(QPalette defaultPalette)
{
    _pDefaultPalette = new QPalette(defaultPalette);
    _pDarkPalette = new QPalette(defaultPalette);
    _pDefaultConsolePalette = new QPalette(defaultPalette);
    _pDarkConsolePalette = new QPalette(defaultPalette);
    _pDarkNaviWidgetPalette = new QPalette(defaultPalette);
    _pTrueDarkGray = new QColor();
    _pLinkButtonColor = new QColor();

    _pTrueDarkGray->setRed(30);
    _pTrueDarkGray->setBlue(30);
    _pTrueDarkGray->setGreen(30);

    _pLinkButtonColor->setRed(37); //Я не знаю почему, но там выставляется именно такой цвет.
    _pLinkButtonColor->setBlue(37); //Идея в том, чтобы скрыть кнопку в которой ссылка
    _pLinkButtonColor->setGreen(37);

    _pDarkPalette->setColor(QPalette::Window, Qt::black);

    _pDarkPalette->setColor(QPalette::Active, QPalette::WindowText, Qt::white);
    _pDarkPalette->setColor(QPalette::Disabled, QPalette::WindowText, Qt::lightGray);
    _pDarkPalette->setColor(QPalette::Inactive, QPalette::WindowText, Qt::darkGray);

    _pDarkPalette->setColor(QPalette::Active, QPalette::ButtonText, Qt::white);
    _pDarkPalette->setColor(QPalette::Disabled, QPalette::ButtonText, Qt::lightGray);
    _pDarkPalette->setColor(QPalette::Inactive, QPalette::ButtonText, Qt::darkGray);

    _pDarkPalette->setColor(QPalette::Active, QPalette::Text, Qt::white);
    _pDarkPalette->setColor(QPalette::Disabled, QPalette::Text, Qt::lightGray);
    _pDarkPalette->setColor(QPalette::Inactive, QPalette::Text, Qt::darkGray);

    _pDarkPalette->setColor(QPalette::Active, QPalette::Highlight, Qt::yellow);
    _pDarkPalette->setColor(QPalette::Disabled, QPalette::Highlight, Qt::yellow);
    _pDarkPalette->setColor(QPalette::Inactive, QPalette::Highlight, Qt::yellow);

    _pDarkPalette->setColor(QPalette::Active, QPalette::HighlightedText, Qt::black);
    _pDarkPalette->setColor(QPalette::Disabled, QPalette::HighlightedText, Qt::black);
    _pDarkPalette->setColor(QPalette::Inactive, QPalette::HighlightedText, Qt::black);

    _pDarkPalette->setColor(QPalette::Disabled, QPalette::Base, Qt::darkGray);
    _pDarkPalette->setColor(QPalette::Active, QPalette::Base, *_pTrueDarkGray);
    _pDarkPalette->setColor(QPalette::Inactive, QPalette::Base, Qt::gray);

    _pDarkPalette->setColor(QPalette::Disabled, QPalette::Button, Qt::darkGray);
    _pDarkPalette->setColor(QPalette::Active, QPalette::Button, *_pTrueDarkGray);
    _pDarkPalette->setColor(QPalette::Inactive, QPalette::Button, Qt::gray);

    *_pDarkNaviWidgetPalette = *_pDarkPalette;
    _pDarkNaviWidgetPalette->setColor(QPalette::Active, QPalette::Text, Qt::black);
    _pDarkNaviWidgetPalette->setColor(QPalette::Disabled, QPalette::Text, Qt::black);
    _pDarkNaviWidgetPalette->setColor(QPalette::Inactive, QPalette::Text, Qt::black);

    _pDefaultConsolePalette->setColor(QPalette::Base, Qt::black);
    _pDefaultConsolePalette->setColor(QPalette::Text, Qt::white);

    _pDarkConsolePalette->setColor(QPalette::Base, *_pTrueDarkGray);
    _pDarkConsolePalette->setColor(QPalette::Text, Qt::white);
}

QPalette PaletteMngr::getDark() { return *_pDarkPalette; }

QPalette PaletteMngr::getDefault() { return *_pDefaultPalette; }

QPalette PaletteMngr::getConsoleDark() { return *_pDarkConsolePalette; }

QPalette PaletteMngr::getConsoleDefault() { return *_pDefaultConsolePalette; }

QPalette PaletteMngr::getNaviWidgetDark() { return *_pDarkNaviWidgetPalette; }

QString PaletteMngr::getDarkLinkStyleSheet()
{
    return QString("QToolButton {color: yellow;background: %1;} QToolButton:hover{ background: %1; border : 0px} "
                   "QToolButton:window{ background: lightGray;}")
        .arg(_pLinkButtonColor->name(QColor::HexRgb));
}

QString PaletteMngr::getDefaultLinkStyleSheet() { return "color: blue"; }
