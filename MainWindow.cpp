#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setUpModel();

    setWindowTitle("Tomasz Piecha Logika rozmyta - Analiza Stanu Upojenia alkoholowego");

    QPixmap bkgnd("://images/beer.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    ui->resultLabel->setStyleSheet("QLabel { color : red; }");

    ui->resultImage->installEventFilter(this);
}

void MainWindow::setUpModel() {
    engine = new Engine();
    engine->setName("Drunk-level-gauge");

    ageInput = new InputVariable;
    ageInput->setName("Age");
    ageInput->setRange(13, 100);
    ageInput->addTerm(new ZShape("YOUNG", 13, 23));
    ageInput->addTerm(new Trapezoid("AVERAGE", 18, 22, 50, 70));
    ageInput->addTerm(new Trapezoid("OLD", 50, 85, 100, 100));
    engine->addInputVariable(ageInput);

    weightInput = new InputVariable;
    weightInput->setName("Weight");
    weightInput->setRange(15, 200);
    weightInput->addTerm(new Triangle("SUPERLIGHT", -10, 40));
    weightInput->addTerm(new Trapezoid("LIGHT", 25, 40, 55, 70));
    weightInput->addTerm(new Trapezoid("AVERAGE", 40, 60, 80, 130));
    weightInput->addTerm(new Trapezoid("FAT", 75, 201));
    engine->addInputVariable(weightInput);

    amountInput = new InputVariable;
    amountInput->setName("Amount");
    amountInput->setRange(1, 15);
    amountInput->addTerm(new Triangle("LITTLE", -3, 5));
    amountInput->addTerm(new Triangle("MEAN", 2, 7));
    amountInput->addTerm(new Trapezoid("ALOT", 4, 15, 15, 15));
    engine->addInputVariable(amountInput);


    drunkLevel = new OutputVariable;
    drunkLevel->setName("DrunkLevel");
    drunkLevel->setRange(0, 100);
    drunkLevel->setDefaultValue(fl::nan);
    drunkLevel->addTerm(new Triangle("SOBER", -20, 30));
    drunkLevel->addTerm(new Triangle("TIPSY", 15, 50));
    drunkLevel->addTerm(new Triangle("DRUNK", 35, 80));
    drunkLevel->addTerm(new Triangle("WASTED", 60, 140));
    drunkLevel->fuzzyOutput()->setAccumulation(new AlgebraicSum);
    drunkLevel->setDefuzzifier(new Centroid);

    engine->addOutputVariable(drunkLevel);

    ruleBlock = new RuleBlock;
    ruleBlock->setConjunction(new Minimum);
    ruleBlock->setActivation(new AlgebraicProduct);
    for(QString rule : rules) {
        ruleBlock->addRule(Rule::parse(rule.toStdString(), engine));
    }
    engine->addRuleBlock(ruleBlock);
}

void MainWindow::on_pushButton_clicked() {
    std::string status;
    if (!engine->isReady(&status)) {
        std::cout << status;
        throw Exception("Engine not ready. The following errors were encountered:\n" + status, FL_AT);
    }

    scalar age = ui->ageDoubleSpinBox->value();
    scalar weight = ui->weightDoubleSpinBox->value();
    scalar amount = ui->amountDoubleSpinBox->value();

    ageInput->setInputValue(age);
    weightInput->setInputValue(weight);
    amountInput->setInputValue(amount);

    engine->process();

    ui->resultLabel->setText(QString::number(drunkLevel->getOutputValue()));
    this->setResultImage(drunkLevel->getOutputValue());

    engine->restart();
}

void MainWindow::setResultImage(double result) {
    if(result <= 30) {
        image = QImage("://images/sober.png");
    } else if(result <= 40) {
        image = QImage("://images/tipsy.png");
    } else if(result <= 55) {
        image = QImage("://images/drunk.png");
    } else {
        image = QImage("://images/wasted.png");
    }
}

bool MainWindow::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->resultImage && event->type() == QEvent::Paint) {
        QPainter painter;
        painter.begin(ui->resultImage);
        painter.drawImage(ui->resultImage->rect(), image);
        painter.end();
        ui->resultImage->raise();
        qApp->processEvents();
        return false;
    }
    return false;
}

MainWindow::~MainWindow() {
    delete ui;
}


