#include <DApplication>
#include <DMainWindow>
#include <DWidgetUtil>
#include <DApplicationSettings>
#include <DTitlebar>
#include <DProgressBar>
#include <DFontSizeManager>
#include <DAboutDialog>

#include <QPropertyAnimation>
#include <QDate>
#include <QLayout>
DWIDGET_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    DApplication a(argc, argv);
    DAboutDialog dialog;

    a.setAttribute(Qt::AA_UseHighDpiPixmaps);
    a.setApplicationName("dtk-application");
    a.setProductName("dtk-application");
    a.setAboutDialog(&dialog);

    // Title
    dialog.setWindowTitle("dtk-application");
    // Descrition
    dialog.setProductName("<span>Description</span>");
    // Icons
    dialog.setProductIcon(QIcon(":/images/logo.svg"));
    // Organization logo
    dialog.setCompanyLogo(QPixmap(":/images/deepines.png"));
    // About
    dialog.setDescription(
        "<span style=' font-size:8pt; font-weight:600;'>Deepin en Español </span>"
        "<a href='https://deepinenespañol.org'>https://deepinenespañol.org</a><br/>"
        "<span style=' font-size:8pt; font-weight:600;'>Deepin Latin Code - developers</span>");
    dialog.setVersion(DApplication::buildVersion("Version 0.1"));
    dialog.setWebsiteName("deepinenespañol.org");
    dialog.setWebsiteLink("https://deepinenespañol.org");


    a.loadTranslator();
    a.setApplicationDisplayName(QCoreApplication::translate("Main", "DTK Application"));

    // Saves the program window configuration
    DApplicationSettings as;
    Q_UNUSED(as)

    DMainWindow w;
    w.titlebar()->setIcon(QIcon(":/images/logo.svg"));
    w.titlebar()->setTitle("Hello dtk");
    // Sets a size for the window
    w.setMinimumSize(QSize(600, 200));

    QWidget *cw = new QWidget(&w);
    QVBoxLayout *layout = new QVBoxLayout(cw);
    QDate today = QDate::currentDate();
    DProgressBar *yearProgressBar = new DProgressBar();
    yearProgressBar->setMaximum(today.daysInYear());
    // Set font size
    DFontSizeManager::instance()->bind(yearProgressBar, DFontSizeManager::T1);

    yearProgressBar->setAlignment(Qt::AlignCenter);
    QObject::connect(yearProgressBar, &DProgressBar::valueChanged, yearProgressBar, [yearProgressBar](int value){
        yearProgressBar->setFormat(QString("Su %1 Progreso en el uso: %2%").arg(QDate::currentDate().year())
                                   .arg(value * 100 / yearProgressBar->maximum()));
    });

    layout->addWidget(yearProgressBar);
    w.setCentralWidget(cw);
    w.show();

    auto animation = new QPropertyAnimation(yearProgressBar, "value");
    animation->setDuration(5000);
    animation->setStartValue(0);
    animation->setEndValue(today.dayOfYear());
    animation->start();

    Dtk::Widget::moveToCenter(&w);

    return a.exec();
}
