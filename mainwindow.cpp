#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->OpenButton, &QPushButton::clicked, this, &MainWindow::onOpenFileClicked);
    connect(ui->SearchButton, &QPushButton::clicked, this, &MainWindow::onSearchClicked);
    connect(ui->SaveButton, &QPushButton::clicked, this, &MainWindow::onFileSaveClicked);
    connect(ui->CloseButton, &QPushButton::clicked, this, &MainWindow::onFileCloseClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFileClicked() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Document"), QDir::homePath(), tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            ui->textEdit->setText(in.readAll());
            file.close();
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
        }
    }
}

void MainWindow::onSearchClicked() {
    QString searchWord = ui->lineEdit->text();
    QString documentContent = ui->textEdit->toPlainText();

    if (documentContent.contains(searchWord, Qt::CaseInsensitive)) {
        QMessageBox::information(this, tr("Result"), tr("Word found!"));
    } else {
        QMessageBox::information(this, tr("Result"), tr("Word not found."));
    }
}

void MainWindow::onFileSaveClicked() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Document"), QDir::homePath(), tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << ui->textEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
        }
    }
}

void MainWindow::onFileCloseClicked() {
    auto reply =QMessageBox::question(this, tr("Confirmation"), tr("Are you sure you wanna close the document?"), QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->textEdit->clear();
    }
}


