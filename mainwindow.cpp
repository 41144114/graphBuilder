#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMimeData>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_file = new QFile();
    connect(&m_graphView, &GraphView::closed, this, &MainWindow::onGraphViewClosed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString fName = QFileDialog::getOpenFileName();
    if(fName.isEmpty())
        return;

    ui->lineEdit->setText(fName);
    readFile(fName);
}

void MainWindow::readFile(QString fName)
{
    m_file->setFileName(fName);
    m_file->open(QIODevice::ReadOnly);
    QString line = m_file->readLine();
    line = line.simplified();
    QStringList head = line.split(";");
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
        for(int i = 0; i < head.count(); ++i)
        {
            ui->comboBox->addItem("Столбец №" + QString::number(i));
            ui->comboBox_2->addItem("Столбец №" + QString::number(i));
        }
    }

    m_file->seek(0);
    int i = 0;
    QString temp;
    QStringList splitLine;
    QVector<double> counterVector;
    int nCols = ui->comboBox_2->count();
    for(int j = 0; j < ui->comboBox->count(); ++j)
    {
        QVector<double> *tempVect = new QVector<double>;
        m_dataList.append(*tempVect);
    }
    while(m_file->atEnd() == false)
    {
        counterVector.append(i);
        ++i;

        temp = m_file->readLine();
        splitLine = temp.split(';');
        for(int j = 1; j <= splitLine.count() && j <= nCols; ++j)
        {
            m_dataList[j].append(splitLine.at(j-1).toDouble());
        }
    }
    m_dataList[0].append(counterVector);
    m_file->close();
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
        m_graphView.buildGraph(&m_dataList[ui->comboBox->currentIndex()], &m_dataList[ui->comboBox_2->currentIndex() + 1],
                ui->lineEdit_2->text(), ui->lineEdit_3->text(), ui->checkBox->isChecked(),
                ui->comboColor->currentIndex(), ui->comboLineType->currentIndex());
        ui->pushButton_2->setText("Добавить график");
        ui->comboBox->setEnabled(false);
    }
    else
    {
        m_graphView.addGraph(&m_dataList[ui->comboBox->currentIndex()], &m_dataList[ui->comboBox_2->currentIndex() + 1],
                ui->checkBox->isChecked(), ui->comboColor->currentIndex(), ui->comboLineType->currentIndex());
    }
}

void MainWindow::onGraphViewClosed()
{
    ui->pushButton_2->setText("Построить график");
    ui->comboBox->setEnabled(true);
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
