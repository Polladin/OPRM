#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QString>
#include <QFileDialog>

#include <string>
#include <locale>

#include "decoder.hpp"

extern Decoder decoder;


// Convert a wstring to a QString
QString ws2qs(const std::wstring& str)
{
    return (QString((const QChar*)str.c_str(), str.length()));
}

// Convert a QString to a wstring
std::wstring qs2ws(const QString& str)
{
    return (std::wstring((wchar_t*)str.unicode(), str.length()));
}

// separate file path adn file name
std::wstring get_file_path(const std::wstring& filePath)
{
    auto pathEnd = filePath.find_last_of(L"/\\");
    return filePath.substr(0, pathEnd+1);
}

/**********************************************
 *      Constructor for UI class
 **********************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


/**********************************************
 *      Destructor for UI class
 **********************************************/
MainWindow::~MainWindow()
{
    delete ui;
}


/**********************************************
 *      Select MASK file
 **********************************************/
void MainWindow::on_selectMaskBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    ui->logBrowser->append(QString("Open MASK file : ") + fileName);

    fileMask.set_file_name(qs2ws(fileName));
    ui->maskFileNameLabel->setText(fileName);
}


/**********************************************
 *      Select SOURCE file
 **********************************************/
void MainWindow::on_selectSrcBtn_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"));
    ui->logBrowser->append(QString("Open File to Decode : ") + fileName);

    fileToDecode.set_file_name(qs2ws(fileName));
    ui->sourceFileNameLabel->setText(fileName);
}


/**********************************************
 *      Read File Name from 'Text' on UI
 **********************************************/
QString MainWindow::get_file_name_for_result()
{
    // Get result file name
    QString fileName = ui->resultFileNameEditor->text();

    fileName = QString(ws2qs(get_file_path(fileToDecode.get_file_name()))) + fileName;

    // Set file name to Result File
    fileResult.set_file_name(qs2ws(fileName));

    return fileName;
}


/**********************************************
 *      Print Hext parsing in LOG
 **********************************************/
void MainWindow::log_hex_string(const HexString& hexStr)
{
    if (!hexStr.is_correct())
    {
        //Error
        ui->logBrowser->append(QString("ERROR! Hex String is not correct : ") + QString(hexStr.get_hex_string().c_str()));
    }
    else
    {
        ui->logBrowser->append(QString("Set offset : 0x") + QString(hexStr.get_hex_string().c_str())
                               + QString(" (") + QString::number(hexStr.get_number()) + QString(")"));
    }
}


/**********************************************
 *      Decrypt Button Click()
 **********************************************/
void MainWindow::on_decryptBtn_clicked()
{

    get_file_name_for_result();

    HexString hexStr(ui->hexOffsetText->text().toUtf8().constData());
    log_hex_string(hexStr);

    if (hexStr.is_correct())
    {
         decoder.decode(fileMask, fileToDecode, fileResult, hexStr.get_number());
         ui->logBrowser->append(QString("Decrypt result have been saved in file : ") + QString(ws2qs(fileResult.get_file_name())));
    }
}


/**********************************************
 *      Encrypt Button Click()
 **********************************************/
void MainWindow::on_encryptBtn_clicked()
{
    get_file_name_for_result();

    HexString hexStr(ui->hexOffsetText->text().toUtf8().constData());
    log_hex_string(hexStr);

    if (hexStr.is_correct())

    if (hexStr.is_correct())
    {
         decoder.encode(fileMask, fileToDecode, fileResult, hexStr.get_number());
         ui->logBrowser->append(QString("Encrypt result have been saved in file : ") + QString(ws2qs(fileResult.get_file_name())));
    }
}
