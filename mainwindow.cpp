#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QList>
#include <QChar>
#include <QString>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    file = new QFile();
    res ="";
    devolver = "";
    bitErrorFlag = 0;

    actual = new int[20];
    matriz = new int*[4];
    for (int i=0; i<4; i++)
        matriz[i] = new int[12];

    matriz[0][0] = 0,
            matriz[0][1]=0,
            matriz[0][2]= 0,
            matriz[0][3]=0,
            matriz[0][4]= 0,
            matriz[0][5]= 0,
            matriz[0][6]= 0,
            matriz[0][7]= 1,
            matriz[0][8]= 1,
            matriz[0][9]= 1,
            matriz[0][10]= 1,
            matriz[0][11]= 1;

    matriz[1][0] = 0,
            matriz[1][1]=0,
            matriz[1][2]= 0,
            matriz[1][3]=1,
            matriz[1][4]= 1,
            matriz[1][5]= 1,
            matriz[1][6]= 1,
            matriz[1][7]= 0,
            matriz[1][8]= 0,
            matriz[1][9]= 0,
            matriz[1][10]= 0,
            matriz[1][11]= 1;

    matriz[2][0] = 0,
            matriz[2][1]=1,
            matriz[2][2]= 1,
            matriz[2][3]=0,
            matriz[2][4]= 0,
            matriz[2][5]= 1,
            matriz[2][6]= 1,
            matriz[2][7]= 0,
            matriz[2][8]= 0,
            matriz[2][9]= 1,
            matriz[2][10]= 1,
            matriz[2][11]= 0;

    matriz[3][0] = 1,
            matriz[3][1]=0,
            matriz[3][2]= 1,
            matriz[3][3]=0,
            matriz[3][4]= 1,
            matriz[3][5]= 0,
            matriz[3][6]= 1,
            matriz[3][7]= 0,
            matriz[3][8]= 1,
            matriz[3][9]= 0,
            matriz[3][10]= 1,
            matriz[3][11]= 0;


    aux = new int[4];
    aux[0] = 8, aux[1] = 4, aux[2] = 2, aux[3] = 1;



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_triggered()
{
    ui->plainTextEdit->clear();
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File to Encode/Decode"),
                                                    "/home",
                                                    tr("Anyfile (*.*)"));
    file->setFileName(fileName);
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::information(this,"Error","Error open file <<"+fileName+">>",QMessageBox::Ok);
        return;
    }
    QString text = (QString)file->readAll();
    ui->plainTextEdit->insertPlainText(text);
    file->close();

}

//---------------------------------------------------------------


QString MainWindow::getDevolver() {
    return devolver;
}

int MainWindow::XOR(int a, int b) {  // La  computadora no reconoce 0  y 1 sino el código ASCII
    int c = 0;                     //de los mismos  por tanto se convierten a 0 y 1
    if (a == 48) {                       //según el código que se introduzca
        a = 0;
    } else if (a == 49) {
        a = 1;
    }
    if (b == 48) {
        b = 0;
    } else if (b == 49) {
        b = 1;
    }

    if (a != b) {
        c = 1;
    } else {
        c = 0;
    }
    return c;
}


int MainWindow::OR(int a, int b) {  //Este método si lo que encuentre devuelve un 1 entre dos
    //valores siempre  cuando no sea  0 y 0   sino devuelve 0 .
    int c = 0;
    if (a == 48) {
        a = 0;
    } else if (a == 49) {
        a = 1;
    }
    if (b == 48) {
        b = 0;
    } else if (b == 49) {
        b = 1;
    }
    if ((a == 0) && (b == 0)) {
        c = 0;
    } else {
        c = 1;
    }
    return c;
}


void MainWindow::cambio(int valor) { //Este método si lo que encuentre es un 1 en el valor
    // pasado por parámetro lo cambia por un 0  y si
    if (valor == 1) {           //  lo que encuentra es un 0 lo cambia por un 1
        valor = 0;
    } else {
        valor = 1;
    }
}


QString MainWindow::codificar(QString varbinario) { //Codificación de Hamming tiene por parámetro
    // un arreglo de tipo QString que tiene como
    // valores 0 y 1 y devuelve una cadena
    // de QString
    /*LLenar la matriz Hamming*/
    int M1 = (int)varbinario.at(0).toLatin1()-48,
        M2 = (int)varbinario.at(1).toLatin1()-48,
        M3 =(int) varbinario.at(2).toLatin1()-48,
        M4 =(int) varbinario.at(3).toLatin1()-48,
        M5 = (int)varbinario.at(4).toLatin1()-48,
        M6 = (int)varbinario.at(5).toLatin1()-48,
        M7 = (int)varbinario.at(6).toLatin1()-48,
        M8 = (int)varbinario.at(7).toLatin1()-48;

    /*Suma especial entre todos los numeros de la matriz mas
    las posiciones de los bit del codigo ... m1,m2,m3....*/

    int C4 = XOR(XOR(M7, M8), XOR(M5, M6));
    int C3 = XOR(XOR(M4, M8), XOR(M2, M3));
    int C22 = XOR(XOR(M1, M3), XOR(M4, M6));
    int C2 = XOR(C22, M7);
    int C11 = XOR(XOR(M1, M2), XOR(M4, M5));
    int C1 = XOR(C11, M7);

    /*Guardar los resultados de la suma XOR en un arreglo*/
    actual[0] = C1;
    actual[1] = C2;
    actual[2] = M1;
    actual[3] = C3;
    actual[4] = M2;
    actual[5] = M3;
    actual[6] = M4;
    actual[7] = C4;
    actual[8] = M5;
    actual[9] = M6;
    actual[10] = M7;
    actual[11] = M8;

    QString temp=toString();
    devolver="";

    return temp;

}

/*La distancia de Hamming para códigos binarios puede calcularse a través del peso
de Hamming (WH), que es la cantidad de 1(unos) resultante de la suma (xor)
entre dos palabras de código*/

/*La distancia mínima de un código lineal es igual al mínimo peso de sus
 palabras distintas de cero*/


int MainWindow::distanciaMin(QString cad1, QString cad2) {

    int cont = 0, len = (cad1.length() < cad2.length()) ? cad1.length() : cad2.length();

    for (int i=0; i<len; i++)
        cont += XOR(cad1.at(i).toLatin1()-48,cad2.at(i).toLatin1()-48);

    return cont;
}

/*decodicar Hamming tiene como parámetro una cadena de String que pasa por parámetro
y */

QString MainWindow::decodificar(QString cadena) {
    QString result = "";
    int bitError = 0;

    int cadCodif[12];
    int resultado[4];

    for (int i=0; i<12; i++)
        cadCodif[i] = cadena.at(i).toLatin1()-48;

    resultado[0]=XOR(XOR(XOR(cadCodif[8],cadCodif[9]),XOR(cadCodif[11],cadCodif[10])),cadCodif[7]);
    resultado[1]=XOR(XOR(XOR(cadCodif[4],cadCodif[5]),XOR(cadCodif[6],cadCodif[11])),cadCodif[3]);
    resultado[2]=XOR(XOR(XOR(cadCodif[5],cadCodif[6]),XOR(cadCodif[9],cadCodif[10])),XOR(cadCodif[1],cadCodif[2]));
    resultado[3]=XOR(XOR(XOR(cadCodif[0],cadCodif[2]),XOR(cadCodif[4],cadCodif[6])),XOR(cadCodif[8],cadCodif[10]));

    for (int k = 0; k < 4; k++) {
        if (resultado[k] == 1)
            bitError += aux[k];
    }

    if (bitError == 0) {
        result = QString(cadena.at(2))+QString(cadena.at(4))+QString(cadena.at(5))+QString(cadena.at(6))+QString(cadena.at(8))+QString(cadena.at(9))+QString(cadena.at(10))+QString(cadena.at(11));
    } else {
        bitErrorFlag = bitError;
        bitError-=1;

        for (int i=2; i<12; i++)
        {
            if (bitError == i){
                result += (cadCodif[i] == 1) ? tr("0") : tr("1");
            }
            else
                result += cadena.at(i);
            if (i == 2 || i == 6)
                i++;
        }

    }
    return result;
}

QString MainWindow::toString() {
    for (int i = 0; i < 12; i++) {
        if (actual[i] == 49) {
            actual[i] = 1;
        } else if (actual[i] == 48) {
            actual[i] = 0;
        }
        devolver += QString().setNum(actual[i]);
    }
    return devolver;
}




void MainWindow::on_actionEncode_triggered()
{
    QString text = ui->plainTextEdit->document()->toPlainText();
    QString aux = "",res="";

    int ind = 0;

    while (ind < text.length()){
        aux += text.at(ind);
        ind++;
        if (aux.length() == 8){
            res += codificar(aux);
            aux = "";
        }
        else if(ind == text.length()){
            while(aux.length() < 8) aux += tr("0");
            res += codificar(aux);
            aux = "";
        }
    }

    ui->plainTextEdit_2->clear();
    ui->plainTextEdit_2->setPlainText(res);

}

void MainWindow::on_actionDecode_triggered()
{
    QString text = ui->plainTextEdit_2->document()->toPlainText();
    QString aux = "",res="",msg="";
    int cantErrors = 0;
    QList<QString> listaErrors;
    int ind = 0,blocks=1;

    while (ind < text.length()){
        aux += text.at(ind);
        ind++;
        if (aux.length() == 12){
            res += decodificar(aux);
            if (bitErrorFlag != 0){
                cantErrors++;
                listaErrors.push_back(tr("(block ")+tr("").setNum(blocks)+tr(",")+tr(" bit ")+tr("").setNum(bitErrorFlag)+tr(")"));
            }
            blocks++;
            aux = "";
        }
        else if(ind == text.length()){
            while(aux.length() < 12) aux += tr("0");
            res += decodificar(aux);
            if (bitErrorFlag != 0){
                cantErrors++;
                listaErrors.push_back(tr("(block ")+tr("").setNum(blocks)+tr(",")+tr(" bit ")+tr("").setNum(bitErrorFlag)+tr(")"));

            }
            blocks++;
            aux = "";
        }
        bitErrorFlag = 0;
    }
    if (cantErrors > 0){
        msg+=tr("There are ")+tr("").setNum(cantErrors)+tr(" errors: ");
        for (int i=0; i<listaErrors.length(); i++)
            msg += listaErrors.at(i) + tr(",");
    }

    ui->plainTextEdit_3->setPlainText(msg);
    ui->plainTextEdit->clear();
    ui->plainTextEdit->setPlainText(res);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,tr("About HammingEncoder..."),tr("NOTE: This encoder does not open binary files,"
                                                                   "only open text files which have as contents 0 and 1.\n\nThanks, Randy team"),QMessageBox::Ok);
}

void MainWindow::on_actionMin_Distance_triggered()
{
    QString s1 = ui->plainTextEdit->toPlainText(), s2 = ui->plainTextEdit_2->toPlainText();
    QMessageBox::information(this,tr("Minimum Hamming Distance "),tr("The Minimum Hamming Distance is %1").arg(distanciaMin(s1,s2)),QMessageBox::Ok);
}
