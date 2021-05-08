#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMimeData>
#include <QDebug>
#include <QSettings>
#include <palettemngr.h>

const QString kPathKey = "lastFilePath";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Построитель графиков");
    _pFile = new QFile();
    connect(&_graphView, &GraphView::closed, this, &MainWindow::onGraphViewClosed);
//    PaletteMngr mngr(palette());
//    this->setPalette(mngr.getDark());
}

MainWindow::~MainWindow()
{
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
//=============================================================


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

void MainWindow::onGraphViewClosed()
{
    ui->pushButton_2->setText("Построить график");
    ui->comboBox->setEnabled(true);
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
    for(int j = 0; j < ui->comboBox->count(); ++j)
    {
        QVector<double> *tempVect = new QVector<double>;
        _dataList.append(*tempVect);
    }
    while(_pFile->atEnd() == false)
    {
        counterVector.append(i);
        ++i;

        temp = _pFile->readLine();
        splitLine = temp.split(';');
        for(int j = 1; j <= splitLine.count() && j <= nCols; ++j)
        {
            _dataList[j].append(splitLine.at(j-1).toDouble());
        }
    }
    _dataList[0].append(counterVector);
    _pFile->close();
}

void MainWindow::clearData()
{
    for(int i = 0; i < _dataList.count(); ++i)
        _dataList[i].clear();
}

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

