#include "MaFenetre.h"
#include "charger_csv.h"

#include <vector>

typedef std::vector <std::string> CVString;

bool checkTab(CVString tab, std::string val) {
    for (unsigned i = 0; i < tab.size(); i++) {
        if(tab[i] == val) {
            return true;
        }
    }
    return false;
}


MaFenetre::MaFenetre(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(800,600);
    m_bou = new QPushButton("Quitter", this);
    m_bou->setGeometry(600,400,80,40);

    m_bouPred = new QPushButton("Prédire", this);
    m_bouPred->setGeometry(100,400,80,40);

    m_lab = new QLabel("Fièvre", this);
    m_lab->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_lab->move(200, 125);

    read_csv (m_mat, m_vet, "data.csv");

    m_com = new QComboBox(this);
    m_com->setGeometry(300,150,100,30);

    m_com = new QComboBox(this);
    m_com->setGeometry(200,150,100,30);

    CVString tab;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][0];
        if(! checkTab(tab,s)) {
            tab.push_back(s);
            QString qs = QString::fromUtf8(s.c_str());
            m_com->addItem(qs);
        }
    }

    m_labe = new QLabel("Douleur", this);
    m_labe->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_labe->move(300, 125);

    m_comb = new QComboBox(this);
    m_comb->setGeometry(300,150,100,30);

    CVString tabl;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][1];
        if(! checkTab(tabl,s)) {
            tabl.push_back(s);
            QString qs = QString::fromUtf8(s.c_str());
            m_comb->addItem(qs);
        }
    }

    m_label = new QLabel("Toux", this);
    m_label->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_label->move(400, 125);

    m_combo = new QComboBox(this);
    m_combo->setGeometry(400,150,100,30);

    CVString table;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][2];
        if(! checkTab(table,s)) {
            table.push_back(s);
            QString qs = QString::fromUtf8(s.c_str());
            m_combo->addItem(qs);
        }
    }

    m_tra = new QLabel(this);
    m_tra->setFont(QFont("Arial", 12, QFont::Bold, true));
    m_tra->move(320, 300);

    connect(m_com, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));
    connect(m_comb, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));
    connect(m_combo, SIGNAL(currentIndexChanged(const QString &)),
            this, SLOT(setCouleur()));

    connect(m_bou, SIGNAL(clicked()),
            this, SLOT(setQuitter()));

    connect(m_bouPred, SIGNAL(clicked()),
            this, SLOT(setPrediction()));

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

QString MaFenetre::prediction(std::string str) {
    QString qs = QString::fromUtf8(str.c_str());
    return qs;
}

void MaFenetre::setPrediction()
{
    read_csv (m_mat, m_vet, "data.csv");
    CVString tab;
    std::string s;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        std::string s = m_mat[i][3];
        if(! checkTab(tab,s)) {
            tab.push_back(s);
        }
    }
    double score = 0;
    std::string maladie;
    QString bout1 = m_com->currentText();
    QString bout2 = m_comb->currentText();
    QString bout3 = m_combo->currentText();
    std::string sym1 = bout1.toStdString();
    std::string sym2 = bout2.toStdString();
    std::string sym3 = bout3.toStdString();
    for(unsigned i = 0; i < tab.size(); i++) {
        double score2 = calculScore(tab[i],sym1,sym2,sym3);
        if(score < score2) {
            maladie = tab[i];
            score = score2;
        }
    }
    QString qs = QString::fromUtf8(maladie.c_str());
    m_tra->setText(qs);
}

double MaFenetre::calculScore(std::string maladie, std::string sym1, std::string sym2, std::string sym3) {
    double score = 0;
    double freq = calculFreq(maladie);
    double conf1 = calculConf(sym1,maladie,0);
    double conf2 = calculConf(sym2,maladie,1);
    double conf3 = calculConf(sym3,maladie,2);
    score = freq * conf1 * conf2 * conf3;
    return score;
}

double MaFenetre::calculFreq(std::string str) {
    read_csv (m_mat, m_vet, "data.csv");
    double maladie = 0;
    for(unsigned i = 0; i < m_mat.size(); i++) {
        std::string mal = m_mat[i][3];
        if(mal == str) {
            maladie = maladie + 1;
        }
    }

    return maladie/m_mat.size();
}

double MaFenetre::calculConf(std::string str, std::string targ, unsigned col) {
    read_csv (m_mat, m_vet, "data.csv");
    double compteur = 0;
    double nbStr = 0;
    for (unsigned i = 0; i < m_mat.size(); i++) {
        if(m_mat[i][col] == str) {
            nbStr = nbStr + 1;
            if(m_mat[i][3] == targ) {
                compteur = compteur + 1;
            }
        }
    }
    return compteur/nbStr;
}
