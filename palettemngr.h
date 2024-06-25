#ifndef PALETTEMNGR_H
#define PALETTEMNGR_H

class QPalette;
class QString;
class QColor;

/**
 * Сюда просто вынесен весь функционал по заполнению палитр и некоторых styleSheets
 */

class PaletteMngr
{
public:
    PaletteMngr(QPalette defaultPalette);
    QPalette getDefault();
    QPalette getDark();
    QPalette getConsoleDefault();
    QPalette getConsoleDark();
    QPalette getNaviWidgetDark();
    QString getDefaultLinkStyleSheet();
    QString getDarkLinkStyleSheet();

private:
    QPalette* _pDefaultPalette;
    QPalette* _pDarkPalette;
    QPalette* _pDefaultConsolePalette;
    QPalette* _pDarkConsolePalette;
    QPalette* _pDarkNaviWidgetPalette;
    QColor* _pTrueDarkGray;
    QColor* _pLinkButtonColor;
};

#endif // PALETTEMNGR_H
