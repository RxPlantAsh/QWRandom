#include "dialog.h"
#include "ui_dialog.h"

#include <QDebug>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    srand(time(NULL));
    QRegularExpression regExp("[1-9][0-9]+");
    ui->lineEditDown->setValidator(new QRegularExpressionValidator(regExp, this));
    ui->lineEditUp->setValidator(new QRegularExpressionValidator(regExp, this));
    ui->lineEditRange->setValidator(new QRegularExpressionValidator(regExp, this));

    connect(ui->closeBtn, SIGNAL(clicked()), this, SLOT(close()));
}

Dialog::~Dialog()
{
    delete ui;
}

int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

void Dialog::on_runBtn_clicked()
{
    int down = ui->lineEditDown->text().toInt();
    int up = ui->lineEditUp->text().toInt();
    int range = ui->lineEditRange->text().toInt();

    if (ui->checkRepe->isChecked() && range > up - down) {
        ui->NumberList->setText((down == up ? QString::number(down) : QString::number(down).append("~").append(QString::number(up))).append("(好好填条件去😡"));
        return;
    }

    int tmp;
    QString tmpStr;

//    int * lst = new int [up - down];
//    bool * cklst = new bool [up - down];
//    memset(cklst, false, range);

    int lst[1024];
    bool cklst[1024] = {false};

    for (int i = 0; i < range; i++) {
        tmp = rand() % (up - down) + down;

        qDebug() << "for " << tmp;

        if (ui->checkRepe->isChecked()) {
            while (cklst[tmp] == true) {
                tmp = rand() % (up - down + 1) + down;
                qDebug() << "while " << tmp;
            }
            cklst[tmp] = true;
        }

        lst[i] = tmp;
    }

    if (ui->checkSort->isChecked())
        qsort(lst, range, sizeof(int), cmpfunc);

    for (int i = 0; i < range; i++)
        tmpStr.append(QString::number(lst[i])).append(" ");

    ui->NumberList->setText(tmpStr);

//    delete[] lst;
//    delete[] cklst;
}

