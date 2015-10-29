#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
    void Hamming();
    QString getDevolver();
    int XOR(int a, int b);
    int OR(int a, int b);
    void cambio(int valor);
    QString codificar(QString varbinario);
    int distanciaMin(QString cad1, QString cad2);
    QString decodificar(QString cadena);
    QString toString();

private slots:
    void on_actionOpen_triggered();

    void on_actionEncode_triggered();

    void on_actionDecode_triggered();

    void on_actionAbout_triggered();

    void on_actionMin_Distance_triggered();

private:
    Ui::MainWindow *ui;
    QFile* file;

    QString res;
    QString devolver;

    int * actual;
    int ** matriz ;
    int bitErrorFlag;

    int * aux ;

};

#endif // MAINWINDOW_H
