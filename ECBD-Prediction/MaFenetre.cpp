#include "MaFenetre.h"
#include "charger_csv.h"

MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800,600);
    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(600,400,80,40);
    m_lab = new QLabel("Fièvre", this);
    m_lab->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_lab->move(200, 125);

    read_csv (m_mat, m_vet, "data.csv");

    m_com = new QComboBox(this);
    m_com->setGeometry(300,150,100,30);

    m_com = new QComboBox(this);
    m_com->setGeometry(200,150,100,30);

    for(unsigned i = 0; i < m_mat.size(); i++) {
        string s = m_mat[i][0];
        QString qs = QString::fromUtf8(s.c_str());
        m_com->addItem(qs);
    }

    m_labe = new QLabel("Douleur", this);
    m_labe->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_labe->move(300, 125);

    m_comb = new QComboBox(this);
    m_comb->setGeometry(300,150,100,30);

    for(unsigned i = 0; i < m_mat.size(); i++) {
        string s = m_mat[i][1];
        QString qs = QString::fromUtf8(s.c_str());
        m_comb->addItem(qs);
    }

    m_label = new QLabel("Toux", this);
    m_label->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_label->move(400, 125);

    m_combo = new QComboBox(this);
    m_combo->setGeometry(400,150,100,30);

    for(unsigned i = 0; i < m_mat.size(); i++) {
        string s = m_mat[i][2];
        QString qs = QString::fromUtf8(s.c_str());
        m_combo->addItem(qs);
    }

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(320, 300);

    connect(m_bou, SIGNAL(clicked()), this, SLOT(setQuitter()));
    connect(m_com, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));
    connect(m_comb, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));
    connect(m_combo, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));

}

void MaFenetre::setQuitter()
{
    exit(0);
}

void MaFenetre::setCouleur()
{
    couleur = m_com->currentText();
    m_tra->setText(">> " + couleur + " <<");
}
