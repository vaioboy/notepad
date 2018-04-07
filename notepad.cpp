#include "notepad.h"
#include "ui_notepad.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFont>
#include <QFontDialog>

notepad::notepad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::notepad)
{
    ui->setupUi(this);
}

notepad::~notepad()
{
    delete ui;
}

void notepad::on_actionNew_triggered()
{
    current_file.clear();
    ui->textEdit->setText(QString());
}

void notepad::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName();
    QFile file(file_name);
    current_file = file_name;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }
    setWindowTitle(file_name);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void notepad::on_actionSave_triggered()
{
    QString file_name;
    if(current_file.isEmpty())
    {
       file_name = QFileDialog::getSaveFileName();
       current_file = file_name;
    }
    else
    {
       file_name = current_file;
    }
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(file_name);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void notepad::on_actionSave_as_triggered()
{
    QString file_name = QFileDialog::getSaveFileName();
    QFile file(file_name);
    if(!file.open((QIODevice::WriteOnly | QIODevice::Text)))
    {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }
    setWindowTitle(file_name);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void notepad::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void notepad::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void notepad::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void notepad::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void notepad::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void notepad::on_actionPrint_triggered()
{
    QPrinter print_dev;
    QPrintDialog dialog(&print_dev, this);
    if(dialog.exec() == QDialog::Rejected)
    {
        return;
    }
    ui->textEdit->print(&print_dev);
}

void notepad::on_actionExit_triggered()
{
    QCoreApplication::quit();
}

void notepad::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "This is a simple text editor demo");
}

void notepad::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if(ok)
    {
        ui->textEdit->setFont(font);
    }
}
