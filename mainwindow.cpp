#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMimeData>
#include <QDebug>
#include <QSettings>
#include "palettemngr.h"
#include <QMenu>
#include <QMessageBox>
#include "aboutprogramwindow.h"

const QString kPathKey = "lastFilePath";
const QString kThemeKey = "isDarkTheme";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Построитель графиков");
    _pFile = new QFile();
    connect(&_graphView, &GraphView::closed, this, &MainWindow::onGraphViewClosed);
    _graphView.setEnabledContext(true);
    _pPaletteMngr = new PaletteMngr(palette());


    ui->pushButton_2->setEnabled(false);
    setupGlobalMenu();

    _pAboutProgram = new AboutProgramWindow();
    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}





//============ Window slots ===================================
void MainWindow::on_pushButton_clicked()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    QString dir;
    if(settings.contains(kPathKey))
        dir = settings.value(kPathKey).toString();
    else
        dir = "/";

    QString fName = QFileDialog::getOpenFileName(this, "Выбор файла с данными", dir);
    if(fName.isEmpty())
        return;

    QFileInfo info(fName);
    settings.setValue(kPathKey, info.absoluteFilePath());

    ui->lineEdit->setText(fName);
    readFile(fName);
}

void MainWindow::on_pushButton_2_clicked()
{
    if(ui->lineEdit->text().isEmpty())
        return ;
    if(ui->comboBox->count() == 0)
        return;
    if(ui->comboBox_2->count() == 0)
        return;

    if(ui->pushButton_2->text() == "Построить график")
    {
        crutchWithHead();
        _graphView.buildGraph(&_dataList[ui->comboBox->currentIndex()], &_dataList[ui->comboBox_2->currentIndex() + 1],
                ui->lineEdit_2->text(), ui->lineEdit_3->text(),
                ui->comboColor->currentIndex(), ui->comboLineType->currentIndex(), ui->doubleSpinBox->value(),
                ui->lineEditHeader->text(), ui->lineEditPIctureLabel->text());
        ui->pushButton_2->setText("Добавить график");
        ui->comboBox->setEnabled(false);
    }
    else
    {
        crutchWithHead();
        _graphView.addGraph(&_dataList[ui->comboBox->currentIndex()], &_dataList[ui->comboBox_2->currentIndex() + 1],
                 ui->comboColor->currentIndex(), ui->comboLineType->currentIndex(), ui->doubleSpinBox->value());
    }
}

void MainWindow::on_checkBox_clicked()
{
    if(_head.isEmpty() == false)
        setComboBoxContent();
}

void MainWindow::onGraphViewClosed()
{
    ui->pushButton_2->setText("Построить график");
    ui->comboBox->setEnabled(true);
}
//=============================================================
//=
//=
//=
//=
//=========== Reading file and fill data vector =================
void MainWindow::setComboBoxContent()
{
    QStringList head = _head.split(";");
    if(head.last().isEmpty())   head.takeLast();

    ui->comboBox->clear();
    ui->comboBox_2->clear();
    ui->comboBox->addItem("Задать автоматически");
    if(ui->checkBox->isChecked())
    {
        ui->comboBox->addItems(head);
        ui->comboBox_2->addItems(head);
    }
    else
    {
        for(int i = 1; i <= head.count(); ++i)
        {
            ui->comboBox->addItem("Столбец №" + QString::number(i));
            ui->comboBox_2->addItem("Столбец №" + QString::number(i));
        }
    }
}

void MainWindow::crutchWithHead()
{
    if(ui->checkBox->isChecked() && _isHeadAdded)
    {
        for(int i = 1; i < _dataList.count(); ++i)
            _dataList[i].takeFirst();
        _dataList[0].takeLast();
        _isHeadAdded = false;
    }
    else if(ui->checkBox->isChecked() == false && _isHeadAdded == false)
    {

        QStringList temp = _head.split(";");
        QString num;

        for(int i = 1; i < _dataList.count(); ++i)
        {
            num = temp.at(i - 1);
            _dataList[i].prepend(num.toDouble());
        }
        _dataList[0].append(_dataList[0].last() + 1);
        _isHeadAdded = true;
    }
}

void MainWindow::readFile(QString fName)
{
    _pFile->setFileName(fName);
    _pFile->open(QIODevice::ReadOnly);
    _head = _pFile->readLine();
    _head = _head.simplified();
    _isHeadAdded = false;
    clearData();

    setComboBoxContent();

    int i = 0;
    QString temp;
    QStringList splitLine;
    QVector<double> counterVector;
    int nCols = ui->comboBox_2->count();
    _dataList.resize(nCols + 1);

    while(_pFile->atEnd() == false)
    {
        counterVector.append(i);
        ++i;

        temp = _pFile->readLine();
        temp = temp.simplified();
        splitLine = temp.split(';');
        for(int j = 1; j <= splitLine.count() && j <= nCols; ++j)
            _dataList[j].append(splitLine.at(j-1).toDouble());
    }
    _dataList[0].append(counterVector);
    _pFile->close();
    ui->pushButton_2->setEnabled(true);
}

void MainWindow::clearData()
{
    for(int i = 0; i < _dataList.count(); ++i)
        _dataList[i].clear();
}
//==============================================================
//=
//=
//=
//=
//==================== Events ===================================================================
void MainWindow::dropEvent(QDropEvent *event)
{
   const QMimeData* data = event->mimeData();
   if(data->hasUrls())
   {
        readFile(data->urls().at(0).toLocalFile());
        ui->lineEdit->setText(data->urls().at(0).toLocalFile());
   }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
        e->acceptProposedAction();
}
//===============================================================================================
//=
//=
//=
//=
//================ Context menu =======================================================================================
void MainWindow::setupGlobalMenu()
{
    connect(this, &MainWindow::customContextMenuRequested,       this, &MainWindow::onShowGlobalMenu);

    _pGlobalMenu = new QMenu(this);
    _pAboutQtAction = new QAction("О Qt", this);
    _pAboutProgrammAction = new QAction("О программе", this);
    _pThemeAction  = new QAction("Тёмная тема", this);

    _pThemeAction->setCheckable(true);
    _pThemeAction->setChecked(false);
    connect(_pAboutQtAction,    &QAction::triggered,        this, &MainWindow::onAboutQt);
    connect(_pAboutProgrammAction,       &QAction::triggered,        this, &MainWindow::onAboutProgram);
    connect(_pThemeAction,     &QAction::triggered,        this, &MainWindow::onTheme);


    _pGlobalMenu->addAction(_pThemeAction);
    _pGlobalMenu->addAction(_pAboutProgrammAction);
    _pGlobalMenu->addAction(_pAboutQtAction);
}

void MainWindow::onShowGlobalMenu(QPoint point)
{
    _pGlobalMenu->popup(this->mapToGlobal(point));
}

void MainWindow::onTheme()
{
    if(_isDarkTheme)
    {
        _isDarkTheme = false;
        setPalette(_pPaletteMngr->getDefault());
    }
    else
    {
        _isDarkTheme = true;
        setPalette(_pPaletteMngr->getDark());
    }
}

void MainWindow::onAboutQt()
{
    QMessageBox::aboutQt(this, "О Qt");
}

void MainWindow::onAboutProgram()
{
    _pAboutProgram->show();
}


//========================= Registry ==================================================================================
void MainWindow::loadSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    if(settings.contains(kThemeKey))
    {
        bool isDark = settings.value(kThemeKey).toBool();
        if(isDark)
        {
            _isDarkTheme = false;
            onTheme();
        }
        else
        {
            _isDarkTheme = true;
            onTheme();
        }
        _pThemeAction->setChecked(!_isDarkTheme);
    }
    else
        _isDarkTheme = false;
}

void MainWindow::saveSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue(kThemeKey, palette() == _pPaletteMngr->getDark());
}
