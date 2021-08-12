#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) //todo: program chrashes if no matches were found
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = findChild<QVBoxLayout*>("mainLayout");
    mainLayout->addWidget(new ChartsWidget(counter, this));

    inputWidget = findChild<QWidget*>("inputWidget");

    QLineEdit *phraseEdit = findChild<QLineEdit*>("phraseEdit");
    QTimeEdit *startTimeEdit = findChild<QTimeEdit*>("startTimeEdit");
    QTimeEdit *endTimeEdit = findChild<QTimeEdit*>("endTimeEdit");
    QCheckBox *caseSensitiveCheck = findChild<QCheckBox*>("caseSensitiveCheck");
    QCheckBox *onlyContainCheck = findChild<QCheckBox*>("onlyContainCheck");
    QPushButton *searchButton = findChild<QPushButton*>("searchButton");

    connect(phraseEdit, &QLineEdit::textChanged,
            &counter, &PhraseCounter::setPhrase);
    connect(startTimeEdit, &QTimeEdit::timeChanged,
            &counter, &PhraseCounter::setStartTime);
    connect(endTimeEdit, &QTimeEdit::timeChanged,
            &counter, &PhraseCounter::setEndTime);
    connect(caseSensitiveCheck, &QCheckBox::stateChanged,
            &counter, &PhraseCounter::setCaseSensitive);
    connect(onlyContainCheck, &QCheckBox::stateChanged,
            &counter, &PhraseCounter::setOnlyContain);
    connect(searchButton, &QPushButton::clicked,
            &counter, &PhraseCounter::search);

    // init values
    counter.setPhrase(phraseEdit->text());
    counter.setStartTime(startTimeEdit->time());
    counter.setEndTime(endTimeEdit->time());
    counter.setCaseSensitive(caseSensitiveCheck->isChecked());
    counter.setOnlyContain(onlyContainCheck->isChecked());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    const QString &fileName = QFileDialog::getOpenFileName(
                this, "Select chat file", "", "Chat (*.txt)");

    QFile chatFile{fileName};

    if (chatFile.exists() && chatFile.fileName().endsWith(".txt")) {
        inputWidget->setEnabled(true);

        counter.setChat(WhatsAppChat{chatFile});
    }
}
