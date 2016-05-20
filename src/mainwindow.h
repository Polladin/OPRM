#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include <string>

#include "hexstring.hpp"
#include "filestorage.hpp"

namespace Ui {
class MainWindow;
}

// Convert a wstring to a QString
QString ws2qs(const std::wstring& str);

// Convert a QString to a wstring
std::wstring qs2ws(const QString& str);

// separate file path adn file name
std::wstring get_file_path(const std::wstring& filePath);


/***************************************
 *      UI class
 ***************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_selectMaskBtn_clicked();

    void on_selectSrcBtn_clicked();

    void on_decryptBtn_clicked();

    void on_encryptBtn_clicked();

private:

    QString get_file_name_for_result();
    void log_hex_string(const HexString& hexStr);

    Ui::MainWindow *ui;


    FileMask        fileMask        {L""};
    FileToDecode    fileToDecode    {L""};
    FileResult      fileResult      {L""};
};

#endif // MAINWINDOW_H
