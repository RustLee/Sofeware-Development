#include "get_tool.h"
#include "ui_get_tool.h"
#include <QFile>
#include <QDebug>
#include <QTextStream>

Get_tool::Get_tool(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Get_tool)
{
    ui->setupUi(this);
    QString path =  qApp->applicationDirPath() + "/tool";
    QString picPath = path + "/tool.jpg";
    QPixmap image(picPath);
    image.load(picPath);
    image = image.scaled(ui->label->size(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    ui->label->clear();
    ui->label->setPixmap(image);
    ui->label->show();
    QString textPath = qApp->applicationDirPath() + "/tool/tool.txt";
    qDebug()<<textPath;
    QFile file(textPath);
    QStringList lines;
    if(file.open(QFile::ReadOnly))
    {
        QTextStream txtStream(&file);
        QString line;
        while (!txtStream.atEnd()) {
            line = txtStream.readLine();
            lines += line;
        }
        file.close();
    }
    int i = 0;
    while (i<lines.count()) {
        ui->listWidget->addItem(lines.at(i));
        i++;

    }

}

Get_tool::~Get_tool()
{
    delete ui;
}
